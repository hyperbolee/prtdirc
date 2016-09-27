//  analysistools.C
//
//  Functions that are used in multiple
//  places in my analysis code to reduce redundancy
//
//  Author: Lee Allison, Apr.29.2016

// include ROOT headers
#include "TCanvas.h"
#include "TCollection.h"
#include "TError.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TList.h"
#include "TROOT.h"
#include "TSpectrum.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TTree.h"

#include "../prttools/prttools.C"

// don't include more than once
#ifndef analysistools
#define analysistools

/*
  Use for testing
  Draws TObject on global canvas
  then waits for primitives
  before deleting
*/

void DrawWait(TObject *&obj)
{
	TCanvas *c_tmp = new TCanvas();
	c_tmp->cd();
	obj->Draw();
	c_tmp->Update();
	c_tmp->WaitPrimitive();
	delete c_tmp;
}

/*
  Set default style for all macros
*/
void SetStyle(bool batch = 1, int optfit = 1)
{
	gROOT->SetBatch(batch); // don't draw to screen
	gStyle->SetOptFit(optfit); // show fit parameters
	gStyle->SetLegendBorderSize(0); // no border on legend
	gErrorIgnoreLevel = kWarning; // ignore 'Info in...' messages
}

/*
  Sets a TGraph's Y-axis range, axis titles
  marker style and color of the marker
*/
void StyleGraph(TGraph *&gr, double min, double max,
				TString xtitle = "", TString ytitle = "",
				int marker = 20, Color_t color = kBlue,
				TString name = "", TString title = "")
{
	// axis styling
	gr->GetYaxis()->SetRangeUser(min,max);
	gr->GetYaxis()->SetTitle(ytitle.Data());
	gr->GetXaxis()->SetTitle(xtitle.Data());

	// marker styling
	gr->SetMarkerStyle(marker);
	gr->SetMarkerColor(color);

	// name and title
	gr->SetName(name);
	gr->SetTitle(title);
}

/*
  Normlize simulation to data
  using integral method
*/
double NormSim(TH1D *&sim, TH1D *&dat)
{   // scale simulation integral to data
	double areaS = sim->Integral();
	double areaD = dat->Integral();
	double scale = areaD/areaS;

	sim->Scale(scale);
	
	return scale;
}

/*
 Subtracts simulated background from
 given histogram of data
*/
void BGSub(TH1D *&sim, TH1D *&dat, TTree *&tree, 
		   int bins, TString pidcut = "PID>1000",
		   Color_t fill = kBlue, int style = 3002,
		   int smooth = 0)
{   // normalize simulation
	double scale = NormSim(sim,dat);

	// get simulated background
	TH1D *bg = new TH1D("bg","bg",bins,0.6,1);
	tree->Project("bg","theta",Form("%s && path!=LUTpath",pidcut.Data()));
	bg->Scale(scale);

	if(smooth>0) bg->Smooth(smooth);

	// subtract background and style
	sim->Add(bg,-1);
	dat->Add(bg,-1);
	dat->SetFillStyle(style);
	dat->SetFillColor(fill);

	// free pointer
	delete bg;
} // end BGSub()

/*
  Finds peak in timing difference spectrum
*/
double DiffPeak(TTree *&tree, TString pidcut = "PID>1000")
{
	TSpectrum *spec = new TSpectrum(10); // peak finder
	TH1D *diff = new TH1D("diff","diff",200,-5,5);

	tree->Project("diff","diff",pidcut.Data());
	spec->Search(diff,2,"nodraw",0.7);
	double diffpeak = spec->GetPositionX()[0];

	// testing
	//TCanvas *c_tmp = new TCanvas();
	//diff->Draw();
	//c_tmp->WaitPrimitive();
	//delete c_tmp;
	

	delete diff;
	delete spec;

	return diffpeak;
} // end DiffPeak()

/*
  Use a TSpectrum to find a peak in a reconstructed
  theat_C distribution from TH1D hist and fit it 
  with a gaus+pol1 fit from TF1 fit.
  Returns the parameters of the gaussian part
  of the fit as an array
*/
double* SpecSearch(TSpectrum *&spec, TH1D *&hist, TF1 *&fit, double range = 0.03)
{
    // uses a TSpectrum to find a peak in hist
	// and set mean and multiplicative constant
	double con(0), mean(0), sigma(0);
	int nfound = spec->Search(hist,2,"nobackground nodraw",0.6);
	if(nfound)
	{ // if peak found use spectrum peak
		mean = spec->GetPositionX()[0];
		con  = spec->GetPositionY()[0];
	}
	else
	{ // if no peak found use maximum
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		if(mean>0.86) mean = 0.82; // stay within range 
		con  = hist->GetMaximum();
		//cout << "didn't find peak" << endl;
	}

	// fit hist
	double height = hist->GetBinCenter(20); // rouch estimate for constant term
	fit->SetParameters(con,mean,0.01,height,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-range,mean+range);
	
	con = fit->GetParameter(0);
	mean = fit->GetParameter(1);
	sigma = fit->GetParameter(2);

	double *parms = new double[3];
	parms[0] = con;
	parms[1] = mean;
	parms[2] = sigma;

	return parms;
}

/*
  Returns full reconstructed thetaC
  histogram where each MCP has been 
  shifted such that the mean of the
  gaussian aligns with the expected
  value
*/
TH1D* ThetaCorr( TTree *&tree,
				 bool prot = 1,
				 TString pidcut = "PID>1000",
				 double *&shifts,
				 TString corrtitle = "theta",
				 int bins = 120 )
{
	double angleP  = 0.8168; // assume 7 GeV for now
	double anglePi = 0.8249;
	double angle;
	if(prot) angle = angleP;
	else     angle = anglePi;
	
	const int nMCP = 15;
	TH1D *mcpHist[nMCP];
	TH1D *thetaCorr = new TH1D(corrtitle,corrtitle,bins,0.6,1);
	TF1 *mcpfit = new TF1("mcpfit","gaus");
	mcpfit->SetParameters(100,angle,0.007);

	double diffpeak = DiffPeak(tree,pidcut);
	pidcut += Form(" && abs(diff-%f)<1",diffpeak);

	// loop over mcps
	for(int mcpid = 0; mcpid < nMCP; mcpid++)
	{
        // get timing peak for MCP=mcpid
		TString cut = pidcut + Form(" && mcp==%d",mcpid);
		//cut += Form(" && mcp==%d",mcpid);
		//double diffpeak = DiffPeak(tree,cut);
		//cout << "MCP " << mcpid << " time shift\t" << diffpeak << endl;

		// project from tree
		// using PID cut and time cut
		//cut += Form(" && abs(diff-%f)<1",diffpeak);
		TString mcpname = Form("mcp%d",mcpid);
		mcpHist[mcpid] = new TH1D(mcpname,mcpname,bins,0.6,1);
		tree->Project(mcpname,"theta",cut);

		mcpHist[mcpid]->GetXaxis()->SetRangeUser(angle-0.04,angle+0.04);
		double max = mcpHist[mcpid]->GetXaxis()->GetBinCenter(mcpHist[mcpid]->GetMaximumBin());
		//cout << "max\t" << max << endl;
		mcpHist[mcpid]->Fit(mcpfit,"lq","",max-0.03,max+0.03);
		mcpHist[mcpid]->GetXaxis()->UnZoom();
		
		double shift =  angle - mcpfit->GetParameter(1);
		shifts[mcpid] = shift;
		//cout << "shift\t" << shift << endl;

		tree->Project(mcpname,Form("theta+%f",shift),cut);
		thetaCorr->Add(mcpHist[mcpid]);

	}

	return thetaCorr;
}


TCanvas* drawFish(TTree *&tree, TString selection = "PID>1000",
				  TString digidata = "", int layout = 3,
				  double maxz = -2, double minz = -2)
{   // assign mcpid and pixid from the hits tree
	int mcpid(0), pixid(0);
	tree->SetBranchAddress("mcp",&mcpid);
	tree->SetBranchAddress("pix",&pixid);
    
	// entry by entry selection
	TTreeFormula* tform 
		= new TTreeFormula("tree selection",selection.Data(),tree);

	// initialize pad and color scale from prttools
	initDigi();
	SetRootPalette(1);
	int entries = tree->GetEntries();
	cout << "selection: " << selection << endl;
	cout << "entries in tree: " << entries << endl;
	for (int i_entry=0; i_entry<entries; i_entry++)
	{
		tree->GetEntry(i_entry);
		//cout << "entry " << i_entry << endl;
		//cout << "\tmcp: " << mcpid << endl;
		//cout << "\tpix: " << pixid << endl;

		if(tform->EvalInstance())
			fhDigi[mcpid]->Fill(pixid%8, pixid/8);
	}

	drawDigi("m,p,v\n",3,-2,-2);
	cDigi->cd();
	(new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[14]))->Draw();

	return cDigi;
}

#endif

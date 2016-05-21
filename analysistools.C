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

// don't include more than once
#ifndef analysistools
#define analysistools

/*
  Set default style for all macros
*/
void SetStyle()
{
	gROOT->SetBatch(1); // don't draw to screen
	gStyle->SetOptFit(1); // show fit parameters
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
	spec->Search(diff,2,"nodraw",0.9);
	double diffpeak = spec->GetPositionX()[0];

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
double* SpecSearch(TSpectrum *&spec, TH1D *&hist, TF1 *&fit)
{
    // uses a TSpectrum to find a peak in hist
	// and set mean and multiplicative constant
	double con(0), mean(0), sigma(0);
	int nfound = spec->Search(hist,2,"nodraw",0.6);
	if(nfound)
	{ // if peak found use spectrum peak
		mean = spec->GetPositionX()[0];
		con  = spec->GetPositionY()[0];
	}
	else
	{ // if no peak found use usual method
	  // 
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		if(mean>0.86) mean = 0.82; // stay within range 
		con  = hist->GetMaximum();
		cout << "didn't find peak" << endl;
	}

	// fit hist
	double height = hist->GetBinCenter(20);
	fit->SetParameters(con,mean,0.01,height,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-0.03,mean+0.03);
	
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
TCanvas* drawFish(TTree *hits, TString selection = "PID>1000",
				  TString digidata = "", int layout = 3,
				  double maxz = -2, double minz = -2)
{   // assign mcpid and pixid from the hits tree
	int mcpid(0), pixid(0);
	hits->SetBranchAddress("mcp",&mcpid);
	hits->SetBranchAddress("pix",&pixid);
    
	// entry by entry selection
	TTreeFormula* tform 
		= new TTreeFormula("tree selection",selection,hits);

	// initialize pad and color scale from prttools
	initDigi();
	SetRootPalette(1);
	int entries = hits->GetEntries();
	for (int i_entry=0; i_entry<entries; i_entry++)
	{
		hits->GetEntry(i_entry);
		if(tform->EvalInstance() == 0) continue;
	    
	    fhDigi[mcpid]->Fill(pixid%8, pixid/8);
	}

	drawDigi("m,p,v\n",3,-2,-2);
	cDigi->cd();
	(new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[0]))->Draw();

	return cDigi;
	}*/

#endif

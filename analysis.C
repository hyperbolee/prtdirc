// restructuring analysistools.C to be
// more streamlined and useful for after
// modifying analysis scripts

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "../prttools/prttools.C"

/*
  Use a TSpectrum to find the peak in a
  histogram distribution and save the (x,y)
  position of the peak in passed parameters
*/
int findPeak(TH1D *&hist, double &mean, double &ampl, double track = -1)
{
	TSpectrum *spec = new TSpectrum(3);
	int nfound; // some spectra are weird

	// work around to find peak for 50,90,and 100 deg
	// tracks in data for 151 since they are hard
	// to find in the background subtracted spectra
	if(track==90)
		nfound = spec->Search(hist,1,"nobackground nodraw",0.6);

	else if(track==50 || track==100)
		nfound = spec->Search(hist,0.5,"nodraw",0.6);

	else
		nfound = spec->Search(hist,2,"nobackground nodraw",0.6);
	
	// if no peaks found exit
	if(nfound < 1)
	{
		delete spec;
		return 0;
	}

	// define mean and amplitude of peak
	mean = spec->GetPositionX()[0];
	ampl = spec->GetPositionY()[0];

	// work around for 85 degree track
	// with second peak in timing
	// spectrum (very annoying...)
	if(track == 85 && nfound > 1)
	{
		mean = spec->GetPositionX()[1];
		ampl = spec->GetPositionY()[1];
	}
	
	delete spec;
	return nfound;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Find peak for time difference distribution from tree
*/
int findPeak(TTree *&tree, double &mean, double track = -1)
{
	double dummy; // dummy variable for amplitude

	// make time diff histogram and project
	TH1D *diff = new TH1D("diff","diff",200,-5,5);
	tree->Project("diff","diff","PID>1000");
	
	int nfound = findPeak(diff,mean,dummy,track);

	delete diff;
	return nfound;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Use findPeak to find a peak in reconstructed
  theta_C distribution and with with a given fit
  function (gaussian + some order polynomial)
  Returns 0 if no peak found, or
  1 if fitting was successful
*/
int fitPeak(TH1D *&hist, TF1 *&fit, const double range = 0.03, double track = -1)
{
	double mean(0), ampl(0);
	int nfound = findPeak(hist, mean, ampl, track);

	if(nfound < 1)
		return 0;
	
	// rough estimate for constant term
	double shift = hist->GetBinCenter(20);
	
	// set initial parameters and fit histogram
	// set parameters for up to x^3
	fit->SetParameters(ampl,mean,0.01,shift,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-range,mean+range);

	return 1;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Normalize data to simulation and
  subtract simulated background
  from prism ambiguities
*/
void subBackground(TTree *&tree, TH1D *& sim,
					TH1D *&data, TString cut)
{
	// histogram of simulated
	// comibnatorial background
	TH1D *bg = new TH1D("bg","bg",120,0.6,1);
	tree->Project("bg","theta",Form("%s && path!=LUTpath",cut.Data()));
	
	// get normalization constant
	// between sim and data (scale)
	double sim_area  = sim->Integral();
	double data_area = data->Integral();
	double scale     = data_area/sim_area;

	// scale simulation and background
	sim->Scale(scale);
	bg->Scale(scale);

	// subtract background from data and simulation
	sim->Add(bg,-1);
	data->Add(bg,-1);

	// to make clear in plots that background was
	// subtracted, add fill to histograms
	sim->SetFillStyle(3002);
	sim->SetFillColor(kBlue);

	data->SetFillStyle(3002);
	data->SetFillColor(kBlue);

	delete bg;
	return;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Format the stats box of a given histogram to be
  22% x 18% of the total pad area in the upper 
  right corner of the canvas with information
  about the fitted mean and SPR of the histogram
*/
void formatStats(TCanvas *&canv, TPaveStats *&pavestats, TH1D *&hist,
				double track, double mean, double spr)
{
	// clean up  pavestats
	pavestats->Clear();
	
	// define bounds of stats box
	// numbers are percentage of full pad
	double x1 = 0.73;  pavestats->SetX1NDC(x1); // left
	double x2 = 0.95;  pavestats->SetX2NDC(x2); // right
	double y1 = 0.77;  pavestats->SetY1NDC(y1); // bottom
	double y2 = 0.95;  pavestats->SetY2NDC(y2); // top

	pavestats->AddText(Form("%.2f#circ track",track));
	pavestats->AddText(Form("mean = %.3f mrad",mean));
	pavestats->AddText(Form("SPR = %.3f mrad",spr));
	pavestats->SetTextSize(0.03);

	// remove default stats and draw new stats box
	hist->SetStats(0);
	pavestats->Draw();
	canv->Modified();

	return;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Draw hit map on MCPs using prttools
*/
TCanvas* drawFishMCP(TTree *&tree)
{
	// get total entries from tree
	int entries = tree->GetEntries();
	
	// set mcp and pix ID from tree
	int mcpid(0), pixid(0);
	tree->SetBranchAddress("mcp",&mcpid);
	tree->SetBranchAddress("pix",&pixid);

	// initialize pad and color scale from prttools
	initDigi();
	SetRootPalette(15);

	// loop over all entries of tree and fill canvas
	for( int entry = 0; entry < entries; entry++ )
	{
		tree->GetEntry(entry);
		fhDigi[mcpid]->Fill(pixid%8,pixid/8);
	}

	// draw pad and add color scale to the right
	drawDigi("",3,-2,-2);
	cDigi->cd();
	(new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[14]))->Draw();

	return cDigi;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Similar to drawFishMCP but don't use prttools
  Instead draw (x,y) position of each hit for more
  fine-grained look at fish.
  Only to be used with simulation, as data has no
  ability to say what the exact coordinate of the hit was
  Also looks better when using simulation file with full
  detector plane (i.e. not discritized by MCPs/pixels)
*/
TCanvas* drawFishXY(TTree *&tree)
{
	//initialize canvas and 2D histogram
	TCanvas *canv = new TCanvas();
	TH2D *fish = new TH2D("fish","fish",350,-50,300,200,-100,100);

	// project from tree onto hist
	tree->Project("fish","y:x");

	fish->Draw("colz");

	return canv;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

#endif // ANALYSIS_H

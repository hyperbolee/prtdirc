#include "constants_org.h"
#include <iostream>
#include <fstream>

TH1D *theta;
TH1D *multi;

void reconstruction_org(TString infile="../build/reco_spr.root", Int_t num_events = 10000, char *runtype="data")
{
	gStyle->SetOptFit(1111); // show fit parameters
	gStyle->SetOptStat(0);   // remove stats box
	TGaxis::SetMaxDigits(4); // put axis in scientific notation

	TFile *f = TFile::Open(infile); 
	TTree *t = (TTree*)f->Get("reco"); //Lee's Tree
	TTree *d = (TTree*)f->Get("dirc"); //Roman's Tree

	// make counter histograms to make better cuts (later)
	//TH1D *tof1 = 

	// define cut and project from tree to histogram
	theta = new TH1D("theta","theta",100,0.6,1.0);
	if(runtype=="data")
		t->Project("theta","theta",data_cut);
	else
		t->Project("theta","theta",sim_cut);

	// preliminary paramters for fit of theta
	double height = theta->GetMaximum();
	double center = theta->GetBinCenter(theta->GetMaximumBin());
	double sigma  = 0.015;
	double slope  = 1.0;
	double shift  = height/3;

	// define custom fit, set parameters, and fit to data
	TF1 *gaus0 = new TF1("gaus0", "gaus+[3]*x+[4]", 
						 center-0.05, center+0.05);
	gaus0->SetParameters(height,center,sigma,slope,shift);
	gaus0->SetParNames("height","mean","sigma","slope","const");

	TCanvas *c1 = new TCanvas();
	c1->cd();
	theta->Fit("gaus0","QR");

	// set value of lens and alpha from dirc tree
	int lens(0);
	double angle(0),beam(0),yield(0),nph(0);
	d->SetBranchAddress("lens",&lens);
	d->SetBranchAddress("theta",&angle);
	d->SetBranchAddress("beam",&beam);
	d->SetBranchAddress("yield",&yield);
	d->SetBranchAddress("nph",&nph);
	d->GetEntry(0);
	
	// define strings for picture and root file names
	//cout << "defining strings" << endl;
	char *namt = Form("theta_{c} lens %d angle %d",lens,(int)angle);
	char *pict = Form("../macro/reconstruction/reco_%s_%d_%d.png",
					  runtype,lens,(int)angle);
	//cout << pict << endl;

	// format histogram for saving
	double max = 1.1*theta->GetMaximum();
	theta->SetTitle("");
	theta->GetXaxis()->SetLabelSize(0.06);
	theta->GetYaxis()->SetLabelSize(0.06);
	theta->GetXaxis()->SetRangeUser(0.61,1);
	theta->GetYaxis()->SetRangeUser(0,max);
	theta->Draw();
	c1->Print(pict);

	// save histogram again without fit parameters
   	gStyle->SetOptFit(0);
	c1->cd();
	theta->Draw();
	pict = Form("../macro/reconstruction/reco_%s_%d_%d_nofit.png",
				runtype,lens,(int)angle);
	c1->Print(pict);

	double truesig = 1000*gaus0->GetParameter("sigma");
	// print relevant info to screen and file
	char *outnm = Form("../macro/sigma_%s.tsv",runtype);
	ofstream out;
	out.open(outnm, fstream::in | fstream::out | fstream::app);
	out << infile 
		<< "\t" << angle 
		<< "\t" << lens  
		<< "\t" << truesig 
		<< "\t" << yield 
		<< "\t" << nph << endl;
	out.close();
	cout << "\033[1;31m" << infile
		 << "\nsigma:\t" << truesig
		 << "\nhits/e:\t" << nph
		 << "\nphts/e:\t" << yield 
		 << "\033[0m" <<  endl;
	
}

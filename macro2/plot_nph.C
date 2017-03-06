#include "TString.h"
#include "TChain.h"
#include "TGraph.h"
#include "TFile.h"

#include <iostream>

void plot_nph( TString dir = "", bool eventType = 0)
{
	// set string for later use based on eventType
	TString saveString;
	if(eventType) saveString = "data";
	else saveString = "sim";

	// make TChain for dirc TTree in reco files
	TChain *chDIRC = new TChain("dirc");
	chDIRC->Add(dir+"/reco_*.root");

	// get number of points from chain
	// must make a selection here to work
	// excluding 160 because it is bad in data
	int n = chDIRC->Draw("nph:theta","theta<160");
	if(n==0)
	{
		cout << "No reco files found in dir=" << dir.Data() << endl;
		cout << "Exiting" << endl;
		return;
	}

	// everything looks good
	// make TGraph and sort
	TGraph *grNPH = new TGraph(n,chDIRC->GetV2(),chDIRC->GetV1());
	grNPH->Sort();
	grNPH->SetMarkerStyle(20);
	grNPH->SetMarkerSize(0.7);
	grNPH->SetMarkerColor(kRed);

	grNPH->Draw("lp");
}

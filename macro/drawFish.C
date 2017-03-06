//#########################################
// Modified version of drawScan.C
// Uses reconstructed file instead
// of processed data file
//
// Lee Allison - Dec. 23 2015
// Updated - Dec. 8 2016

#include "../drawing.C"
// #include "constants.h"

void drawFish(TString infile="../build/reco_spr.root", bool sim = 0, int study = 151)
{
	double track(0);
	
	// define file, trees, and variables
	TFile *file = TFile::Open(infile);
	TTree *hits = file->Get("hits");
	TTree *dirc = file->Get("dirc");
	
	dirc->SetBranchAddress("theta",&track);
	dirc->GetEntry(0);

	// define useful strings
	TString type = sim ? "sim" : "data";
	TString name = Form("fish_%s_%d_%.2f",type.Data(),study,track);

	// make detector plane, draw, and save
	detectorPlane fish("");
	fish = drawFishMCP(hits);
	fish.SetDesc(name);
	fish.Print("fish/"+name+".png");
	fish.Close();

	//file->Close();
	
	delete hits;
	delete dirc;
	delete file;
}

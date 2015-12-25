//#########################################
// Modified version of drawScan.C
// Adds TPad to right of MCPs
// to show relative  number
// of hits in each pixel
//
// Lee Allison - Dec. 23 2015

#include "../../prttools/prttools.C"
#include "constants.h"

void drawFish(TString infile="../build/reco_spr.root")
{
	int mcpid(0), pixid(0);
	

	TFile *f = TFile::Open(infile);
	TTree *h = f->Get("reco");
	TTree *d = f->Get("dirc");

	h->SetBranchAddress("mcp",&mcpid);
	h->SetBranchAddress("pix",&pixid);

	// make counter histograms for cut
	// TODO: only do this part for beam data
	//       add event type to dirc tree and test that
	char *selection = Form("1");
	TH1D *tof1 = new TH1D("time-tof1","time-tof1",1000,0,1000);
	TH1D *tof2 = new TH1D("time-tof2","time-tof2",1000,0,1000);
	TH1D *trig = new TH1D("time-trig","time-trig",1000,0,1000);

	// project onto counter histograms
	h->Project("time-tof1","time-tof1");
	h->Project("time-tof2","time-tof2");
	h->Project("time-trig","time-trig");
	
	// make cuts w/ counters
	counterCut(tof1, selection);
	counterCut(tof2, selection);
	counterCut(trig, selection);
	cout << "data selection:\t" << selection << endl;
    
	TTreeFormula* tform 
		= new TTreeFormula("tree selection",selection,h);

	initDigi();
	SetRootPalette(1);
	for (Int_t ientry=0; ientry<h->GetEntries(); ientry++)
	{
		h->GetEntry(ientry);
		fhDigi[mcpid]->Fill(pixid%8, pixid/8);
	}
    
	drawDigi("m,p,v\n",3,-2,-2);
	cDigi->cd();
	(new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[0]))->Draw();

}


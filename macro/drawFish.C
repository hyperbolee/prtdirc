//#########################################
// Modified version of drawScan.C
// Adds TPad to right of MCPs
// to show relative  number
// of hits in each pixel
//
// Lee Allison - Dec. 23 2015

#include "../../prttools/prttools.C"
#include "constants.h"

void drawFish(TString infile="../build/reco_spr.root", int save = 0)
{
	int mcpid(0), pixid(0), lens(0);
	double angle(0);
	
	// define file, trees, and variables
	TFile *f = TFile::Open(infile);
	TTree *h = f->Get("hits");
	TTree *d = f->Get("dirc");

	h->SetBranchAddress("mcp",&mcpid);
	h->SetBranchAddress("pix",&pixid);
	d->SetBranchAddress("lens",&lens);
	d->SetBranchAddress("theta",&angle);
	d->GetEntry(0);

	// make counter histograms for cut
	// TODO: only do this part for beam data
	//       add event type to dirc tree and test that
	char *selection = Form("1");
	//tof1Cut(h,selection);
	//tof2Cut(h,selection);
	//trigCut(h,selection);
	cout << "data selection:\t" << selection << endl;
    
	TTreeFormula* tform 
		= new TTreeFormula("tree selection",selection,h);

	// initialize pad, set color scale, and fill fish
	initDigi();
	SetRootPalette(1);
	int badC(0);
	for (Int_t ientry=0; ientry<h->GetEntries(); ientry++)
	{
		h->GetEntry(ientry);
		if(tform->EvalInstance()==0) // skip if "bad" entry
			badC++;
		//	continue;
		fhDigi[mcpid]->Fill(pixid%8, pixid/8);
	}
	cout << "bad:\t" << badC << "\ntot:\t" << h->GetEntries()-badC << endl;
	drawDigi("m,p,v\n",3,-2,-2);
	cDigi->cd();
	(new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[0]))->Draw();
	if(save)
		cDigi->Print(Form("fish/fish_%d_%.1f.png",lens,angle));
}


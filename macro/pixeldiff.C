//#########################################
// Plots time difference for whole
// detector plane, each MCP
// and two selected pixels
// in those MCPs for 
//
// Lee Allison - Jan. 12, 2016

#include "../../prttools/prttools.C"
#include "constants.h"

void pixeldiff(TString infile="../build/reco_spr.root", 
			   TString id="")
{
	// variables from tree and pixels of interest
	int entries(0);
	int pixels[15][2] = {{11,59}, {11,52}, {10,29},
						 { 9,29}, {24,31}, {41,36},
						 {41,21}, {14,27}, {51, 9},
						 {46,18}, {38,59}, {13,52},
						 {10,51}, { 9,36}, {50,20}};
						  

	// set up root objects
	TFile *f = TFile::Open(infile);
	TTree *t = f->Get("reco");
	TCanvas *c = new TCanvas();

	entries = t->GetEntries();
	c->cd();
	
	// define histogram for difference and initial projection
	gStyle->SetOptStat(0);   // remove stats box
	TH1D *diff = new TH1D("diff","diff",500,-5,5);
	t->Project("diff","diff","PID>1000");
	diff->SetTitle("");
	diff->Draw();
	c->Print(Form("timecuts/diff_plane%s.png",id.Data()));

	// define 2D histogram for diff vs. theta
	TH2D *thetadiff = new TH2D("thetadiff","thetadiff",
							   500,-5,-5,200,0.6,1);
	t->Project("thetadiff","theta:diff","PID>1000");
	thetadiff->SetTitle("");
	thetadiff->GetXaxis()->SetRangeUser(-5,5);
	thetadiff->GetYaxis()->SetRangeUser(0.6,1);
	thetadiff->Draw("colz");
	c->Print(Form("timecuts/thetadiff_plane%s.png",id.Data()));
	
	// draw histograms with cut on individual mcps
	for(int mcp=0; mcp<15; mcp++)
	{
		// time diff histogram
		t->Project("diff","diff",Form("PID>1000 && mcp==%d",mcp));
		diff->Draw();
		c->Print(Form("timecuts/diff_mcp%d%s.png",mcp,id.Data()));

		// time diff vs. theta 2D histogram
		t->Project("thetadiff","theta:diff",
				   Form("PID>1000 && mcp==%d",mcp));
		thetadiff->Draw("colz");
		c->Print(Form("timecuts/thetadiff_mcp%d%s.png",
					  mcp,id.Data()));

		// cut on mcp and pixel ID
		for(int p=0; p<2; p++)
		{
			int pix = pixels[mcp][p];

			// time diff histogram
			t->Project("diff","diff",
					   Form("PID>1000 && mcp==%d && pix==%d",mcp,pix));
			diff->Draw();
			c->Print(Form("timecuts/diff_mcp%d_pix%d%s.png",
						  mcp,pix,id.Data()));

			// time diff vs. theta 2D histogram
			t->Project("thetadiff","theta:diff",
					   Form("PID>1000 && mcp==%d && pix==%d",mcp,pix));
			thetadiff->Draw("colz");
			c->Print(Form("timecuts/thetadiff_mcp%d_pix%d%s.png",
						  mcp,pix,id.Data()));
		}
	}
}

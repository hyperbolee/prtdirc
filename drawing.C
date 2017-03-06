// struct and methods for drawing
// hit patters of 2015 data
//
// these would be included in analysis.C
// but for some reason my compiler doesn't like
// TPaletteAxis so I have separated them

#ifndef DRAWING_H
#define DRAWING_H

#include "analysis.C"

int ID = 0; // so all detectorPlane ids are unique
/* 
   struct for drawing the detector plane
   useful for drawing multiple instances
   of detector plane for multiple cuts
*/
struct detectorPlane {
	// description (e.g. cuts)
	TString desc;

	// id of object (to avoid replacing histograms etc)
	int id;

	// number of events and hits/event included
	int nevents;
	int nhits;

	// mcps and pixels
	static const int nmcp =  15;
	static const int npix = 64;

	// histograms and pads
	TH2F *mcp_hist[nmcp]; // MCP heat map
	TPad *mcp_pads[nmcp];
	TPad *glob_pad;

	// canvas for the drawing of the things
	TCanvas *mcp_plane; // MCP heat map

	detectorPlane(TString ds = "mcp plane") {
		// set name
		desc = ds;
		id = ID++; // !!! must be unique for each canvas !!!
		nhits   = 0;
		nevents = 0;

		// initialize MCP hists
		for( int m=0; m<nmcp; m++ ){
			mcp_hist[m] = new TH2F(Form("mcp%d_%d",m,id),Form("mcp%d_%d",m,id),8,0.,8.,8,0.,8.);
			mcp_hist[m]->SetStats(0);
			mcp_hist[m]->SetTitle(0);
			mcp_hist[m]->GetXaxis()->SetNdivisions(10);
			mcp_hist[m]->GetYaxis()->SetNdivisions(10);
			mcp_hist[m]->GetXaxis()->SetLabelOffset(100);
			mcp_hist[m]->GetYaxis()->SetLabelOffset(100);
			mcp_hist[m]->GetXaxis()->SetTickLength(1);
			mcp_hist[m]->GetYaxis()->SetTickLength(1);
			mcp_hist[m]->GetXaxis()->SetAxisColor(15);
			mcp_hist[m]->GetYaxis()->SetAxisColor(15);
		}
    
	} // end constructor

	// mutators
	void SetDesc( TString ds ){ desc = ds; }
	void SetEvents( int events ){ nevents = events; }
	void SetHits( int hits ){ nhits = hits; }

	// fetchers
	TString GetDesc(){ return desc; }
	int GetEvents(){ return nevents; }
	int GetHits(){ return nhits; }

	// fill mcp histograms
	void Fill(int mcp, int row, int col, double weight=1) {
		mcp_hist[mcp]->Fill(col,row,weight);
	}

	// close canvas
	void Close() {
		mcp_plane->Close(); 
	}

	// print canvas
	void Print(TString savename = "mcp_plane.pdf") {
		mcp_plane->Print(savename);
	} // end Print()

	// draw detector plane
	void Draw() {

		// make canvas and global pad for heat maps
		//if(!mcp_plane)
		mcp_plane = new TCanvas(Form("mcp_plane_%d",id),Form("MCP plane %d: %s",id,desc.Data()),0,0,800,400);
		//mcp_plane->SetWindowPosition((id%4)%2*800,((id%4)/2)*400);
		mcp_plane->cd();

		//if(!glob_pad)
		glob_pad  = new TPad(Form("globPad_%d",id),"T",0.04,0.04,0.90,0.96);
		glob_pad->Draw();
		glob_pad->cd();

		//cout << "canvas and glob pad created" << endl;

		// make MCP pads
		//if(!mcp_pads[0]){
		int pad(0), nrow(3), ncol(5);
		float shift(0), shiftw(0.02), shifth(0);
		float bw(0.02), bh(0.01), tbw(0.02), tbh(0.01);

		for( int c=0; c<ncol; c++ ){
			for( int r=0; r<nrow; r++ ){
				if(r==1) shift = -0.028;
				else shift = 0;
	  
				mcp_pads[pad] =  new TPad(Form("pad%d_%d",r+ncol*c,id),"T", c/(Double_t)ncol+tbw+shift+shiftw , r/(Double_t)nrow+tbh+shifth, (c+1)/(Double_t)ncol-tbw+shift+shiftw, (1+r)/(Double_t)nrow-tbh+shifth, 21);

				mcp_pads[pad]->SetFillColor(kCyan-8);
				mcp_pads[pad]->SetMargin(0.04,0.04,0.04,0.04);
				mcp_pads[pad]->Draw();
				pad++;
			}
		}
		//}

		//cout << "mcp pads created" << endl;

		// get min and max across plane
		double max = 0;
		for( int m=0; m<nmcp; m++ ){
			double tmp = mcp_hist[m]->GetBinContent(mcp_hist[m]->GetMaximumBin());
			if(max<tmp) max = tmp;
		}

		//cout << "max found" << endl;

		// set min/max for each hist and draw
		for( int m=0; m<nmcp; m++ ){
			mcp_pads[m]->cd();

			mcp_hist[m]->SetMinimum(0);
			mcp_hist[m]->SetMaximum(max);
			mcp_hist[m]->Draw("col");
		}


		// draw scale to right
		mcp_plane->Modified();
		mcp_plane->Update();
		mcp_plane->cd();
		TPaletteAxis *palette = new TPaletteAxis(0.92,0.1,0.96,0.90,mcp_hist[0]);
		palette->Draw(); 


	} // end Draw()

}; // end struct detectorPlane

/*
  Draw hit map on MCPs using
  detectorPlane struct
*/
detectorPlane drawFishMCP(TTree *&tree, int PID = 2212)
{
	// get total entries from tree
	int entries = tree->GetEntries();
	
	// set mcp and pix ID from tree
	int mcpid(0), pixid(0);
	int pid(0);
	tree->SetBranchAddress("mcp",&mcpid);
	tree->SetBranchAddress("pix",&pixid);
	tree->SetBranchAddress("PID",&pid);

	// initialize pad and color scale
	detectorPlane fish("fish");
	TGaxis::SetMaxDigits(3);
	SetRootPalette(15);

	// loop over all entries of tree and fill canvas
	for( int entry = 0; entry < entries; entry++ )
	{
		tree->GetEntry(entry);
		if(pid==PID) fish.Fill(mcpid,pixid/8,pixid%8);
	}

	// draw canvas
	fish.Draw();

	return fish;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Similar to drawFishMCP but don't use detectorPlane
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

	SetRootPalette(15);
	fish->Draw("colz");

	return canv;
}
//----------------------------------------------------------------
//----------------------------------------------------------------


#endif // DRAWING_H

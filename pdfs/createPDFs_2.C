/*
  Second version of createPDFs.C
  Using the faster method of looping through
  each Event and Hit to get timing information
  (see testtime.C for example)
*/

#include "../src/PrtHit.h"
#include "../src/PrtEvent.h"
#include "../analysis.C"
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

// #include "../../prttools/prttools.C"


void createPDFs_2()
{
	// let's see what happens
	//gROOT->ProcessLine(".L ../src/PrtHit.cxx+");
	//gROOT->ProcessLine(".L ../src/PrtEvent.cxx+");
	
	TString datadir = "../data/152/";//"/home/lee/DIRC/prtdirc/pdfs/";
	TSystemDirectory dir(datadir,datadir);
	TList *files = dir.GetListOfFiles();
	files->Sort();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// histograms for each pixel of each
	// mcp for each file and partile
	static const int nmcp(15), npix(64), nfiles(30);
	TFile *outfile = new TFile("pdf_hists.root","recreate");
	TH1D *hprot[nfiles][nmcp][npix];
	TH1D *hpion[nfiles][nmcp][npix];

	//TCanvas *canv = new TCanvas();
	//canv->cd();

	PrtEvent *fEvent;
	PrtHit    fHit;

	int count = 0;
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith("C.root") )
			continue; // don't process directories or non-root files
		cout << "Processing " << fname << endl;
		
		TChain *ch = new TChain("data");
		ch->Add(datadir+fname);
		ch->SetBranchAddress("PrtEvent",&fEvent);
		ch->GetEntry(0);

		int entries = ch->GetEntries();
		double track = fEvent->GetAngle();
		if(abs(track-130)>0.01) continue;
		
		// int nprot = ch->GetEntries("fParticle>1000");
		// int npion = ch->GetEntries("fParticle<1000");

		cout << "Total entries: " << entries << endl;

		int nprot(0), npion(0);
		
		// initialize histograms
		for(int mcp=0; mcp<nmcp; mcp++)
		{
			for(int pix=0; pix<npix; pix++)
			{
				// simple progress meter
				cout << "\rDefining hists: mcp " << mcp << "...pix " << pix << "..." << flush;
				// define name of each histogram
				TString name = "pdf_%d_%.2f_mcp%d_pix%d";
				TString prtname = Form(name.Data(),2212,track, mcp,pix);
				TString piname = Form(name.Data(),211,track, mcp,pix);

				// define new histograms for pion and proton
				hprot[count][mcp][pix] = new TH1D(prtname,prtname,1000,0,50);
				hpion[count][mcp][pix] = new TH1D(piname,piname,1000,0,50);
			}
		}

		cout << endl << endl;

		// loop over events and fill histograms
		for(int entry=0; entry<entries; entry++)
		{
			ch->GetEntry(entry);
			int hits = fEvent->GetHitSize();
			int pid  = fEvent->GetParticle();

			cout << Form("\rProcessing Event %d",entry) << flush;

			bool t1(false), t2(false);

			// loop through hits first to make sure triggers fired
			for(int hit=0; hit<hits; hit++)
			{
				
				fHit = fEvent->GetHit(hit);
				int chan = fHit.GetChannel();

				if(chan==1344) t1 = true; // trigger 1
				if(chan==1346) t2 = true; // trigger 2
			}

			// skip events that didn't fire on both triggers
			if(!t1 || !t2) continue;

			// increment particle numbers
			// if(pid==211)  npion++;
			// if(pid==2212) nprot++;
			
			for(int hit=0; hit<hits; hit++)
			{
				
				fHit = fEvent->GetHit(hit);

				int mcp = fHit.GetMcpId();
				int pix = fHit.GetPixelId()-1;
				double time = fHit.GetLeadTime();

				// time cuts
				if(track<=80)
					if(time<11 || time>35) continue;
				
				if(track>=95)
					if(time<3 || time>20) continue;

				if(pid==211)  hpion[count][mcp][pix]->Fill(time);
				if(pid==2212) hprot[count][mcp][pix]->Fill(time);

				
			}
		}

		cout << endl << endl;

		// for(int mcp=0; mcp<nmcp; mcp++)
		// {
		// 	for(int pix=0; pix<npix; pix++)
		// 	{
		// 		hprot[count][mcp][pix]->Scale(double(1./nprot));
		// 		hpion[count][mcp][pix]->Scale(double(1./npion));
		// 	}
		// }
				
		count++;
		//if(count > 2) break; // testing

		ch->Delete();
	}
	cout << endl << endl;

	outfile->Write();
}
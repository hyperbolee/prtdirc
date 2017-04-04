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

#include <map>

// #include "../../prttools/prttools.C"


void createPDFs_2(int normId = 1, int smooth = 0, int sigma = 3)
{
	// let's see what happens
	//gROOT->ProcessLine(".L ../src/PrtHit.cxx+");
	//gROOT->ProcessLine(".L ../src/PrtEvent.cxx+");

	gErrorIgnoreLevel = kWarning; // ignore 'Info in...' messages
	
	TString datadir = "../data/151/";//"/home/lee/DIRC/prtdirc/pdfs/";
	TSystemDirectory dir(datadir,datadir);
	TList *files = dir.GetListOfFiles();
	files->Sort();
	TSystemFile *file;
	TString fname;
	TIter next(files);
	
	// histograms for each pixel of each
	// mcp for each file and partile
	static const int nmcp(15), npix(64), nfiles(30);
	TFile *outfile = new TFile(Form("pdf_norm%d_smooth%d.root",normId,smooth),"recreate");
	TH1F *hprot [nfiles][nmcp][npix];
	TH1F *hpion [nfiles][nmcp][npix];

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
		
		
		TChain *ch = new TChain("data");
		ch->Add(datadir+fname);
		ch->SetBranchAddress("PrtEvent",&fEvent);
		ch->GetEntry(0);

		int entries = ch->GetEntries();
		double track = fEvent->GetAngle();
		if(abs(track-25)>0.01) continue;

		cout << "Processing " << fname << endl;
		
		//int totprot = ch->GetEntries("fParticle>1000");
		//int totpion = ch->GetEntries("fParticle<1000");

		cout << "Total entries: " << entries << endl;

		int nprot(0), npion(0); // num tracks
		int tprot(0), tpion(0); // num hits
		
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
				hprot[count][mcp][pix] = new TH1F(prtname,prtname,250,0,100);
				hpion[count][mcp][pix] = new TH1F(piname,piname,250,0,100);
			}
		}

		cout << endl << endl;

		int prlim(0), pilim(0);
		for(int entry=0; entry<entries; entry++)
		{
			ch->GetEntry(entry);
			int hits = fEvent->GetHitSize();
			int pid = fEvent->GetParticle();
		
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

			if(pid==211)  pilim++;
			if(pid==2212) prlim++;
		}

		int limit = prlim<=pilim ? prlim : pilim;

		// loop over events and fill histograms
		for(int entry=0; entry<entries; entry++)
		{
			//if(npion>=75000) continue;
			//if(nprot>=75000) continue;
			
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

			// check to make sure particle limit
			// hasn't been reached yet
			if(npion==limit && nprot==limit) break;
			if(pid==211  && npion>=limit) continue;
			if(pid==2212 && nprot>=limit) continue;

			// increment species numbers
			if(pid==211)  npion++;
			if(pid==2212) nprot++;

			//int multiHit[15][64] = { 0 };
			map<int, map<int,int> > multiHit;
			
			for(int hit=0; hit<hits; hit++)
			{
				
				fHit = fEvent->GetHit(hit);

				int mcp = fHit.GetMcpId();
				int pix = fHit.GetPixelId()-1;
				double time = fHit.GetLeadTime();

				// skip multiple hits in same channel
				if(++multiHit[mcp][pix]>1)
					continue;

				// time cut
				if(time<0 || time>40)
					continue;

				if(pid==211)
				{
					tpion++;
					hpion[count][mcp][pix]->Fill(time);
				}
				if(pid==2212)
				{
					tprot++;
					hprot[count][mcp][pix]->Fill(time);
				}

				
			}
		}

		cout << endl;
		cout << "prlim " << prlim << endl;
		cout << "pilim " << pilim << endl;
		cout << "limit " << limit << endl;
		cout << "nprot " << nprot << endl;
		cout << "npion " << npion << endl;
		cout << "tprot " << tprot << endl;
		cout << "tpion " << tpion << endl;

		for(int mcp=0; mcp<nmcp; mcp++)
		{
			for(int pix=0; pix<npix; pix++)
			{
				double sProt(1);
				double sPion(1);
				switch(normId)
				{
					case 0:
						sProt = 1.;
						sPion = 1.;
						break;
						
					case 1:
						sProt = 1./double(nprot);
						sPion = 1./double(npion);
						break;

					case 2:
						sProt = double(hprot[count][mcp][pix]->GetEntries())/nprot;
						sPion = double(hpion[count][mcp][pix]->GetEntries())/npion;
						break;

					case 3:
						sProt = double(hprot[count][mcp][pix]->GetEntries())/tprot;
						sPion = double(hpion[count][mcp][pix]->GetEntries())/tpion;
						break;

					case 4:
						sProt = 1./double(tprot);
						sPion = 1./double(tpion);
						break;
				}				

				// normalize histograms and smooth
				hprot[count][mcp][pix]->Scale(sProt);
				hpion[count][mcp][pix]->Scale(sPion);

				if(smooth)
				{
					hprot[count][mcp][pix]->Smooth(smooth);
					hpion[count][mcp][pix]->Smooth(smooth);
				}

				hprot[count][mcp][pix]->SetLineColor(kBlue);
				hpion[count][mcp][pix]->SetLineColor(kRed);

				if(sigma>0)
				{
					hprot[count][mcp][pix]->Rebin(int(sigma));
					hpion[count][mcp][pix]->Rebin(int(sigma));
				}

				// write outfile and clean up memory
				hprot[count][mcp][pix]->Write();
				hpion[count][mcp][pix]->Write();
				
				hprot[count][mcp][pix]->Delete();
				hpion[count][mcp][pix]->Delete();
			}
		}
				
		count++;
		//if(count > 2) break; // testing

		ch->Delete();
	}
	cout << endl << endl;

	//outfile->Write();
	outfile->Close();
	outfile->Delete();
	
}

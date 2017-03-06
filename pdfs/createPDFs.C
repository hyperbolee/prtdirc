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


void createPDFs()
{
	// let's see what happens
	//gROOT->ProcessLine(".L ../src/PrtHit.cxx+");
	//gROOT->ProcessLine(".L ../src/PrtEvent.cxx+");
	
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
		double track = fEvent->GetAngle();
		if(abs(track-125)>1) continue;
		
		int nprot = ch->GetEntries("fParticle>1000");
		int npion = ch->GetEntries("fParticle<1000");

		cout << "nprot " << nprot << endl;
		cout << "npion " << npion << endl;

		for(int mcp=0; mcp<nmcp; mcp++)
		{
			for(int pix=0; pix<npix; pix++)
			{
				// simple progress meter
				cout << "\rmcp " << mcp << "...pix " << pix << "..." << flush;
				// define name of each histogram
				TString name = "pdf_%d_%.2f_mcp%d_pix%d";
				TString prtname = Form(name.Data(),2212,track, mcp,pix);
				TString piname = Form(name.Data(),211,track, mcp,pix);

				// define new histograms for pion and proton
				hprot[count][mcp][pix] = new TH1D(prtname,prtname,500,0,100);
				hpion[count][mcp][pix] = new TH1D(piname,piname,500,0,100);

				// project onto histogrms
				//int nprot =
				ch->Project(prtname,"fHitArray.fLeadTime",Form("fParticle>1000 && fHitArray.fMcpId==%d && fHitArray.fPixelId==%d",mcp,pix+1));
				//int npi =
				ch->Project(piname,"fHitArray.fLeadTime",Form("fParticle<1000 && fHitArray.fMcpId==%d && fHitArray.fPixelId==%d",mcp,pix+1));

				// scale histograms such that the y-axis is
				// the probability for 1 particle
				if(nprot>0) hprot[count][mcp][pix]->Scale(1.0/double(nprot));
				if(npion>0) hpion[count][mcp][pix]->Scale(1.0/double(npion));
			}
		}
		cout << "\r" << flush; // return to front of line

		count++;
		//if(count > 2) break; // testing		
	}
	cout << endl << endl;

	outfile->Write();
}

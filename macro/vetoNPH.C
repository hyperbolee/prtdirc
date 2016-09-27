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

void vetoNPH()
{
	// save path
	TString path = "../studies/veto/";

	// initialize input root file
	TFile *infile;
	
	// photon yield graphs
	TGraph *trig1   = new TGraph(); // photon yield trig1
	TGraph *trig12  = new TGraph(); // trig1+trig2
	//TGraph *vetoL   = new TGraph();
	//TGraph *vetoR   = new TGraph();
	//TGraph *vetoTR  = new TGraph();
	//TGraph *vetoTL  = new TGraph();
	//TGraph *vetoBR  = new TGraph();
	TGraph *vetoT1  = new TGraph(); // veto1+trig1
	//TGraph *vetoT2  = new TGraph(); // veto2+trig2
	TGraph *vetoTA  = new TGraph(); // veto1+2 + trig1+2
	TGraph *novtT1  = new TGraph(); // trig1 w/o veto
	TGraph *novtT12 = new TGraph(); // trig1+2 w/o vetos

	// num events graphs
	TGraph *etrg1   = new TGraph(); // events trig1
	TGraph *etrg12  = new TGraph(); // events trig1+2
	TGraph *eveto1  = new TGraph(); // events veto1+trig1
	//TGraph *eveto2  = new TGraph(); // events veto2+trig2
	TGraph *eveto12 = new TGraph(); // events veto1+2 + trig1+2
	TGraph *enovt1  = new TGraph(); // events trig1 w/o veto
	TGraph *enovt12 = new TGraph(); // events trig1+2 w/o vetos

	// photon yields
	double t1(0), t12(0); // vL(0), vR(0);   // uncut and trig1
	//double vTR(0), vTL(0), vBR(0); // trig2
	double vT1(0), vT2(0), vTA(0); // consolidated
	double nV1(0), nV12(0); // w/o vetos

	// event numbers
	int et1(0), et12(0);
	int ev1(0), ev2(0), ev12(0);
	
	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	TString datdir = path + "root/";

	// grab files from data directory
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// loop over each root file in directory
	int n(0); // counter
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files
		cout << "Processing " << fname << endl;

		double track(0); // polar angle

		// grab root file, set tree, and get veto counter values
		infile = TFile::Open(datdir+fname);
		TTree *dirc   = (TTree*)infile->Get("dirc");
		dirc->SetBranchAddress("nph",&t1);
		dirc->SetBranchAddress("trigNph",&t12);
		//dirc->SetBranchAddress("vetoL",&vL);
		//dirc->SetBranchAddress("vetoR",&vR);
		//dirc->SetBranchAddress("vetoTR",&vTR);
		//dirc->SetBranchAddress("vetoTL",&vTL);
		//dirc->SetBranchAddress("vetoBR",&vBR);
		dirc->SetBranchAddress("vetoT1",&vT1);
		//dirc->SetBranchAddress("vetoT2",&vT2);		
		dirc->SetBranchAddress("vetoTA",&vTA);
		dirc->SetBranchAddress("novt1",&nV1);
		dirc->SetBranchAddress("novt12",&nV12);
		dirc->SetBranchAddress("etrig1",&et1);
		dirc->SetBranchAddress("etrig12",&et12);
		dirc->SetBranchAddress("eveto1",&ev1);
		//dirc->SetBranchAddress("eveto2",&ev2);
		dirc->SetBranchAddress("eveto12",&ev12);
		dirc->SetBranchAddress("theta",&track);
		dirc->GetEntry(0);

		if( track == 160 ) continue; // bad points

		// add next point to each graph
		double per = 1; // 100/t1;
		trig1->SetPoint(n,track,t1);
		trig12->SetPoint(n,track,t12);
		//vetoL->SetPoint(n,track,vL*per);
		//vetoR->SetPoint(n,track,vR*per);
		//vetoTR->SetPoint(n,track,vTR*per);
		//vetoTL->SetPoint(n,track,vTL*per);
		//vetoBR->SetPoint(n,track,vBR*per);
		vetoT1->SetPoint(n,track,vT1*per);
		//vetoT2->SetPoint(n,track,vT2*per);
		vetoTA->SetPoint(n,track,vTA*per);
		novtT1->SetPoint(n,track,nV1*per);
		novtT12->SetPoint(n,track,nV12*per);
				

		per = 1/double(et1);
		etrg1->SetPoint(n,track,double(et1)*per);
		etrg12->SetPoint(n,track,double(et12)*per);
		eveto1->SetPoint(n,track,double(ev1)*per);
		//eveto2->SetPoint(n,track,double(ev2)*per);
		eveto12->SetPoint(n,track,double(ev12)*per);
		enovt1->SetPoint(n,track,(double)(et1-ev1)*per);
		enovt12->SetPoint(n,track,(double)(et12-ev12)*per);
		
		delete dirc;

		n++;
	}

	// sort graphs
	trig1->Sort();
	trig12->Sort();
	//vetoL->Sort();
	//vetoR->Sort();
	//vetoTR->Sort();
	//vetoTL->Sort();
	//vetoBR->Sort();
	vetoT1->Sort();
	//vetoT2->Sort();
	vetoTA->Sort();
	novtT1->Sort();
	novtT12->Sort();

	etrg1->Sort();
	etrg12->Sort();
	eveto1->Sort();
	//eveto2->Sort();
	eveto12->Sort();
	enovt1->Sort();
	enovt12->Sort();

	// set names for readability
	trig1->SetName("trig1");
	trig12->SetName("trig12");
	//vetoL->SetName("vetoL");
	//vetoR->SetName("vetoR");
	//vetoTR->SetName("vetoTR");
	//vetoTL->SetName("vetoTL");
	//vetoBR->SetName("vetoBR");
	vetoT1->SetName("vetoT1");
	//vetoT2->SetName("vetoT2");
	vetoTA->SetName("vetoTA");
	novtT1->SetName("noVeto1");
	novtT12->SetName("noVeto12");

	etrg1->SetName("etrig1");
	etrg12->SetName("etrig12");
	eveto1->SetName("eveto1");
	//eveto2->SetName("eveto2");
	eveto12->SetName("eveto12");
	enovt1->SetName("eNoVeto1");
	enovt12->SetName("eNoVeto12");

	// make outfile and add graphs
	TFile *outfile = new TFile(path+"vetoNPH.root","recreate");
	outfile->Add(trig1);
	outfile->Add(trig12);
	//outfile->Add(vetoL);
	//outfile->Add(vetoR);
	//outfile->Add(vetoTR);
	//outfile->Add(vetoTL);
	//outfile->Add(vetoBR);
	outfile->Add(vetoT1);
	//outfile->Add(vetoT2);
	outfile->Add(vetoTA);
	outfile->Add(novtT1);
	outfile->Add(novtT12);
	outfile->Add(etrg1);
	outfile->Add(etrg12);
	outfile->Add(eveto1);
	//outfile->Add(eveto2);
	outfile->Add(eveto12);
	outfile->Add(enovt1);
	outfile->Add(enovt12);

	// write and close
	outfile->Write();
	outfile->Close();
}

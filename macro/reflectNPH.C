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

void reflectNPH()
{
	// save path
	TString path = "../studies/reflectivity/";

	// initialize input root file
	TFile *infile;
	
	// photon yield graphs
	TGraph *nph = new TGraph(); 

	// store photon yield to add to graph
	double NPH(0);
	
	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	//TString simdir = path + "reco/";
	TString simdir = "../data/150/reco/cs/";

	// grab files from data directory
	TSystemDirectory dir(simdir,simdir);
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
		infile = TFile::Open(simdir+fname);
		TTree *dirc   = (TTree*)infile->Get("dirc");
		dirc->SetBranchAddress("nph",&NPH);
		dirc->SetBranchAddress("theta",&track);
		dirc->GetEntry(0);

		if( track == 0 ||
			track == 160 ) continue; // bad point for data

		cout << "\ttrack " << track << endl;
		cout << "\tnph   " << NPH   << endl;

		// add next point to each graph
		nph->SetPoint(n,track,NPH);
		
		delete dirc;

		n++;
	}

	// sort graph
	nph->Sort();

	// set names for readability
	nph->SetName("reflectNPH");

	// make outfile and add graphs
	TFile *outfile = new TFile(path+"reflectNPH150.root","recreate");
	outfile->Add(nph);

	// write and close
	outfile->Write();
	outfile->Close();
}

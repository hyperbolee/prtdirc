#include "../analysis.C"

void plot_fish( int study = 151 )
{
	// save path
	TString savepath = Form("./analysis/%d/fish/",study);

	// track of current file
	double track(0);

	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	TString simdir = Form("../simulation/151/reco/cs/");
	TString datdir =  Form("../data/%d/reco/cs/",study);
	
	// grab files from data directory
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// reused file and tree objects in loop
	TFile *sim_file;
	TTree *sim_hits;
	TFile *data_file;
	TTree *data_dirc, *data_hits;

	// loop over each root file in directory
	// and extract nph, spr, and mean thetaC
	// for both data and sim w/ and w/o bgsub
	int n(0); // counter
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files

		// define data file and trees
		data_file = TFile::Open(datdir+fname);
		data_dirc = (TTree*)data_file->Get("dirc");
		data_hits = (TTree*)data_file->Get("hits");
		data_dirc->SetBranchAddress("theta",&track);
		data_dirc->GetEntry(0);

		// make sure simulation of run exists
		FileStat_t buffer;
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		if(gSystem->GetPathInfo(simfile.Data(),buffer))
		{
			data_file->Close();
			continue;
		}

		cout << "Processing " << track << ": " << fname << endl;

		// define simulation file and trees
		sim_file = TFile::Open(simfile);
		sim_hits = (TTree*)sim_file->Get("hits");

		// make data plot
		TCanvas *data_canv = drawFishMCP(data_hits);
		data_canv->Print(savepath+Form("data_%.2f.png",track));

		TCanvas *sim_canv = drawFishMCP(sim_hits);
		sim_canv->Print(savepath+Form("sim_%.2f.png",track));

		// clear files and trees for next loop
		data_file->Close();
		sim_file->Close();

		// clean up pointers
		delete sim_canv;
		delete data_canv;

		n++;
		if(n>0) break;
	}

	
}

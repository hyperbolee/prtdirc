//
// Macro used to generate plot of
// Single Photon Resolution (SPR)
// for both data and simulation
// and save to root file
//
// Author: Lee Allison, 2016

#include "../analysis.C"

void plot_bg()
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in..' messages
	
	// save path
	TString savepath = "./backgrounds/";

	// variables for output trees
	double track(0); // polar track angle

	const int bins = 120;

	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	TString simdir = Form("../simulation/151/reco/cs/");
	
	// grab files from data directory
	TSystemDirectory dir(simdir,simdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// reused objects in loop
	TCanvas *canv = new TCanvas(); // canvas for drawing

	TFile *sim_file;  // for simulation
	TTree *sim_dirc, *sim_reco;

	// loop over each root file in directory
	// and extract nph, spr, and mean thetaC
	// for both data and sim w/ and w/o bgsub
	int n(0); // counter
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files

		// define simulation file and trees
		sim_file = TFile::Open(simdir+fname);
		sim_reco = (TTree*)sim_file->Get("reco");
		sim_dirc = (TTree*)sim_file->Get("dirc");
		sim_dirc->SetBranchAddress("theta",&track);
		sim_dirc->GetEntry(0);
		
		cout << "Processing " << track << ": " << fname << endl;

		// do the same for protons and pions
		// there has to be a better way.....
		for(int pid=211; pid<=2212; pid+=2001)
		{
			TString particle;
			if(pid==211){ particle = "pi"; } 
			else{ particle = "p"; }

			// define histogram for reconstructed thetaC
			TH1D *sim_theta = new TH1D("sim_theta","sim_theta",bins,0.6,1);
			
			// find timing peak for sim
			// to use for timing cut
			double sim_time;
			findPeak(sim_reco,sim_time);
		
			TString sim_cut = Form("PID==%d && abs(diff-%f)<1 && path!=LUTpath",pid,sim_time);

			// project thetaC onto histograms
			sim_reco->Project("sim_theta","theta",sim_cut);
		
			sim_theta->SetTitle(Form("sim #theta_{C} %s background, %.2f#circ",particle.Data(),track));
			sim_theta->Draw();
			canv->Print(savepath+Form("sim_%s_bg_%.2f.png",particle.Data(),track));


			// clear persistant objects and increment
			// counter for next loop
			canv->Clear();
			sim_file->Clear();
			sim_reco->Clear();
			sim_dirc->Clear();

			// clean up pointers
			delete sim_theta;
		}
		
		n++;
		
		//if(n>0) break;
	}
	
	// clean up pointers
	delete canv;
	delete file;
	delete files;
}


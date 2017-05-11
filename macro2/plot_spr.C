//
// Macro used to generate plot of
// Single Photon Resolution (SPR)
// for both data and simulation
// and save to root file
//
// Author: Lee Allison, 2016

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

#include "errors.h"

void plot_spr( int study = 151, // select run
			   int polrank = 1, // polynomial fit rank
			   double range = 30) // +- fit range [mrad]
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in..' messages
	
	// save path
	//TString savepath = Form("./analysis/%d/pol%d_%d/",study,polrank,int(range));
	TString savepath = "~/Desktop/thetaC/";

	// want to do bg subtraction or print canvases?
	bool subtractBG = true;
	bool printCanv  = true;

	// variables for output trees
	int pid(0);
	double track(0); // polar track angle
	// double err_nph(0), err_spr(0), err_thc(0); // error per track angle
	double sim_nph(0), data_nph(0); // photon yields
	double sim_spr(0), data_spr(0); // fit SPR
	double sim_mean(0), data_mean(0); // fit mean thetaC 
	double sim_spr_bg(0), data_spr_bg(0); // fit SPR w/ bg sub
	double sim_mean_bg(0), data_mean_bg(0); // fit mean w/ bg sub

	const int bins = 120;

	// create new file and trees to hold analysis results
	TString theta = "theta"; // thetaOld == uncorrected MCP angle
	TString thetaSave = ""; // "_old" == uncorrected MCP angle
	TFile *out_file = new TFile(savepath+"analysis.root","recreate");
	TTree *sim_tree = new TTree("sim","simulation tree");
	TTree *data_tree = new TTree("data","data tree");

	// make branches for simulation tree
	sim_tree->Branch("track",&track,"track/D");
	
	sim_tree->Branch("pid",&pid,"pid/I");
	sim_tree->Branch("nph",&sim_nph,"sim_nph/D");
	sim_tree->Branch("spr",&sim_spr,"sim_spr/D");
	sim_tree->Branch("mean",&sim_mean,"sim_mean/D");
	sim_tree->Branch("spr_bg",&sim_spr_bg,"sim_spr_bg/D");
	sim_tree->Branch("mean_bg",&sim_mean_bg,"sim_mean_bg/D");

	// make branches for data tree
	data_tree->Branch("track",&track,"track/D");
	data_tree->Branch("pid",&pid,"pid/I");
	data_tree->Branch("nph",&data_nph,"data_nph/D");
	data_tree->Branch("spr",&data_spr,"data_spr/D");
	data_tree->Branch("mean",&data_mean,"data_mean/D");
	data_tree->Branch("spr_bg",&data_spr_bg,"data_spr_bg/D");
	data_tree->Branch("mean_bg",&data_mean_bg,"data_mean_bg/D");

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

	// reused objects in loop
	TCanvas *canv = new TCanvas(); // canvas for drawing
	
	TPaveStats *pavestats = new TPaveStats(); // hist stats
	pavestats->SetBorderSize(1);
	pavestats->SetFillColor(kWhite);

	TFile *data_file; // file and tree objects
	TFile *sim_file;  // for data and simulation
	TTree *data_dirc, *data_reco;
	TTree *sim_dirc, *sim_reco;

	// loop over each root file in directory
	// and extract nph, spr, and mean thetaC
	// for both data and sim w/ and w/o bgsub
	int n(0); // counter
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith("_spr.root") )
			continue; // don't process directories or non-root files

		// define data file and trees
		data_file = TFile::Open(datdir+fname);
		data_dirc = (TTree*)data_file->Get("dirc");
		data_reco = (TTree*)data_file->Get("reco");
		data_dirc->SetBranchAddress("theta",&track);
		data_dirc->SetBranchAddress("nph",&data_nph);
		data_dirc->GetEntry(0);

		// make sure simulation of run exists
		FileStat_t buffer;
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		if(gSystem->GetPathInfo(simfile.Data(),buffer))
		{
			//data_file->Close();
			continue;
		}

		//if(track != 75) continue;

		cout << "Processing " << track << ": " << fname << endl;

		// define simulation file and trees
		sim_file = TFile::Open(simfile);
		sim_dirc = (TTree*)sim_file->Get("dirc");
		sim_reco = (TTree*)sim_file->Get("reco");
		sim_dirc->SetBranchAddress("nph",&sim_nph);
		sim_dirc->GetEntry(0);
		
		// do the same for protons and pions
		for(pid=211; pid<=2212; pid+=2001)
		{
			TString particle;
			if(pid==211){ particle = "pi"; } 
			else{ particle = "p"; }

			// define histograms for reconstructed thetaC
			TH1D *sim_theta = new TH1D("sim_theta","sim_theta",bins,0.6,1);
			TH1D *data_theta = new TH1D("data_theta","data_theta",bins,0.6,1);
			TH1D *sim_theta_bg = new TH1D("sim_theta_bg","sim_theta_bg",bins,0.6,1);
			TH1D *data_theta_bg = new TH1D("data_theta_bg","data_theta_bg",bins,0.6,1);

			// define fit functions
			TString function = Form("gaus+pol%d(3)",polrank);
			TF1 *sim_fit  = new TF1("sim_fit",function);
			TF1 *data_fit = new TF1("data_fit",function);
			TF1 *sim_fit_bg  = new TF1("sim_fit_bg",function);
			TF1 *data_fit_bg = new TF1("data_fit_bg",function);

			// find timing peak for data and sim
			// to use for timing cuts
			double sim_time, data_time;
			findPeak(sim_reco,sim_time);
			if(track == 75)
				findPeak(data_reco,data_time,75);
			else
				findPeak(data_reco,data_time);
			cout << "time: " << data_time << endl;	
		
			TString sim_cut = Form("PID==%d && abs(diff-%f)<1",pid,sim_time);
			TString data_cut = Form("PID==%d && abs(diff-%f)<1",pid,data_time);

			// project thetaC onto histograms
			sim_reco->Project("sim_theta",theta,sim_cut);
			sim_reco->Project("sim_theta_bg",theta,sim_cut);
			data_reco->Project("data_theta",theta,data_cut);
			data_reco->Project("data_theta_bg",theta,data_cut);

			// subtract background
			subBackground(sim_reco,sim_theta_bg,data_theta_bg,sim_cut);

			// fit distributions and get SPR and mean
			// simulation
			fitPeak(sim_theta,sim_fit,range/1000);
			sim_mean     = 1000*sim_fit->GetParameter(1);
			sim_spr      = 1000*sim_fit->GetParameter(2);
		
			sim_theta->SetTitle(Form("sim #theta_{C} %s reco, %.2f#circ",particle.Data(),track));
			formatStats(canv,pavestats,sim_theta,track,sim_mean,sim_spr);
			canv->Print(savepath+Form("thetaC/sim_%s_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

			// simulation bg sub
			fitPeak(sim_theta_bg,sim_fit_bg,range/1000);
			sim_mean_bg  = 1000*sim_fit_bg->GetParameter(1);
			sim_spr_bg   = 1000*sim_fit_bg->GetParameter(2);
		
			sim_theta_bg->SetTitle(Form("sim #theta_{C} %s reco bgsub, %.2f#circ",particle.Data(),track));
			formatStats(canv,pavestats,sim_theta_bg,track,sim_mean_bg,sim_spr_bg);
			canv->Print(savepath+Form("thetaC/sim_%s_bg_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

			// data
			fitPeak(data_theta,data_fit,range/1000);
			data_mean    = 1000*data_fit->GetParameter(1);
			data_spr     = 1000*data_fit->GetParameter(2);
		
			data_theta->SetTitle(Form("data #theta_{C} %s reco, %.2f#circ",particle.Data(),track));
			formatStats(canv,pavestats,data_theta,track,data_mean,data_spr);
			canv->Print(savepath+Form("thetaC/data_%s_%.2f%s.png",particle.Data(),track,thetaSave.Data()));
			

			// data bg sub
			fitPeak(data_theta_bg,data_fit_bg,range/1000,track);
			data_mean_bg = 1000*data_fit_bg->GetParameter(1);
			data_spr_bg  = 1000*data_fit_bg->GetParameter(2);
			//double temp_var;
			//findPeak(data_theta_bg,temp_var,temp_var,track);
			data_theta_bg->Draw();
			data_theta_bg->SetTitle(Form("data #theta_{C} %s reco bgsub, %.2f#circ",particle.Data(),track));
			formatStats(canv,pavestats,data_theta_bg,track,data_mean_bg,data_spr_bg);
			canv->Print(savepath+Form("thetaC/data_%s_bg_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

			// write TTrees
			sim_tree->Fill();
			data_tree->Fill();

			// clear persistant objects and increment
			// counter for next loop
			canv->Clear();
			pavestats->Clear();
			data_file->Clear();
			data_reco->Clear();
			data_dirc->Clear();
			sim_file->Clear();
			sim_reco->Clear();
			sim_dirc->Clear();

			// clean up pointers
			delete sim_fit;
			delete data_fit;
			delete sim_fit_bg;
			delete data_fit_bg;
			delete sim_theta;
			delete data_theta;
			delete sim_theta_bg;
			delete data_theta_bg;
		}
		n++;
		cout << "finishing track " << track << endl;
		//if(n>20) break;
	}

	//cout << "out of the loop" << endl;
	// write output file
	out_file->Write();
	//out_file->Close();
	cout << "out_file written" << endl;

	// close loop files
	//sim_file->Close();
	//data_file->Close();
	//out_file->Close();

	// clean up pointers
	// delete canv;
	// delete sim_file;
	// delete data_file;
	// delete out_file;
	//cout << "objects deleted" << endl;
	//delete file;
	//delete files;
	//delete sim_tree;
	//delete data_tree;
	//delete out_file;
}


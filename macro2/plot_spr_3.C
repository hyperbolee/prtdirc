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
#include "TGraphErrors.h"

#include "errors.h"

TGraphErrors* SetGraph(TString name, TString axis, bool sim)
{
	TGraphErrors *graph = new TGraphErrors();

	graph->SetName(name);
	graph->SetTitle(name+axis);

	graph->SetMarkerStyle(20);
	graph->SetMarkerSize(0.7);

	int color = sim ? kBlue : kRed;
	graph->SetLineColor(color);
	graph->SetMarkerColor(color);

	return graph;
}

void plot_spr_3( TString infile )
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in..' messages

	setErrors();
	totalErrors();

	const int bins = 120;
	double track(0), dnph(0), snph(0);
	TString theta = "theta";
	TString thetaSave = "";
	
	TCanvas *canv = new TCanvas();

	TPaveStats *pavestats = new TPaveStats(); // hist stats
	pavestats->SetBorderSize(1);
	pavestats->SetFillColor(kWhite);

	TFile *data_file = TFile::Open(infile);
	TTree *data_dirc = (TTree*)data_file->Get("dirc");
	TTree *data_reco = (TTree*)data_file->Get("reco");
	data_dirc->SetBranchAddress("theta",&track);
	data_dirc->SetBranchAddress("nph",&dnph);
	data_dirc->GetEntry(0);

	// don't want 160
	if(track >150)
		return;
	
	// save path
	TString savepath = "./analysis/";
	TString simdir   = "../simulation/151/reco/cs/";
	FileStat_t buffer;
	TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
	if(gSystem->GetPathInfo(simfile.Data(),buffer))
	{
		cout << "SIMULATION FILE " << track << " NOT FOUND, EXITING." << endl;

		delete data_file;
		delete data_dirc;
		delete data_reco;
		
		return;
	}

	TFile *sim_file = TFile::Open(simfile);
	TTree *sim_dirc = (TTree*)sim_file->Get("dirc");
	TTree *sim_reco = (TTree*)sim_file->Get("reco");
	sim_dirc->SetBranchAddress("nph",&snph);
	sim_dirc->GetEntry(0);
	
	TFile *outfile = new TFile(savepath+Form("analysis_%.2f.root",track),"recreate");

	TGraphErrors *grSimNPH = SetGraph("simNPH",";polar track [#circ];photon yield [hits/event]",1);
	TGraphErrors *grDataNPH = SetGraph("dataNPH",";polar track [#circ];photon yield [hits/event]",0);

	grSimNPH->SetPoint(0,track,snph);
	grDataNPH->SetPoint(0,track,dnph);

	grSimNPH->SetPointError(0,0,sim_nph_err[track]);
	grDataNPH->SetPointError(0,0,sim_nph_err[track]);

	outfile->Add(grSimNPH);
	outfile->Add(grDataNPH);
	outfile->Write();

	delete grSimNPH;
	delete grDataNPH;

	for(int pid=211; pid<=2212; pid+=2001)
	{
		TString particle;
		if(pid==211){ particle = "pion"; } 
		else{ particle = "prot"; }

		// define histograms for reconstructed thetaC
		TH1D *sim_theta = new TH1D("sim_theta","sim_theta",bins,0.6,1);
		TH1D *data_theta = new TH1D("data_theta","data_theta",bins,0.6,1);
		TH1D *sim_theta_bg = new TH1D("sim_theta_bg","sim_theta_bg",bins,0.6,1);
		TH1D *data_theta_bg = new TH1D("data_theta_bg","data_theta_bg",bins,0.6,1);

		// define fit functions
		TString bg_func = "gaus(0)+pol0(3)";
		TString sim_func = getFitFunctionSim(track,pid);
		TString dat_func = getFitFunctionSim(track,pid);
		TF1 *sim_fit  = new TF1("sim_fit",sim_func);
		TF1 *data_fit = new TF1("data_fit",dat_func);
		TF1 *sim_fit_bg  = new TF1("sim_fit_bg",bg_func);
		TF1 *data_fit_bg = new TF1("data_fit_bg",bg_func);

		// find timing peak for data and sim
		// to use for timing cuts
		double sim_time, data_time;
		findPeak(sim_reco,sim_time);
			
		if(track == 75)
			findPeak(data_reco,data_time,track);
		else
			findPeak(data_reco,data_time);	
		
		TString sim_cut = Form("PID==%d && abs(diff-%f)<1",pid,sim_time);
		TString data_cut = Form("PID==%d && abs(diff-%f)<1",pid,data_time);

		//TString sim_cut = Form("PID==%d",pid);
		//TString data_cut = sim_cut;

		// project thetaC onto histograms
		sim_reco->Project("sim_theta",theta,sim_cut);
		sim_reco->Project("sim_theta_bg",theta,sim_cut);
		data_reco->Project("data_theta",theta,data_cut);
		data_reco->Project("data_theta_bg",theta,data_cut);

		// subtract background
		subBackground(sim_reco,sim_theta_bg,data_theta_bg,sim_cut);

		// get range for data and sim
		double loD, hiD, loS, hiS;
		getFitRangeSim(track,pid,loS,hiS);
		//getFitRangeData(track,pid,loD,hiD);
		getFitRangeSim(track,pid,loD,hiD);

		// fit distributions and get SPR and mean
		// simulation
		if(track == 95)
			fitPeak2(sim_theta,sim_fit,loS/1000,hiS/1000,track);
		else
			fitPeak2(sim_theta,sim_fit,loS/1000,hiS/1000);
		double sim_mean     = 1000*sim_fit->GetParameter(1);
		double sim_spr      = 1000*sim_fit->GetParameter(2);
		
		sim_theta->SetTitle(Form("sim #theta_{C} %s reco, %.2f#circ, %s -%.0f +%.0f",particle.Data(),track,sim_func.Data(),loS,hiS));
		formatStats(canv,pavestats,sim_theta,track,sim_mean,sim_spr);
		canv->Print(savepath+Form("thetaC/sim_%s_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

		// simulation bg sub
		double bg_range = 0.06;
		fitPeak(sim_theta_bg,sim_fit_bg,bg_range,track);
		double sim_mean_bg  = 1000*sim_fit_bg->GetParameter(1);
		double sim_spr_bg   = 1000*sim_fit_bg->GetParameter(2);
		
		sim_theta_bg->SetTitle(Form("sim #theta_{C} %s reco bgsub, %.2f#circ",particle.Data(),track));
		formatStats(canv,pavestats,sim_theta_bg,track,sim_mean_bg,sim_spr_bg);
		canv->Print(savepath+Form("thetaC/sim_%s_bg_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

		// data
		fitPeak2(data_theta,data_fit,loD/1000,hiD/1000);
		double data_mean    = 1000*data_fit->GetParameter(1);
		double data_spr     = 1000*data_fit->GetParameter(2);
		
		data_theta->SetTitle(Form("data #theta_{C} %s reco, %.2f#circ, %s -%.0f +%.0f",particle.Data(),track,dat_func.Data(),loD,hiD));
		formatStats(canv,pavestats,data_theta,track,data_mean,data_spr);
		canv->Print(savepath+Form("thetaC/data_%s_%.2f%s.png",particle.Data(),track,thetaSave.Data()));
			

		// data bg sub
		fitPeak(data_theta_bg,data_fit_bg,bg_range,track);
		double data_mean_bg = 1000*data_fit_bg->GetParameter(1);
		double data_spr_bg  = 1000*data_fit_bg->GetParameter(2);
		//double temp_var;
		//findPeak(data_theta_bg,temp_var,temp_var,track);
		data_theta_bg->Draw();
		data_theta_bg->SetTitle(Form("data #theta_{C} %s reco bgsub, %.2f#circ",particle.Data(),track));
		formatStats(canv,pavestats,data_theta_bg,track,data_mean_bg,data_spr_bg);
		canv->Print(savepath+Form("thetaC/data_%s_bg_%.2f%s.png",particle.Data(),track,thetaSave.Data()));

		// graphs
		TGraphErrors *grSimSPR = SetGraph(Form("simSPR_%d",pid),";polar track [#circ];SPR [mrad]",1);
		TGraphErrors *grDataSPR = SetGraph(Form("dataSPR_%d",pid),";polar track [#circ];SPR [mrad]",0);
		TGraphErrors *grSimTHC = SetGraph(Form("simTHC_%d",pid),";polar track [#circ];#theta_{C} [mrad]",1);
		TGraphErrors *grDataTHC = SetGraph(Form("dataTHC_%d",pid),";polar track [#circ];#theta_{C} [mrad]",1);
		
		grSimSPR->SetPoint(0,track,sim_spr_bg);
		grSimSPR->SetPointError(0,0,sim_spr_err[track]);
		
		grDataSPR->SetPoint(0,track,data_spr_bg);
		grDataSPR->SetPointError(0,0,data_spr_err[track]);
		
		grSimTHC->SetPoint(0,track,sim_mean_bg);
		grSimTHC->SetPointError(0,0,sim_thc_err[track]);

		grDataTHC->SetPoint(0,track,data_mean_bg);
		grDataTHC->SetPointError(0,0,data_thc_err[track]);

		outfile->cd();
		grSimSPR->Write();
		grDataSPR->Write();
		grSimTHC->Write();
		grDataTHC->Write();
		
		// clear persistant objects
		canv->Clear();
		pavestats->Clear();

		// clean up pointers
		delete sim_fit;
		delete data_fit;
		delete sim_fit_bg;
		delete data_fit_bg;
		delete sim_theta;
		delete data_theta;
		delete sim_theta_bg;
		delete data_theta_bg;
		delete grSimSPR;
		delete grSimTHC;
		delete grDataSPR;
		delete grDataTHC;
	}

	delete data_dirc;
	delete data_reco;
	delete data_file;
	
	delete sim_dirc;
	delete sim_reco;
	delete sim_file;
}


void dataBGsub( TString datafile )
{
	// get info for data file
	TFile *data   = TFile::Open(datafile);
	TTree *ddTree = data->Get("dirc");
	TTree *drTree = data->Get("reco");

	// set track angle from data
	double angle(0);
	ddTree->SetBranchAddress("theta",&angle);
	ddTree->GetEntry(0);
	cout << angle << endl;
	/*if(fmod(angle,5)>0)
	{ // only have sim for 5 deg steps
		printf("Unable to process %.2f deg track angle\n",angle);
		return;
	}	

	// get info for simulation file
	TString simfile = Form("../simulation/151/reco/reco_3CS_%d_full_spr.root",int(angle));
	TFile *sim = TFile::Open(simfile);
	TTree *srTree = sim->Get("reco");

	// set up histograms and integrals
	double intData(0), intSim(0), scale(0);
	TH1D *hData = new TH1D("hData","hData",200,0.6,1); // data
	TH1D *hSim  = new TH1D("hSim","hSim",200,0.6,1); // sim
	TH1D *hBG   = new TH1D("hBG","hBG",200,0.6,1); // sim bg
	TH1D *hDiff = new TH1D("hDiff","hDiff",200,0.6,1); // data-bg

	drTree->Project("hData","theta","PID>1000");
	srTree->Project("hSim","theta");
	srTree->Project("hBG","theta","nref!=LUTnref || path!=LUTpath");
	
	intData = hData->Integral();
	intSim  = hSim->Integral();
	scale   = intData/intSim;
	hSim->Scale(scale);
	hBG->Scale(scale);
	hDiff->Add(hSim,hBG,1,-1);
	
	TCanvas *c1 = new TCanvas();
	c1->cd();
	hSim->SetLineColor(kRed);
	hSim->SetLineWidth(2);
	hBG->SetLineColor(kGreen);
	hSim->Draw();
	hData->Draw("same");
	hBG->Draw("same");

	TCanvas *c2 = new TCanvas();
	c2->cd();
	hDiff->Draw();*/
}

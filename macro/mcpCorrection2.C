void mcpCorrection2(TString infile = "")
{
	// open uncalibrated file
	TFile *_file0 = TFile::Open(infile);
	TTree *reco = (TTree*)_file0->Get("reco");

	// new file and tree to store calibrated data
	TFile *file = new TFile("calib.root","RECREATE");
	TTree *calib = new TTree("calib","calibrated reconstruction data");

	// make divided canvas for all mcps
	TCanvas *canv = new TCanvas("canv","mcp peaks",900,700);
	gStyle->SetOptStat(0);
	canv->Divide(5,3,0,0);

	// spectrum for peak finding, and fit and hists to store
	TSpectrum *spec = new TSpectrum(1);
	TF1 *fit = new TF1("mcpfit","gaus",0.75,0.875);
	TH1D *mcp[15];

	double shifts[15];
	double angle = 0.8168; // calculated proton angle @ 7 GeV
	double mean(0), const(0);
	
	// calibration tree variables
	int mcpid(0), pixid(0);
	double theta(0), old(0);
	calib->Branch("mcp",&mcpid,"mcpid/I");
	calib->Branch("pix",&pixid,"pixid/I");
	calib->Branch("theta",&theta,"theta/D");
	calib->Branch("old",&old,"old/D");

	reco->SetBranchAddress("mcp",&mcpid);
	reco->SetBranchAddress("pix",&pixid);
	reco->SetBranchAddress("theta",&old);

	// loop over mcps to find shift
	for(int i=0; i<15; i++){
		canv->cd(i+1);

		char *mcpname = Form("mcp%d",i);
		mcp[i] = new TH1D(mcpname,mcpname,40,0.75,0.875);
		reco->Project(mcpname,"theta",Form("mcp==%d",i));

		if(mcp[i]->GetEntries() < 10)
		{
			mcp[i]->Draw();
			continue;
		}

		spec->Search(mcp[i],1,"nodraw");
		mean = spec->GetPositionX()[0];
		fit->SetParameter(1,mean);
		fit->SetParameter(2,0.009);
		mcp[i]->Fit(fit,"Q","",mean-0.018,mean+0.018);
		mcp[i]->Draw();

		shifts[i] = fit->GetParameter(1) - angle;
	}

	// loop over entries in tree
	for(int ientry = 0; ientry < reco->GetEntries(); ientry++)
	{
		reco->GetEntry(ientry);
		
		theta = old + shifts[mcpid];
		calib->Fill();
	}

	file->Write();
}

TString path = "../studies/bgsub/";
TString cutpath = path+"pol3_3/";
TString function = "gaus+pol3(3)";
bool smooth = false;

TFile *save = new TFile(cutpath+"C/plots_bgsub.root","RECREATE");

void SpecSearch(TSpectrum *&spec, TH1D *&hist, TF1 *&fit,
				double &mean, double &con, TString type)
{
	// uses a TSpectrum to find a peak in hist
	// and set mean and multiplicative constant
	int nfound = spec->Search(hist,2,"nodraw",0.9);
	if(nfound)
	{ // if peak found use spectrum peak
		mean = spec->GetPositionX()[0];
		con  = spec->GetPositionY()[0];
	}
	else
	{ // if no peak found use usual method
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		if(mean>0.86) mean = 0.82; // stay within range 
		con  = hist->GetMaximum();
		cout << "*";
	}

	// fit hist
	if(type=="sim") fit->SetParameters(con,mean,0.01,0,0,0,0);
	else fit->SetParameters(con,mean,0.01,con/3,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-0.03,mean+0.03);
}

void dataBGsub( Int_t studyID=151 )
{
	// set ROOT options
	gROOT->SetBatch(1);
	gStyle->SetOptFit(1);
	gStyle->SetLegendBorderSize(0);

	// define paths to data and simulation files
	TString simdir = Form("../simulation/%d/reco/cs/",studyID);
	TString datdir =  Form("../data/%d/reco/cs/",studyID);

	// grab files from dirname
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// graphs and histograms
	TGraph *grSUBsim = new TGraph();
	TGraph *grANGsim = new TGraph();
	TGraph *grSUBdat = new TGraph();
	TGraph *grANGdat = new TGraph();
	TH1D *hDDat, *hDSim, *hBG, *hData, *hSim;

	// loop over all files in dir
	int n(0); // counter dummy variable
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files

		// definee data file and trees
		double track(0), momS(0), momD(0);
		TFile *tfile = TFile::Open(datdir+fname);
		TTree *tdirc = (TTree*)tfile->Get("dirc");
		TTree *treco = (TTree*)tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->SetBranchAddress("beam",&momD);
		tdirc->GetEntry(0);

		// make sure simulation of run exists
		FileStat_t buf;
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		if(gSystem->GetPathInfo(simfile.Data(),buf)) continue;
		if(track==160) continue; // skip bad file
		cout << "Processing " << fname << endl;

		// define simulation file and tree
		TFile *sfile = new TFile(simfile);
		TTree *sreco = (TTree*)sfile->Get("reco");
		TTree *sdirc = (TTree*)sfile->Get("dirc");
		sdirc->SetBranchAddress("beam",&momS);
		sdirc->GetEntry(0);
		momS /= 1000; // scale sim to GeV

		// spectrum and fit
		double con(0), meanS(0), meanD(0), sigmaS(0), sigmaD(0);
		TSpectrum *spec = new TSpectrum(10); // peak finder
		TF1 *gausD = new TF1("gausD",function);
		TF1 *gausS = new TF1("gausS",function);
		
		// get peak of time distribution
		TH1D *diffD  = new TH1D("diffD","diffD",200,-5,5);
		treco->Project("diffD","diff","PID>1000");
		spec->Search(diffD,2,"nodraw",0.9);
		double dpeak = spec->GetPositionX()[0];
		
		// create histograms
		int bins(80);
		double min(0.6), max(1);
		double areaD(0), areaS(0), scale(0);
		hData = new TH1D("hData","hData",bins,min,max);// data
		hSim  = new TH1D("hSim","hSim",bins,min,max);// sim
		hBG   = new TH1D("hBG","hBG",bins,min,max);//bg
		hDDat = new TH1D("hDDat","hDDat",bins,min,max);// diff
		hDSim = new TH1D("hDSim","hDSim",bins,min,max);

		// project onto histograms
		treco->Project("hData","theta",Form("PID>1000 && abs(diff-%f)<1",dpeak));
		sreco->Project("hSim","theta");
		sreco->Project("hBG","theta","path!=LUTpath");
		sreco->Project("hDSim","theta","path==LUTpath");

		// scale background and subtract from data
		areaD = hData->Integral();
		areaS = hSim->Integral();
		scale = areaD/areaS;
		hSim->Scale(scale);
		hBG->Scale(scale);
		if(smooth) hBG->Smooth();
		hDDat->Add(hData,hBG,1,-1);

		// search spectra, find mean, and fit
		SpecSearch(spec, hDSim, gausS, meanS, con, "sim");
		SpecSearch(spec, hDDat, gausD, meanD, con, "data");

		// get fitted sigma and set subtraction graph points
		sigmaS = gausS->GetParameter(2);
		sigmaD = gausD->GetParameter(2);
		grSUBsim->SetPoint(n,track,TMath::Abs(1000*sigmaS));
		grSUBdat->SetPoint(n,track,TMath::Abs(1000*sigmaD));

		// calculate true theta_C and set angle graph points
		double pmass = 0.9382723;
		double tangS = acos(sqrt(momS*momS + pmass*pmass)/momS/1.4738);
		double tangD = acos(sqrt(momD*momD + pmass*pmass)/momD/1.4738);

		meanS = gausS->GetParameter(1);
		meanD = gausD->GetParameter(1);
		grANGsim->SetPoint(n,track,1000*(tangS-meanS));
		grANGdat->SetPoint(n,track,1000*(tangD-meanD));
		
		// print some info about current run
		cout << "track\t" << track << endl;
		cout << "dpeak\t" << dpeak << endl;
		cout << "sigmaS\t" << sigmaS << endl;
		cout << "sigmaD\t" << sigmaD << endl;
		cout << "trueC\t" << tangS << endl;
		cout << "meanS\t" << meanS << endl;
		cout << "meanD\t" << meanD << endl << endl;

		// save histograms
		TCanvas *c_tmp = new TCanvas();
		hDSim->SetTitle(Form("#theta_{C}, %.2f BG sub sim",track));
		hDSim->GetYaxis()->SetRangeUser(0,1.2*hDSim->GetMaximum());
		hDSim->SetFillStyle(3002);
		hDSim->SetFillColor(kBlue);
		hDSim->Draw();
		c_tmp->Print(cutpath+Form("sim_bgsub_%.2f.png",track));

		hDDat->SetTitle(Form("#theta_{C}, %.2f BG sub data",track));
		hDDat->GetYaxis()->SetRangeUser(1.1*hDDat->GetMinimum(),1.2*hDDat->GetMaximum());
		hDDat->SetFillStyle(3002);
		hDDat->SetFillColor(kBlue);
		hDDat->Draw();
		if(smooth)
			c_tmp->Print(cutpath+Form("data_bgsub_smooth_%.2f.png",track));
		else
			c_tmp->Print(cutpath+Form("data_bgsub_%.2f.png",track));
		

		// delete allocated pointers
		// cause memory leaks are bad, m'kay?
		delete spec;
		delete diffD;
		delete gausS;
		delete gausD;
		delete sreco;
		delete sdirc;
		delete treco;
		delete tdirc;
		delete sfile;
		delete tfile;
		delete c_tmp;

		n++;
		//if(n>0) break; // testing
		
	} // end while loop
	
	// sort graphs
	grSUBsim->Sort();
	grSUBdat->Sort();
	grANGsim->Sort();
	grANGdat->Sort();

	/*TCanvas *c2 = new TCanvas(); c2->cd();
	hDDat->Draw();

	TCanvas *c3 = new TCanvas(); c3->cd();
	hDSim->Draw();*/


	// draw subtraction graphs
	TCanvas *c1 = new TCanvas(); c1->cd();
	grSUBsim->GetXaxis()->SetRangeUser(0,180);
	grSUBsim->GetXaxis()->SetTitle("#theta_{track} [deg]");
	grSUBsim->GetYaxis()->SetRangeUser(0,30);
	grSUBsim->GetYaxis()->SetTitle("SPR [mrad] w/ background sub");
	grSUBsim->SetMarkerStyle(20);
	grSUBsim->SetMarkerColor(kBlue);
	grSUBsim->SetTitle("");
	grSUBsim->Draw("APL");

	grSUBdat->SetMarkerStyle(20);
	grSUBdat->SetMarkerColor(kRed);
	grSUBdat->Draw("PL");
	
	// legend for each canvas
	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
	leg->AddEntry(grSUBdat,"beam data", "lp");
	leg->AddEntry(grSUBsim,"simulation", "lp");
	leg->Draw();
	if(smooth)
	{
		c1->Print(cutpath+"angle_vs_SPR_smooth_bgsub.png");
		c1->Print(cutpath+"C/angle_vs_SPR_smooth_bgsub.C");
	}
	else
	{
		c1->Print(cutpath+"angle_vs_SPR_bgsub.png");
		c1->Print(cutpath+"C/angle_vs_SPR_bgsub.C");
	}

	// draw angle diff graphs
	TCanvas *c2 = new TCanvas(); c2->cd();
	grANGsim->GetXaxis()->SetRangeUser(0,180);
	grANGsim->GetXaxis()->SetTitle("#theta_{track} [deg]");
	grANGsim->GetYaxis()->SetRangeUser(-10,20);
	grANGsim->GetYaxis()->SetTitle("calculated - measured #theta_{C} [mrad]");
	grANGsim->SetMarkerStyle(20);
	grANGsim->SetMarkerColor(kBlue);
	grANGsim->SetTitle("");
	grANGsim->Draw("APL");

	grANGdat->SetMarkerStyle(20);
	grANGdat->SetMarkerColor(kRed);
	grANGdat->Draw("PL");
	
	leg->Draw();
	if(smooth)
	{
		c2->Print(cutpath+"angle_vs_thetaCdiff_smooth_bgsub.png");
		c2->Print(cutpath+"C/angle_vs_thetaCdiff_smooth_bgsub.C");
	}
	else
	{
		c2->Print(cutpath+"angle_vs_thetaCdiff_bgsub.png");
		c2->Print(cutpath+"C/angle_vs_thetaCdiff_bgsub.C");
	}

	// save graphs to .root file
	save->cd();
	grSUBsim->Write("grSUBsim");
	grSUBdat->Write("grSUBdat");
	grANGsim->Write("grANGsim");
	grANGdat->Write("grANGdat");
	save->Write();
}

#include "../analysistools.C"

void dataBGsub( int studyID=151,
				int polRank = 1,
				bool bgsub = true,
				int smooth = 0 )
{
	// set ROOT options
	SetStyle();

	TString path = Form("../studies/bgsub%d/",studyID);
	TString cutpath = Form("../studies/bgsub%d/",studyID);
	TString function = Form("gaus+pol%d(3)",polRank);

	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	TString simdir = Form("../simulation/151/reco/cs/");
	TString datdir =  Form("../data/%d/reco/cs/",studyID);

	// grab files from dirname
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// graphs and histograms
	TCanvas *c_tmp = new TCanvas();
	TGraph *grNPHsim = new TGraph();
	TGraph *grSUBsim = new TGraph();
	TGraph *grANGsim = new TGraph();
	TGraph *grNPHdat = new TGraph();
	TGraph *grSUBdat = new TGraph();
	TGraph *grANGdat = new TGraph();
	TH1D *hData, *hSim;

	// loop over all files in dir
	int n(0); // counter dummy variable
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files
		if( fname.Contains("pi+")) continue;

		// definee data file and trees
		double track(0), snph(0), dnph(0);
		double momS(0), momD(0);
		TFile *tfile = TFile::Open(datdir+fname);
		TTree *tdirc = (TTree*)tfile->Get("dirc");
		TTree *treco = (TTree*)tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->SetBranchAddress("beam",&momD);
		tdirc->SetBranchAddress("nph",&dnph);
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
		sdirc->SetBranchAddress("nph",&snph);
		sdirc->GetEntry(0);

		// do stuff with tree entries
		momS /= 1000; // scale sim to GeV
		grNPHsim->SetPoint(n,track,snph);
		grNPHdat->SetPoint(n,track,dnph);

		// spectrum and fit
		double con(0), meanS(0), meanD(0), sigmaS(0), sigmaD(0);
		TSpectrum *spec = new TSpectrum(10); // peak finder
		TF1 *gausD = new TF1("gausD",function);
		TF1 *gausS = new TF1("gausS",function);
		
		// get peak of time distribution
		double dpeak = DiffPeak(treco, "PID>1000");
		
		// create histograms
		int bins(80);
		double min(0.6), max(1);
		double areaD(0), areaS(0), scale(0);
		hData = new TH1D("hData","hData",bins,min,max);// data
		hSim  = new TH1D("hSim","hSim",bins,min,max);// sim

		// project onto histograms
		treco->Project("hData","theta",Form("PID>1000 && abs(diff-%f)<1",dpeak));
		sreco->Project("hSim","theta");

		if(bgsub) BGSub(hSim, hData, sreco, bins, "PID>1000");

		// search spectra, find mean, and fit
		double *simpar = SpecSearch(spec, hSim, gausS);
		double *datpar = SpecSearch(spec, hData, gausD);

		// get fitted sigma and set subtraction graph points
		sigmaS = simpar[2];
		sigmaD = datpar[2];
		grSUBsim->SetPoint(n,track,TMath::Abs(1000*sigmaS));
		grSUBdat->SetPoint(n,track,TMath::Abs(1000*sigmaD));

		// calculate true theta_C and set angle graph points
		double pmass = 0.9382723; // proton mass
		double tangS = acos(sqrt(momS*momS + pmass*pmass)/momS/1.4738);
		double tangD = acos(sqrt(momD*momD + pmass*pmass)/momD/1.4738);

		meanS = simpar[1];
		meanD = datpar[1];
		grANGsim->SetPoint(n,track,1000*(meanS));
		grANGdat->SetPoint(n,track,1000*(meanD));
		
		// print some info about current run
		cout << "track\t" << track << endl;
		cout << "dpeak\t" << dpeak << endl;
		cout << "sigmaS\t" << sigmaS << endl;
		cout << "sigmaD\t" << sigmaD << endl;
		cout << "trueC\t" << tangS << endl;
		cout << "meanS\t" << meanS << endl;
		cout << "meanD\t" << meanD << endl << endl;

		// save histograms
		TString simsave = cutpath + "sim_";
		TString datsave = cutpath + "data_";

		if(bgsub)
		{
			simsave += "bgsub_";
			datsave += "bgsub_";
		}

		if(smooth)
		{
			simsave += "smooth_";
			datsave += "smooth_";
		}
		
		c_tmp->Clear();
		hSim->SetTitle(Form("#theta_{C}, %.2f BG sub sim",track));
		hSim->GetYaxis()->SetRangeUser(0,1.2*hSim->GetMaximum());
		hSim->Draw();
		c_tmp->Print(simsave+Form("%.2f.png",track));

		hData->SetTitle(Form("#theta_{C}, %.2f BG sub data",track));
		hData->GetYaxis()->SetRangeUser(1.1*hData->GetMinimum(),1.2*hData->GetMaximum());
		hData->Draw();
		c_tmp->Print(datsave+Form("%.2f.png",track));
		

		// delete allocated pointers
		// cause memory leaks are bad, m'kay?
		delete spec;
		delete gausS;
		delete gausD;
		delete sreco;
		delete sdirc;
		delete treco;
		delete tdirc;
		delete sfile;
		delete tfile;

		n++;
		//if(n>2) break; // testing
		
	} // end while loop
	
	// sort graphs
	grNPHsim->Sort();
	grNPHdat->Sort();
	grSUBsim->Sort();
	grSUBdat->Sort();
	grANGsim->Sort();
	grANGdat->Sort();

	// define file extension
	TString grsave = "";
	if(bgsub) grsave += "_bgsub";
	if(smooth) grsave += "_smooth";

	// draw subtraction graphs
	TCanvas *c1 = new TCanvas(); c1->cd();
	StyleGraph(grSUBsim, 0, 30, "#theta_{track} [deg]", "SPR [mrad] w/ background sub", 20, kBlue, "grSUBsim", "");
	grSUBsim->Draw("AP");

	StyleGraph(grSUBdat, 0, 30, "#theta_{track} [deg]", "SPR [mrad] w/ background sub", 20, kRed, "grSUBdat", "");
	grSUBdat->Draw("P");
	
	// legend for each canvas
	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
	leg->AddEntry(grSUBdat,"beam data", "lp");
	leg->AddEntry(grSUBsim,"simulation", "lp");
	leg->Draw();
	c1->Print(cutpath+"angle_vs_SPR"+grsave+".png");
	c1->Print(cutpath+"C/angle_vs_SPR"+grsave+".C");

	// draw angle diff graphs
	TCanvas *c2 = new TCanvas(); c2->cd();
	StyleGraph(grANGsim, 810, 830, "#theta_{track} [deg]", "#theta_{C} [mrad]", 20, kBlue, "grANGsim", "");
	grANGsim->Draw("AP");

	StyleGraph(grANGdat, 810, 830, "#theta_{track} [deg]", "#theta_{C} [mrad]", 20, kRed, "grANGdat", "");
	grANGdat->Draw("P");
	
	leg->Draw();
	c2->Print(cutpath+"angle_vs_thetaC"+grsave+".png");
	c2->Print(cutpath+"C/angle_vs_thetaC"+grsave+".C");

	TCanvas *c3 = new TCanvas(); c3->cd();
	StyleGraph(grNPHsim, 0, 120, "#theta_{track} [deg]", "photon yield per track", 20, kBlue, "grNPHsim", "");
	grNPHsim->Draw("AP");

	StyleGraph(grNPHdat, 0, 120, "#theta_{track} [deg]", "photon yield per track", 20, kRed, "grNPHdat", "");
	grNPHdat->Draw("P");

	leg->Draw();
	c3->Print(cutpath+"angle_vs_NPH.png");
	c3->Print(cutpath+"C/angle_vs_NPH.C");
		
    // recreate ROOT outfile and write graphs
	TString outsave = cutpath + "C/plots";
	if(bgsub) outsave += "_bgsub";
	if(smooth) outsave += "_smooth";

	TFile *outfile = new TFile(outsave+".root","RECREATE");
	outfile->Add(grNPHsim);
	outfile->Add(grNPHdat);
	outfile->Add(grSUBsim);
	outfile->Add(grSUBdat);
	outfile->Add(grANGsim);
	outfile->Add(grANGdat);
	outfile->Write();
}

#include "../analysistools.C"
#include <map>

void dataBGsub( int studyID=151,
				int polRank = 1,
				bool bgsub = true,
				double range = 0.03,
				TString subpath = "",
				int smooth = 0 )
{
	// set ROOT options
	SetStyle();

// rounds to nearest 2 decimal points
// x = floor(num*100+0.5)/100;

	int Ntracks = 27;
	double trackArray[] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150};

	double simNphRms[] = {4.75399, 4.24257, 3.80918, 2.90641, 2.93381, 2.62834, 2.49965, 2.13157, 2.08317, 1.69119, 1.96914, 1.12007, 1.07004, 1.27149, 1.68325, 1.00135, 1.1533, 1.41431, 2.28174, 2.13506, 1.79662, 2.31432, 2.45003, 2.80395, 3.10261, 2.70906, 2.94089};

	double simSprRms[] = {1.21764, 0.819654, 0.887126, 0.841177, 1.08473, 1.1831, 1.24323, 0.782515, 1.14815, 1.09383, 1.28786, 0.754463, 1.42482, 1.8524, 0.776857, 1.00929, 0.963242, 0.592127, 1.20926, 1.29103, 1.10608, 1.07536, 1.39913, 1.23385, 0.891853, 0.94846, 0.87744};

	double simThCRms[] = {0.681253, 0.641128, 0.755128, 0.716335, 0.737272, 0.888617, 1.09789, 0.715848, 1.28238, 0.988347, 4.58416, 0.900438, 6.40116, 11.1414, 0.495319, 0.923698, 0.753418, 0.637377, 1.18986, 1.06407, 0.974018, 0.774967, 0.82848, 0.85149, 0.703532, 0.872792, 0.648799};

	double datNphRms[] = {2.57682, 2.90279, 3.68057, 3.16531, 3.42834, 3.45497, 3.30653, 2.94084, 2.34549, 2.58196, 1.88362, 1.91003, 1.77793, 2.12425, 2.13557, 2.33426, 2.26705, 3.12229, 2.72548, 2.44147, 2.84474, 2.42765, 2.9538, 2.38616, 3.30042, 2.78812, 2.52843};

	double datSprRms[] = {3.56994, 0.770208, 1.20776, 0.670966, 1.28239, 1.97487, 1.56307, 1.60339, 1.01395, 1.71102, 1.00396, 1.56715, 1.44186, 3.15248, 1.43943, 1.55113, 1.10648, 0.94553, 1.04546, 0.94569, 0.830281, 0.60792, 0.946363, 0.640244, 0.557258, 0.400557, 0.52546};

	double datThCRms[] = {1.31638, 0.678542, 0.834017, 0.637891, 0.725545, 0.731959, 1.0123, 0.834032, 0.941784, 1.08122, 1.07038, 1.38872, 1.41628, 8.16396, 0.976971, 1.70776, 0.881894, 0.928424, 0.728263, 0.702393, 0.598629, 0.476104, 0.557351, 0.44133, 0.590336, 0.43922, 0.530601};


	map<double,double> simNphMap;
	map<double,double> simSprMap;
	map<double,double> simThCMap;
	map<double,double> datNphMap;
	map<double,double> datSprMap;
	map<double,double> datThCMap;
	//cout << "track[0] " << trackArray[0] << endl;

	for(int i=0; i<Ntracks; i++)
	{
		// fill sim maps
		simNphMap[trackArray[i]] = simNphRms[i];
		simSprMap[trackArray[i]] = simSprRms[i];
		simThCMap[trackArray[i]] = simThCRms[i];

		// fill data maps
		datNphMap[trackArray[i]] = datNphRms[i];
		datSprMap[trackArray[i]] = datSprRms[i];
		datThCMap[trackArray[i]] = datThCRms[i];
	}
	//cout << "simNphMap[0] " << simNphMap[20] << endl;
	//return;


	int bins(120);
	TString path = Form("../studies/bgsub%d/",studyID);
	TString cutpath = Form("../studies/bgsub%d/",studyID);
	cutpath += subpath + "/";
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
	TGraphErrors *grNPHsim = new TGraphErrors();
	TGraphErrors *grSUBsim = new TGraphErrors();
	TGraph *grANGsim = new TGraph();
	TGraphErrors *grNPHdat = new TGraphErrors();
	TGraphErrors *grSUBdat = new TGraphErrors();
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
		//if(track!=120) continue; // testing
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
		grNPHsim->SetPointError(n,0,simNphMap[track]);
		grNPHdat->SetPoint(n,track,dnph);
		grNPHdat->SetPointError(n,0,datNphMap[track]);

		// spectrum and fit
		double con(0), meanS(0), meanD(0), sigmaS(0), sigmaD(0);
		TSpectrum *spec = new TSpectrum(10); // peak finder
		TF1 *gausD = new TF1("gausD",function);
		TF1 *gausS = new TF1("gausS",function);
		
		// get peak of time distribution
		double dpeak = DiffPeak(treco, "PID>1000");
		double speak = DiffPeak(sreco, "PID>1000");
		
		// create histograms
		double min(0.6), max(1);
		double areaD(0), areaS(0), scale(0);
		hData = new TH1D("hData","hData",bins,min,max);// data
		hSim  = new TH1D("hSim","hSim",bins,min,max);// sim

		// project onto histograms
		treco->Project("hData","theta",Form("PID>1000 && abs(diff-%f)<1",dpeak));
		sreco->Project("hSim","theta",Form("PID>1000 && abs(diff-%f)<1",speak));

		if(bgsub) BGSub(hSim, hData, sreco, bins, Form("PID>1000 && abs(diff-%f)<1",speak));

		// search spectra, find mean, and fit
		double *simpar = SpecSearch(spec, hSim, gausS,range);
		double *datpar = SpecSearch(spec, hData, gausD,range);

		// get fitted sigma and set subtraction graph points
		sigmaS = simpar[2];
		sigmaD = datpar[2];
		grSUBsim->SetPoint(n,track,TMath::Abs(1000*sigmaS));
		grSUBsim->SetPointError(n,0,simSprMap[track]);
		grSUBdat->SetPoint(n,track,TMath::Abs(1000*sigmaD));
		grSUBdat->SetPointError(n,0,datSprMap[track]);

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
	StyleGraph(grSUBsim, 0, 30, "#theta_{track} [deg]", "SPR [mrad]", 20, kBlue, "grSUBsim", "");
	grSUBsim->SetLineColor(kBlue);
	grSUBsim->Draw("APL");

	StyleGraph(grSUBdat, 0, 30, "#theta_{track} [deg]", "SPR [mrad]", 20, kRed, "grSUBdat", "");
	grSUBdat->SetLineColor(kRed);
	grSUBdat->Draw("PL");
	
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
	grANGsim->Draw("APL");

	StyleGraph(grANGdat, 810, 830, "#theta_{track} [deg]", "#theta_{C} [mrad]", 20, kRed, "grANGdat", "");
	grANGdat->Draw("PL");
	
	leg->Draw();
	c2->Print(cutpath+"angle_vs_thetaC"+grsave+".png");
	c2->Print(cutpath+"C/angle_vs_thetaC"+grsave+".C");

	TCanvas *c3 = new TCanvas(); c3->cd();
	StyleGraph(grNPHsim, 0, 120, "#theta_{track} [deg]", "photon yield per track", 20, kBlue, "grNPHsim", "");
	grNPHsim->SetLineColor(kBlue);
	grNPHsim->Draw("APL");

	StyleGraph(grNPHdat, 0, 120, "#theta_{track} [deg]", "photon yield per track", 20, kRed, "grNPHdat", "");
	grNPHdat->SetLineColor(kRed);
	grNPHdat->Draw("PL");

	leg->Draw();
	c3->Print(cutpath+"angle_vs_NPH.png");
	c3->Print(cutpath+"C/angle_vs_NPH.C");
		
    // create ROOT outfile and write graphs
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

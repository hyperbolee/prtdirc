#include "../analysistools.C"

void vetoSPR( TString vetocut = "1" , TString vetosave = "" )
{
	// set ROOT options
	SetStyle();

	// variables for later
	int bins = 120;
	double range = 0.03;

	// save path and fit function
	TString path = "../studies/veto/";
	TString cutpath = path+"SPR/";
	TString function = "gaus+pol1(3)";

	// define paths to data and simulation files
	// assumes I'm only looking at 3CS lens
	TString simdir = "../simulation/151/reco/cs/";
	TString datdir = "../studies/veto/root/";

	// grab files from dirname
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// graphs and histograms
	TCanvas *c_tmp = new TCanvas();
	TGraph *grSPRdat = new TGraph();
	TGraph *grSUBdat = new TGraph();
	TH1D *hData, *hDSub, *hSim;

	// loop over all files in dir
	int n(0); // counter dummy variable
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files
		

		// define data file and trees
		double track(0);
		TFile *tfile = TFile::Open(datdir+fname);
		TTree *tdirc = (TTree*)tfile->Get("dirc");
		TTree *treco = (TTree*)tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->GetEntry(0);

		if(track==160) continue; // skip bad file

		// make sure simulation of run exists
		FileStat_t buf;
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		if(gSystem->GetPathInfo(simfile.Data(),buf))
		{
			printf("\nSimulation of %.2f track not found\n",track);
			continue;
		}
		
		cout << "Processing " << fname << endl;

		// define simulation file and tree
		TFile *sfile = new TFile(simfile);
		TTree *sreco = (TTree*)sfile->Get("reco");

		// fits and parameters
		double mean(0), spr(0);
		double meansub(0), sprsub(0);
		TF1 *gausD = new TF1("gausD",function); // data fit
		TF1 *gausS = new TF1("gausS",function); // bgsub fit
		
		// get peak of time distribution
		double dpeak = DiffPeak(treco, "PID>1000");
		double speak = DiffPeak(sreco, "PID>1000");
		
		// create histograms
		double min(0.6), max(1);
		hData = new TH1D("hData","hData",bins,min,max);// data
		hDSub = new TH1D("hDSub","hDSub",bins,min,max);// bgsub data
		hSim  = new TH1D("hSim","hSim",bins,min,max);// sim

		// define cuts
		TString datacut = Form("PID>1000 && abs(diff-%f)<1 && %s",
							   dpeak,vetocut.Data());
		TString simcut  = Form("PID>1000 && abs(diff-%f)<1",speak);

		// project onto histograms
		treco->Project("hData","theta",datacut);
		treco->Project("hDSub","theta",datacut);
		sreco->Project("hSim","theta",simcut);

		// subtract simulation background
		BGSub(hSim, hDSub, sreco, bins, simcut);

		// search spectra, find mean, and fit
		TSpectrum *spec = new TSpectrum(10); // peak finder
		double *datpar = SpecSearch(spec, hData, gausD, range);
		double *subpar = SpecSearch(spec, hDSub, gausS, range);

		// get fitted means and sigmas and set graph points
		mean  = datpar[1]; meansub = subpar[1];
		spr   = datpar[2]; sprsub  = subpar[2];
		grSPRdat->SetPoint(n,track,TMath::Abs(1000*spr));
		grSUBdat->SetPoint(n,track,TMath::Abs(1000*sprsub));
		
		// print some info about current run
		cout << "\ttrack\t" << track << endl;
		cout << "\tpeak\t" << dpeak << endl;
		cout << "\tspr\t" << spr << endl;
		cout << "\tmean\t" << mean << endl << endl;

		// save histograms
		TString datsave = cutpath + "data_";
		TString subsave = datsave + "bgsub_";
		TString save_id = Form("%.2f",track);
		if(vetosave != "") save_id += Form("_%s",vetosave.Data());
		save_id += ".png";

		double hdmax = hData->GetMaximum();
		c_tmp->Clear();
		hData->SetTitle(Form("#theta_{C}, %.2f#circ data, %s",track,vetosave.Data()));
		hData->GetYaxis()->SetRangeUser(0,1.2*hdmax);
		hData->Draw();
		c_tmp->Update();

		// make cleaner stats box
		double y1 = 0.95*hdmax;
		double y2 = 1.25*hdmax;
		TPaveStats *pavestats = new TPaveStats(0.92,y1,1.02,y2);
		pavestats->SetBorderSize(1);
		pavestats->SetFillColor(kWhite);
		pavestats->AddText(Form("data_%.2f",track));
		pavestats->AddText(Form("mean        %.3f",1000*mean));
		pavestats->AddText(Form("SPR           %.3f",1000*spr));
		pavestats->Draw();
		hData->SetStats(0);
		c_tmp->Modified();
		c_tmp->Print(datsave+save_id);

		double hsmax = hDSub->GetMaximum();
		c_tmp->Clear();
		hDSub->SetTitle(Form("#theta_{C}, %.2f#circ BGsub data, %s",track,vetosave.Data()));
		hDSub->GetYaxis()->SetRangeUser(0,1.2*hsmax);
		hDSub->Draw();
		c_tmp->Update();

		double y3 = 0.95*hsmax;
		double y4 = 1.25*hsmax;
		TPaveStats *pavestats2 = new TPaveStats(0.92,y3,1.02,y4);
		pavestats2->SetBorderSize(1);
		pavestats2->SetFillColor(kWhite);
		pavestats2->AddText(Form("bgsub_%.2f",track));
		pavestats2->AddText(Form("mean        %.3f",1000*meansub));
		pavestats2->AddText(Form("SPR           %.3f",1000*sprsub));
		pavestats2->Draw();
		hDSub->SetStats(0);
		c_tmp->Modified();
		c_tmp->Print(subsave+save_id);
	
		

		// delete allocated pointers
		// cause memory leaks are bad, m'kay?
		delete pavestats;
		delete pavestats2;
		delete spec;
		delete gausS;
		delete gausD;
		delete sreco;
		delete treco;
		delete tdirc;
		delete sfile;
		delete tfile;

		n++;
		//if(n>1) break; // testing
		
	} // end while loop
	
	// sort graphs
	grSPRdat->Sort();
	grSUBdat->Sort();

	// draw subtraction graphs
	TCanvas *c1 = new TCanvas(); c1->cd();
	StyleGraph(grSPRdat, 0, 30, "#theta_{track} [deg]", "SPR [mrad]", 20, kBlue, "grSPRdat", "");
	StyleGraph(grSUBdat, 0, 30, "#theta_{track} [deg]", "SPR [mrad]", 20, kRed,  "grSUBdat", "");
	grSPRdat->SetLineColor(kBlue);
	grSUBdat->SetLineColor(kRed);
	grSPRdat->Draw("PL");
	grSUBdat->Draw("PLsame");
	
	// legend for each canvas
	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
	leg->AddEntry(grSPRdat,"beam data", "lp");
	leg->AddEntry(grSUBdat,"bg subtracted", "lp");
	leg->Draw();
	//c1->Print(cutpath+"../SPR.png");
	c1->Print(cutpath+"../SPR.C");
		
    // create ROOT outfile and write graphs

	TFile *outfile = new TFile(cutpath+Form("../SPR_%s.root",vetosave.Data()),"RECREATE");
	outfile->Add(grSPRdat);
	outfile->Add(grSUBdat);
	outfile->Write();
}

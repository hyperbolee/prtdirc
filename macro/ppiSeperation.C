#include "../analysistools.C"

void ppiSeperation()
{
	SetStyle();

	// calculated thetaC values
	double p_calc  = 816.8;
	double pi_calc = 824.9;

	TString datdir  =  "../data/151/reco/cs/";
	TString simdir  = "../simulation/151/reco/cs/";
	TString savedir = "../studies/p-pi_seperation";
	
	// proton graphs
	TGraph *grPCS = new TGraph(); // calc - sim
	TGraph *grPCD = new TGraph(); // calc - data
	TGraph *grPSD = new TGraph(); // sim - data
	TGraph *grPCSbg = new TGraph(); // calc - sim w/ bgsub
	TGraph *grPCDbg = new TGraph(); // calc - data w/ bgsub
	TGraph *grPSDbg = new TGraph(); // sim - data w/ bgsub

	// pi+ graphs
	TGraph *grPiCS = new TGraph(); // calc - sim
	TGraph *grPiCD = new TGraph(); // calc - data
	TGraph *grPiSD = new TGraph(); // sim - data
	TGraph *grPiCSbg = new TGraph(); // calc - sim w/ bgsub
	TGraph *grPiCDbg = new TGraph(); // calc - data w/ bgsub
	TGraph *grPiSDbg = new TGraph(); // sim - data w/ bgsub

	// grab files from dirname
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	files->Sort();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	int n = 0;
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files

		double track(0);
		TFile *tfile = TFile::Open(datdir+fname);
		TTree *tdirc = (TTree*)tfile->Get("dirc");
		TTree *treco = (TTree*)tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->GetEntry(0);
		
		// don't want 160
		if(track == 160)
		{
			delete treco;
			delete tdirc;
			delete tfile;

			continue;
		}

		// check if both proton and pion simulated files exist
		FileStat_t buf;
		TString pfile  = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		TString pifile = simdir+Form("reco_3CS_%.2f_pi+_cs_avr_spr.root",track);

		bool pfile_nf  = gSystem->GetPathInfo(pfile.Data(),buf);
		bool pifile_nf = gSystem->GetPathInfo(pifile.Data(),buf);

		if(pfile_nf || pifile_nf)
		{
			delete treco;
			delete tdirc;
			delete tfile;

			continue;
		}

		cout << "Processing " << fname << endl;
	
		double ppeak = DiffPeak(treco,"PID>1000");
		double pipeak = DiffPeak(treco,"PID<1000");

		// setup ROOT files and TTrees for prot and pi+
		TFile *psimfile = new TFile(pfile);
		TFile *pisimfile = new TFile(pifile);
		TTree *ptree = (TTree*)psimfile->Get("reco");
		TTree *pitree = (TTree*)pisimfile->Get("reco");

		// define histograms for pi+ and proton
		// and project onto them from trees
		TH1D *psim = new TH1D("psim","psim",120,0.6,1);
		TH1D *pisim = new TH1D("pisim","pisim",120,0.6,1);
		TH1D *pdata = new TH1D("pdata","pdata",120,0.6,1);
		TH1D *pidata = new TH1D("pidata","pidata",120,0.6,1);

		ptree->Project("psim","theta","PID>1000");
		pitree->Project("pisim","theta","PID<1000");
		treco->Project("pdata","theta",Form("PID>1000 && abs(diff-%f)<1",ppeak));
		treco->Project("pidata","theta",Form("PID<1000 && abs(diff-%f)<1",pipeak));

		// fit histograms and fill non-bgsub graphs
		TSpectrum *spec = new TSpectrum(10);
		TF1 *fitSP = new TF1("fitSP","gaus+pol1(3)");
		TF1 *fitSPi = new TF1("fitSPi","gaus+pol1(3)");
		TF1 *fitDP = new TF1("fitDP","gaus+pol1(3)");
		TF1 *fitDPi = new TF1("fitDPi","gaus+pol1(3)");

		double spmean  = 1000*SpecSearch(spec,psim,fitSP)[1];
		double spimean = 1000*SpecSearch(spec,pisim,fitSPi)[1];
		double dpmean  = 1000*SpecSearch(spec,pdata,fitDP)[1];
		double dpimean = 1000*SpecSearch(spec,pidata,fitDP)[1];

		// set graph points
		grPCS->SetPoint(n,track,p_calc-spmean);
		grPCD->SetPoint(n,track,p_calc-dpmean);
		grPSD->SetPoint(n,track,spmean-dpmean);
		grPiCS->SetPoint(n,track,pi_calc-spimean);
		grPiCD->SetPoint(n,track,pi_calc-dpimean);
		grPiSD->SetPoint(n,track,spimean-dpimean);
		
		// subtract background and fill graphs
		BGSub(psim,pdata,ptree,120,"PID>1000");
		BGSub(pisim,pidata,pitree,120,"PID<1000");

		spmean  = 1000*SpecSearch(spec,psim,fitSP)[1];
		spimean = 1000*SpecSearch(spec,pisim,fitSPi)[1];
		dpmean  = 1000*SpecSearch(spec,pdata,fitDP)[1];
		dpimean = 1000*SpecSearch(spec,pidata,fitDP)[1];

		// set graph points
		grPCSbg->SetPoint(n,track,p_calc-spmean);
		grPCDbg->SetPoint(n,track,p_calc-dpmean);
		grPSDbg->SetPoint(n,track,spmean-dpmean);
		grPiCSbg->SetPoint(n,track,pi_calc-spimean);
		grPiCDbg->SetPoint(n,track,pi_calc-dpimean);
		grPiSDbg->SetPoint(n,track,spimean-dpimean);

		// free up memory
		delete fitDP;
		delete fitDPi;
		delete fitSP;
		delete fitSPi;
		delete spec;
		delete psim;
		delete pisim;
		delete pdata;
		delete pidata;
		delete ptree;
		delete pitree;
		delete psimfile;
		delete pisimfile;
		delete treco;
		delete tdirc;
		delete tfile;

		n++;
	} // end while(files)

	// sort graphs
	grPCS->Sort(); grPCSbg->Sort();
	grPCD->Sort(); grPCDbg->Sort();
	grPSD->Sort(); grPSDbg->Sort();
	grPiCS->Sort(); grPiCSbg->Sort();
	grPiCD->Sort(); grPiCDbg->Sort();
	grPiSD->Sort(); grPiSDbg->Sort();

	// style graphs
	// (so glad I made a function to do this...
	char *xtitle = "#theta_{track} [#circ]";
	char *ytitle = "#Delta #theta_{C} [mrad]";
	StyleGraph(grPCS,-10,10,xtitle,ytitle);
	StyleGraph(grPiCS,-10,10,xtitle,ytitle,
			   23,kRed);
	StyleGraph(grPCD,-10,10,xtitle,ytitle);
	StyleGraph(grPiCD,-10,10,xtitle,ytitle,
			   23,kRed);
	StyleGraph(grPSD,-10,10,xtitle,ytitle);
	StyleGraph(grPiSD,-10,10,xtitle,ytitle,
			   23,kRed);

	// style bgsub graphs
	StyleGraph(grPCSbg,-10,10,xtitle,ytitle);
	StyleGraph(grPiCSbg,-10,10,xtitle,ytitle,
			   23,kRed);
	StyleGraph(grPCDbg,-10,10,xtitle,ytitle);
	StyleGraph(grPiCDbg,-10,10,xtitle,ytitle,
			   23,kRed);
	StyleGraph(grPSDbg,-10,10,xtitle,ytitle);
	StyleGraph(grPiSDbg,-10,10,xtitle,ytitle,
			   23,kRed);

	// make legend
	TLegend *leg = new TLegend(0.45,0.7,0.74,0.89);
	leg->AddEntry(grPCS,"proton","lp");
	leg->AddEntry(grPiCS,"pi+","lp");
	leg->SetTextSize(0.05);

	// print graphs to files
	TCanvas *canv = new TCanvas();
	grPCS->SetTitle("Calc - Sim");
	grPCS->Draw("APL");
	grPiCS->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/calc_sim.png");

	canv->Clear();
	grPCD->SetTitle("Calc - Data");
	grPCD->Draw("APL");
	grPiCD->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/calc_data.png");
	
	canv->Clear();
	grPSD->SetTitle("Sim - Data");
	grPSD->Draw("APL");
	grPiSD->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/sim_data.png");

	// bgsub graphs
	grPCSbg->SetTitle("Calc - Sim w/ bg sub");
	grPCSbg->Draw("APL");
	grPiCSbg->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/calc_sim_bgsub.png");

	canv->Clear();
	grPCDbg->SetTitle("Calc - Data w/ bg sub");
	grPCDbg->Draw("APL");
	grPiCDbg->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/calc_data_bgsub.png");
	
	canv->Clear();
	grPSDbg->SetTitle("Sim - Data w/ bg sub");
	grPSDbg->Draw("APL");
	grPiSDbg->Draw("PL");
	leg->Draw();
	canv->Print(savedir+"/sim_data_bgsub.png");


}

#include "../analysistools.C"

void binSize()
{
	gROOT->SetBatch(1);
	gStyle->SetOptFit(1);
	gStyle->SetLegendBorderSize(0);

	int studyID = 151;
	int bins[] = {80, 120, 160, 200, 400};
	TString datdir =  Form("../data/%d/reco/cs/",studyID);
	TString simdir = Form("../simulation/%d/reco/cs/",studyID);
	TString savedir = "../studies/binning";

	// grab files from dirname
	TSystemDirectory dir(datdir,datdir);
	TList *files = dir.GetListOfFiles();
	files->Sort();
	TSystemFile *file;
	TString fname;
	TIter next(files);

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
		
		// only want specific files for now
		if(track != 20 &&
		   track != 65 &&
		   track != 90 &&
		   track != 125)
		{
			delete treco;
			delete tdirc;
			delete tfile;

			continue;
		}
		cout << "Processing " << fname << endl;
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		TFile *sfile = new TFile(simfile);
		TTree *sreco = (TTree*)sfile->Get("reco");

		// get diff cut before loop
		TSpectrum *spec = new TSpectrum(10);
		double dpeak = DiffPeak(treco);
		
		for(int b=0; b<5; b++)
		{
			int bin = bins[b];
			cout << "\tbins " << bin << endl;

			TH1D *dat, *sim, *cdat, *csim;
			dat = new TH1D("dat","dat",bin,0.6,1);
			sim = new TH1D("sim","sim",bin,0.6,1);
			cdat = new TH1D("cdat","cdat",bin,0.6,1);
			csim = new TH1D("csim","csim",bin,0.6,1);
			
			sreco->Project("sim","theta","PID>1000");
			sreco->Project("csim","theta","PID>1000");
			treco->Project("dat","theta",Form("PID>1000 && abs(diff-%f)<1",dpeak));
			treco->Project("cdat","theta",Form("PID>1000 && abs(diff-%f)<1",dpeak));

			BGSub(csim,cdat,sreco,bin);

			TF1 *fitsim = new TF1("fitsim","gaus+pol1(3)");
			TF1 *fitdat = new TF1("fitdat","gaus+pol1(3)");
			TF1 *fitcsim = new TF1("fitcsim","gaus+pol1(3)");
			TF1 *fitcdat = new TF1("fitcdat","gaus+pol1(3)");

			SpecSearch(spec,sim,fitsim);
			SpecSearch(spec,csim,fitcsim);
			SpecSearch(spec,dat,fitdat);
			SpecSearch(spec,cdat,fitcdat);
			
			TString name = savedir + "/%s_%.2f_b%d.png";
			TString title = "%s %.2f#circ %d bins";
			TCanvas *c1 = new TCanvas();
			
			sim->SetTitle(Form(title.Data(),"Sim",track,bin));
			sim->Draw();
			c1->Print(Form(name.Data(),"sim",track,bin));

			csim->SetTitle(Form(title.Data(),"Sim BGSub",track,bin));
			csim->Draw();
			c1->Print(Form(name.Data(),"sim_bgsub",track,bin));

			dat->SetTitle(Form(title.Data(),"Data",track,bin));
			dat->Draw();
			c1->Print(Form(name.Data(),"data",track,bin));

			cdat->SetTitle(Form(title.Data(),"Data BGSub",track,bin));
			cdat->Draw();
			c1->Print(Form(name.Data(),"data_bgsub",track,bin));

			delete c1;
			delete fitsim;
			delete fitdat;
			delete fitcsim;
			delete fitcdat;
			delete dat;
			delete cdat;
			delete sim;
			delete csim;
			
		} // end for(bin)

		delete spec;
		delete sreco;
		delete sfile;
		delete treco;
		delete tdirc;
		delete tfile;
		
	} // end while(file)

}

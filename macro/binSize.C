#include "../analysistools.C"

void binSize()
{
	SetStyle();

	int studyID = 151;
	int nbins = 5;
	//int bins[] = {60};
	int bins[] = {80, 100, 120, 140, 160};
	//int bins[] = {80, 120, 160, 200, 400};
	TString datdir =  Form("../data/%d/reco/cs/",studyID);
	TString simdir = Form("../simulation/%d/reco/cs/",studyID);
	TString savedir = "../studies/binning";

	const int ntracks = 1;
	TGraph *grsim[ntracks];
	TGraph *grdat[ntracks];
	TGraph *grsimbg[ntracks];
	TGraph *grdatbg[ntracks];
	for(int i=0; i<ntracks; i++)
	{
		grsim[i] = new TGraph();
		grdat[i] = new TGraph();
		grsimbg[i] = new TGraph();
		grdatbg[i] = new TGraph();
	}

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
		
		// only want specific files for now
		/*if(track != 20 &&
		   track != 65 &&
		   track != 90 &&
		   track != 125)*/
		if(track != 60)
		{
			delete treco;
			delete tdirc;
			delete tfile;

			continue;
		}
		cout << "Processing " << fname << endl;
		cout << "\ttrack: " << track << endl;
		grsim[n]->SetTitle(Form("%.2f",track));
		grdat[n]->SetTitle(Form("%.2f",track));
		grsimbg[n]->SetTitle(Form("%.2f",track));
		grdatbg[n]->SetTitle(Form("%.2f",track));
		TString simfile = simdir+Form("reco_3CS_%.2f_cs_avr_spr.root",track);
		TFile *sfile = new TFile(simfile);
		TTree *sreco = (TTree*)sfile->Get("reco");

		// get diff cut before loop
		TSpectrum *spec = new TSpectrum(10);
		double dpeak = DiffPeak(treco);
		
		for(int b=0; b<nbins; b++)
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

			grsim[n]->SetPoint(b,bin,1000*fitsim->GetParameter(2));
			grdat[n]->SetPoint(b,bin,1000*fitdat->GetParameter(2));
			grsimbg[n]->SetPoint(b,bin,1000*fitcsim->GetParameter(2));
			grdatbg[n]->SetPoint(b,bin,1000*fitcdat->GetParameter(2));

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
		
		n++;
	} // end while(file)

	TCanvas *casim = new TCanvas();
	TCanvas *cadat = new TCanvas();
	TCanvas *casimbg = new TCanvas();
	TCanvas *cadatbg = new TCanvas();
	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);

	int i = 0;
	double min(5), max(15);
	Color_t color[] = {kRed, kBlue, kGreen, kCyan};
	TString grtitle = grsim[i]->GetTitle();

	casim->cd();
	StyleGraph(grsim[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
	grsim[i]->SetTitle("Simulation");
	grsim[i]->Draw("APL");

	cadat->cd();
	StyleGraph(grdat[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
	grdat[i]->SetTitle("Test Beam");
	grdat[i]->Draw("APL");

	casimbg->cd();
	StyleGraph(grsimbg[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
	grsimbg[i]->SetTitle("Simulation BGSub");
	grsimbg[i]->Draw("APL");

	cadatbg->cd();
	StyleGraph(grdatbg[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
	grdatbg[i]->SetTitle("Test Beam BGSub");
	grdatbg[i]->Draw("APL");

	leg->AddEntry(grsim[i],Form("%s#circ",grtitle.Data()),"lp");
	
	for(i=1; i<ntracks; i++)
	{
		grtitle = grsim[i]->GetTitle();
		//grtitle = Form("%.2f",tracks[i]);

		casim->cd();
		StyleGraph(grsim[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
		grsim[i]->Draw("PL");

		cadat->cd();
		StyleGraph(grdat[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
		grdat[i]->Draw("PL");

		casimbg->cd();
		StyleGraph(grsimbg[i],min,max,"SPR [mrad]",
			   "# of bins", 20+i,color[i]);
		grsimbg[i]->Draw("PL");

		cadatbg->cd();
		StyleGraph(grdatbg[i],min,max,"# of bins",
			   "SPR [mrad]", 20+i,color[i]);
		grdatbg[i]->Draw("PL");

		leg->AddEntry(grsim[i],Form("%s#circ",grtitle.Data()),"lp");
	}
	
	casim->cd(); leg->Draw();
	cadat->cd(); leg->Draw();
	casimbg->cd(); leg->Draw();
	cadatbg->cd(); leg->Draw();
	
	casim->Print(Form("%s/bin_vs_SPR_sim.png",savedir.Data()));
	cadat->Print(Form("%s/bin_vs_SPR_data.png",savedir.Data()));
	casimbg->Print(Form("%s/bin_vs_SPR_simbg.png",savedir.Data()));
	cadatbg->Print(Form("%s/bin_vs_SPR_databg.png",savedir.Data()));

	casim->Print(Form("%s/C/bin_vs_SPR_sim.C",savedir.Data()));
	cadat->Print(Form("%s/C/bin_vs_SPR_data.C",savedir.Data()));
	casimbg->Print(Form("%s/C/bin_vs_SPR_simbg.C",savedir.Data()));
	cadatbg->Print(Form("%s/C/bin_vs_SPR_databg.C",savedir.Data()));
}

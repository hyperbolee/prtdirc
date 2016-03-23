void graphSPR(TString dirname, TGraph *&grSPR)
{
	gStyle->SetOptFit(1);
	
	// grab files from dirname
	TSystemDirectory dir(dirname,dirname);
	TList *files = dir.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	// loop over all files in dir
	int n(0); // counter dummy variable
	while( file=(TSystemFile*)next() )
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files
		cout << "Processing " << fname << endl;

		TCanvas *c_tmp = new TCanvas();
		// open root file and assign trees
		int nfound(0);
		double track(0), con(0), mean(0), sigma(0);
		TFile *tfile = TFile::Open(dirname+fname);
		TTree *tdirc = tfile->Get("dirc");
		TTree *treco = tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->GetEntry(0);

		// project reconstruction to histogram
		//TCanvas *c_tmp = new TCanvas();
		//c_tmp->cd();
		TH1D *theta = new TH1D("theta","theta",200,0.6,1);
		treco->Project("theta","theta","PID>1000 && abs(diff)<2");
		theta->SetTitle(Form("#theta_{C} %.2f",track));

		// use TSpectrum to fit reconstruction
		TSpectrum *spec = new TSpectrum(10);
		TF1 *gaus0 = new TF1("gaus0","gaus+[3]");

		// find peak and set parameters of fit
		nfound = spec->Search(theta,2,"nodraw",0.9); // no draw
		if(nfound>0)
		{ // peak found with TSpectrum
			mean = spec->GetPositionX()[0];
			con  = spec->GetPositionY()[0];
		}
		else
		{ // use usual method
			mean = theta->GetBinCenter(theta->GetMaximumBin());
			con  = theta->GetMaximum();
			cout << "*";
		}

		// fit spectrum, get sigma, and fill graph
		gaus0->SetParameters(con,mean,0.01,con/3);
		theta->Fit("gaus0","NQ","",0.75,0.89);//mean-0.03,mean+0.03); //N
		sigma = gaus0->GetParameter(2);
		grSPR->SetPoint(n,track,TMath::Abs(1000*sigma));
		n++;
		theta->DrawCopy();
		gaus0->DrawCopy("same");

		// print useful info
		cout << "track\t" << track << endl;
		cout << "mean\t" << mean << endl;
		cout << "sigma\t" << 1000*sigma << endl << endl;

		// delete allocated pointers
		// memory hog-age is bad, m'kay?
		delete spec;
		delete gaus0;
		delete theta;
		delete treco;
		delete tdirc;
		delete tfile;

		
		if(n>0)break; //testing
	} // end while

	// sort graph before exiting
	grSPR->Sort();

}

void plotSPR(int studyID=151, TString luttype="")
{
	 // define paths to data and simulation files
	TString simdir = Form("../simulation/%d/reco/%s",studyID,luttype.Data());
	TString datdir =  Form("../data/%d/reco/%s",studyID,luttype.Data());
	// define SPR graphs and fill them
	TGraph *grSPRsim = new TGraph();
	TGraph *grSPRdat = new TGraph();
	graphSPR(simdir,grSPRsim);
	graphSPR(datdir,grSPRdat);
	

	// draw
	TCanvas *c1 = new TCanvas();
	grSPRsim->GetXaxis()->SetRangeUser(0,180);
	grSPRsim->GetYaxis()->SetRangeUser(0,30);//1.15*TMath::MaxElement(grSPRsim->GetN(),grSPRsim->GetY()));
	grSPRsim->SetMarkerStyle(20);
	grSPRsim->SetMarkerColor(kBlue);
	grSPRsim->Draw("APL");

	grSPRdat->SetMarkerStyle(20);
	grSPRdat->SetMarkerColor(kRed);
	grSPRdat->Draw("PL");
}

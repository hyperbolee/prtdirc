// plotSPR.C
// 
// macro to plot SPR, photon yield, and
// difference in calculated and measured theta_C
// all as functions of track angle

// whether or not to print histograms to files
bool print = true;
TString path = "../studies/bgsub158/";
TString cutpath = path;//+"pol3_3/";

//TFile *save = new TFile(cutpath+"C/plots.root","RECREATE");

void fillGraphs(TString dirname, TString type, 
				TGraph *&grSPR, TGraph *&grNPH, TGraph *&grANG)
{
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

		// open root file and assign trees
		double nph(0), beam(0), track(0);
		double con(0), mean(0), sigma(0);
		TFile *tfile = TFile::Open(dirname+fname);
		TTree *tdirc = (TTree*)tfile->Get("dirc");
		TTree *treco = (TTree*)tfile->Get("reco");
		tdirc->SetBranchAddress("theta",&track);
		tdirc->SetBranchAddress("beam",&beam);
		tdirc->SetBranchAddress("nph",&nph);
		tdirc->GetEntry(0);

		if(track==160) continue; // bad statistics, skip
		//if(45>track || track>55) continue; // testing odd section

		if(type=="sim") beam /= 1000; // shift sim to GeV
		if(type=="sim" && fmod(atof(Form("%.0f",track)),10)>0) continue;
		double pmass   = 0.9382723;
		double trangle = acos(sqrt(beam*beam + pmass*pmass)/beam/1.4738); // true cherenkov angle
		
		// define spectrum and fit
		TSpectrum *spec = new TSpectrum(10);
				
		// get peak of time distribution
		TH1D *diff  = new TH1D("diff","diff",200,-5,5);
		treco->Project("diff","diff","PID>1000");
		spec->Search(diff,2,"nodraw",0.9);
		double dpeak = spec->GetPositionX()[0];
		
		TH1D *theta = new TH1D("theta","theta",80,0.6,1);
		treco->Project("theta","theta",
					   Form("PID>1000 && abs(diff-%f)<1",dpeak));
		
		theta->SetTitle(Form("%s #theta_{C} %.2f",type.Data(),track));


		// find peak and set parameters of fit
		int nfound = spec->Search(theta,2,"nodraw",0.9); // no draw
		if(nfound>0)
		{ // peak found with TSpectrum
			mean = spec->GetPositionX()[0];
			con  = spec->GetPositionY()[0];
		}
		else
		{ // use usual method
			mean = theta->GetBinCenter(theta->GetMaximumBin());
			if(mean>0.86) mean = 0.82; // stay within range 
			con  = theta->GetMaximum();
			cout << "*";
		}

		// fit spectrum, get sigma, and fill graph
		char *fitOpt = "NQ";
		if(print) fitOpt = "Q";
		TF1 *gaus0 = new TF1("gaus0","gaus+pol1(3)");
		gaus0->SetParameters(con,mean,0.01,con/3,10,10);
		gaus0->SetParName(1,"#theta_{C}");
		gaus0->SetParName(2,"#sigma");
		theta->Fit("gaus0",fitOpt,"",mean-0.03,mean+0.03);
		sigma = gaus0->GetParameter(2);
		grSPR->SetPoint(n,track,TMath::Abs(1000*sigma));
		grNPH->SetPoint(n,track,nph);
		grANG->SetPoint(n,track,1000*(trangle-mean));
		
		// print useful info
		cout << "track\t" << track << endl;
		cout << "nph \t" << nph << endl;
		cout << "tdiff\t" << dpeak << endl;
		cout << "adiff\t" << trangle-mean << endl;
		cout << "mean\t" << mean << endl;
		cout << "sigma\t" << 1000*sigma << endl << endl;


		// draw histograms and save pretty pictures if print set
		if(print) 
		{
			TCanvas *c_tmp = new TCanvas(); c_tmp->cd();
			theta->Draw();
			c_tmp->Print(cutpath+Form("%s_%.2f.png",type.Data(),track));

			if(type=="sim" && false)
			{
				// 1D histogram of wavelength from simulation
				TH1D *lamb = new TH1D("lamb","lamb",600,300,600);

				TTree *thits = (TTree*)tfile->Get("hits");
				thits->Project("lamb","lambda","PID>1000");

				lamb->SetTitle(Form("Wavelength, %.2f #theta_{track}",track));
				lamb->Draw();
				c_tmp->Print(path+Form("sim_wvl_%.2f.png",track));

				
				// set statbox position for 2D histogram
				gStyle->SetStatX(0.9);
				gStyle->SetStatY(0.9);

				// 2D histogram of wavelength vs reconstructed angle
				TH2D *wave = new TH2D("wave","wave",200,0.6,1,600,300,600);
				treco->Project("wave","lambda:theta","PID>1000 && abs(diff)<1");
				wave->SetTitle(Form("%.2f #theta_{C} vs. wavelength",track));
				wave->Draw("colz");
				c_tmp->Print(path+Form("sim_wVt_%.2f.png",track));
				// clean up
				delete lamb;
				delete thits;
				delete wave;

				//reset statbox for 1D histograms
				gStyle->SetStatX(0.98);
				gStyle->SetStatY(0.935);
			}
			
			delete c_tmp;
		
		} // end if(print)

		// delete allocated pointers
		// memory hog-age is bad, m'kay?
		delete spec;
		delete gaus0;
		delete theta;
		delete treco;
		delete tdirc;
		delete tfile;

		n++;
		//if(n>1)break; //testing
	} // end while

	// sort graphs before exiting
	grSPR->Sort();
	grNPH->Sort();
	grANG->Sort();
} // end fillGraphs()

void plotSPR(int studyID=151, TString luttype="cs/")
{
	gStyle->SetOptFit(1);
	gStyle->SetLegendBorderSize(0);
	if(print) gROOT->SetBatch(1);

	// define paths to data and simulation files
	TString simdir = Form("../simulation/151/reco/%s",luttype.Data());
	TString datdir =  Form("../data/%d/reco/%s",studyID,luttype.Data());
	// define SPR graphs and fill them
	TGraph *grSPRsim = new TGraph();
	TGraph *grNPHsim = new TGraph();	
	TGraph *grANGsim = new TGraph();
	TGraph *grSPRdat = new TGraph();
	TGraph *grNPHdat = new TGraph();
	TGraph *grANGdat = new TGraph();

	fillGraphs(simdir,"sim",grSPRsim,grNPHsim,grANGsim);
	fillGraphs(datdir,"data",grSPRdat,grNPHdat,grANGdat);
	//cout << "grSPRsim: "; grSPRsim->Print();
	//cout << "grANGsim: "; grANGsim->Print();
	//cout << "grNPHsim: "; grNPHsim->Print();
	
	// draw SPR graphs
	TCanvas *c1 = new TCanvas("c1","c1",700,500); c1->cd();
	//grSPRsim->GetXaxis()->SetRangeUser(0,180);
	grSPRsim->GetXaxis()->SetTitle("#theta_{track} [deg]");
	grSPRsim->GetYaxis()->SetRangeUser(0,30);
	grSPRsim->GetYaxis()->SetTitle("SPR [mrad]");
	grSPRsim->SetMarkerStyle(20);
	grSPRsim->SetMarkerColor(kBlue);
	grSPRsim->SetTitle("");
	grSPRsim->Draw("APL");

	grSPRdat->SetMarkerStyle(20);
	grSPRdat->SetMarkerColor(kRed);
	grSPRdat->Draw("PL");

	// legend for each canvas
	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
	leg->AddEntry(grSPRdat,"beam data", "lp");
	leg->AddEntry(grSPRsim,"simulation", "lp");
	leg->Draw();
	if(print) c1->Print(cutpath+"angle_vs_SPR.png");
	if(print) c1->Print(cutpath+"C/angle_vs_SPR.C");

	// draw photon yield graphs
	TCanvas *c2 = new TCanvas(); c2->cd();
	grNPHsim->GetXaxis()->SetRangeUser(0,180);
	grNPHsim->GetXaxis()->SetTitle("#theta_{track} [deg]");
	grNPHsim->GetYaxis()->SetRangeUser(0,130);
	grNPHsim->GetYaxis()->SetTitle("photon yield per event");
	grNPHsim->SetMarkerStyle(20);
	grNPHsim->SetMarkerColor(kBlue);
	grNPHsim->SetTitle("");
	grNPHsim->Draw("APL");

	grNPHdat->SetMarkerStyle(20);
	grNPHdat->SetMarkerColor(kRed);
	grNPHdat->Draw("PL");

	leg->Draw();
	if(print) c2->Print(path+"angle_vs_nph.png");
	if(print) c2->Print(path+"C/angle_vs_nph.C");

	// draw angle difference graphs
	TCanvas *c3 = new TCanvas(); c3->cd();
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
	if(print) c3->Print(cutpath+"angle_vs_thetaCdiff.png");
	if(print) c3->Print(cutpath+"C/angle_vs_thetaCdiff.C");
	
	// save graphs to .root file
	/*save->cd();
	grSPRsim->Write("grSUBsim");
	grSPRdat->Write("grSUBdat");
	grANGsim->Write("grANGsim");
	grANGdat->Write("grANGdat");
	save->Write();*/

} // end plotSPR.C


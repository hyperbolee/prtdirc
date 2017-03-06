// Difference of two functions to find intersection
TF1 *pFit;
TF1 *piFit;
double intersect(double *x, double*par) {
   return TMath::Abs(pFit->EvalPar(x,par) - piFit->EvalPar(x,par));
}

void plot_sepPower( TString dir = "", int study = 151, bool simulation = 1 )
{
	gErrorIgnoreLevel = kWarning; // ignore 'Info in..' messages

	// set string for data vs sim
	TString saveString;
	if(simulation) saveString = "sim";
	else saveString = "data";

	// save directory
	TString saveDIR = Form("../studies/sep_power/%d",study);

	// chain of all files in directory to plot separation power
	TChain *chDIRC = new TChain("dirc");
	chDIRC->Add(dir+"/reco_*.root");

	TCanvas *canv = new TCanvas();
	int n = chDIRC->Draw("separation:theta","theta<160");
	if(n==0 && false)
	{
		cout << "No reco files found in dir=" << dir.Data() << endl;
		cout << "Exiting" << endl;
		return;
	}

	// everything looks good
	// make TGraph and sort
	TGraph *grSEP = new TGraph(n,chDIRC->GetV2(),chDIRC->GetV1());
	grSEP->Sort();
	grSEP->SetMarkerStyle(20);
	grSEP->SetMarkerSize(0.7);
	grSEP->SetMarkerColor(kRed);
	grSEP->SetName("separation_power");
	//grSEP->Draw("lp");

	TSystemDirectory directory(dir,dir);
	TList *files = directory.GetListOfFiles();
	TSystemFile *file;
	TString fname;
	TIter next(files);

	TFile *data_file;
	TTree *data_tree;
	TH1D *pSep;
	TH1D *piSep;
	TGraph *pGID = new TGraph(); // good PID on proton
	TGraph *pBID = new TGraph(); // protons as pions
	TGraph *piGID = new TGraph(); // good PID on pions
	TGraph *piBID = new TGraph(); // pions as protons
	canv->Clear();
	
	// loop over each root file in directory
	// and extract nph, spr, and mean thetaC
	// for both data and sim w/ and w/o bgsub
	int count(0); // counter
	while( file=(TSystemFile*)next())
	{
		fname = file->GetName();
		if( file->IsDirectory() || !fname.EndsWith(".root") )
			continue; // don't process directories or non-root files

		data_file = TFile::Open(dir+fname);
		data_tree = (TTree*)data_file->Get("dirc");
		pSep = (TH1D*)data_file->Get("Psep");
		piSep = (TH1D*)data_file->Get("Pisep");

		double theta(0);
		data_tree->SetBranchAddress("theta",&theta);
		data_tree->GetEntry(0);

		pFit = pSep->GetFunction("gaus");
		piFit = piSep->GetFunction("gaus");
		pFit->SetLineColor(kMagenta+2);
		piFit->SetLineColor(kMagenta);
		TF1 *diff = new TF1("diff",intersect,-30,30,0);

		double xlo = TMath::Min(pFit->GetParameter(1),piFit->GetParameter(1));
		double xhi = TMath::Max(pFit->GetParameter(1),piFit->GetParameter(1));
		double xint = diff->GetMinimumX(xlo,xhi);

		TMarker *mark = new TMarker(xint,pFit->Eval(xint),24);
		mark->SetMarkerColor(kBlack);
		mark->SetMarkerSize(3);

		// if(theta==75)
		// {
		// 	cout << "xlo [" << xlo << "]" << endl;
		// 	cout << "xhi [" << xhi << "]" << endl;
		// 	cout << "xmin [" << xint << "]" << endl;
		// 	cout << "p integral [" << pFit->Integral(-30,60) << "]" << endl;
		// 	cout << "p tail [" << pFit->Integral(xint,60) << "]" << endl;
		// 	cout << "pi integral [" << piFit->Integral(-30,60) << "]" << endl;
		// 	cout << "pi tail [" << piFit->Integral(-30,xint) << "]" << endl;
			
		// }

		pSep->Draw();
		piSep->Draw("same");
		pFit->Draw("same");
		piFit->Draw("same");;
		mark->Draw();
		canv->Print(saveDIR+Form("/ppi_sep_%.2f.png",theta));

		double badIDp = pFit->Integral(xint,60)/pFit->Integral(-30,60);
		double badIDpi = piFit->Integral(-30,xint)/piFit->Integral(-30,60);
		double goodIDp = 1 - badIDp;
		double goodIDpi = 1 - badIDpi;

		pBID->SetPoint(count,theta,badIDp);
		pGID->SetPoint(count,theta,goodIDp);
		piBID->SetPoint(count,theta,badIDpi);
		piGID->SetPoint(count,theta,goodIDpi);
		
		data_file->Clear();
		pSep->Clear();
		pFit->Clear();
		piSep->Clear();
		piFit->Clear();
		canv->Clear();
		
		count++;
		//if(count>0) break;
	}

	// sort
	pBID->Sort();
	pGID->Sort();
	piBID->Sort();
	piGID->Sort();

	pBID->SetName("PasPi");
	pGID->SetName("PasP");
	piBID->SetName("PiasP");
	piGID->SetName("PiasPi");
	
	TFile *outfile = new TFile(saveDIR+"/PID.root","recreate");
	outfile->Add(pBID);
	outfile->Add(pGID);
	outfile->Add(piBID);
	outfile->Add(piGID);
	outfile->Add(grSEP);
	outfile->Write();
}

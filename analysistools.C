//  analysistools.C
//  Functions that are used in multiple
//  places in my analysis code to reduce redundancy
//
//  Author: Lee Allison, Apr.29.2016

/*
 Subtracts simulated background from
 given histogram of data
*/
void BGSub(TH1D *&sim, TH1D *&dat, TTree *&tree, int bins)
{   // scale simulation integral to data
	double areaS = sim->Integral();
	double areaD = dat->Integral();
	double scale = areaD/areaS;

	// get simulated background
	TH1D *bg = new TH1D("bg","bg",bins,0.6,1);
	tree->Project("bg","theta","PID>1000 && path!=LUTpath");
	sim->Scale(scale);
	bg->Scale(scale);

	// subtract background and style
	sim->Add(bg,-1);
	dat->Add(bg,-1);
	dat->SetFillStyle(3002);
	dat->SetFillColor(kBlue);

	// free pointer
	delete bg;
} // end BGSub()

/*
  Finds peak in timing difference spectrum
*/
double DiffPeak(TTree *&tree)
{
	TSpectrum *spec = new TSpectrum(10); // peak finder
	TH1D *diff = new TH1D("diff","diff",200,-5,5);

	tree->Project("diff","diff","PID>1000");
	spec->Search(diff,2,"nodraw",0.9);
	double diffpeak = spec->GetPositionX()[0];

	delete diff;
	delete spec;

	return diffpeak;
} // end DiffPeak()

double* SpecSearch(TSpectrum *&spec, TH1D *&hist, TF1 *&fit)
{
    // uses a TSpectrum to find a peak in hist
	// and set mean and multiplicative constant
	double con(0), mean(0), sigma(0);
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
	}

	// fit hist
	double height = hist->GetBinCenter(20);
	fit->SetParameters(con,mean,0.01,height,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-0.03,mean+0.03);
	
	con = fit->GetParameter(0);
	mean = fit->GetParameter(1);
	sigma = fit->GetParameter(2);
	double parms[] = {con, mean, sigma};

	return parms;
}

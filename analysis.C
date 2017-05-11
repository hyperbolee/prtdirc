// restructuring analysistools.C to be
// more streamlined and useful for after
// modifying analysis scripts

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "../prttools/prttools.C"

/*
  Use a TSpectrum to find the peak in a
  histogram distribution and save the (x,y)
  position of the peak in passed parameters
*/
int findPeak(TH1D *&hist, double &mean, double &ampl, double track = -1)
{
	TSpectrum *spec = new TSpectrum(3);
	int nfound; // some spectra are weird

	// work around to find peak for 50,90,and 100 deg
	// tracks in data for 151 since they are hard
	// to find in the background subtracted spectra
	if(track==95)
		nfound = spec->Search(hist,1,"nobackground nodraw",0.9);

	else if(track==50 || track==100)
		nfound = spec->Search(hist,0.5,"nodraw",0.6);

	else
		nfound = spec->Search(hist,2,"nobackground nodraw",0.6);
	
	// if no peaks found exit
	if(nfound < 1)
	{
		delete spec;
		return 0;
	}

	// define mean and amplitude of peak
	mean = spec->GetPositionX()[0];
	ampl = spec->GetPositionY()[0];

	// work around for 85 degree track
	// with second peak in timing
	// spectrum (very annoying...)
	if(track == 85 && nfound > 1)
	{
		mean = spec->GetPositionX()[1];
		ampl = spec->GetPositionY()[1];
	}
	
	delete spec;
	return nfound;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Find peak for time difference distribution from tree
  Default to protons
*/
int findPeak(TTree *&tree, double &mean, double track = -1, int PID = 2212)
{
	double dummy; // dummy variable for amplitude

	// make time diff histogram and project
	TH1D *diff = new TH1D("diff","diff",200,-5,5);
	tree->Project("diff","diff");
	//tree->Project("diff","diff",Form("PID==%d",PID));
	
	int nfound = findPeak(diff,mean,dummy,track);

	// for some cases none or multiple peaks are found
	// in these cases just assume mean is at zero
	if(nfound == 0 || abs(mean)>1 && track!=75 ) mean = 0;

	delete diff;
	return nfound;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Use findPeak to find a peak in reconstructed
  theta_C distribution and with with a given fit
  function (gaussian + some order polynomial)
  Returns 0 if no peak found, or
  1 if fitting was successful
*/
int fitPeak(TH1D *&hist, TF1 *&fit, const double range = 0.03, double track = -1)
{
	double mean(0), ampl(0);
	int nfound = findPeak(hist, mean, ampl,track);

	if(nfound < 1 && abs(track-115)<1)
	{
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		ampl = hist->GetMaximum();
	}
	else if(nfound<1)
		return 0;
	
	// rough estimate for constant term
	double shift = hist->GetBinCenter(20);
	
	// set initial parameters and fit histogram
	// set parameters for up to x^3
	fit->SetParameters(ampl,mean,0.01,shift,10,0,0);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-range,mean+range);

	//std::cout << "fit mean: " << 1000*fit->GetParameter(1) << " mrad" << std::endl;
	//std::cout << "fit spr : " << 1000*fit->GetParameter(2) << " mrad" << std::endl << std::endl;

	return 1;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Use findPeak to find a peak in reconstructed
  theta_C distribution and with with a given fit
  function (gaussian + some order polynomial)
  Returns 0 if no peak found, or
  1 if fitting was successful
*/
int fitPeak2(TH1D *&hist, TF1 *&fit, double lo = 0.03, double hi = 0.03, double track = -1)
{
	double mean(0), ampl(0);
	int nfound = findPeak(hist, mean, ampl,track);

	if(nfound < 1 && abs(track-115)<1)
	{
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		ampl = hist->GetMaximum();
	}
	else if(nfound<1)
		return 0;
	
	// rough estimate for constant term
	double shift = hist->GetBinCenter(20);
	
	// set initial parameters and fit histogram
	// set parameters for up to x^3
	fit->SetParameters(ampl,mean,0.01,shift,10,1,1);
	fit->SetParName(1,"#theta_{C}");
	fit->SetParName(2,"#sigma");
	hist->Fit(fit->GetName(),"Q","",mean-lo,mean+hi);

	return 1;
}
//----------------------------------------------------------------
//----------------------------------------------------------------



/*
  Correct thetaC mean per MCP during reconstruction
  by replacing the "theta" branch of the reconstruction
  tree with a new TBranch with the corrected values.
  Values are corrected by looping over each MCP, fitting
  the thetaC distribution, and calculating a shift based
  on the difference b/w fitted mean and trueangle, values
  are stored in an array and used to shift the thetaC
  value from the original theta branch and store in the 
  new branch entry by entry
*/
void mcpCorrection(TTree *&tree, double momentum, double track)
{
	// electron, muon, pion, kaon, proton
	double mass[] = {0.000511,0.1056584,0.139570,0.49368,0.9382723};
	double angleP  = acos(sqrt(momentum*momentum+ mass[4]*mass[4])/momentum/1.4738)-0.002;
	double anglePi = acos(sqrt(momentum*momentum + mass[2]*mass[2])/momentum/1.4738)-0.002;
	
	double shift[2][15] = {0}; // shift for each MCP per particle (0==prot, 1==pion)
	

	// histogram for projecting from tree and fitting
	TH1D *mcpHist = new TH1D("mcpHist","mcpHist",40,0.75,0.85);

	// loop over pions and protons
	for(int pid = 211; pid<=2212; pid+=2001)
	{
		// get expected angle for given PID
		double trueang = (pid>1000) ? angleP : anglePi;
		
		// get timing peak
		double timediff;
		findPeak(tree,timediff);

		// get entries within timing window
		int cutEntries = tree->GetEntries(Form("abs(diff-%f)<1 && PID==%d",timediff,pid));

		// loop over mcps
		for(int mcp = 0; mcp<15; mcp++)
		{
			mcpHist->Reset(); // so I don't have to make a new one for each iteration

			// entries in this MCP
			int mcpEntries = tree->Project("mcpHist","thetaOld",Form("PID==%d && abs(diff-%f)<1 && mcp==%d",pid,timediff,mcp));

			// if < 5% of all events are in this MCP skip it
			// too few to fit/shift
			if(double(mcpEntries)/cutEntries<0.05) continue;

			// make fit for mcphist
			TF1 *mcpFit = new TF1("mcpFit","gaus+pol0(3)");
			int peaks = fitPeak(mcpHist,mcpFit);

			// if no peaks found in fitting skip
			if(peaks<1){ delete mcpFit; continue;}
			if(peaks>1){ std::cout << Form("track %.2f, mcp %d: %d peaks\n", track, mcp, peaks); }

			// peak found, get angle difference and store in shift
			// pid%2 == 0 for prot, 1 for pion
			double mcpPeak = mcpFit->GetParameter(1);
			shift[pid%2][mcp] = mcpPeak - trueang;

			std::cout << Form("pid: %d, mcp: %d, shift: %f",pid,mcp,shift[pid%2][mcp]) << std::endl;

			delete mcpFit;
		}
	}

	delete mcpHist;

	// Now loop over all entries in tree and replace branch

	int pid(0), mcp(0); // for storing pid/mcp info from tree
	double theta(0), thetaOld(0); // for getting value from tree
	int entries = tree->GetEntries(); // all entries

	// set branch addresses
	tree->SetBranchAddress("PID",&pid);
	tree->SetBranchAddress("mcp",&mcp);
	tree->SetBranchAddress("thetaOld",&thetaOld);
	
	// new theta branch to add to tree
	TBranch *thetaCorr = tree->Branch("theta",&theta,"theta/D");

	std::cout << "filling new thetaC branch" << std::endl;
	for(int entry=0; entry<entries; entry++)
	{
		// get values and 
		tree->GetEntry(entry);
		theta = thetaOld - shift[pid%2][mcp];
		
		thetaCorr->Fill();
	}
	
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  After MCP correction we also need to do a correction to
  the log likelihood histograms
*/
void llCorrection(TTree *&tree,
				  TH1F *&lnProt, TF1 *&fProt,
				  TH1F *&lnPion, TF1 *&fPion)
{

	std::cout << "filling new log liklihood plots" << std::endl;
	
	// clear the histograms
	lnProt->Reset();
	lnPion->Reset();
	
	int pid(0), oldPid(0), event(0), oldEvent(0);
	int entries = tree->GetEntries();
	double theta(0), noise(0.3);
	double sum(0), sum1(0), sum2(0);

	tree->SetBranchAddress("PID",&pid);
	tree->SetBranchAddress("event",&event);
	tree->SetBranchAddress("theta",&theta);

	tree->GetEntry(0);
	oldEvent = event;
	oldPid   = pid;

	for(int i=0; i<entries; i++)
	{
		tree->GetEntry(i);

		// fill histograms and reset variables
		// when reaching end of each event
		if(event!=oldEvent)
		{
			sum = sum1 - sum2;
			if(sum!=0)
			{
				if(oldPid==211)  lnPion->Fill(sum);
				if(oldPid==2212) lnProt->Fill(sum);
			}
				
			sum1 = 0;
			sum2 = 0;
			oldEvent = event;
			oldPid   = pid;
		}

		// evaluate theta for both functions
		if(theta>0.4 && theta<0.9)
		{
			double f1 = fProt->Eval(theta);
			double f2 = fPion->Eval(theta);

			sum1 += -TMath::Log(f1+noise);
			sum2 += -TMath::Log(f2+noise);
		}

		// need to fill at end of final entry too
		if(i==entries-1)
		{
			sum = sum1 - sum2;
			if(sum!=0)
			{
				if(pid==211)  lnPion->Fill(sum);
				if(pid==2212) lnProt->Fill(sum);
			}
		}
		
	} // end entries loop
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Normalize data to simulation and
  subtract simulated background
  from prism ambiguities
*/
void subBackground(TTree *&tree, TH1D *& sim,
				   TH1D *&data, TString cut)
{
	// histogram of simulated
	// comibnatorial background
	TH1D *bg = new TH1D("bg","bg",120,0.6,1);
	tree->Project("bg","theta",Form("%s && path!=LUTpath",cut.Data()));
	
	// get normalization constant
	// between sim and data (scale)
	double sim_area  = sim->Integral();
	double data_area = data->Integral();
	double scale     = data_area/sim_area;

	// scale simulation and background
	sim->Scale(scale);
	bg->Scale(scale);

	// subtract background from data and simulation
	sim->Add(bg,-1);
	data->Add(bg,-1);

	// to make clear in plots that background was
	// subtracted, add fill to histograms
	sim->SetFillStyle(3002);
	sim->SetFillColor(kBlue);

	data->SetFillStyle(3002);
	data->SetFillColor(kBlue);

	delete bg;
	return;
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Format the stats box of a given histogram to be
  22% x 18% of the total pad area in the upper 
  right corner of the canvas with information
  about the fitted mean and SPR of the histogram
*/
void formatStats(TCanvas *&canv, TPaveStats *&pavestats, TH1D *&hist,
				 double track, double mean, double spr)
{
	// clean up  pavestats
	pavestats->Clear();
	
	// define bounds of stats box
	// numbers are percentage of full pad
	double x1 = 0.73;  pavestats->SetX1NDC(x1); // left
	double x2 = 0.95;  pavestats->SetX2NDC(x2); // right
	double y1 = 0.77;  pavestats->SetY1NDC(y1); // bottom
	double y2 = 0.95;  pavestats->SetY2NDC(y2); // top

	pavestats->AddText(Form("%.2f#circ track",track));
	pavestats->AddText(Form("mean = %.3f mrad",mean));
	pavestats->AddText(Form("SPR = %.3f mrad",spr));
	pavestats->SetTextSize(0.03);

	// remove default stats and draw new stats box
	hist->SetStats(0);
	pavestats->Draw();
	canv->Modified();

	return;
}
//----------------------------------------------------------------
//----------------------------------------------------------------


/*
  Returns fit function appropriate for the given track angle
  and particle species for beam data

  Functions to return are gaussian plus a polynomial of
  rank 0, 1, or 2
*/
TString getFitFunctionData(double track, int PID, int type = 0)
{
	switch(PID)
	{
	case 211 : // pions
		if(track == 55 ||
		   track == 65 ||
		   track == 75 ||
		   track == 80 ||
		   track == 90 ||
		   track == 105 ||
		   track == 110 ||
		   track == 115 ||
		   track == 120 ||
		   track == 125 ||
		   track == 140 ||
		   track == 145 )
			return "gaus(0)+pol0(3)";

		break;

	case 2212 : // protons
		if(track == 25 ||
		   track == 40 ||
		   track == 55 ||
		   track == 75 ||
		   track == 105 ||
		   track == 110 ||
		   track == 120 ||
		   track == 135 ||
		   track == 140 ||
		   track == 145 )
			return "gaus(0)+pol0(3)";
		
		else if(track == 150)
			return "gaus(0)+pol2(3)";

		break;
		
	}

	// linear background default
	return "gaus(0)+pol1(3)";
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Sets range of fit function appropriate for the given 
  track angle and particle species for beam data

  lo == milliradians below median of fit
  hi == milliradians above median of fit
*/
void getFitRangeData(double track, int PID, double &lo, double &hi)
{
	switch(PID)
	{
	case 211 : // pions
		if(track == 75 ||
		   track == 110 ||
		   track == 140 ||
		   track == 150 )
		{
			lo = 20;
			hi = 20;
		}
		
		if(track == 55 ||
		   track == 65 ||
		   track == 70 ||
		   track == 80 ||
		   track == 85 ||
		   track == 90 ||
		   track == 105 ||
		   track == 115 ||
		   track == 145 )
		{
			lo = 25;
			hi = 25;
		}

		if(track == 20 ||
		   track == 25 ||
		   track == 45 ||
		   track == 50 ||
		   track == 60 ||
		   track == 95 ||
		   track == 100 )
		{
			lo = 30;
			hi = 30;
		}

		if(track == 125)
		{
			lo = 40;
			hi = 40;
		}

		if(track == 30)
		{
			lo = 40;
			hi = 30;
		}

		if(track == 35)
		{
			lo = 30;
			hi = 40;
		}

		if(track == 40)
		{
			lo = 30;
			hi = 25;
		}

		if(track == 120)
		{
			lo = 30;
			hi = 35;
		}

		if(track == 130)
		{
			lo = 25;
			hi = 20;
		}

		if(track == 135)
		{
			lo = 40;
			hi = 25;
		}
		
		break;
		
	case 2212 : // protons
		if(track == 20 ||
		   track == 105 )
		{
			lo = 20;
			hi = 20;
		}

		if(track == 55 ||
		   track == 60 ||
		   track == 110 ||
		   track == 130 )
		{
			lo = 25;
			hi = 25;
		}
		
		if(track == 30 ||
		   track == 50 ||
		   track == 65 ||
		   track == 70 ||
		   track == 75 ||
		   track == 80 ||
		   track == 90 ||
		   track == 95 ||
		   track == 115 )
		{
			lo = 30;
			hi = 30;
		}

		if(track == 85 ||
		   track == 100 )
		{
			lo = 40;
			hi = 40;
		}

		if(track == 35 ||
		   track == 40 ||
		   track == 45 )
		{
			lo = 50;
			hi = 50;
		}

		if(track == 25)
		{
			lo = 20;
			hi = 30;
		}

		if(track == 120)
		{
			lo = 25;
			hi = 20;
		}

		if(track == 125)
		{
			lo = 40;
			hi = 25;
		}

		if(track == 135)
		{
			lo = 25;
			hi = 30;
		}

		if(track == 140)
		{
			lo = 45;
			hi = 30;
		}

		if(track == 145)
		{
			lo = 45;
			hi = 35;
		}

		if(track == 150)
		{
			lo = 45;
			hi = 40;
		}

		break;
		
	}
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Returns fit function appropriate for the given track angle
  and particle species for beam data

  Functions to return are gaussian plus a polynomial of
  rank 0, 1, or 2
*/
TString getFitFunctionSim(double track, int PID, int type = 0)
{
	switch(PID)
	{
	case 211 : // pions
		if(track == 25 ||
		   track == 45 ||
		   track == 125 ||
		   track == 135 ||
		   track == 140 ||
		   track == 145 )
			return "gaus(0)+pol0(3)";

		if(track == 20 ||
		   track == 30 ||
		   track == 40 ||
		   track == 50 ||
		   track == 55 ||
		   track == 60 ||
		   track == 70 ||
		   track == 75 ||
		   track == 80 ||
		   track == 85 ||
		   track == 90 ||
		   track == 95 ||
		   track == 100 ||
		   track == 105 ||
		   track == 110 ||
		   track == 120 ||
		   track == 130 ||
		   track == 150  )
			return "gaus(0)+pol2(3)";

		break;

	case 2212 : // protons
		if(track == 45 ||
		   track == 55 ||
		   track == 115 ||
		   track == 135 ||
		   track == 145  )
			return "gaus(0)+pol0(3)";
		
		if(track == 20 ||
		   track == 25 ||
		   track == 40 ||
		   track == 50 ||
		   track == 60 ||
		   track == 65 ||
		   track == 70 ||
		   track == 75 ||
		   track == 80 ||
		   track == 85 ||
		   track == 90 ||
		   track == 95 ||
		   track == 100 ||
		   track == 110 ||
		   track == 120 ||
		   track == 125 ||
		   track == 130 ||
		   track == 140 ||
		   track == 150 )
			return "gaus(0)+pol2(3)";

		break;
		
	}

	// linear background default
	return "gaus(0)+pol1(3)";
}
//----------------------------------------------------------------
//----------------------------------------------------------------

/*
  Sets range of fit function appropriate for the given 
  track angle and particle species for beam data

  lo == milliradians below median of fit
  hi == milliradians above median of fit
*/
void getFitRangeSim(double track, int PID, double &lo, double &hi)
{
	switch(PID)
	{
	case 211 : // pions
		if(track == 140)
			lo = 20;
		
		if(track == 130)
			lo = 25;

		if(track == 20 ||
		   track == 40 ||
		   track == 60 ||
		   track == 75 ||
		   track == 80 ||
		   track == 105 ||
		   track == 145  )
			lo = 30;

		if(track == 25 ||
		   track == 45 ||
		   track == 50 ||
		   track == 55 ||
		   track == 70 ||
		   track == 65  )
			lo = 35;
		
		if(track == 30 ||
		   track == 35 ||
		   track == 85 ||
		   track == 90 ||
		   track == 110 ||
		   track == 150 )
			lo = 40;

		if(track == 95 ||
		   track == 100 ||
		   track == 115 ||
		   track == 120 ||
		   track == 125 ||
		   track == 135 )
			lo = 50;

		if(track == 75  )
			hi = 25;

		if(track == 20 ||
		   track == 65 ||
		   track == 145 )
			hi = 30;

		if(track == 25 ||
		   track == 40 ||
		   track == 95 ||
		   track == 115 ||
		   track == 130 ||
		   track == 140 )
			hi = 35;

		if(track == 30 ||
		   track == 35 ||
		   track == 55 ||
		   track == 70 ||
		   track == 90 ||
		   track == 105 ||
		   track == 110 )
			hi = 40;

		if(track == 60)
			hi = 45;

		if(track == 45 ||
		   track == 80 ||
		   track == 100 ||
		   track == 120 ||
		   track == 125 ||
		   track == 135 ||
		   track == 150)
			hi = 50;

		if(track == 50)
			hi = 55;

		if(track == 85)
			hi = 60;
	
		
		break;
		
	case 2212 : // protons
		if(track == 55)
		{
			lo = 30;
			hi = 30;
		}

		if(track == 145)
		{
			lo = 60;
			hi = 60;
		}

		if(track == 40)
		{
			lo = 30;
			hi = 45;
		}
		
		if(track == 50)
		{
			lo = 30;
			hi = 40;
		}

		if(track == 65)
		{
			lo = 20;
			hi = 25;
		}

		if(track == 85)
		{
			lo = 30;
			hi = 35;
		}

		if(track == 115 ||
		   track == 140 )
		{
			lo = 30;
			hi = 30;
		}

		if(track == 70)
		{
			lo = 40;
			hi = 50;
		}

		if(track == 135)
		{
			lo = 30;
			hi = 30;
		}

		if(track == 95)
		{
			lo = 50;
			hi = 30;
		}

		if(track == 110)
		{
			lo = 30;
			hi = 45;
		}

		if(track == 100)
		{
			lo = 35;
			hi = 35;
		}

		if(track == 125 )
		{
			lo = 35;
			hi = 35;
		}

		if(track == 130)
		{
			lo = 35;
			hi = 60;
		}

		if(track == 20)
		{
			lo = 25;
			hi = 60;
		}

		if(track == 35)
		{
			lo = 25;
			hi = 35;
		}

		if(track == 75)
		{
			lo = 35;
			hi = 35;
		}

		if(track == 60)
		{
			lo = 30;
			hi = 45;
		}

		if(track == 120)
		{
			lo = 40;
			hi = 40;
		}

		if(track ==30)
		{
			lo = 30;
			hi = 50;
		}

		if(track == 80 )
		{
			lo = 35;
			hi = 35;
		}

		if(track == 45)
		{
			lo = 60;
			hi = 60;
		}

		if(track == 25)
		{
			lo = 40;
			hi = 45;
		}

		if(track == 90)
		{
			lo = 45;
			hi = 45;
		}

		if(track == 105)
		{
			lo = 45;
			hi = 30;
		}

		if(track == 150)
		{
			lo = 45;
			hi = 30;
		}
		
		break;
		
	}
}
//----------------------------------------------------------------
//----------------------------------------------------------------

#endif // ANALYSIS_H

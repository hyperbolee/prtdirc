#include "../analysistools.C"

void mcpCorrection(TString infile = "", int simulation = 0)
{
	SetStyle();
	double track(0);
	TFile *file = TFile::Open(infile);
	TTree *tree = (TTree*)file->Get("reco");
	TTree *dirc = (TTree*)file->Get("dirc");
	dirc->SetBranchAddress("theta",&track);
	dirc->GetEntry(0);

	TString pidcut = "PID>1000";
	TString evtype = "data";
	if(simulation)
		evtype = "sim";

	int bins = 120;
	double angleP  = 0.8168; // assume 7 GeV for now
	double anglePi = 0.8249;
	double angle = angleP; // proton
	
	const int nMCP = 15;
	TCanvas *c1 = new TCanvas();
	TH1D *mcpHist[nMCP];
	TH1D *theta = new TH1D("theta","theta",bins,0.6,1);
	TH1D *thetaCorr = new TH1D("thetaCorr","thetaCorr",bins,0.6,1);
	double diffpeak = DiffPeak(tree,pidcut);
	TF1 *thfit  = new TF1("thfit","gaus+pol1(3)");
	TF1 *mcpfit = new TF1("mcpfit","gaus+pol1(3)");
	mcpfit->SetParameters(1000,angle,0.007,100,0,0);

	tree->Project("theta","theta",pidcut+Form(" && abs(diff-%f)<1",diffpeak));
	TSpectrum *spec = new TSpectrum(10);
	SpecSearch(spec,theta,thfit);
	
	theta->Draw();
	c1->Print(Form("mcpcorr/%s_theta_%.2f.png",evtype.Data(),track));

	// loop over mcps
	for(int mcpid = 0; mcpid < nMCP; mcpid++)
	{
		//if(mcpid != 9 && mcpid != 13 && mcpid != 14) continue;
		// get timing peak for MCP=mcpid
		//TString cut = pidcut + Form(" && mcp==%d",mcpid);
		TString cut = pidcut;
		//cut += " && path==LUTpath";
		cut += Form(" && abs(diff-%f)<1",diffpeak);
		cut += Form(" && mcp==%d",mcpid);

		// project from tree
		// using PID cut and time cut
		//cut += Form(" && abs(diff-%f)<1",diffpeak);
		TString mcpname = Form("mcp%d",mcpid);
		mcpHist[mcpid] = new TH1D(mcpname,mcpname,bins,0.6,1);
		tree->Project(mcpname,"theta",cut);

		mcpHist[mcpid]->GetXaxis()->SetRangeUser(angle-0.04,angle+0.04);
		double max = mcpHist[mcpid]->GetXaxis()->GetBinCenter(mcpHist[mcpid]->GetMaximumBin());
		//cout << "max\t" << max << endl;
		if(mcpid == 9)
		{ 
			mcpfit->SetParameters(1000,angle,0.01,100,10);
		}

		else if(mcpid == 13)
		{
			if(simulation) mcpfit->SetParameters(1000,angle,0.01,100,10);
			else mcpfit->SetParameters(100,angle,0.003,1,0);
		}

		else if(mcpid == 14)
		{
			if(simulation) mcpfit->SetParameters(2000,angle,0.02,500,10);
			else mcpfit->SetParameters(500,angle,0.02,100,0);
		}


		mcpHist[mcpid]->Fit(mcpfit,"lq","",max-0.03,max+0.03);
		mcpHist[mcpid]->GetXaxis()->UnZoom();
		mcpHist[mcpid]->Draw();
		c1->Print(Form("mcpcorr/%s_mcp_%d_%.2f.png",evtype.Data(),mcpid,track));
		
		double shift =  angle - mcpfit->GetParameter(1);

		tree->Project(mcpname,Form("theta+%f",shift),cut);
		thetaCorr->Add(mcpHist[mcpid]);
		mcpHist[mcpid]->Fit(mcpfit,"lq","",angle-0.03,angle+0.03);

		mcpHist[mcpid]->SetTitle(mcpname+" corrected");
		mcpHist[mcpid]->Draw();
		c1->Print(Form("mcpcorr/%s_mcp_%d_%.2f_shift.png",evtype.Data(),mcpid,track));

		// "reset" after special cases
		mcpfit->SetParameters(1000,angle,0.007,100,0,0);
	}

	SpecSearch(spec,thetaCorr,thfit);
	thetaCorr->Draw();
	c1->Print(Form("mcpcorr/%s_theta_%.2f_corrected.png",evtype.Data(),track));
}

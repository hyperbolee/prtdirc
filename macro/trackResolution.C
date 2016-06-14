#include "../analysistools.C"

void trackResolution(double sigcorr = 0.0,
					 TString path = "../studies/bgsub151/C/")
{

	// check that root file exists
	TString infile = path + "plots.root";
	TString bgfile = path + "plots_bgsub.root";
	FileStat_t buf;
	if(gSystem->GetPathInfo(infile.Data(),buf) ||
	   gSystem->GetPathInfo(bgfile.Data(),buf))
	{
		cout << "Either " << infile << " or " << bgfile << " doesn't exist. Check paths and try again." << endl;
		return;
	}

	// create TFile and TGraphs
	TFile *file   = TFile::Open(infile);
	TFile *fileBG = TFile::Open(bgfile);
	TGraph *grNPH = (TGraph*)file->Get("grNPHsim");
	TGraph *grSPR = (TGraph*)file->Get("grSUBsim");
	TGraph *grSPRbg = (TGraph*)fileBG->Get("grSUBsim");
	TGraph *grTRK   = new TGraph();
	TGraph *grTRKbg = new TGraph();

	int points = grNPH->GetN();
	if(points != grSPR->GetN())
	{
		cout << "Graphs have different number of points. Check graphs and try again." << endl;
		return;
	}

	double x, yN, yS;
	for(int p=0; p<points; p++)
	{
		// track res without bgsub
		grNPH->GetPoint(p,x,yN);
		grSPR->GetPoint(p,x,yS);
		cout << "SPR:\t" << yS << endl;

		double res = TMath::Sqrt(yS*yS/yN + sigcorr*sigcorr);
		grTRK->SetPoint(p,x,res);

		// track res with bgsub
		grSPRbg->GetPoint(p,x,yS);
		res = TMath::Sqrt(yS*yS/yN + sigcorr*sigcorr);
		grTRKbg->SetPoint(p,x,res);
	}

	StyleGraph(grTRK,0,2.5,"polar angle [#circ]","#sigma_{track}",
			   20,kRed,"",Form("Angle resolution per track, #sigma_{correlated} = %.2f",sigcorr));
	grTRK->Draw("APL");

	StyleGraph(grTRKbg,0,2.5,"polar angle [#circ]","#sigma_{track}",
			   20,kBlue);
	grTRKbg->Draw("PL");

	TLegend *leg = new TLegend(0.6,0.7,0.89,0.89);
	leg->AddEntry(grTRK,"without background sub","lp");
	leg->AddEntry(grTRKbg,"with background sub","lp");
	leg->Draw();
}

/*
  Reconstruct input file using time-based
  reconstruction with probability
  distribution functions (PDFs) from the
  pdf_hists.root file

  Author - Lee Allison, March 2017
*/
#include "../src/PrtHit.h"
#include "../src/PrtEvent.h"
#include "../analysis.C"
#include "TCanvas.h"
#include "TCollection.h"
#include "TError.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TList.h"
#include "TROOT.h"
#include "TSpectrum.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TTree.h"
#include "TMarker.h"

#include <map>

// function to find intersection of
// proton and pion distributions
TF1 *prFit;
TF1 *piFit;
double intersect(double *x, double*par) {
   return TMath::Abs(prFit->EvalPar(x,par) - piFit->EvalPar(x,par));
}

void timebasedReco(TString infile, int normId = 1, int smooth = 0, int sigma = 3)
{
	PrtEvent *fEvent;
	PrtHit    fHit;

	double track, time, noise(1e-5);
	int mcp, pix, pid, entries, simulation(0);

	TChain *data = new TChain("data");
	data->Add(infile);
	data->SetBranchAddress("PrtEvent",&fEvent);
	data->GetEntry(1);
	track = fEvent->GetAngle();
	
	entries = data->GetEntries()>4000 ? 4000 : data->GetEntries();
	
	// for reconstruction
	TCanvas *canv = new TCanvas();
	TGraph *tmp1;
	TGraph *tmp2;
	
	TH1F *diffPr = new TH1F("diffPr","diffPr;ln L(p) - ln L(#pi);entries [#]",220,-60,60);
	TH1F *diffPi = new TH1F("diffPi","diffPi;ln L(p) - ln L(#pi);entries [#]",220,-60,60);
	TFile *PDF = TFile::Open(Form("pdf_norm%d_smooth%d.root",normId,smooth));


	//if(entries>10000) entries = 10000;

	int nprot(0), npion(0);
	for(int entry=0; entry<entries; entry++)
	{
		data->GetEntry(entry);
		int hits = fEvent->GetHitSize();
		pid = fEvent->GetParticle();
		simulation = fEvent->GetType();
		
		int goodHits = 0;

		cout << Form("\rProcessing Event %d",entry) << flush;
		if(!simulation)
		{
			bool t1(false), t2(false);
			
			// loop through hits first to make sure triggers fired
			for(int hit=0; hit<hits; hit++)
			{
				
				fHit = fEvent->GetHit(hit);
				int chan = fHit.GetChannel();

				if(chan==1344) t1 = true; // trigger 1
				if(chan==1346) t2 = true; // trigger 2
			}

			// skip events that didn't fire on both triggers
			if(!t1 || !t2) continue;
		}

		if(pid==211)  npion++;
		if(pid==2212) nprot++;

		double sum(0), sum1(0), sum2(0);

		//int multiHit[15][64] = {0};
		map<int, map<int,int> > multiHit;
		
		for(int hit=0; hit<hits; hit++)
		{
			fHit = fEvent->GetHit(hit);
			mcp = fHit.GetMcpId();
			pix = fHit.GetPixelId()-1;
			time = fHit.GetLeadTime();

			// skip multiple hits in same channel
			if(++multiHit[mcp][pix]>1)
				continue;

			// time cut
			if(time<0 || time>40)
				continue;

			// TH1D *thist1 = (TH1D*)PDF->Get(Form("pdf_211_%.2f_mcp%d_pix%d",track,mcp,pix));
			// TH1D *thist2 = (TH1D*)PDF->Get(Form("pdf_2212_%.2f_mcp%d_pix%d",track,mcp,pix));
			// tmp1 = new TGraph(thist1->Rebin(2));
			// tmp2 = new TGraph(thist2->Rebin(2));

			tmp1 = new TGraph((TH1F*)PDF->Get(Form("pdf_211_%.2f_mcp%d_pix%d",track,mcp,pix)));
			tmp2 = new TGraph((TH1F*)PDF->Get(Form("pdf_2212_%.2f_mcp%d_pix%d",track,mcp,pix)));

			double f1 = tmp1->Eval(time);//tmp1->GetBinContent(tmp1->FindBin(time));
			double f2 = tmp2->Eval(time);//tmp2->GetBinContent(tmp2->FindBin(time));
			
			if(f1>0) sum1 += TMath::Log(f1+noise);
			if(f2>0) sum2 += TMath::Log(f2+noise);

			tmp1->Delete();
			tmp2->Delete();

			// thist1->Delete();
			// thist2->Delete();

			goodHits++;
		}

		if(goodHits<20) continue;
		sum = sum1-sum2;
		
		if(sum)
		{
			if(pid==211)  diffPi->Fill(sum);
			if(pid==2212) diffPr->Fill(sum);
		}
	}

	// set histograms to same Y-axis
	double maxPi = diffPi->GetMaximum();
	double maxPr = diffPr->GetMaximum();

	double max = maxPi>maxPr ? maxPi : maxPr;

	//diffPi->Scale(max/maxPi);
	//diffPr->Scale(max/maxPr);
	diffPi->GetYaxis()->SetRangeUser(0,1.1*max);
	diffPr->GetYaxis()->SetRangeUser(0,1.1*max);

	// fit and get separation power
	diffPi->Fit("gaus","Q");
	diffPr->Fit("gaus","Q");

	piFit = diffPi->GetFunction("gaus");
	prFit = diffPr->GetFunction("gaus");
	TF1 *diff = new TF1("diff",intersect,-50,50,0);

	double meanPi = piFit->GetParameter(1);
	double sigmaPi = piFit->GetParameter(2);

	double meanPr = prFit->GetParameter(1);
	double sigmaPr = prFit->GetParameter(2);

	double separation = 2*fabs(meanPi-meanPr)/(sigmaPi+sigmaPr);
	double crossing   = diff->GetMinimumX(meanPr,meanPi);

	cout << "\nnprot:\t" << nprot << endl;
	cout << "npion:\t" << npion << endl;
	cout << "SEPARATION:\t" << separation << " stdev" << endl;
	cout << "CROSSING:\t" << crossing << endl;

	// draw all the things
	diffPi->SetTitle(Form("%s seperation %.4f#sigma, intersect %.2f",simulation?"sim":"data",separation,crossing));
	diffPi->SetLineColor(kRed);

	
	canv->cd();
	diffPi->Draw();
	diffPr->Draw("same");
	
	TMarker *m = new TMarker(crossing,prFit->Eval(crossing),24);
	m->SetMarkerColor(kPink);
	m->SetMarkerSize(3);
	m->Draw();
	canv->WaitPrimitive();

	if(true)
	{
		TString evtype = simulation ? "sim" : "data";
		canv->Print(Form("separation_%s_norm%d_smooth_%d.png",evtype.Data(),normId,smooth));
	}
	
	diffPr->Delete();
	diffPi->Delete();
	diff->Delete();
	data->Delete();
	m->Delete();
	canv->Close();
	canv->Delete();

	return;
}



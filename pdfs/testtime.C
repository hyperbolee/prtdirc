/*
  Quick test to see if projecting from a TTree is slower
  or faster than looping through each Event and Hit to
  get the timing information.


  CONCLUSION: It is roughly 70 times faster to loop
              through each Event and Hit rather than projecting
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

void testtime(TString infile = "../simulation/151/sim_3CS_125.00.root")
{
	TStopwatch watch1, watch2;

	PrtEvent *event;
	PrtHit hit;
	TFile *file = TFile::Open(infile);
	TChain ch("data");
	ch.Add(infile);
	ch.SetBranchAddress("PrtEvent",&event);
	int entries = ch.GetEntries();

	TH1D *timehist1 = new TH1D("timehist1","timehist1",500,0,100);
	TH1D *timehist2 = new TH1D("timehist2","timehist2",500,0,100);

	watch1.Start();
	for(int mcp=0; mcp<15; mcp++)
	{
		for(int pix=0; pix<64; pix++)
		{
			TH1D *tmp = new TH1D("tmp","tmp",500,0,100);
			ch.Project("tmp","fHitArray.fLeadTime",Form("fHitArray.fMcpId==%d && fHitArray.fPixelId==%d",mcp,pix+1));
			timehist1->Add(tmp);
			delete tmp;
		}
	}
	watch1.Stop();

	watch2.Start();
	for(int entry=0; entry<entries;entry++)
	{
		ch.GetEntry(entry);
		int hits = event->GetHitSize();
		for(int ihit=0; ihit<hits; ihit++)
		{
			hit = event.GetHit(ihit);

			timehist2->Fill(hit.GetLeadTime());
		}
	}

	watch2.Stop();

	cout << "Projection time" << endl;
	cout << "===============" << endl;
	cout << "CPU:\t" << watch1.CpuTime() << endl;
	cout << "Real:\t" << watch1.RealTime() << endl;
	cout << "entries:\t" << timehist1->GetEntries() << endl << endl;

	cout << "Loop time" << endl;
	cout << "===============" << endl;
	cout << "CPU:\t" << watch2.CpuTime() << endl;
	cout << "Real:\t" << watch2.RealTime() << endl;
	cout << "entries:\t" << timehist2->GetEntries() << endl << endl;
	
	timehist1->SetLineColor(kRed);
	timehist1->SetLineWidth(2);
	timehist1->Draw();
	timehist2->Draw("same");
}

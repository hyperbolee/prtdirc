// Functions useful for test beam analysis
// Written by Lee Allison. Dec. 4, 2015
#include "constants.h"

void timeWindow( TFile *infile, double w0, double w1, double w2, double w3)
{
	// w0 -> w1 = time window around peak of time-expt
	// w2 -> w0 = window to left of w01
	// w1 -> w3 = window to right of w01

	// grab trees from infile
	TTree *dirc = infile->Get("dirc");
	TTree *reco = infile->Get("reco");

	// get lens, bar angle, and beam momentum
	int lens(0);
	double alpha(0),beam(0);
	dirc->SetBranchAddress("lens",&lens);
	dirc->SetBranchAddress("theta",&alpha);
	dirc->GetEntry(0);

	// define histograms of diff, outside diff, and counters
	TH1D *diff = new TH1D("diff","diff",1000,-50,50);
	TH1D *dout = new TH1D("dout","dout",1000,-50,50);
	TH1D *tof1 = new TH1D("time-tof1","time-tof1",1000,0,1000);
	TH1D *tof2 = new TH1D("time-tof2","time-tof2",1000,0,1000);
	TH1D *trig = new TH1D("time-trig","time-trig",1000,0,1000);

	// project to histograms
	reco->Project("diff","diff");
	reco->Project("dout","diff");
	reco->Project("time-tof1","time-tof1");
	reco->Project("time-tof2","time-tof2");
	reco->Project("time-trig","time-trig");

	// get diff value at peak and define initial cut
	double diffpeak = diff->GetMaximumBin();
	diffpeak = (diffpeak-500)/10;
	char *diffcut = Form("%f<diff-%f && diff-%f<%f",w0,diffpeak,diffpeak,w1);
	cout << "Initial cut\t" << diffcut << endl;
	
	
}

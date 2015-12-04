// Constants and useful functions for
// prtdirc macros and simulation
// Written by Lee Allison.

// particle IDs
int proton = 2212;
int piplus =  212;

// counter channels
int tof1_chan =  960;
int tof2_chan = 1104;
int trig_chan = 1344;

// cut around time-expt peak
double expt_lo =-3;
double expt_hi = 3;

//char *fish_cut = Form("%f<(time-tof1) && (time-tof1)<%f && %f<(time-trig) && (time-trig)<%f && cnt1==1 && cntT==1",tof1_lo,tof1_hi,trig_lo,trig_hi);

// usual cut on data
//char *data_cut = Form("%f<(time-expt) && (time-expt)<%f && PID>1000",expt_lo,expt_hi);

char *cut = Form("%f<diff && diff<%f && PID==%d",expt_lo,expt_hi,proton);

// add cut from histogram counter to cut string
void counterCut( TH1D *counter )
{
	int min(0), max(0); // first zero bins around peak
	int bin = counter->GetMaximumBin(); // bin at peak

	// set min
	for(int b=bin; b>0; b--)
		if(counter->GetBinContent(b) == 0)
		{
			min = b;
			break;
		}

	// set max
	for(int b=bin; b<2*bin; b++)
		if(counter->GetBinContent(b) == 0)
		{
			max = b;
			break;
		}

	char *title = counter->GetTitle();
	char *ccut = Form(" && %d<%s && %s<%d", min, title, title, max);
	strcat(cut,ccut);

}

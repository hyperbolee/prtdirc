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

// default cut for beam data
char *def_cut = Form("%f<diff && diff<%f && PID==%d",expt_lo,expt_hi,proton);

// add cut from histogram counter to a string
void counterCut( TH1D *counter , char *&tmpcut = def_cut)
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
	strcat(tmpcut,ccut);

}

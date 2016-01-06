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

// finds zeros around peak of TH1D and adds
// that range to cut tmpcut
void cntrCut( TH1D *&cntr, char *&tmpcut , char *title)
{
	int min(0), max(0); // first zero bins around peak
	int bin = cntr->GetMaximumBin(); // bin at peak

	// set min
	for(int b=bin; b>0; b--)
		if(cntr->GetBinContent(b) == 0)
		{
			min = b;
			break;
		}

	// set max
	for(int b=bin; b<2*bin; b++)
		if(cntr->GetBinContent(b) == 0)
		{
			max = b;
			break;
		}

	char *ccut = new char[180];
	sprintf(ccut," && %d<%s && %s<%d", min, title, title, max);
	strcat(tmpcut,ccut);
}

// define cut around peak of tof1 distribution
void tof1Cut( const TTree *&tree, 
			  char *&tmpcut = def_cut, 
			  int save = 0)
{
	// define counter hist and project
	TH1D *tof1 = new TH1D("time-tof1","time-tof1",1000,0,1000);
	tree->Project("time-tof1","time-tof1");

	cntrCut(tof1,tmpcut,"time-tof1");
}

// define cut around peak of tof2 distribution
void tof2Cut( const TTree *&tree, 
			  char *&tmpcut = def_cut,
			  int save = 0)
{
	// define counter hist and project
	TH1D *tof2 = new TH1D("time-tof2","time-tof2",1000,0,1000);
	tree->Project("time-tof2","time-tof2");

	cntrCut(tof2,tmpcut,"time-tof2");
}

// define cut around peak of trig distribution
void trigCut( const TTree *&tree, 
			  char *&tmpcut = def_cut,
			  int save = 0)
{
	// define counter hist and project
	TH1D *trig = new TH1D("time-trig","time-trig",1000,0,1000);
	tree->Project("time-trig","time-trig");

	cntrCut(trig,tmpcut,"time-trig");
}

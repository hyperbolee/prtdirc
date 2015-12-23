// Constants and useful functions for
// prtdirc macros and simulation
//#include "../../prttools/prttools.C"

// particle IDs
int proton = 2212;
int piplus =  212;

// counter channels
int tof1_chan = 960;
int tof2_chan = 1104;
int trig_chan = 1344;

// counter times( mcp - counter )
double tof1_lo = 740;//200;
double tof1_hi = 770;//220;

double trig_lo = 410;//-140;
double trig_hi = 443;//-110;

// test cuts for small time peaks
double t1lo(770.),t1hi(800.);
double trlo(443.),trhi(470.);

// cut around time-expt peak
// hopefully this will later be shifted to centered at 0
double expt_lo =-1.5;
double expt_hi = 1.5;

char *fish_cut = Form("%f<(time-tof1) && (time-tof1)<%f && %f<(time-trig) && (time-trig)<%f && cnt1==1 && cntT==1",tof1_lo,tof1_hi,trig_lo,trig_hi);

// usual cut on data
char *data_cut = Form("%f<(time-expt) && (time-expt)<%f && PID>1000",expt_lo,expt_hi);

char *sim_cut  = Form("%f<(time-expt) && (time-expt)<%f",expt_lo,expt_hi);


char *data_cut1 = Form("%f<(time-tof1) && (time-tof1)<%f && %f<(time-trig) && (time-trig)<%f && cnt1==1 && cntT==1",tof1_lo,tof1_hi,trig_lo,trig_hi);

char *smll_cut = Form("%f<(time-tof1) && (time-tof1)<%f && %f<(time-trig) && (time-trig)<%f && cnt1==1 && cntT==1",t1lo,t1hi,trlo,trhi);

char *full_cut = Form("%f<(time-tof1) && (time-tof1)<%f && %f<(time-trig) && (time-trig)<%f && cnt1==1 && cntT==1",tof1_lo,t1hi,trig_lo,trhi);

// mcp==1 && pix==27

// if pixel is one of the dead pixels
// from test beam, ignore it in simulation
bool DeadPixel(int mcp, int pix)
{
	if(mcp==0 && pix==16)  return true;
	if(mcp==1 && pix==47)  return true;
	if(mcp==3 && pix==5)   return true;
	if(mcp==3 && pix==6)   return true;
	if(mcp==3 && pix==7)   return true;
	if(mcp==6 && pix==0)   return true;
	if(mcp==6 && pix==1)   return true;
	if(mcp==6 && pix==2)   return true;
	if(mcp==6 && pix==3)   return true;
	if(mcp==6 && pix==4)   return true;
	if(mcp==6 && pix==5)   return true;
	if(mcp==6 && pix==6)   return true;
	if(mcp==6 && pix==7)   return true;
	if(mcp==6 && pix==8)   return true;
	if(mcp==6 && pix==9)   return true;
	if(mcp==6 && pix==10)  return true;
	if(mcp==6 && pix==11)  return true;
	if(mcp==6 && pix==12)  return true;
	if(mcp==6 && pix==13)  return true;
	if(mcp==6 && pix==14)  return true;
	if(mcp==6 && pix==15)  return true;
	if(mcp==8 && pix==16)  return true;
	if(mcp==8 && pix==17)  return true;
	if(mcp==8 && pix==24)  return true;
	if(mcp==8 && pix==31)  return true;
	if(mcp==9 && pix==52)  return true;
	if(mcp==10 && pix==47) return true;
	if(mcp==12 && pix==47) return true;
	if(mcp==12 && pix==54) return true;
	if(mcp==12 && pix==55) return true;
	if(mcp==12 && pix==63) return true;

	return false;
}

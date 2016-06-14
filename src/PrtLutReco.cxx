// -----------------------------------------
// PrtLutReco.cpp
//
// Created on: 13.07.2013
// Author: R.Dzhygadlo at gsi.de
// -----------------------------------------

#include "PrtLutReco.h"

#include "PrtManager.h"

#include "PrtLutNode.h"
#include "PrtTrackInfo.h"
#include "PrtPhotonInfo.h"
#include "PrtAmbiguityInfo.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TRotation.h"
#include "TGraph.h"
#include <TVirtualFitter.h>
#include <TArc.h>
#include <TLegend.h>
#include "../../prttools/prttools.C"


using std::cout;
using std::endl;

TH1F*  fHist0 = new TH1F("timediff",";t_{calc}-t_{measured} [ns];entries [#]", 500,-10,10);
TH1F*  fHist1 = new TH1F("time1",";measured time [ns];entries [#]",   1000,0,100);
TH1F*  fHist2 = new TH1F("time2",";calculated time [ns];entries [#]", 1000,0,100);
TH2F*  fHist3 = new TH2F("time3",";calculated time [ns];measured time [ns]", 500,0,80, 500,0,40);
TH2F*  fHist4 = new TH2F("time4",";#theta_{c}sin(#varphi_{c});#theta_{c}cos(#varphi_{c}", 100,-1,1, 100,-1,1);
TH2F*  fHist5 = new TH2F("time5",";#theta_{c}sin(#varphi_{c});#theta_{c}cos(#varphi_{c}", 100,-1,1, 100,-1,1);

TH1F *hLnDiffP = new TH1F("hLnDiffP",  ";ln L(p) - ln L(#pi);entries [#]",200,-30,30);
TH1F *hLnDiffPi = new TH1F("hLnDiffPi",";ln L(p) - ln L(#pi);entries [#]",200,-30,30);

TF1 *gF1 = new TF1("gaus0","[0]*exp(-0.5*((x-[1])/[2])*(x-[1])/[2])",0.7,0.9);
TF1 *gF2= new TF1("gaus0","[0]*exp(-0.5*((x-[1])/[2])*(x-[1])/[2])",0.7,0.9);

Int_t gg_i(0), gg_ind(0);
TGraph gg_gr;
PrtLutNode *fLutNode[5000];

// -----   Default constructor   -------------------------------------------
PrtLutReco::PrtLutReco(TString infile, TString lutfile, Int_t verbose)
{
	gErrorIgnoreLevel = kWarning;
	fVerbose = verbose;
	fChain = new TChain("data");
	fChain->Add(infile);
	fChain->SetBranchAddress("PrtEvent", &fEvent);

	fFile = new TFile(lutfile);
	fTree=(TTree *) fFile->Get("prtlut") ;
	fLut = new TClonesArray("PrtLutNode");
	fTree->SetBranchAddress("LUT",&fLut); 
	fTree->GetEntry(0);

	fHist = new TH1F("chrenkov_angle_hist","chrenkov angle;#theta_{C} [rad];entries [#]", 80,0.6,1); //150
	fFit = new TF1("fgaus","[0]*exp(-0.5*((x-[1])/[2])*(x-[1])/[2]) +x*[3]",0.35,0.9);
	fSpect = new TSpectrum(10);

	/*if(infile.Contains("beam_")){
	  TString fileid(infile);
	  fileid.Remove(0,fileid.Last('/')+1);
	  fileid.Remove(fileid.Last('.')-1);
	  //prt_data_info = getDataInfo(fileid);
    
	  TString opath(infile);
	  opath.Remove(opath.Last('/'));
	  if(infile.Contains("C.root")){
	  fSavePath = opath+Form("/%dr/%d",prt_data_info.getStudyId(),prt_data_info.getFileId());
	  }else{
	  fSavePath = opath+Form("/%ds/%d",prt_data_info.getStudyId(),prt_data_info.getFileId());
	  }
    
	  }else*/
	fSavePath="auto";
	std::cout<<"fSavePath  "<< fSavePath <<std::endl;    

	for(Int_t i=0; i<5000; i++){
		fLutNode[i] = (PrtLutNode*) fLut->At(i);
	}
	cout << "-I- PrtLutReco: Intialization successfull" << endl;
}

// -----   Destructor   ----------------------------------------------------
PrtLutReco::~PrtLutReco(){

}


Int_t mcpdata[15][65];
Int_t cluster[15][65];
Int_t lneighbours[65];
Int_t lsize(0);

Int_t getneighbours(Int_t m, Int_t p)
{
	for(Int_t i=0; i<65; i++) if(p==lneighbours[i]) return -1;
	lneighbours[lsize]=p;
	lsize++;
	for(Int_t t=0; t<65; t++)
	{
		if(mcpdata[m][t])
		{
			for(Int_t i=0; i<65; i++) 
				if(t==lneighbours[i]) continue;
			if((t==p-1 && p%8!=0) || (t==p+1 && p%8!=7) ||
			   (t==p+8 && p<57) || (t==p-8 && p>8)) getneighbours(m,t);
		}
	}
	return lsize;
}

void getclusters()
{
	for(Int_t m=0; m<15; m++)
	{
		for(Int_t p=0; p<65; p++)
		{
			if(mcpdata[m][p])  cluster[m][p] = getneighbours(m,p);
			lsize=0;
			for(Int_t i=0; i<65; i++) lneighbours[i]=0;
		}
	}
}

// 
#include <iterator>
int tofpix1[] = {54,56,71,73}; // 2x2 center
int tofpix2[] = {52,53,55,57,58,59,68,69,70,72,74,75}; // 4x4 second  "ring"
int tofpix3[] = {34,36,38,40,42,44,50,51,60,61,66,65,76,77,83,85,87,89,91,93}; // 6x6 third "ring"
int getTOFring( int chan )
{
	chan -= 960; // shift lowest pixel to zero
	if(chan>95) chan-=96; // shift second tof to same range

	// check if channel is in each "ring" of TOF
	bool r1 = std::find(std::begin(tofpix1), std::end(tofpix1), chan) != std::end(tofpix1);
	bool r2 = std::find(std::begin(tofpix2), std::end(tofpix2), chan) != std::end(tofpix2);
	bool r3 = std::find(std::begin(tofpix3), std::end(tofpix3), chan) != std::end(tofpix3);

	if(r1) return 1;
	if(r2) return 2;
	if(r3) return 3;
	
	return 4;
}

 
//-------------- Loop over tracks ------------------------------------------
void PrtLutReco::Run(Int_t start, Int_t end, Double_t shift){
	cout << "Start Reco run" << endl;

	TVector3 dird, dir, momInBar(0,0,1),posInBar,cz;
	Double_t cangle,spr,tangle,boxPhi,weight,evtime,bartime, lenz,dirz,luttheta, barHitTime, hitTime;
	Int_t pdgcode, evpointcount=0;
	Bool_t reflected = kFALSE;
	gStyle->SetOptFit(111);

	TVector3 fnX1 = TVector3 (1,0,0);   
	TVector3 fnY1 = TVector3( 0,1,0);
	bool testTrRes = false;
	Double_t angdiv,dtheta,dtphi,prtangle;

	TString outFile = PrtManager::Instance()->GetOutName()+"_spr.root";
	Int_t lensID(0);
	Double_t beam(0);
	Double_t theta(0),phi(0), trr(0), nph(0), yield(0),
		par1(0), par2(0), par3(0), par4(0), par5(0), par6(0), test1(0), test2(0),test3(0),separation(0);
	Double_t minChangle(0);
	Double_t maxChangle(1);
	Double_t rad = TMath::Pi()/180.;
	Double_t criticalAngle = asin(1.00028/1.47125); // n_quarzt = 1.47125; //(1.47125 <==> 390nm)
	TRandom rnd;

	SetRootPalette(1);
	CreateMap();
	initDigi();
  
	TFile file(outFile,"recreate");
	TTree tree("dirc","SPR");
	tree.Branch("spr", &spr,"spr/D");
	tree.Branch("trr", &trr,"trr/D");
	tree.Branch("nph",&nph,"nph/D");
	tree.Branch("yield",&yield,"yield/D");
	tree.Branch("cangle",&cangle,"cangle/D");
	tree.Branch("separation",&separation,"separation/D");
	tree.Branch("par3",&par3,"par3/D");
	tree.Branch("par4",&par4,"par4/D");
	tree.Branch("par5",&par5,"par5/D");
	tree.Branch("par6",&par6,"par6/D");
	tree.Branch("test1",&test1,"test1/D");
	tree.Branch("test2",&test2,"test2/D");
	tree.Branch("lens",&lensID,"lensID/I");
	tree.Branch("beam",&beam,"beam/D");
	tree.Branch("theta",&theta,"theta/D");
	tree.Branch("phi",&phi,"phi/D");

	test1 = PrtManager::Instance()->GetTest1();

    Int_t baramb(0);
	Int_t tMCP(0), tPix(0), tPID(0), tNRef(0), tNRefLUT(0), tHits(0), tPi(0), tProt(0), tChan(0);
	Double_t  tTof1(0), tTof2(0), tTrig(0), tX(0), tY(0);
	Double_t tTheta(0), tLambda(0), tTime(0), tExpt(0), tDiff(0), tPath(0), tPathLUT(0), assume(0);

    // counter channels
	int tof1_chan =  960;
	int tof2_chan = 1104;
	int trig_chan = 1344;

	// tree for ambiguity information (theta_C, etc)
	TTree *lTree = new TTree("reco","reconstruction");
	lTree->SetAutoSave(0);
	lTree->Branch("mcp",&tMCP,"tMCP/I"); // mcp hit
	lTree->Branch("pix",&tPix,"tPix/I"); // pixel hit
	lTree->Branch("x",&tX,"tX/D"); // x position on detector
	lTree->Branch("y",&tY,"tY/D"); // y position on detector
	lTree->Branch("chan",&tChan,"tChan/I"); // channel number
	lTree->Branch("PID",&tPID,"tPID/I"); // particle ID
	lTree->Branch("npi",&tPi,"tPi/I"); // number of pions
	lTree->Branch("nprot",&tProt,"tProt/I"); // number of protons
	lTree->Branch("nref",&tNRef,"tNRef/I"); // number of reflections
	lTree->Branch("path",&tPath,"tPath/D"); // path ID in prizm
	lTree->Branch("LUTnref",&tNRefLUT,"tNRefLUT/I"); // reflections
	lTree->Branch("LUTpath",&tPathLUT,"tPathLUT/D"); // path ID
	lTree->Branch("hits",&tHits,"tHits/I");
	lTree->Branch("theta",&tTheta,"tTheta/D"); // theta_C
	lTree->Branch("lambda",&tLambda,"tLambda/D"); // wave length
	lTree->Branch("track",&prtangle,"prtangle/D"); // track
	lTree->Branch("aTrack",&assume,"assume/D"); // assumed track
	lTree->Branch("baramb",&baramb,"baramb/I"); // bar ambiguity correct?
	lTree->Branch("time",&tTime,"tTime/D"); // arrival time of hit
	lTree->Branch("expt",&tExpt,"tExpt/D"); // expected arrival time
	lTree->Branch("diff",&tDiff,"tDiff/D"); // difference in times
	lTree->Branch("tof1",&tTof1,"tTof1/D"); // timing of TOF1
	lTree->Branch("tof2",&tTof2,"tTof2/D"); // timing of TOF2
	lTree->Branch("trig",&tTrig,"tTrig/D"); // timing of TRIG
	
	// tree for hit-by-hit information (timing, etc)
	TTree *hTree = new TTree("hits","hit by hit variables");
   	hTree->Branch("mcp",&tMCP,"tMCP/I");
	hTree->Branch("pix",&tPix,"tPix/I");
	hTree->Branch("x",&tX,"tX/D"); // x position on detector
	hTree->Branch("y",&tY,"tY/D"); // y position on detector
	hTree->Branch("chan",&tChan,"tChan/I");
	hTree->Branch("PID",&tPID,"tPID/I");
	hTree->Branch("npi",&tPi,"tPi/I"); // number of pions
	hTree->Branch("nprot",&tProt,"tProt/I"); // number of protons
	hTree->Branch("nref",&tNRef,"tNRef/I"); // number of reflections
	hTree->Branch("path",&tPath,"tPath/D"); // path ID in prizm
	hTree->Branch("track",&prtangle,"prtangle/D");
	hTree->Branch("aTrack",&assume,"assume/D"); // assumed track
	hTree->Branch("lambda",&tLambda,"tLambda/D");
	hTree->Branch("time",&tTime,"tTime/D");
	hTree->Branch("tof1",&tTof1,"tTof1/D");
	hTree->Branch("tof2",&tTof2,"tTof2/D");
	hTree->Branch("trig",&tTrig,"tTrig/D");
  
	Int_t nEvents = fChain->GetEntries();
	if(end==0) end = nEvents;
  
	std::cout<<"Run started for ["<<start<<","<<end <<"]"<<std::endl;
	Int_t nsHits(0),nsEvents(0),nsYield(0),studyId(0),nHits(0),ninfit(0);
	Bool_t loopoverall(false);
	if(start<0)
	{
		loopoverall=true;
		ninfit=abs(start);
		start=0;
	}
	cout << "Start event loop" << endl;
	cout << "start\t" << start << endl;
	cout << "nEvents\t" << nEvents << endl;

	// event-by-event fitting and spread of reconstructed angle
	TH1D *eRecoP = new TH1D("eRecoP","eRecoP",120,0.6,1);
	TH1D *eRecoPi = new TH1D("eRecoPi","eRecoPi",120,0.6,1);
	TH1D *aSpreadP = new TH1D("aSpreadP","angSpreadP",200,0.6,1);
	TH1D *aSpreadPi = new TH1D("aSpreadPi","angSpreadPi",200,0.6,1);

	bool simulation(false);
	gROOT->SetBatch(1);
	for (Int_t ievent=start; ievent<end; ievent++)
	{
		fChain->GetEntry(ievent);
		nHits = fEvent->GetHitSize();
		simulation = fEvent->GetType();
		eRecoP->Reset();
		eRecoPi->Reset();// reset hist for each event

		if(ievent%1000==0) 
			std::cout<<"Event # "<< ievent << " has "<< nHits <<" hits"<<std::endl;

		if(ievent==start)
		{
			tree.SetTitle(fEvent->PrintInfo());
			assume = fEvent->GetAngle();
			prtangle = fEvent->GetAngle() + shift;
			studyId = fEvent->GetGeometry();
			lensID = fEvent->GetLens();
			beam = fEvent->GetMomentum().z();

			if(!simulation)
			{ // beam center correction for data
				momInBar.RotateY(TMath::Pi()-prtangle*rad-0.0045);
				momInBar.RotateX(0.0045);
			}
			else momInBar.RotateY(TMath::Pi()-prtangle*rad);
			// momInBar = fEvent->GetMomentum().Unit();

			if(fVerbose==3)
			{
				cz = momInBar.Unit();
				cz = TVector3(-cz.X(),cz.Y(),cz.Z());
			}
		}
		
		Double_t momentum=fEvent->GetMomentum().Mag();
		int tofPid(0);
		if(simulation) momentum /= 1000;
		tofPid=fEvent->GetParticle();
		if(tofPid==212) tofPid=211; //why?


		Int_t pdg[]={11,13,211,321,2212};
		Double_t mass[] = {0.000511,0.1056584,0.139570,0.49368,0.9382723};    
		Double_t angle1(0), angle2(0),sum1(0),sum2(0), sigma(0.009),range(5*sigma),noise(0.3);
    
		fAngleP = acos(sqrt(momentum*momentum+ mass[4]*mass[4])/momentum/1.4738)-0.002; //1.4738 = 370 = 3.35
		fAnglePi= acos(sqrt(momentum*momentum + mass[2]*mass[2])/momentum/1.4738)-0.002;

		gF1->SetParameter(0,1);
		gF2->SetParameter(0,1);
    
		gF1->SetParameter(1,fAngleP);
		gF2->SetParameter(1,fAnglePi);

		gF1->SetParameter(2,sigma);
		gF2->SetParameter(2,sigma);

		if(!simulation)
		{
			if(fabs(momentum-7)<0.1) //why?
			{
				if( tofPid==2212 && 
					fEvent->GetTest1()<175.6 ) continue;
				if( tofPid==211  && 
					fEvent->GetTest1()>175.1 ) continue;
			}
		}

		if(nHits<5) continue;

		tHits = nHits;
		tTof1 = tTof2 = tTrig = 0;
		int rt1(5), rt2(5); // assume outter ring
		// use this loop for tighter cuts 
		for(Int_t ihit=0; ihit<nHits; ihit++)
		{
			fHit = fEvent->GetHit(ihit);
			
			int chan = fHit.GetChannel();
			int ring = getTOFring(chan);

			if(992<=chan && chan<=1055)
				if(ring<rt1) rt1 = ring;
			
			if(1088<=chan && chan<=1151)
				if(ring<rt2) rt2 = ring;

			//if(ievent==17)
			//std::cout << Form("channel %d, r1 %d, r2 %d",chan, rt1, rt2) << std::endl;

			//if(chan == tof1_chan) tTof1 = hitTime;
			//if(chan == tof2_chan) tTof2 = hitTime;
			//if(chan == trig_chan) tTrig = hitTime;

		}
		tTof1 = rt1;
		tTof2 = rt2;
		//if(rt2==5 || rt1==5)
		//std::cout <<Form("%d: (%d,%d)",ievent,rt1,rt2)<< std::endl;
		
		tPID  = fEvent->GetParticle();
		if(tPID>1000) tProt++;
		else tPi++;
		for(Int_t h=0; h<nHits; h++)
		{
			fHit = fEvent->GetHit(h);
			hitTime = fHit.GetLeadTime();
			// set hit information for trees
			tTime = hitTime;
			tMCP  = fHit.GetMcpId();
			tPix  = fHit.GetPixelId()-1;
			tChan = fHit.GetChannel();
			tX    = fHit.GetGlobalPos().X();
			tY    = fHit.GetGlobalPos().Y();
			tMCP  = fHit.GetMcpId();
			tPix  = fHit.GetPixelId() - 1;

			if(simulation)
				tLambda = fHit.GetTotTime();

			{ //time cuts
				if(prtangle<=80)
				{
					if(hitTime<11 || hitTime>35) continue;
					reflected = kTRUE;
				}
				else if(prtangle>=95)
				{
					if(hitTime<3 || hitTime>20) continue;
					reflected = kFALSE;
				}
				else
				{
					if(hitTime<13.5)  reflected = kFALSE; //13.5
					else reflected = kTRUE;
				}
			}
      
			Double_t radiatorL = 1250; //bar

			if(studyId==152 || 
			   studyId==153 || 
			   studyId==161 || 
			   studyId==162 || 
			   studyId==171 || 
			   studyId==172 || 
			   studyId==173 || 
			   studyId==1175 || 
			   studyId==176 || 
			   studyId==177 || 
			   studyId==178)
				radiatorL = 1224.9; //plate
			

			Double_t z =  fEvent->GetBeamZ();
			if(simulation)
				lenz = radiatorL/2.-fHit.GetPosition().Z();
			else
				lenz = z-1/tan(prtangle*rad)*(122+(z-96)/tan((135-0.5*prtangle)*rad))+25; // +25 for correction to data
			

			if(fVerbose==3)
			{
				TVector3 cd = fHit.GetMomentum();
				fHist5->Fill(cd.Theta()*TMath::Sin(cd.Phi()),cd.Theta()*TMath::Cos(cd.Phi()));
			}

			
			if(reflected) lenz = 2*radiatorL - lenz;
			Int_t ch = map_mpc[tMCP][tPix];
			if(badcannel(ch)) continue;

			Int_t x(0),y(0), piid(tPix) , nedge(0);
			TString lutname = fFile->GetName();
			bool csCorr = lutname.Contains("cs_avr");
			if(csCorr) // if not charge-sharing LUT don't bother
			{
				for(Int_t h=0; h<nHits; h++) {
					Int_t pid=fEvent->GetHit(h).GetPixelId()-1;
					Int_t mid=fEvent->GetHit(h).GetMcpId();
					Double_t tdif=fabs(hitTime-fEvent->GetHit(h).GetLeadTime());
				    
					if(mid!=tMCP || pid==piid || tdif>0.3) continue;
					if(pid==piid-1 && piid%8!=0) x-=1;
					if(pid==piid+1 && piid%8!=7) x+=1;

					if(pid==piid-8 && piid>=8) y-=1;
					if(pid==piid+8 && piid<56) y+=1;
				}
      
				if(x== 0 && y== 0) nedge=0;
				if(x==-1 && y== 0) nedge=1;
				if(x==-1 && y== 1) nedge=2;
				if(x== 0 && y== 1) nedge=3;
				if(x== 1 && y== 1) nedge=4;
				if(x== 1 && y== 0) nedge=5;
				if(x== 1 && y==-1) nedge=6;
				if(x== 0 && y==-1) nedge=7;
				if(x==-1 && y==-1) nedge=8;

				//cout<< tMCP << tPix << " nedge "<<nedge <<" x " <<x << "  y  "<<y<<endl;
			}

			Int_t sensorId = 100*fHit.GetMcpId()+fHit.GetPixelId();
			if(sensorId==1) continue;

			hTree->Fill();
			Bool_t isGoodHit(false);
			Int_t size =fLutNode[sensorId]->Entries();
			for(int i=0; i<size; i++){
				weight = 1; //fLutNode[sensorId]->GetWeight(i);
				if(csCorr)
				    dird = fLutNode[sensorId]->GetEntryCs(i,nedge);
				else 
					dird = fLutNode[sensorId]->GetEntry(i);

				evtime = fLutNode[sensorId]->GetTime(i);
				Int_t pathid = fLutNode[sensorId]->GetPathId(i);
	
				for(int u=0; u<2; u++)
				{
					if(u == 0) dir = dird;
					if(u == 1) dir.SetXYZ( -dird.X(), dird.Y(), dird.Z());
					if(u == 2) dir.SetXYZ( dird.X(),-dird.Y(),  dird.Z()); //no need when no divergence in vertical plane
					if(u == 3) dir.SetXYZ( -dird.X(),-dird.Y(), dird.Z()); //no need when no divergence in vertical plane
					if(reflected) dir.SetXYZ( dir.X(), dir.Y(), -dir.Z());
					if(dir.Angle(fnX1) < criticalAngle || dir.Angle(fnY1) < criticalAngle) continue;

					TVector3 phmom = fHit.GetMomentum(); // photon momentum
					if( simulation && // product will be > 0 if components have the same sign
						( phmom.X()*dir.X() > 0 ) &&
						( phmom.Y()*dir.Y() > 0 ) &&
						( phmom.Z()*dir.Z() > 0 )  )
						baramb = 1;
					
					else
						baramb = 0;
						

					luttheta = dir.Theta();  
					if(luttheta > TMath::PiOver2()) luttheta = TMath::Pi()-luttheta;

					bartime = fabs(lenz/cos(luttheta)/198.);
	 
					fHist0->Fill((bartime+evtime)-hitTime);
					fHist1->Fill(hitTime);
					fHist2->Fill(bartime+evtime);

					if(fabs((bartime+evtime)-hitTime)>test1)
						continue;
					
					fHist3->Fill(fabs((bartime+evtime)),hitTime);
					tangle = momInBar.Angle(dir);
					if(tangle > minChangle && tangle < maxChangle){
						fHist->Fill(tangle ,weight);

						if(0.7<tangle && tangle<0.9)
						{
							if(fabs((bartime+evtime)-hitTime)<3)
							//isGoodHit=true;
								if(fabs(tangle-0.815)<0.07) isGoodHit=true; //test2
							//if(studyId>=160) isGoodHit=true;
						}

						if(true && tangle>0.4 && tangle<0.9 ){
							Double_t f1 = gF1->Eval(tangle);
							Double_t f2 = gF2->Eval(tangle);
							// if(f1<noise) f1 =noise;
							// if(f2<noise) f2 =noise;
							sum1 += -TMath::Log(f1+noise);
							sum2 += -TMath::Log(f2+noise);

							// sum1 += -TMath::Log(fabs((fAngleP-tangle)/f1));
							// sum2 += -TMath::Log(fabs((fAnglePi-tangle)/f2));	      
						}

						tNRef = fHit.GetNreflectionsInPrizm();
						tNRefLUT = fLutNode[sensorId]->GetNRefl(i);
						tPath = fHit.GetPathInPrizm();
						tPathLUT = pathid;
						tTheta = tangle;
						tTime  = hitTime;
						tExpt  = bartime + evtime;
						tDiff  = tTime - tExpt;

						if(tPID>1000 )//&& abs(tDiff)<1)
							eRecoP->Fill(tangle);
						if(tPID<1000 )//&& abs(tDiff)<1)
							eRecoPi->Fill(tangle);
							
						lTree->Fill();

						if(fVerbose==3)
						{	      
							TVector3 rdir = TVector3(-dir.X(),dir.Y(),dir.Z());
							rdir.RotateUz(cz);	      
							Double_t phi = rdir.Phi();
							Double_t tt =  rdir.Theta();
							fHist4->Fill(tt*TMath::Sin(phi),tt*TMath::Cos(phi));

							//for cherenckov circle fit
							gg_gr.SetPoint(gg_i,tt*TMath::Sin(phi),tt*TMath::Cos(phi));
							gg_i++;
						}
					}
				}
			}
			
			nsYield++;
			if(isGoodHit) nsHits++; 	
		} // end hit loop

		// fit eventReco and save mean to angSpread
		int xlow = eRecoP->FindBin(0.8);
		int xhi = eRecoP->FindBin(0.84);
		int areaP = eRecoP->Integral(xlow,xhi);
		int areaPi = eRecoPi->Integral(xlow,xhi);
		if(areaP && tPID>1000)
		{
			eRecoP->Fit("gaus","Q","",0.78,0.86);
			aSpreadP->Fill(eRecoP->GetFunction("gaus")->GetParameter(1));
		}
		if(areaPi && tPID<1000)
		{
			eRecoPi->Fit("gaus","Q","",0.78,0.86);
			aSpreadPi->Fill(eRecoPi->GetFunction("gaus")->GetParameter(1));
		}
		
		

		for(Int_t j=0; j<15; j++){
			for(Int_t i=0; i<65; i++){
				mcpdata[j][i]=0;
				cluster[j][i]=0;
			}
		}

		Double_t sum = sum1-sum2;
		if(sum!=0){
			if(tofPid==2212) hLnDiffP->Fill(sum);
			if(tofPid==211)  hLnDiffPi->Fill(sum);
		}

		if(++nsEvents>=end || fVerbose>4)
		{
			if(loopoverall)
			{
				FindPeak(cangle,spr, prtangle);
				nph = nsHits/(Double_t)ninfit;
				yield = nsYield/(Double_t)ninfit;
				spr = spr*1000;
				trr = spr/sqrt(nph);
				theta = prtangle;
				par3 = fEvent->GetTest1();
				std::cout<<"p  "<<sum1 << "   pi "<<sum2 << "  s "<< sum<<std::endl;
				std::cout<<"RES   "<<spr << "   N "<< nph << " trr  "<<trr<<std::endl; 
				tree.Fill();
			}
			else break;
		}
	} // end event loop
	
	// draw spread histograms for testing
	/*TCanvas *c1 = new TCanvas(); c1->cd();
	aSpreadP->Draw();
	aSpreadPi->SetLineColor(kRed);
	aSpreadPi->Draw("same");
	c1->Update();
	c1->WaitPrimitive();
	delete c1;*/
  
	if(!loopoverall)
	{
		FindPeak(cangle,spr, prtangle);
		nph = nsHits/(Double_t)nsEvents;
		yield = nsYield/(Double_t)nsEvents;
		spr = spr*1000;
		trr = spr/sqrt(nph);
		theta = prtangle;
		par3 = fEvent->GetTest1();
		std::cout<<"RES   "<<spr << "   N "<< nph << " trr  "<<trr<<std::endl; 
		tree.Fill();
	}
	else
	{
		//if(!fVerbose) gROOT->SetBatch(1);
		canvasAdd("r_lhood",800,400);
		prt_normalize(hLnDiffP,hLnDiffPi);
		hLnDiffP->SetLineColor(2);

		TF1 *ff;
		Double_t m1,m2,s1,s2; 
		if(hLnDiffP->GetEntries()>10){
			hLnDiffP->Fit("gaus","S");
			ff = hLnDiffP->GetFunction("gaus");
			m1=ff->GetParameter(1);
			s1=ff->GetParameter(2);
		}
		if(hLnDiffPi->GetEntries()>10){
			hLnDiffPi->Fit("gaus","S");
			ff = hLnDiffPi->GetFunction("gaus");
			m2=ff->GetParameter(1);
			s2=ff->GetParameter(2);
		}
		separation = (fabs(m2-m1))/(0.5*(s1+s2));
		std::cout<<"separation "<< separation <<std::endl;

		//gStyle->SetOptFit(0);
		//gStyle->SetOptStat(0);
		
		hLnDiffP->SetName(Form("s_%2.2f",separation));
		hLnDiffP->Draw();
		hLnDiffPi->SetLineColor(4);
		hLnDiffPi->Draw("same");
		canvasSave(1,0);
		//waitPrimitive("r_lhood","w");
		if(fVerbose) gROOT->SetBatch(0);
		tree.Fill();
	}
	/*fHist0->Write();
	fHist1->Write();
	fHist2->Write();
	fHist3->Write();
	fHist4->Write();
	fHist5->Write();*/
	aSpreadP->Write();
	aSpreadPi->Write();
	hLnDiffP->SetName("Psep");
	hLnDiffP->Write();
	hLnDiffPi->SetName("Pisep");
	hLnDiffPi->Write();
	file.Write();
}

Int_t g_num =0;
Bool_t PrtLutReco::FindPeak(Double_t& cherenkovreco, Double_t& spr, Double_t a){
	cherenkovreco=0;
	spr=0;
	//  gStyle->SetCanvasPreferGL(kTRUE);
  
	if(fHist->GetEntries()>20 ){
		gROOT->SetBatch(1);
		Int_t nfound = fSpect->Search(fHist,1,"",0.9); //0.6
		if(nfound>0) cherenkovreco = fSpect->GetPositionX()[0];
		else cherenkovreco =  fHist->GetXaxis()->GetBinCenter(fHist->GetMaximumBin());

		fFit->SetParameters(100,cherenkovreco,0.010,10);   // peak
		// fFit->SetParameter(1,cherenkovreco);   // peak
		// fFit->SetParameter(2,0.005); // width
		fFit->SetParLimits(0,0,1E6);
		fFit->SetParLimits(1,cherenkovreco-0.04,cherenkovreco+0.04); 
		fFit->SetParLimits(2,0.005,0.030); // width
		//fHist->Fit("fgaus","M","",cherenkovreco-0.05,cherenkovreco+0.05);
		//fFit->FixParameter(3,fFit->GetParameter(3)); // width
		fHist->Fit("fgaus","M","",cherenkovreco-0.035,cherenkovreco+0.035);
		cherenkovreco = fFit->GetParameter(1);
		spr = fFit->GetParameter(2); 
		if(fVerbose>1) gROOT->SetBatch(0);
    
		Bool_t storePics(false);
		if(storePics){
			canvasAdd("r_tangle",800,400);
			fHist->SetTitle(Form("theta %3.1f", a));
			fHist->SetMinimum(0);
			fHist->Draw();
       
			canvasAdd("r_time",800,400);
			fHist1->SetTitle(Form("theta %3.1f", a));
			fHist1->SetLineColor(2);
			fHist1->Draw();
			fHist2->Draw("same");

			canvasAdd("r_diff",800,400);
			fHist0->SetTitle(Form("theta %3.1f", a));
			fHist0->Draw();
    
			canvasAdd("r_cm",800,400);
			fHist3->SetTitle(Form("theta %3.1f", a));
			fHist3->Draw("colz");

			waitPrimitive("r_cm");
			canvasSave(1,0);
			canvasDel("*");
      
			if(fVerbose==3){
				TCanvas* c2 = new TCanvas("c2","c2",0,0,800,400);
				c2->Divide(2,1);
				c2->cd(1);
     
				fHist4->SetStats(0);
				fHist4->SetTitle(Form("Calculated from LUT, #theta = %3.1f#circ", a));
				fHist4->Draw("colz");
				Double_t x0(0), y0(0), theta(cherenkovreco);
				FitRing(x0,y0,theta);
				TVector3 corr(x0,y0,1-TMath::Sqrt(x0*x0+y0*y0));
				std::cout<<"Tcorr "<< corr.Theta()*1000<< "  Pcorr "<< corr.Phi() <<std::endl;

				TLegend *leg = new TLegend(0.5,0.7,0.85,0.87);
				//      leg->SetFillColor(0);
				//leg->SetFillColorAlpha(0,0.8);
				leg->SetFillStyle(0);
				//leg->SetFillStyle(4000); 
				leg->SetBorderSize(0);
				leg->AddEntry((TObject*)0,Form("Entries %0.0f",fHist4->GetEntries()),"");
				leg->AddEntry((TObject*)0,Form("#Delta#theta_{c} %f [mrad]",corr.Theta()*1000),"");
				leg->AddEntry((TObject*)0,Form("#Delta#varphi_{c} %f [mrad]",corr.Phi()),"");
				leg->Draw();

				TArc *arc = new TArc(x0,y0,theta);
				arc->SetLineColor(kRed);
				arc->SetLineWidth(1);
				arc->SetFillStyle(0);
				arc->Draw();
				gg_i=0;
				gg_gr.Set(0);

				c2->cd(2);
				gStyle->SetOptStat(1110); 
				fHist5->SetTitle(Form("True from MC, #theta = %d#circ", int(a)));
				fHist5->Draw("colz");

				c2->Print(Form("spr/tcorr_%d.png", int(a)));
				c2->Modified();
				c2->Update();
				c2->WaitPrimitive("");
			}
		}
	}

	if(fVerbose<2) gROOT->SetBatch(0);
	fHist->Reset();
	fHist0->Reset();
	fHist1->Reset();
	fHist2->Reset();
	fHist3->Reset();
	fHist4->Reset();

	return (cherenkovreco>0 && cherenkovreco<1);
}

void circleFcn(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t) {
	Int_t np = gg_gr.GetN();
	f = 0;
	Double_t *x = gg_gr.GetX();
	Double_t *y = gg_gr.GetY();
	for (Int_t i=0;i<np;i++) {
		Double_t u = x[i] + par[0];
		Double_t v = y[i] + par[1];
		Double_t dr = par[2] - TMath::Sqrt(u*u+v*v);
		f += dr*dr;  
	}
	std::cout<<"fcn  "<< f<<std::endl;
  
}

void circleFcn2(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t) {
	Int_t np = gg_gr.GetN();
	f = 0;
	Double_t *x = gg_gr.GetX();
	Double_t *y = gg_gr.GetY();
	for (Int_t i=0;i<np;i++) {
		Double_t u = x[i] + par[0];
		Double_t v = y[i] + par[1];
		Double_t dr = par[2] - TMath::Sqrt(u*u+v*v);
		if(dr>0.07) f += dr*dr; 
		else f += fabs(dr);
	}
}

void PrtLutReco::FitRing(Double_t& x0, Double_t& y0, Double_t& theta){
	TGraph ff_gr;
	Int_t ff_i(0);
	Int_t np = gg_gr.GetN();
	Double_t *x = gg_gr.GetX();
	Double_t *y = gg_gr.GetY();
	for (Int_t i=0;i<np;i++) {
		if( fabs(theta - TMath::Sqrt(x[i]*x[i]+y[i]*y[i]))<0.05) {
			ff_gr.SetPoint(ff_i,x[i],y[i]);
			ff_i++;
		}
	}
	gg_gr = ff_gr;

	//Fit a circle to the graph points
	TVirtualFitter::SetDefaultFitter("Minuit");  //default is Minuit
	TVirtualFitter *fitter = TVirtualFitter::Fitter(0, 3);
	fitter->SetPrecision(0.00000001);
	fitter->SetMaxIterations(1000);

	fitter->SetFCN(circleFcn);
	fitter->SetParameter(0, "x0",   0.03, 0.01, -0.05,0.05);
	fitter->SetParameter(1, "y0",   0, 0.01, -0.05,0.05);
	fitter->SetParameter(2, "R",    theta, 0.01, theta-0.05,theta+0.05);

	//fitter->FixParameter(0);
	//fitter->FixParameter(1);
	fitter->FixParameter(2);
	Double_t arglist[1] = {0};
	fitter->ExecuteCommand("MINIMIZE", arglist, 0);

	// fitter->SetFCN(circleFcn2);
	// fitter->ExecuteCommand("MINIMIZE", arglist, 0);

	x0 = fitter->GetParameter(0);
	y0 = fitter->GetParameter(1);
	theta = fitter->GetParameter(2);
}

Int_t PrtLutReco::FindPdg(Double_t mom, Double_t cangle){
	Int_t pdg[]={11,13,211,321,2212};
	Double_t mass[] = {0.000511,0.1056584,0.139570,0.49368,0.9382723};
	// Int_t pdg[]={211,321,2212};
	// Double_t mass[] = {0.139570,0.49368,0.9382723};
	Double_t tdiff, diff=100;
	Int_t minid=0;
	for(Int_t i=0; i<5; i++){
		tdiff = fabs(cangle - acos(sqrt(mom*mom + mass[i]*mass[i])/mom/1.46907)); //1.46907 - fused silica
		if(tdiff<diff){
			diff = tdiff;
			minid = i;
		}
	}
	return pdg[minid]; 
}


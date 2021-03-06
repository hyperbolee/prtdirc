#define prt__sim
#include "../src/PrtHit.h"
#include "../src/PrtEvent.h"
#include "../../prttools/prttools.C"

void drawScan(TString infile="../build/hits.root"){
  // infile="/media/l/hex/dirc/data/beam_15188064753C0.root";
  //infile="/media/l/hex/dirc/data/beam_15181040321C.root";
  
  fSavePath = "scan3";
  PrtInit(infile,1); //digi
  
  Int_t itest(0);
  PrtHit fHit;
  for (Int_t ievent=0; ievent<1; ievent++)// fCh->GetEntries(); ievent++){
    PrtNextEvent(ievent,1000);
    for(Int_t h=0; h<fEvent->GetHitSize(); h++){
      fHit = fEvent->GetHit(h);
      Int_t mcpid = fHit.GetMcpId();
      Int_t pixid = fHit.GetPixelId()-1;
      
      Double_t time = fHit.GetLeadTime();
      fhDigi[mcpid]->Fill(pixid%8, pixid/8);
    }
  }
  itest = fTest1+50;
  //  drawDigi("m,p,v\n",2,-2,-2);
  drawDigi("m,p,v\n",3,-2,-2);
  cDigi->cd();
  (new TPaletteAxis(0.90,0.1,0.94,0.90,fhDigi[0]))->Draw();
   
  cDigi->SetName(Form("sc_%d_%d",fAngle,fMomentum/1000));
  canvasAdd(cDigi);  
  canvasSave(1,0);
  
}

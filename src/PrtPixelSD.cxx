#include "PrtPixelSD.h"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include <TVector3.h>

#include "PrtEvent.h"
#include "PrtPrizmHit.h"

#include "PrtRunAction.h"
#include "PrtManager.h"

PrtPixelSD::PrtPixelSD( const G4String& name, 
			const G4String& hitsCollectionName,
			G4int nofCells)
  : G4VSensitiveDetector(name){
  collectionName.insert(hitsCollectionName);
}

PrtPixelSD::~PrtPixelSD(){ 
}

void PrtPixelSD::Initialize(G4HCofThisEvent* hce){

 // TTree *gTree = new TTree("Prt","Prototype hits tree");
 // Event *fHit = 0;
 // gTree->Branch("event", "Event", &event, 64000, 0);

  // // Create hits collection
  // fHitsCollection 
  //   = new B4cCalorHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // // Add this collection in hce
  // G4int hcID 
  //   = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  // hce->AddHitsCollection( hcID, fHitsCollection ); 

  // // Create hits
  // // fNofCells for cells + one more for total sums 
  // for (G4int i=0; i<fNofCells+1; i++ ) {
  //   fHitsCollection->insert(new B4cCalorHit());
  // }
 
  //PrtManager::Instance()->AddEvent(PrtEvent());
}

G4bool PrtPixelSD::ProcessHits(G4Step* step, G4TouchableHistory* hist){  
  // // energy deposit
  // G4double edep = step->GetTotalEnergyDeposit();
  
  // // step length
  // G4double stepLength = 0.;
  // if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
  //   stepLength = step->GetStepLength();
  // }

  // if ( edep==0. && stepLength == 0. ) return false;     

  if(step == 0) return false;
 
  //G4ThreeVector translation = hist->GetTranslation();
  //G4ThreeVector localpos = step->GetPreStepPoint()->GetPhysicalVolume()->GetObjectTranslation();
  G4TouchableHistory* touchable = (G4TouchableHistory*)(step->GetPostStepPoint()->GetTouchable());

  // Get cell id 
  G4int layerNumber = touchable->GetReplicaNumber(0);
  //G4cout<< " PixelId = "<<layerNumber << G4endl;
  G4Track* track = step->GetTrack();
  const G4DynamicParticle* dynParticle = track->GetDynamicParticle();
  G4ParticleDefinition* particle = dynParticle->GetDefinition();  
  G4String ParticleName = particle->GetParticleName();
   
  G4ThreeVector globalpos = step->GetPostStepPoint()->GetPosition();
  G4ThreeVector localpos = touchable->GetHistory()->GetTopTransform().TransformPoint(globalpos);
  G4ThreeVector translation = touchable->GetHistory()->GetTopTransform().Inverse().TransformPoint(G4ThreeVector(0,0,0));
  G4ThreeVector inPrismpos = touchable->GetHistory()->GetTransform( 1 ).TransformPoint(globalpos);
  G4ThreeVector g4mom = track->GetVertexMomentumDirection(); //track->GetMomentum();
  G4ThreeVector g4pos = track->GetVertexPosition();
 
  TVector3 globalPos(inPrismpos.x(),inPrismpos.y(),inPrismpos.z());
  //TVector3 globalPos(globalpos.x(),globalpos.y(),globalpos.z());
  TVector3 localPos(localpos.x(),localpos.y(),localpos.z());
  translation=touchable->GetHistory()->GetTransform( 1 ).TransformPoint(translation);
  TVector3 digiPos(translation.x(),translation.y(),translation.z());
  TVector3 momentum(g4mom.x(),g4mom.y(),g4mom.z());
  G4ThreeVector lp = touchable->GetHistory()->GetTransform(1).TransformPoint(g4pos); //pos in wDirc
  TVector3 position(lp.x(),lp.y(),lp.z());
  
  // information form prizm
  G4SDManager* fSDM = G4SDManager::GetSDMpointer();
  G4RunManager* fRM = G4RunManager::GetRunManager();
  G4int collectionID = fSDM->GetCollectionID("PrizmHitsCollection");
  const G4Event* currentEvent = fRM->GetCurrentEvent();
  G4HCofThisEvent* HCofEvent = currentEvent->GetHCofThisEvent();
  PrtPrizmHitsCollection* prizmCol = (PrtPrizmHitsCollection*)(HCofEvent->GetHC(collectionID));
 
  Double_t pathId = 0;
  Int_t refl=0;
  for (G4int i=0;i<prizmCol->entries();i++){
    PrtPrizmHit* phit = (*prizmCol)[i];
    if(phit->GetTrackID()==track->GetTrackID()) {
      refl++;
      pathId += phit->GetNormalId()*1000*refl;
	  // std::cout << "             pathId = " << pathId << std::endl;
	  // std::cout << "phit->GetNormalId() = " << phit->GetNormalId() << std::endl;
	  // std::cout << "               refl = " << refl << std::endl << std::endl;
    }
  }

  //std::cout<<"Number of reflections: "<<refl <<std::endl;

  PrtHit hit;
  hit.SetMcpId(touchable->GetReplicaNumber(1));
  Int_t pixid = touchable->GetReplicaNumber(0);
  hit.SetPixelId(pixid);
  hit.SetGlobalPos(globalPos);
  hit.SetLocalPos(localPos);
  hit.SetDigiPos(digiPos);
  hit.SetPosition(position);
  hit.SetMomentum(momentum);
  if(PrtManager::Instance()->GetRunType()==6){
    G4ThreeVector mominend = step->GetPostStepPoint()->GetMomentum();
    TVector3 mominendv(mominend.x(),mominend.y(),mominend.z());
    hit.SetMomentum(mominendv);
  }
  hit.SetParticleId(track->GetTrackID());
  hit.SetParentParticleId(track->GetParentID());
  hit.SetNreflectionsInPrizm(refl-1);
  hit.SetPathInPrizm(pathId);
  hit.SetCherenkovMC(PrtManager::Instance()->GetCurrentCherenkov());
  // time since track created

  G4double time = step->GetPreStepPoint()->GetLocalTime();
  if(PrtManager::Instance()->GetRunType()==0) time = G4RandGauss::shoot(time,0.2); //resolution [ns]
  hit.SetLeadTime(time);
  Double_t wavelength = 1.2398/(track->GetMomentum().mag()*1E6)*1000;
  hit.SetTotTime(wavelength); //set photon wavelength
  // time since event created
  // step->GetPreStepPoint()->GetGlobalTime()*1000
 
  PrtManager::Instance()->AddHit(hit);


  if(PrtManager::Instance()->GetRunType()==0){
    //charge sharing for 8x8 MCP
    Double_t pixdim(53/16.),chargesig(1),threshold(0.3);
    Double_t x(localPos.x()), y(localPos.y());
    Int_t p(pixid);
    Bool_t ok(false);
    Double_t expd = exp(-(pixdim-fabs(x))/chargesig);
    
    if(x<0 && pixid%8!=1 && expd>G4UniformRand() && expd<threshold){ok=true; p-=1;}
    if(x>0 && pixid%8!=0 && expd>G4UniformRand() && expd<threshold){ok=true; p+=1;}
    expd = exp(-(pixdim-fabs(y))/chargesig);
    if(y<0 && pixid>8    && expd>G4UniformRand() && expd<threshold){ok=true; p-=8;}
    if(y>0 && pixid<57   && expd>G4UniformRand() && expd<threshold){ok=true; p+=8;}
 
    if(ok) {
      hit.SetPixelId(p);
      PrtManager::Instance()->AddHit(hit);
    }
  }
  
  // // Get hit accounting data for this cell
  // B4cCalorHit* hit = (*fHitsCollection)[layerNumber];
  // if ( ! hit ) {
  //   G4ExceptionDescription msg;
  //   msg << "Cannot access hit " << layerNumber; 
  //   G4Exception("PrtPixelSD::ProcessHits()",
  //     "MyCode0004", FatalException, msg);
  // }         

  // // Get hit for total accounting
  // B4cCalorHit* hitTotal 
  //   = (*fHitsCollection)[fHitsCollection->entries()-1];
  
  // // Add values
  // hit->Add(edep, stepLength);
  // hitTotal->Add(edep, stepLength); 
      
  return true;
}

void PrtPixelSD::EndOfEvent(G4HCofThisEvent*){ 
  G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  if(eventNumber%1==0 && PrtManager::Instance()->GetRunType()==0) std::cout<<"Event # "<<eventNumber <<std::endl;
  if(eventNumber%1000==0 && PrtManager::Instance()->GetRunType()!=0) std::cout<<"Event # "<<eventNumber <<std::endl;
  PrtManager::Instance()->Fill();
}


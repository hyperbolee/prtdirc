#include "PrtPrimaryGeneratorAction.h"
#include "PrtPrimaryGeneratorMessenger.h"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "PrtManager.h"

PrtPrimaryGeneratorAction::PrtPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  //create a messenger for this class
  fGunMessenger = new PrtPrimaryGeneratorMessenger(this);

  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e+");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleTime(0.0*ns);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  fParticleGun->SetParticleEnergy(500.0*keV);
}

PrtPrimaryGeneratorAction::~PrtPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

void PrtPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  G4double x,y,z;
  G4double radiatorL = PrtManager::Instance()->GetRadiatorL();
  G4double radiatorW = PrtManager::Instance()->GetRadiatorW();
  G4double radiatorH = PrtManager::Instance()->GetRadiatorH();

  PrtManager::Instance()->AddEvent(PrtEvent());
  if(PrtManager::Instance()->GetBeamDinsion() == -1){ // random momentum
    fParticleGun->SetParticleMomentum(G4ThreeVector(0, 0, 4.0*GeV*G4UniformRand()));
  }

  if(PrtManager::Instance()->GetBeamDinsion() > 0){ // smearing and divergence
    G4double sigma = PrtManager::Instance()->GetBeamDinsion()*mm;
    z = fParticleGun->GetParticlePosition().z();
    x = G4RandGauss::shoot(0,sigma);
    y = G4RandGauss::shoot(0,sigma);
    
    fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
    PrtManager::Instance()->Event()->SetPosition(TVector3(x,y,z));
  }
  if(PrtManager::Instance()->GetRunType() == 1){ // LUT generation
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,radiatorL/2.-0.1));
    G4double angle = -G4UniformRand()*M_PI;
    G4ThreeVector vec(0,0,1);
    vec.setTheta(acos(G4UniformRand()));
    vec.setPhi(2*M_PI*G4UniformRand());
	//    vec.rotateY(-M_PI/2.);

	// to see multiple photons all hitting one pixel
	// all with only 1 bottom reflection
    //vec.setTheta(M_PI/10 + G4UniformRand()/50);
	//vec.setPhi(999*M_PI/1000);//+G4UniformRand()/50);
    
    fParticleGun->SetParticleMomentumDirection(vec);
  }
  if(PrtManager::Instance()->GetRunType() == 5){ // calibration light
    G4double shift = PrtManager::Instance()->GetShift();
    
    fParticleGun->SetParticlePosition(G4ThreeVector(-radiatorL/2.+0.1-shift,0,5+tan(45*M_PI/180.)*shift+25));
    G4double angle = -G4UniformRand()*M_PI;
    G4ThreeVector vec(0,0,1);
    vec.setTheta(acos(G4UniformRand()));
    vec.setPhi(2*M_PI*G4UniformRand());
    
    vec.rotateY(-M_PI/2.);
    fParticleGun->SetParticleMomentumDirection(vec);
  }
  if(PrtManager::Instance()->GetRunType() == 6){ // for determining focal plane of the lens
    G4double shiftx = -radiatorL/2.+0.1;
    G4double shifty = radiatorW/2. - G4UniformRand()*radiatorW;
    G4double shiftz = radiatorH/2. - G4UniformRand()*radiatorH;

    //fParticleGun->SetParticlePosition(G4ThreeVector(shiftx,shifty,shiftz));
    fParticleGun->SetParticlePosition(G4ThreeVector(-radiatorL/2. +10.1, 0,-5));
    G4double angle = -G4UniformRand()*M_PI;
    G4ThreeVector vec(0,0,1);
    //vec.setTheta(M_PI/2.+angle);
    //vec.setTheta(acos(G4UniformRand()));
    //vec.setPhi(2*M_PI*G4UniformRand());
    
    vec.rotateY(-M_PI/2.);
    fParticleGun->SetParticleMomentumDirection(vec);

    fParticleGun->GeneratePrimaryVertex(anEvent);
    shiftx = -radiatorL/2.+0.1;
    shifty = radiatorW/2. - G4UniformRand()*radiatorW;
    shiftz = radiatorH/2. - G4UniformRand()*radiatorH;
    //fParticleGun->SetParticlePosition(G4ThreeVector(shiftx,shifty,shiftz));
    fParticleGun->SetParticlePosition(G4ThreeVector(-radiatorL/2. +10.1,0,5));
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
 
  G4ThreeVector dir = fParticleGun->GetParticleMomentumDirection();
  dir *= fParticleGun->GetParticleMomentum();
  PrtManager::Instance()->SetMomentum(TVector3(dir.x(),dir.y(),dir.z()));
}

void PrtPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

void PrtPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
       "the particleGun is not an opticalphoton " << 
       fParticleGun->GetParticleDefinition()->GetParticleName()<< G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);
}

#include "PrtSteppingAction.h"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"

#include "G4TrackingManager.hh"

#include "PrtManager.h"

PrtSteppingAction::PrtSteppingAction()
	: G4UserSteppingAction()
{ 
	fScintillationCounter = 0;
	fCerenkovCounter      = 0;
	fEventNumber = -1;
}

PrtSteppingAction::~PrtSteppingAction(){ }


void PrtSteppingAction::UserSteppingAction(const G4Step* step)
{
	G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	if (eventNumber != fEventNumber) {
		// G4cout << " Number of Scintillation Photons in previous event: "
		//        << fScintillationCounter << G4endl;
		// G4cout << " Number of Cerenkov Photons in previous event: "
		//        << fCerenkovCounter << G4endl;
		fEventNumber = eventNumber;
		fScintillationCounter = 0;
		fCerenkovCounter = 0;
	}

	G4Track* track = step->GetTrack();
	int parentId = track->GetParentID();

	// std::cout<<"parentId   "<<parentId <<std::endl;
 

	//  G4cout<<step->GetPreStepPoint()->GetPhysicalVolume()->GetName()  <<" - "
	// 	<<step->GetPostStepPoint()->GetPhysicalVolume()->GetName() <<"  "<< G4endl;
	//if(step->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="Bar" && step->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="ExpHall" ) track->SetTrackStatus(fStopAndKill);
	//if(step->GetPreStepPoint()->GetPosition().x()>10 ) track->SetTrackStatus(fStopAndKill);

	G4String ParticleName = track->GetDynamicParticle()->
		GetParticleDefinition()->GetParticleName();

	// make sure the particle doesn't go out of the world before calling the name
	//if(ParticleName == "e-")
	//	track->SetTrackStatus(fStopAndKill);
	
	if(ParticleName == "opticalphoton" && track->GetNextVolume())
	{
		G4StepPoint* preStepPoint = step->GetPreStepPoint();
		G4String prevolume = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
		G4String postvolume = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();
		
		if( prevolume=="wBar" && postvolume=="wLens1")
		{
			double proptime = track->GetLocalTime();
			PrtManager::Instance()->SetPropTime(proptime); // set propogation time of photon inside bar
			//std::cout << "PROPAGATION TIME " << proptime << std::endl;
			double rad2deg = 180/CLHEP::pi;
			double deg2rad = 1/rad2deg;
			
			G4ThreeVector worldPosition = preStepPoint->GetPosition();
			G4ThreeVector localPosition = preStepPoint->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(worldPosition);
			G4ThreeVector lensMom = step->GetPreStepPoint()->GetMomentumDirection();
			//std::cout << "BEFORE\t" << lensMom.theta() << std::endl;
			//std::cout << "BEFORE\t" << lensMom.x() << "\t" << lensMom.y() << "\t" << lensMom.z() << std::endl;
			lensMom.rotateY(PrtManager::Instance()->GetAngle());
			//std::cout << "AFTER\t" << lensMom.theta() << std::endl;
			//std::cout << "AFTER\t" << lensMom.x() << "\t" << lensMom.y() << "\t" << lensMom.z() << std::endl;
			//std::cout << "ROTATED BY " << PrtManager::Instance()->GetAngle()*rad2deg << " DEGREES" << std::endl;
			//TVector3 lensMomT(localPosition.x(),localPosition.y(),localPosition.z());
			TVector3 lensMomT(lensMom.x(),lensMom.y(),lensMom.z());
			PrtManager::Instance()->SetLensMom(lensMomT);

			//track->SetTrackStatus(fStopAndKill); // testing
			//std::cout << "WORLD POSITION:\t" << worldPosition.x() << std::endl;
			//std::cout << "LOCAL POSITION:\t" << localPosition.x() << std::endl;
		}
	}
  
	// std::cout<<"ParticleName "<<ParticleName <<std::endl;
  
	if (ParticleName == "opticalphoton")
		return;

	const std::vector<const G4Track*>* secondaries =
		step->GetSecondaryInCurrentStep();
  
	if (secondaries->size()>0) {
		for(unsigned int i=0; i<secondaries->size(); ++i) {
			if (secondaries->at(i)->GetParentID()>0) {
				if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition()
				   == G4OpticalPhoton::OpticalPhotonDefinition()){
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
						== "Scintillation")fScintillationCounter++;
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName()
						== "Cerenkov")fCerenkovCounter++;
				}
			}
		}
	}
}



#include "PrtDetectorConstruction.h"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "PrtManager.h"
#include "PrtTriggerSD.h"
#include "PrtBarSD.h"
#include "PrtPrizmSD.h"
#include "PrtPixelSD.h"

PrtDetectorConstruction::PrtDetectorConstruction()
	: G4VUserDetectorConstruction(){

	fGeomId = PrtManager::Instance()->GetGeometry();
	fMcpLayout = PrtManager::Instance()->GetMcpLayout();
	fLensId = PrtManager::Instance()->GetLens();
 
	fNRow = 3;
	fNCol = 5;
  
	fHall[0] = 1000; fHall[1] = 500; fHall[2] = 2000;
	fBar[0] = 17; fBar[1] = 32; fBar[2] =1250;
	fMirror[0] = 20; fMirror[1] = 40; fMirror[2] =1;
	fPrizm[0] = 170; fPrizm[1] = 300; fPrizm[3] = 50;  fPrizm[2] = fPrizm[3]+fPrizm[1]*tan(45*deg);
	fMcpTotal[0] = fMcpTotal[1] = 53+6; fMcpTotal[2]=1;
	fMcpActive[0] = fMcpActive[1] = 53; fMcpActive[2]=1;
	fLens[0] = fLens[1] = 40; fLens[2]=10;

	
	if(fLensId == 2){
		fLens[0] = 50; fLens[1] = 175; fLens[2]=14.4;
	}
	if(fLensId == 3){
		fLens[0] = 60; fLens[1] = 60; fLens[2]=15;
	}
	if(fLensId == 4 || fLensId == 5){
		fLens[0] = 50; fLens[1] = 50; fLens[2]=5.7;
	}
	if(fLensId == 6){
		fLens[0] = 26; fLens[1] = 160; fLens[2]=10.9;
	}
	if(fLensId == 7){
		fLens[0] = 60; fLens[1] = 60; fLens[2]=13;
	}
	if(fLensId == 8){
		fLens[0] = 60; fLens[1] = 60; fLens[2]=11;
	}

	if(fMcpLayout == 2012){
		fNCol = 3;
		fPrizm[2] = 30+fPrizm[1]*tan(30*deg); fPrizm[3] = 30;
	}

	if(fMcpLayout == 2015){
		
	}

	if(fMcpLayout == 1){ // testing
		//fPrizm[0] = 1500; // width between non-slanted sides
		//fPrizm[1] = 500; // dist from bar to mcps
		//fPrizm[3] = 1300; // height at bar interface from slanted edge to base
		//fPrizm[2] = fPrizm[3]+fPrizm[1]*tan(45*deg); // lenght of mcp plane

		//PrtManager::Instance()->SetPrismStepX(fPrizm[0]/2);
		//PrtManager::Instance()->SetBeamX(fPrizm[0]/2 + fBar[1]/2);
		
	}

	if(PrtManager::Instance()->GetRadiator()==2){
		fBar[0] = 17.1;
		fBar[1] = 174.8;
		fBar[2] = 1224.9; 
		fMirror[1] = 180; 
	}
  
	// X configuration
	fPrismRadiatorStep = PrtManager::Instance()->GetPrismStepY();
	//if(fPrismRadiatorStep !=0 ) fPrismRadiatorStep = fBar[0]/2.-fPrizm[3]/2.+fPrismRadiatorStep;
	fCenterShift =  G4ThreeVector(0., 0., 0.);

	if(fGeomId == 2015){
		//fPrismRadiatorStep = fPrizm[3]/2.-fBar[0]/2.; 
		//fPrismRadiatorStep = fBar[0]/2.-fPrizm[3]/2.   +30.6;   
		//fCenterShift =  G4ThreeVector(fBar[2]/2.,0,-132);
   
		fCenterShift =  G4ThreeVector(0.5*fBar[2]-96,-0.5*fPrizm[0]+PrtManager::Instance()->GetBeamX(),-122);
	}
  
  
	PrtManager::Instance()->SetRadiatorL(fBar[2]);
	PrtManager::Instance()->SetRadiatorW(fBar[1]);
	PrtManager::Instance()->SetRadiatorH(fBar[0]);			  
	fPrtRot = new G4RotationMatrix();
	//create a messenger for this class
	fGeomMessenger = new PrtDetectorConstructionMessenger(this);

	PrtManager::Instance()->AddInfo("Initialization done");
}


PrtDetectorConstruction::~PrtDetectorConstruction(){}

G4VPhysicalVolume* PrtDetectorConstruction::Construct(){
	DefineMaterials();

	// ------------- Volumes --------------

	// The experimental Hall
	G4Box* gExpHall = new G4Box("gExpHall",fHall[0],fHall[1],fHall[2]);
	lExpHall = new G4LogicalVolume(gExpHall,defaultMaterial,"lExpHall",0,0,0);
	Double_t zshift = (PrtManager::Instance()->GetBeamZ()==-1)? 0: PrtManager::Instance()->GetBeamZ()-96;
	G4VPhysicalVolume* wExpHall  = new G4PVPlacement(0,G4ThreeVector(),lExpHall,"gExpHall",0,false,0);

	// The Trigger and The front material
	G4Box* gFront = new G4Box("gFront",200.,200.,5);
	lFront = new G4LogicalVolume(gFront,frontMaterial,"lFront",0,0,0);
	G4Box* gTrigger = new G4Box("gTrigger",20.,20.,5);
	lTrigger = new G4LogicalVolume(gTrigger,frontMaterial,"lTrigger",0,0,0);
  
	if(fGeomId == 3 || fGeomId == 2015){
		new G4PVPlacement(0,G4ThreeVector(0,0,-1200),lFront,"wFront",lExpHall,false,0);
		new G4PVPlacement(0,G4ThreeVector(0,0,1500),lTrigger,"wTrigger",lExpHall,false,0); 
	}
  
	// The DIRC
	//G4Box* gDirc = new G4Box("gDirc",400.,200.,fBar[2]/2.+fPrizm[1]+50);
	G4Box* gDirc = new G4Box("gDirc",400,500,fBar[2]/2.+fPrizm[1]+50);
	lDirc = new G4LogicalVolume(gDirc,defaultMaterial,"lDirc",0,0,0);

	G4ThreeVector dircpos = G4ThreeVector(0., 0., 0.);
	if(fCenterShift.mag() !=0){
		dircpos = fCenterShift; // G4ThreeVector(fCenterShift, 0., 0.);
		dircpos.rotateY((PrtManager::Instance()->GetAngle()-90)*deg);
	}
	if(fGeomId == 0) zshift=0;
	//tilt scan  fPrtRot->rotateX(PrtManager::Instance()->GetTest1()*deg);
	wDirc  = new G4PVPlacement(fPrtRot,dircpos+G4ThreeVector(-zshift,0,0),lDirc,"wDirc",lExpHall,false,0);

	// The DIRC cover box
	G4Box* gCover = new G4Box("gCover",1,150,fBar[2]/2.);
	G4LogicalVolume *lCover = new G4LogicalVolume(gCover, MirrorMaterial ,"lCover",0,0,0);

	if(fGeomId == 3 || fGeomId == 2015){
		new G4PVPlacement(0,G4ThreeVector(-100,0,0),lCover,"wCover",lDirc,false,0);
	}
  
	// The Bar
	G4Box* gBar = new G4Box("gBar",fBar[0]/2.,fBar[1]/2.,fBar[2]/2.);
	lBar = new G4LogicalVolume(gBar,BarMaterial,"lBar",0,0,0);
	G4double xshift = -(fBar[1]-fPrizm[0])/2.- PrtManager::Instance()->GetPrismStepX();
	if(fGeomId==2015 && PrtManager::Instance()->GetRadiator()==2) xshift = -(fBar[1]-fPrizm[0])/2.;
	wBar =  new G4PVPlacement(0,G4ThreeVector(fPrismRadiatorStep,xshift,0),lBar,"wBar", lDirc,false,0);

	// The Mirror
	G4Box* gMirror = new G4Box("gMirror",fMirror[0]/2.,fMirror[1]/2.,fMirror[2]/2.);
	lMirror = new G4LogicalVolume(gMirror,MirrorMaterial,"lMirror",0,0,0);
	wMirror =new G4PVPlacement(0,G4ThreeVector(fPrismRadiatorStep,xshift,-fBar[2]/2.-fMirror[2]/2.),lMirror,"wMirror", lDirc,false,0);

	// The Lens
 
	G4Box* gfbox = new G4Box("Fbox",fLens[0]/2.,fLens[1]/2.,fLens[2]/2.);
  
	if(fLensId == 1){ // Spherical lens
		G4double r1 = 0; // PrtManager::Instance()->GetTest1(); 
		G4double lensrad1 = (r1==0)? 73.58: r1;
		G4double lensMinThikness = 2; 

		G4ThreeVector zTrans1(0, 0, -lensrad1+fLens[2]/2.-lensMinThikness);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Sphere* gsphere = new G4Sphere("Sphere",0,lensrad1,0,360*deg,0,360*deg);
		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fbox*Sphere", gfbox, gsphere,new G4RotationMatrix(),zTrans1); 
		G4SubtractionSolid* gLens2 = new G4SubtractionSolid("Fbox-Sphere", gfbox, gsphere,new G4RotationMatrix(),zTrans1);
		lLens1 = new G4LogicalVolume(gLens1,Nlak33aMaterial,"lLens1",0,0,0); //Nlak33aMaterial  
		lLens2 = new G4LogicalVolume(gLens2,BarMaterial,"lLens2",0,0,0);
	}

	if(fLensId == 2){ // Cylindrical lens
		G4double lensrad = 73.58;
		G4double lensMinThikness = 8;
		G4ThreeVector zTrans(0, 0, -lensrad+fLens[2]/2.-lensMinThikness);
		G4Tubs* gcylinder = new G4Tubs("Cylinder",0,lensrad,fLens[1]/2.+1.1,0,360*deg);
		G4RotationMatrix* xRot = new G4RotationMatrix();
		xRot->rotateX(M_PI/2.*rad);
		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fbox*Cylinder", gfbox, gcylinder,xRot,zTrans); 
		G4SubtractionSolid* gLens2 = new G4SubtractionSolid("Fbox-Cylinder", gfbox, gcylinder,xRot,zTrans);
		lLens1 = new G4LogicalVolume(gLens1,Nlak33aMaterial,"lLens1",0,0,0); //Nlak33aMaterial  
		lLens2 = new G4LogicalVolume(gLens2,BarMaterial,"lLens2",0,0,0);
	}

	if(fLensId == 334){ // 3-component spherical lens
		G4double lensMinThikness = 2; 
  
		G4double r1 = 0; //PrtManager::Instance()->GetTest1();
		G4double r2 = 0; //PrtManager::Instance()->GetTest2();
  
		G4double lensrad1 = (r1==0)? 47.8: r1;
		G4double lensrad2 = (r2==0)? 29.1: r2;
    
 
		G4ThreeVector zTrans1(0, 0, -lensrad1-fLens[2]/2.+lensrad1-sqrt(lensrad1*lensrad1-fLens[0]/2.*fLens[0]/2.)+lensMinThikness);
		G4ThreeVector zTrans2(0, 0, -lensrad2+fLens[2]/2.-lensMinThikness);
    
		G4Sphere* gsphere1 = new G4Sphere("Sphere1",0,lensrad1,0,360*deg,0,360*deg);
		G4Sphere* gsphere2 = new G4Sphere("Sphere2",0,lensrad2,0,360*deg,0,360*deg);


		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fbox*Sphere1", gfbox, gsphere1,new G4RotationMatrix(),zTrans1); 
		G4SubtractionSolid* gLenst = new G4SubtractionSolid("Fbox-Sphere1", gfbox, gsphere1, new G4RotationMatrix(),zTrans1);

		G4IntersectionSolid* gLens2 = new G4IntersectionSolid("gLenst*Sphere2", gLenst, gsphere2, new G4RotationMatrix(),zTrans2);
		G4SubtractionSolid* gLens3 = new G4SubtractionSolid("gLenst-Sphere2", gLenst, gsphere2,new G4RotationMatrix(),zTrans2);
    
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0);
		lLens2 = new G4LogicalVolume(gLens2,Nlak33aMaterial,"lLens2",0,0,0);
		lLens3 = new G4LogicalVolume(gLens3,BarMaterial,"lLens3",0,0,0);
	}

	if(fLensId == 3){ // 3-component spherical lens
		G4double lensMinThikness = 2; 
  
		G4double r1 = 0; //PrtManager::Instance()->GetTest1();
		G4double r2 = 0; //PrtManager::Instance()->GetTest2();

		//fLens[2] = 30;
  
		r1 = (r1==0)? 47.8: r1;
		r2 = (r2==0)? 29.1: r2;
		G4double shight = 40;
		G4double bwidth = fLens[2]-lensMinThikness*2;

		G4ThreeVector zTrans1(0, 0, -r1-fLens[2]/2.+r1-sqrt(r1*r1-shight/2.*shight/2.) +lensMinThikness);
		G4ThreeVector zTrans2(0, 0, -r2-fLens[2]/2.+r2-sqrt(r2*r2-shight/2.*shight/2.) +lensMinThikness*2);

		G4Box* gfbox0 = new G4Box("Fbox0",fLens[0]/2+1.,fLens[1]/2.+1,fLens[2]/2.);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Box* gfsbox = new G4Box("Fsbox",shight/2.,fLens[1]/2.,fLens[2]/2.);
		G4Tubs* gfstube = new G4Tubs("ftube",0,shight/2.,fLens[2]/2.,0.*deg,360.*deg);

		G4Sphere* gsphere1 = new G4Sphere("Sphere1",0,r1,0,360*deg,0,360*deg);
		G4Sphere* gsphere2 = new G4Sphere("Sphere2",0,r2,0,360*deg,0,360*deg);

		G4IntersectionSolid* gbbox = new G4IntersectionSolid("bbox", gfbox, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,lensMinThikness*2)); 
		G4IntersectionSolid* gsbox = new G4IntersectionSolid("sbox", gfstube, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,-lensMinThikness*2)); 


		G4UnionSolid* gubox = new G4UnionSolid("unionbox", gbbox, gsbox,new G4RotationMatrix(),G4ThreeVector(0,0,0)); 

		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Lens1", gubox, gsphere1,new G4RotationMatrix(),zTrans1); 
		G4SubtractionSolid*  gLenst = new G4SubtractionSolid("temp", gubox, gsphere1, new G4RotationMatrix(),zTrans1);

		G4IntersectionSolid* gLens2 = new G4IntersectionSolid("Lens2", gLenst, gsphere2, new G4RotationMatrix(),zTrans2);
		G4SubtractionSolid*  gLens3 = new G4SubtractionSolid("Lens3", gLenst, gsphere2,new G4RotationMatrix(),zTrans2);
    
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0);
		lLens2 = new G4LogicalVolume(gLens2,Nlak33aMaterial,"lLens2",0,0,0);
		lLens3 = new G4LogicalVolume(gLens3,BarMaterial,"lLens3",0,0,0);
	}

	if(fLensId == 4){ // Spherical lens with air gap // f =250 , d = , w = 5.7
		G4double r1 = 0; // PrtManager::Instance()->GetTest1(); 
		G4double lensrad1 = (r1==0)? 250: r1;
		G4double lensMinThikness = 2; 

		G4ThreeVector zTrans1(0, 0, -lensrad1+fLens[2]/2.-lensMinThikness);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Sphere* gsphere = new G4Sphere("Sphere",0,lensrad1,0,360*deg,0,360*deg);
		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fbox*Sphere", gfbox, gsphere,new G4RotationMatrix(),zTrans1); 
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0); //Nlak33aMaterial
	}

	if(fLensId == 5){ // Spherical lens with air gap // f =250 , d = , w = 5.7 // black edges
		G4double r1 = 0; // PrtManager::Instance()->GetTest1(); 
		G4double lensrad1 = (r1==0)? 250: r1;
		G4double lensMinThikness = 2; 

		G4ThreeVector zTrans1(0, 0, -lensrad1+fLens[2]/2.-lensMinThikness);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Sphere* gsphere = new G4Sphere("Sphere",0,lensrad1,0,360*deg,0,360*deg);
		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fbox*Sphere", gfbox, gsphere,new G4RotationMatrix(),zTrans1);
		G4SubtractionSolid* gLens2 = new G4SubtractionSolid("Fbox-Sphere", gfbox, gsphere,new G4RotationMatrix(),zTrans1);
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0); //Nlak33aMaterial
		lLens2 = new G4LogicalVolume(gLens2,defaultMaterial,"lLens2",0,0,0);
	}

	if(fLensId == 6){ // 3-component cylindrical lens


		// if(fLensId == 3){
		// 	fLens[0] = 60; fLens[1] = 60; fLens[2]=15;
		// }
		// if(fLensId == 6){
		// 	fLens[0] = 26; fLens[1] = 160; fLens[2]=10.9;
		// }
		
		G4double lensMinThikness = 2;
		G4double shight = 17;
  
		G4double r1 = 0; //PrtManager::Instance()->GetTest1();
		G4double r2 = 0; //PrtManager::Instance()->GetTest2();
  
		r1 = (r1==0)? 27.447: r1;
		r2 = (r2==0)? 20.018: r2;

		double d1 = sqrt(r1*r1 - (shight/2.)*(shight/2.));
		double d2 = sqrt(r2*r2 - (shight/2.)*(shight/2.));
		
		G4ThreeVector zTrans1(0, 0,-fLens[2]/2.-d1+lensMinThikness);
		G4ThreeVector zTrans2(0, 0,-fLens[2]/2.-d2+2*lensMinThikness);
		G4ThreeVector zTrans3(0, 0,+lensMinThikness);

		G4Box* gfbox0 = new G4Box("Fbox0",fLens[0]/2.+1,fLens[1]/2.+1,fLens[2]/2-lensMinThikness);
		G4Box* gfsbox = new G4Box("Fsbox",shight/2.,fLens[1]/2.,fLens[2]/2.);

		//G4SubtractionSolid* gLens3 = new G4SubtractionSolid("front",gfbox,gfbox0,new G4RotationMatrix(),zTrans0);
		
		G4Tubs* gcylinder1 = new G4Tubs("Cylinder1",0,r1,fLens[1]/2.+1.1,0,360*deg);
		G4Tubs* gcylinder2 = new G4Tubs("Cylinder2",0,r2,fLens[1]/2.+1.1,0,360*deg);
		
		G4RotationMatrix* xRot = new G4RotationMatrix();
		xRot->rotateX(M_PI/2.*rad);

		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Fsbox*Cylinder1", gfsbox, gcylinder1,xRot,zTrans1); 
		G4SubtractionSolid* gLensT = new G4SubtractionSolid("Fsbox-Cylinder1", gfsbox, gcylinder1,xRot,zTrans1);
		G4IntersectionSolid* gLens2 = new G4IntersectionSolid("lensT*Cylinder2", gLensT, gcylinder2,xRot,zTrans2);
		G4SubtractionSolid* gLensT2 = new G4SubtractionSolid("Fbox-Cylinder2", gfbox, gcylinder2,xRot,zTrans2);
		G4IntersectionSolid* gLens3 = new G4IntersectionSolid("lensT2*Fbox0",gLensT2,gfbox0,new G4RotationMatrix(),zTrans3);

		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0);  
		lLens2 = new G4LogicalVolume(gLens2,Nlak33aMaterial,"lLens2",0,0,0); //Nlak33aMaterial 
		lLens3 = new G4LogicalVolume(gLens3,BarMaterial,"lLens3",0,0,0);
	}

	if(fLensId == 7){ // 3-component spherical lens, no NLaK protrusion
		G4double lensMinThikness = 2; 
  
		G4double r1 = 0; //PrtManager::Instance()->GetTest1();
		G4double r2 = 0; //PrtManager::Instance()->GetTest2();

		//fLens[2] = 30;
  
		r1 = (r1==0)? 47.8: r1;
		r2 = (r2==0)? 29.1: r2;
		G4double shight = 40;

		G4ThreeVector zTrans1(0, 0, -r1-fLens[2]/2.+r1-sqrt(r1*r1-shight/2.*shight/2.) +lensMinThikness);
		G4ThreeVector zTrans2(0, 0, -r2-fLens[2]/2.+r2-sqrt(r2*r2-shight/2.*shight/2.) +lensMinThikness*2);

		G4Box* gfbox0 = new G4Box("Fbox0",fLens[0]/2+1.,fLens[1]/2.+1,fLens[2]/2.);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Box* gfsbox = new G4Box("Fsbox",shight/2.,fLens[1]/2.,fLens[2]/2.);
		G4Tubs* gfstube = new G4Tubs("ftube",0,shight/2.,fLens[2]/2.,0.*deg,360.*deg);

		G4Sphere* gsphere1 = new G4Sphere("Sphere1",0,r1,0,360*deg,0,360*deg);
		G4Sphere* gsphere2 = new G4Sphere("Sphere2",0,r2,0,360*deg,0,360*deg);

		G4IntersectionSolid* gbbox = new G4IntersectionSolid("bbox", gfbox, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,lensMinThikness)); 
		G4IntersectionSolid* gsbox = new G4IntersectionSolid("sbox", gfstube, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,-lensMinThikness));

		G4UnionSolid* gubox = new G4UnionSolid("unionbox", gbbox, gsbox,new G4RotationMatrix(),G4ThreeVector(0,0,0)); 

		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Lens1", gubox, gsphere1,new G4RotationMatrix(),zTrans1); 
		G4SubtractionSolid*  gLenst = new G4SubtractionSolid("temp", gubox, gsphere1, new G4RotationMatrix(),zTrans1);

		G4IntersectionSolid* gLens2 = new G4IntersectionSolid("Lens2", gLenst, gsphere2, new G4RotationMatrix(),zTrans2);
		G4SubtractionSolid*  gLens3 = new G4SubtractionSolid("Lens3", gLenst, gsphere2,new G4RotationMatrix(),zTrans2);
    
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0);
		lLens2 = new G4LogicalVolume(gLens2,Nlak33aMaterial,"lLens2",0,0,0);
		lLens3 = new G4LogicalVolume(gLens3,BarMaterial,"lLens3",0,0,0);
	}

	if(fLensId == 8){ // 3-component spherical lens, no protrusion
		G4double lensMinThikness = 2; 
  
		G4double r1 = 0; //PrtManager::Instance()->GetTest1();
		G4double r2 = 0; //PrtManager::Instance()->GetTest2();

		//fLens[2] = 30;
  
		r1 = (r1==0)? 47.8: r1;
		r2 = (r2==0)? 29.1: r2;
		G4double shight = 40;

		G4ThreeVector zTrans1(0, 0, -r1-fLens[2]/2.+r1-sqrt(r1*r1-shight/2.*shight/2.));// +lensMinThikness);
		G4ThreeVector zTrans2(0, 0, -r2-fLens[2]/2.+r2-sqrt(r2*r2-shight/2.*shight/2.) +lensMinThikness);

		G4Box* gfbox0 = new G4Box("Fbox0",fLens[0]/2+1.,fLens[1]/2.+1,fLens[2]/2.);
		G4Tubs* gfbox = new G4Tubs("Fbox",0,fLens[0]/2.,fLens[2]/2.,0.*deg,360.*deg);
		G4Box* gfsbox = new G4Box("Fsbox",shight/2.,fLens[1]/2.,fLens[2]/2.);
		G4Tubs* gfstube = new G4Tubs("ftube",0,shight/2.,fLens[2]/2.,0.*deg,360.*deg);

		G4Sphere* gsphere1 = new G4Sphere("Sphere1",0,r1,0,360*deg,0,360*deg);
		G4Sphere* gsphere2 = new G4Sphere("Sphere2",0,r2,0,360*deg,0,360*deg);

		G4IntersectionSolid* gbbox = new G4IntersectionSolid("bbox", gfbox, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,0));//lensMinThikness)); 
		G4IntersectionSolid* gsbox = new G4IntersectionSolid("sbox", gfstube, gfbox0,new G4RotationMatrix(),G4ThreeVector(0,0,0));//-lensMinThikness));

		G4UnionSolid* gubox = new G4UnionSolid("unionbox", gbbox, gsbox,new G4RotationMatrix(),G4ThreeVector(0,0,0));

		G4IntersectionSolid* gLens1 = new G4IntersectionSolid("Lens1", gubox, gsphere1,new G4RotationMatrix(),zTrans1); 
		G4SubtractionSolid*  gLenst = new G4SubtractionSolid("temp", gubox, gsphere1, new G4RotationMatrix(),zTrans1);

		G4IntersectionSolid* gLens2 = new G4IntersectionSolid("Lens2", gLenst, gsphere2, new G4RotationMatrix(),zTrans2);
		G4SubtractionSolid*  gLens3 = new G4SubtractionSolid("Lens3", gLenst, gsphere2,new G4RotationMatrix(),zTrans2);
    
		lLens1 = new G4LogicalVolume(gLens1,BarMaterial,"lLens1",0,0,0);
		lLens2 = new G4LogicalVolume(gLens2,Nlak33aMaterial,"lLens2",0,0,0);
		lLens3 = new G4LogicalVolume(gLens3,BarMaterial,"lLens3",0,0,0);
	}

  
	if(fLensId != 0 && fLensId != 10){
		new G4PVPlacement(0,G4ThreeVector(fPrismRadiatorStep,xshift,fBar[2]/2.+fLens[2]/2.),lLens1,"wLens1", lDirc,false,0);
		if(fLensId != 4) new G4PVPlacement(0,G4ThreeVector(fPrismRadiatorStep,xshift,fBar[2]/2.+fLens[2]/2.),lLens2,"wLens2", lDirc,false,0);
		if(fLensId == 3 ||
		   fLensId == 6 ||
		   fLensId == 7 ||
		   fLensId == 8  )  new G4PVPlacement(0,G4ThreeVector(fPrismRadiatorStep,xshift,fBar[2]/2.+fLens[2]/2.),lLens3,"wLens3", lDirc,false,0);
	}else{
		fLens[2]=0; 
	}

	// The Prizm
	G4Trap* gPrizm = new G4Trap("gPrizm",fPrizm[0],fPrizm[1],fPrizm[2],fPrizm[3]);
	lPrizm = new G4LogicalVolume(gPrizm, BarMaterial,"lPrizm",0,0,0);
	G4RotationMatrix* xRot = new G4RotationMatrix();
	xRot->rotateX(M_PI/2.*rad);
	fPrismShift = G4ThreeVector((fPrizm[2]+fPrizm[3])/4.-fPrizm[3]/2.,0,fBar[2]/2.+fPrizm[1]/2.+fLens[2]);
	fPrismShift = G4ThreeVector((fPrizm[2]+fPrizm[3])/4.-fPrizm[3]/2.,0,fBar[2]/2.+fPrizm[1]/2.+fLens[2]);
		
	new G4PVPlacement(xRot,fPrismShift,lPrizm,"wPrizm", lDirc,false,0);

	if(fGeomId==5){ // calibration
		G4double cheight=75;
		G4double cwidth=75;
		G4double shift = PrtManager::Instance()->GetShift();
		G4Trap* gPrizmC = new G4Trap("gPrizmC",cwidth,cheight,cheight,0.00000000000001);
		lPrizmC = new G4LogicalVolume(gPrizmC, BarMaterial,"lPrizmC",0,0,0);
		G4RotationMatrix* xRotC = new G4RotationMatrix();
		xRotC->rotateX(M_PI/2.*rad);
		xRotC->rotateZ(M_PI*rad);
		G4ThreeVector fPrismShiftC = G4ThreeVector(cheight-cheight/4.+fPrizm[3]/2.+tan(45*M_PI/180.)*shift,0,fBar[2]/2.+cheight/2.+fLens[2]+shift);
		new G4PVPlacement(xRotC,fPrismShiftC,lPrizmC,"wPrizmC", lDirc,false,0);
	}
  
	// Scaning plain
	if(false){
		G4double shift = PrtManager::Instance()->GetShift();
		if(shift < 935-fPrizm[1]){
			G4Box* gScan = new G4Box("gScan",350,100,0.01);
			G4LogicalVolume *lScan = new G4LogicalVolume(gScan, BarMaterial ,"lScan",0,0,0);
			new G4PVPlacement(0,G4ThreeVector(0,0,shift),lScan,"wScan",lBar,false,0);
		}else{
			G4Box* gScan = new G4Box("gScan",350,0.01,100);
			G4LogicalVolume *lScan = new G4LogicalVolume(gScan, BarMaterial ,"lScan",0,0,0);
			new G4PVPlacement(0,G4ThreeVector(0,935-shift-150,0),lScan,"wScan",lPrizm,false,0);
		}
	}
  
	G4Box* gMcp;
	G4Box* gPixel;

	if(fMcpLayout>1){
		// The MCP
		gMcp = new G4Box("gMcp",fMcpTotal[0]/2.,fMcpTotal[1]/2.,fMcpTotal[2]/2.);
		lMcp = new G4LogicalVolume(gMcp,BarMaterial,"lMcp",0,0,0);// BarMaterial
  
		// The MCP Pixel
		int mcpDimx = 8;
		int mcpDimy = 8;
		if(fGeomId>101 && fGeomId < 2000) {
			mcpDimx = fGeomId/100;
			mcpDimy = fGeomId%100;
		}
		gPixel = new G4Box("gPixel",fMcpActive[0]/(2*(double)mcpDimx),fMcpActive[1]/(2*(double)mcpDimy),fMcpActive[2]/20.);
		lPixel = new G4LogicalVolume(gPixel,BarMaterial,"lPixel",0,0,0);

		for(int i=0; i<mcpDimx; i++){
			for(int j=mcpDimy-1; j>=0; j--){
				double shiftx = i*(fMcpActive[0]/(double)mcpDimx)-fMcpActive[0]/2.+fMcpActive[0]/(2*(double)mcpDimx);
				double shifty = j*(fMcpActive[0]/(double)mcpDimy)-fMcpActive[0]/2.+fMcpActive[0]/(2*(double)mcpDimy);
				new G4PVPlacement(0,G4ThreeVector(shiftx,shifty,0),lPixel,"wPixel", lMcp,false,8*j+i+1);      
			}
		}
 
		for(int j=0; j<fNRow; j++){
			for(int i=0; i<fNCol; i++){
				double shiftx = i*(fMcpTotal[0]+14)-fPrizm[3]/2+fMcpActive[0]/2.+2.5; // +2.5 adjustment to the prt2014 
				if(j!=1) shiftx -= 14; //(3/2.)*fMcpActive[0]/8.;
				double shifty = (fMcpTotal[0]+3)*(j-1); 

				// // cad version
				// double shiftx = i*(fMcpTotal[0]+14)-fPrizm[3]/2+fMcpActive[0]/2.; 
				// if(j!=1) shiftx += 14;
				// shiftx -= 14;
				// double shifty = j*fMcpTotal[0]-fMcpTotal[0]+3*(j-1); 
	
				if(fMcpLayout==2012){
					shiftx = i*(fMcpActive[0]+2+6)-fBar[0]/2.+fMcpActive[0]/2.-3-1;
					shifty = j*(fMcpActive[0]+9+6)-fPrizm[0]/2.+fMcpActive[0]/2.; //-fPrizm[2]/2.-fPrizm[3]/2.
				}

				if(fMcpLayout==2015){
					Double_t ms = 9;//(fPrizm[2]-5*fMcpTotal[0])/4.;
					shiftx = i*(fMcpTotal[0]+ms)-fPrizm[3]/2+fMcpActive[0]/2.;
					//if(j==1) shiftx -= 3*fMcpActive[0]/8.;
					if(j==1) shiftx -= (3/2.)*fMcpActive[0]/8.; //i*(fMcpTotal[0]+3)-fPrizm[3]/2+fMcpActive[0]/2.+2*fMcpActive[0]/8.;
					shifty = (fMcpTotal[0]+3)*(j-1);
				}
				new G4PVPlacement(0,G4ThreeVector(shiftx,shifty,fBar[2]/2.+fPrizm[1]+fMcpActive[2]/2.+fLens[2]),lMcp,"wMcp", lDirc,false,fNRow*i+j);
			}
		}
	}else{
		// for layout optimization 
		// The MCP
		gMcp = new G4Box("gMcp",fPrizm[2]/2.,fPrizm[0]/2.,fMcpTotal[2]/2.);
		lMcp = new G4LogicalVolume(gMcp,BarMaterial,"lMcp",0,0,0);
  
		// The MCP Pixel
		if(fMcpLayout==0){ //one prism-size mcp with one pixel
			gPixel = new G4Box("gPixel",fPrizm[2]/2.,fPrizm[0]/2.,fMcpActive[2]/16.);
			lPixel = new G4LogicalVolume(gPixel,BarMaterial,"lPixel",0,0,0);
			new G4PVPlacement(0,G4ThreeVector(0,0,0),lPixel,"wPixel", lMcp,false,1);
		}
    
		if(fMcpLayout==1){ //one prism-size mcp with many pixels
			int pixelId = 0;
			int mcpDimx = 80;
			int mcpDimy = 40;
      
			gPixel = new G4Box("gPixel",fPrizm[2]/(2*(double)mcpDimx),fPrizm[0]/(2*(double)mcpDimy),fMcpActive[2]/20.);
			lPixel = new G4LogicalVolume(gPixel,BarMaterial,"lPixel",0,0,0);
			for(int i=0; i<mcpDimx; i++){
				for(int j=0; j<mcpDimy; j++){
					double shiftx = i*(fPrizm[2]/(double)mcpDimx)-fPrizm[2]/2.+fPrizm[2]/(2*(double)mcpDimx);
					double shifty = j*(fPrizm[0]/(double)mcpDimy)-fPrizm[0]/2.+fPrizm[0]/(2*(double)mcpDimy);
					new G4PVPlacement(0,G4ThreeVector(shiftx,shifty,0),lPixel,"wPixel", lMcp,false,pixelId++);      
				}
			}
		}
    
		new G4PVPlacement(0,G4ThreeVector(fPrizm[2]/2.-fPrizm[3]/2.,0,fBar[2]/2.+fPrizm[1]+fMcpActive[2]/2.+fLens[2]),lMcp,"wMcp", lDirc,false,1);
    
    
	}

	const G4int num = 36; 
	G4double WaveLength[num];
	G4double PhotonEnergy[num];
	G4double PMTReflectivity[num];
	G4double EfficiencyMirrors[num];
	const G4double LambdaE = 2.0 * 3.14159265358979323846 * 1.973269602e-16 * m * GeV;
	for(int i=0;i<num;i++){
		WaveLength[i]= (300 +i*10)*nanometer;
		PhotonEnergy[num-(i+1)]= LambdaE/WaveLength[i];
		PMTReflectivity[i]=0.;
		EfficiencyMirrors[i]=0; 
	}

	/***************** QUANTUM EFFICIENCY OF BURLE AND HAMAMTSU PMT'S *****/

	//ideal pmt quantum efficiency
	G4double QuantumEfficiencyIdial[num]=
		{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0};

	// Burle PMT's 
	G4double QuantumEfficiencyB[num] =
		{0.,0.001,0.002,0.005,0.01,0.015,0.02,0.03,0.04,0.05,0.06,
		 0.07,0.09,0.1,0.13,0.15,0.17,0.2,0.24,0.26,0.28,0.282,0.284,0.286,
		 0.288,0.29,0.28,0.26,0.24,0.22,0.20,0.18,0.15,0.13,0.12,0.10};
  
	//hamamatsu pmt quantum efficiency
	G4double QuantumEfficiencyPMT[num]=
		{0.001,0.002,0.004,0.007,0.011,0.015,0.020,0.026,0.033,0.040,0.045,
		 0.056,0.067,0.085,0.109,0.129,0.138,0.147,0.158,0.170,
		 0.181,0.188,0.196,0.203,0.206,0.212,0.218,0.219,0.225,0.230,
		 0.228,0.222,0.217,0.210,0.199,0.177};

	// these quantum efficiencies have to be multiplied by geometry
	//   efficiency of given PMT's
	//   for Hamamatsu by factor 0.7
	//   for Burle by factor 0.45 
	for(G4int k=0;k<36;k++)
    {
		QuantumEfficiencyB[k] =  QuantumEfficiencyB[k] * 0.45 ;
		QuantumEfficiencyPMT[k] =  QuantumEfficiencyPMT[k] *.7;
    }
 
	// G4double QuantumEfficiency[num]= 
	//    { 1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,
	//      1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,
	//      1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};

	//  G4double QuantumEfficiencyPMT[num] =
	//    { 1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,
	//      1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,
	//      1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.,1.};
  
	/* define quantum efficiency for burle PMT's - the same efficiency is 
	   assigned to pads and also to slots !!!! */
    
	//burle pmt - bigger slots => logicPad
	G4MaterialPropertiesTable* PhotocatodBurleMPT = new G4MaterialPropertiesTable();
	PhotocatodBurleMPT->AddProperty("EFFICIENCY",  PhotonEnergy,QuantumEfficiencyB,num);
	PhotocatodBurleMPT->AddProperty("REFLECTIVITY",PhotonEnergy,PMTReflectivity,num);

 
	G4OpticalSurface* BurlePMTOpSurface= 
		new G4OpticalSurface("BurlePMTOpSurface",glisur,polished,
							 dielectric_metal);
	BurlePMTOpSurface->SetMaterialPropertiesTable(PhotocatodBurleMPT);

	// // assignment for pad
	// if(burle)
	//   new G4LogicalSkinSurface("BurlePMTSurface",logicBurPad,BurlePMTOpSurface); 

	// if(burle1)
	//   new G4LogicalSkinSurface("Burle1PMTSurface",logicBur1Pad,BurlePMTOpSurface); 

	/* hamamatsu pmt's - smaller slots => quantum efficiency again
	   assign to slot and pad */
  
	fQuantumEfficiency = QuantumEfficiencyIdial; //QuantumEfficiencyPMT;//QuantumEfficiencyIdial;
	G4MaterialPropertiesTable* PhotocatodHamamatsuMPT = new G4MaterialPropertiesTable();
	PhotocatodHamamatsuMPT->AddProperty("EFFICIENCY",  PhotonEnergy,fQuantumEfficiency,num);
	PhotocatodHamamatsuMPT->AddProperty("REFLECTIVITY",PhotonEnergy,PMTReflectivity,num);

 
	G4OpticalSurface* HamamatsuPMTOpSurface= 
		new G4OpticalSurface("HamamatsuPMTOpSurface",glisur,polished,dielectric_metal);
	HamamatsuPMTOpSurface->SetMaterialPropertiesTable(PhotocatodHamamatsuMPT);

	// // assignment to pad
	// if(hamamatsu8500)
	new G4LogicalSkinSurface("HamamatsuPMTSurface",lPixel,HamamatsuPMTOpSurface);

	// Mirror
	G4OpticalSurface* MirrorOpSurface= 
		new G4OpticalSurface("MirrorOpSurface",glisur,polished,dielectric_metal);
  
	G4double ReflectivityMirrorBar[num]={
		0.8755,0.882,0.889,0.895,0.9,0.9025,0.91,0.913,0.9165,0.92,0.923,
		0.9245,0.9285,0.932,0.934,0.935,0.936,0.9385,0.9395,0.94,
		0.9405,0.9405,0.9405,0.9405,0.94,0.9385,0.936,0.934,
		0.931,0.9295,0.928,0.928,0.921,0.92,0.927,0.9215};

	// modify mirror reflectivity for photon yield testing
	// reduce reflectivity by 20%
	//for(int i=0; i<num; i++)
	//	ReflectivityMirrorBar[i] -= 0.2;

	G4MaterialPropertiesTable *MirrorMPT = new G4MaterialPropertiesTable();
	MirrorMPT->AddProperty("REFLECTIVITY", PhotonEnergy, ReflectivityMirrorBar, num);
	MirrorMPT->AddProperty("EFFICIENCY", PhotonEnergy, EfficiencyMirrors,   num);
  
	MirrorOpSurface->SetMaterialPropertiesTable(MirrorMPT);
	new G4LogicalSkinSurface("MirrorSurface", lMirror,MirrorOpSurface);


	SetVisualization();

	return wExpHall;
}

void PrtDetectorConstruction::DefineMaterials(){
	G4String symbol;             //a=mass of a mole;
	G4double a, z,  density;      //z=mean number of protons;  

	G4int ncomponents, natoms;
	G4double fractionmass;

	// define Elements
	G4Element* H  = new G4Element("Hydrogen",symbol="H" , z=  1., a=  1.01*g/mole);
	G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z=  6., a= 12.01*g/mole);
	G4Element* N  = new G4Element("Nitrogen",symbol="N" , z=  7., a= 14.01*g/mole);
	G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z=  8., a= 16.00*g/mole);
	G4Element* Si = new G4Element("Silicon" ,symbol="Si", z= 14., a= 28.09*g/mole);
	G4Element* Al = new G4Element("Aluminum",symbol="Al", z= 13., a= 26.98*g/mole);


	// quartz material = SiO2
	G4Material* SiO2 = new G4Material("quartz",density= 2.200*g/cm3, ncomponents=2);
	SiO2->AddElement(Si, natoms=1);
	SiO2->AddElement(O , natoms=2);

	Nlak33aMaterial  = new G4Material("Nlak33a",density= 4.220*g/cm3, ncomponents=2);
	Nlak33aMaterial->AddElement(Si, natoms=1);
	Nlak33aMaterial->AddElement(O , natoms=2);

	G4Material* Vacuum = new G4Material("interGalactic", 1., 1.008*g/mole, 
										1.e-25*g/cm3, kStateGas, 
										2.73*kelvin, 3.e-18*pascal);
	G4Material* Air = new G4Material("Air"  , density= 1.290*mg/cm3, ncomponents=2);
	Air->AddElement(N, fractionmass=0.7);
	Air->AddElement(O, fractionmass=0.3);

	G4Material* Aluminum = new G4Material("Aluminum",density=2.7*g/cm3,ncomponents=1);
	Aluminum->AddElement(Al,fractionmass=1.0);

	G4Material* KamLandOil = new G4Material("KamLandOil",density=0.914*g/cm3,ncomponents=2);
	KamLandOil->AddElement(C,natoms=12);
	KamLandOil->AddElement(H,natoms=26);

	G4Material* CarbonFiber = new G4Material("CarbonFiber", density=0.145*g/cm3, ncomponents=1);
	CarbonFiber->AddElement(C,fractionmass=1.0);
			

	/* as I don't know the exact material composition,
	   I will use Epoxyd material composition and add
	   the optical property of Epotek to this material */

	G4Material* Epotek = new G4Material("Epotek",density=1.2*g/cm3,ncomponents=3);

	Epotek->AddElement(C,natoms=3);
	Epotek->AddElement(H,natoms=5);
	Epotek->AddElement(O,natoms=2);


	// liquid water
	density = 1.000*g/cm3;
	G4Material* H2O = new G4Material("Water", density, ncomponents=2);
	H2O->AddElement(H, natoms=2);
	H2O->AddElement(O, natoms=1);
  
	// aerogel
	density = 0.200*g/cm3;
	G4Material* Aerog = new G4Material("Aerogel", density, ncomponents=3);
	Aerog->AddMaterial(SiO2, fractionmass=62.5*perCent);
	Aerog->AddMaterial(H2O , fractionmass=37.4*perCent);
	Aerog->AddElement (C   , fractionmass= 0.1*perCent);


	// assign main materials
	if(fGeomId == 1) defaultMaterial = Vacuum;
	else defaultMaterial = Air; //Vacuum // material of world
	frontMaterial = CarbonFiber; 
	BarMaterial = SiO2; // material of all Bars, Quartz and Window
	OilMaterial = KamLandOil; // material of volume 1,2,3,4
	MirrorMaterial = Aluminum; // mirror material
	epotekMaterial = Epotek; // Epotek material - glue between bars


	// ------------ Generate & Add Material Properties Table ------------

	static const G4double LambdaE = 2.0 * 3.14159265358979323846 * 1.973269602e-16 * m * GeV;
	const G4int num = 36;
	G4double WaveLength[num];
	G4double Absorption[num]; // default value for absorption
	G4double AirAbsorption[num]; // absorption value for air
	G4double AirRefractiveIndex[num]; // air refractive index
	G4double PhotonEnergy[num]; // energy of photons which correspond to the given 
	// refractive or absoprtion values

	G4double PhotonEnergyNlak33a[76] = {1,1.2511,1.26386,1.27687,1.29016,1.30372,1.31758,1.33173,1.34619,1.36097,1.37607,1.39152,1.40731,1.42347,1.44,1.45692,1.47425,1.49199,1.51016,1.52878,1.54787,1.56744,1.58751,1.6081,1.62923,1.65092,1.6732,1.69609,1.71961,1.7438,1.76868,1.79427,1.82062,1.84775,1.87571,1.90452,1.93423,1.96488,1.99652,2.0292,2.06296,2.09787,2.13398,2.17135,2.21006,2.25017,2.29176,2.33492,2.37973,2.42631,2.47473,2.52514,2.57763,2.63236,2.68946,2.7491,2.81143,2.87666,2.94499,3.01665,3.09187,3.17095,3.25418,3.34189,3.43446,3.53231,3.6359,3.74575,3.86244,3.98663,4.11908,4.26062,4.41225,4.57506,4.75035,4.93961};

	/*************************** ABSORPTION COEFFICIENTS *****************************/

	// absorption of KamLandOil per 50 cm - from jjv
	G4double KamLandOilAbsorption[num]=
		{0.97469022,0.976603956,0.978511548,0.980400538,0.982258449,0.984072792,
		 0.985831062,0.987520743,0.989129303,0.990644203,0.992052894,
		 0.993342822,0.994501428,0.995516151,0.996374433,0.997063719,
		 0.997571464,0.997885132,0.997992205,0.997880183,0.997536591,
		 0.99,0.98,0.97,0.96,0.94,0.93,0.924507,0.89982,0.883299,
		 0.85657,0.842637,0.77020213,0.65727,0.324022,0.019192};

	// absorption of quartz per 1 m - from jjv
	G4double QuartzAbsorption[num] = 
		{0.999572036,0.999544661,0.999515062,0.999483019,0.999448285,
		 0.999410586,0.999369611,0.999325013,0.999276402,0.999223336,
		 0.999165317,0.999101778,0.999032079,0.998955488,0.998871172,
		 0.998778177,0.99867541,0.998561611,0.998435332,0.998294892,0.998138345,
		 0.997963425,0.997767484,0.997547418,
		 0.99729958,0.99701966,0.99670255,0.996342167,0.995931242,0.995461041,
		 0.994921022,0.994298396,0.993577567,0.992739402,0.991760297,0.990610945};
  
	// absorption of epotek per one layer - thicknes 0.001'' - from jjv
	G4double EpotekAbsorption[num] = 
		{0.99999999,0.99999999,0.99999999,0.99999999,0.99999999,
		 0.99999999,0.99999999,0.99999999,0.99999999,0.99999999,
		 0.99999999,0.99999999,0.99999999,0.99999999,0.99999999,
		 0.99999999,0.99999999,0.99999999,0.99999999,0.99999999,
		 0.99999999,0.99999999,0.99999999,0.99999999,0.99999999,
		 0.9999,0.9998,0.9995,0.999,0.998,0.997,0.996,0.9955,0.993,
		 0.9871,0.9745};

	//N-Lak 33a
	G4double Nlak33aAbsorption[76]={371813,352095,331021,310814,291458,272937,255238,238342,222234,206897,192313,178463,165331,152896,141140,130043,119585,109747,100507,91846.3,83743.1,76176.7,69126.1,62570.2,56488,50858.3,45660.1,40872.4,36474.6,32445.8,28765.9,25414.6,22372.2,19619.3,17136.9,14906.5,12910.2,11130.3,9550.13,8153.3,6924.25,5848.04,4910.46,4098.04,3398.06,2798.54,2288.32,1856.99,1494.92,1193.28,943.973,739.657,573.715,440.228,333.94,250.229,185.064,134.967,96.9664,68.5529,47.6343,32.4882,21.7174,14.2056,9.07612,5.65267,3.4241,2.01226,1.14403,0.62722,0.330414,0.166558,0.0799649,0.0363677,0.0155708,0.00623089};
  

	G4double EpotekThickness = 0.001*2.54*cm;
	for(int i=0;i<num;i++){
		WaveLength[i]= (300 +i*10)*nanometer;
		Absorption[i]= 100*m; // not true, just due to definiton -> not absorb any
		AirAbsorption[i] = 4.*cm; // if photon in the air -> kill it immediately
		AirRefractiveIndex[i] = 1.; 
		PhotonEnergy[num-(i+1)]= LambdaE/WaveLength[i];

		/* as the absorption is given per length and G4 needs 
		   mean free path length, calculate it here
		   mean free path length - taken as probability equal 1/e
		   that the photon will be absorbed */
      
		EpotekAbsorption[i] = (-1)/log(EpotekAbsorption[i])*EpotekThickness;
		QuartzAbsorption[i] = (-1)/log(QuartzAbsorption[i])*100*cm;
		KamLandOilAbsorption[i] = (-1)/log(KamLandOilAbsorption[i])*50*cm;
	}

	/**************************** REFRACTIVE INDEXES ****************************/
  
	// only phase refractive indexes are necessary -> g4 calculates group itself !!
  
	G4double QuartzRefractiveIndex[num]={
		1.456535,1.456812,1.4571,1.457399,1.457712,1.458038,1.458378,
		1.458735,1.459108,1.4595,1.459911,1.460344,1.460799,1.46128,
		1.461789,1.462326,1.462897,1.463502,1.464146,1.464833,
		1.465566,1.46635,1.46719,1.468094,1.469066,1.470116,1.471252,1.472485,
		1.473826,1.475289,1.476891,1.478651,1.480592,1.482739,1.485127,1.487793};

	G4double EpotekRefractiveIndex[num]={
		1.554034,1.555575,1.55698,1.558266,1.559454,1.56056,1.561604,
		1.562604,1.563579,1.564547,1.565526,1.566536,1.567595,
		1.568721,1.569933,1.57125,1.57269,1.574271,1.576012,
		1.577932,1.580049,1.582381,1.584948,1.587768,1.590859,
		1.59424,1.597929,1.601946,1.606307,1.611033,1.616141,1.621651,1.62758,
		1.633947,1.640771,1.64807};

	G4double KamLandOilRefractiveIndex[num]={
		1.433055,1.433369,1.433698,1.434045,1.434409,1.434793,1.435198,
		1.435626,1.436077,1.436555,1.4371,1.4376,1.4382,1.4388,1.4395,
		1.4402,1.4409,1.4415,1.4425,1.4434,1.4444,1.4455,1.4464,1.4479,1.4501,
		1.450428,1.451976,1.453666,1.455513,1.45754,1.45977,1.462231,1.464958,
		1.467991,1.471377,1.475174};

	double Nlak33aRefractiveIndex[76]={1.73816,1.73836,1.73858,1.73881,1.73904,1.73928,1.73952,1.73976,1.74001,1.74026,1.74052,1.74078,1.74105,1.74132,1.7416,1.74189,1.74218,1.74249,1.74279,1.74311,1.74344,1.74378,1.74412,1.74448,1.74485,1.74522,1.74562,1.74602,1.74644,1.74687,1.74732,1.74779,1.74827,1.74878,1.7493,1.74985,1.75042,1.75101,1.75163,1.75228,1.75296,1.75368,1.75443,1.75521,1.75604,1.75692,1.75784,1.75882,1.75985,1.76095,1.76211,1.76335,1.76467,1.76608,1.76758,1.7692,1.77093,1.77279,1.7748,1.77698,1.77934,1.7819,1.7847,1.78775,1.79111,1.79481,1.79889,1.80343,1.8085,1.81419,1.82061,1.8279,1.83625,1.84589,1.85713,1.87039};

	/* ASSIGNING REFRACTIVE AND ABSORPTION PROPERTIES TO THE GIVEN MATERIALS */

	// Quartz material => Si02
	G4MaterialPropertiesTable* QuartzMPT = new G4MaterialPropertiesTable();
	QuartzMPT->AddProperty("RINDEX",       PhotonEnergy, QuartzRefractiveIndex,num);
	QuartzMPT->AddProperty("ABSLENGTH",    PhotonEnergy, QuartzAbsorption,           num);

	// assign this parameter table to BAR material
	BarMaterial->SetMaterialPropertiesTable(QuartzMPT);

	// Air
	G4MaterialPropertiesTable* AirMPT = new G4MaterialPropertiesTable();
	AirMPT->AddProperty("RINDEX",    PhotonEnergy, AirRefractiveIndex, num);
	AirMPT->AddProperty("ABSLENGTH", PhotonEnergy, AirAbsorption,      num);
	//  assign this parameter table to the air 
	defaultMaterial->SetMaterialPropertiesTable(AirMPT);


	// KamLandOil                                                
	G4MaterialPropertiesTable* KamLandOilMPT = new G4MaterialPropertiesTable();
	KamLandOilMPT->AddProperty("RINDEX", PhotonEnergy, KamLandOilRefractiveIndex, num);
	KamLandOilMPT->AddProperty("ABSLENGTH", PhotonEnergy, KamLandOilAbsorption, num);
	// assing this parameter table  to the KamLandOil
	OilMaterial->SetMaterialPropertiesTable(KamLandOilMPT);  

	// N-Lak 33a                                                
	G4MaterialPropertiesTable* Nlak33aMPT = new G4MaterialPropertiesTable();
	Nlak33aMPT->AddProperty("RINDEX", PhotonEnergyNlak33a, Nlak33aRefractiveIndex, 76);
	Nlak33aMPT->AddProperty("ABSLENGTH",PhotonEnergyNlak33a, Nlak33aAbsorption, 76);
	Nlak33aMaterial->SetMaterialPropertiesTable(Nlak33aMPT);  

	// Epotek Glue                                        
	G4MaterialPropertiesTable* EpotekMPT = new G4MaterialPropertiesTable();
	EpotekMPT->AddProperty("RINDEX", PhotonEnergy, EpotekRefractiveIndex, num);
	EpotekMPT->AddProperty("ABSLENGTH", PhotonEnergy, EpotekAbsorption, num);
	// assign this parameter table to the epotek
	epotekMaterial->SetMaterialPropertiesTable(EpotekMPT);

}

void PrtDetectorConstruction::SetVisualization(){

	G4Colour blue = G4Colour(0.0,0.0,1.0);
	G4Colour green = G4Colour(0.0,1.0,.0);
	G4Colour red = G4Colour(1.0,0.0,.0); 
	G4Colour DircColour = G4Colour(1.,1.0,0.);

	G4VisAttributes *waExpHall = new G4VisAttributes(DircColour);
	waExpHall->SetVisibility(false);
	lExpHall->SetVisAttributes(waExpHall);

	G4VisAttributes *waDirc = new G4VisAttributes(DircColour);
	waDirc->SetVisibility(false);
	lDirc->SetVisAttributes(waDirc);

	G4VisAttributes *waBar = new G4VisAttributes(G4Colour(0.,1.,0.9,0.2));
	waBar->SetVisibility(true);
	lBar->SetVisAttributes(waBar);

	G4VisAttributes *waMirror = new G4VisAttributes(G4Colour(1.,1.,0.9));
	waMirror->SetVisibility(true);
	lMirror->SetVisAttributes(waMirror);

	G4double transp = 0.15;
	if(fLensId!=0 && fLensId!=10){
		G4VisAttributes * vaLens = new G4VisAttributes(G4Colour(0.,1.,1.,transp));
		//vaLens->SetForceWireframe(true);
		//vaLens->SetForceAuxEdgeVisible(true);
		lLens1->SetVisAttributes(vaLens);
		G4VisAttributes * vaLens1 = new G4VisAttributes(G4Colour(0.,0.5,1.0,transp));
		if(fLensId!=4) lLens2->SetVisAttributes(vaLens1);
		if(fLensId==3 ||
		   fLensId==6 ||
		   fLensId==7 ||
		   fLensId==8  ) lLens3->SetVisAttributes(vaLens);
	}

	G4VisAttributes *waPrizm = new G4VisAttributes(G4Colour(0.,0.9,0.9,0.2));
	waPrizm->SetVisibility(true);
	//waPrizm->SetForceAuxEdgeVisible(true);
	//waPrizm->SetForceSolid(true);
	lPrizm->SetVisAttributes(waPrizm);

	G4VisAttributes *waMcp = new G4VisAttributes(green);
	waMcp->SetForceWireframe(true);
	lMcp->SetVisAttributes(waMcp);

	G4VisAttributes *waPixel = new G4VisAttributes(red);
	waPixel->SetForceWireframe(true);
	lPixel->SetVisAttributes(waPixel);

}

void PrtDetectorConstruction::ConstructSDandField(){
	// Sensitive detectors
	PrtPixelSD* pixelSD = new PrtPixelSD("PixelSD", "PixelHitsCollection", 0);
	SetSensitiveDetector("lPixel",pixelSD);
	//SetSensitiveDetector("lScan",pixelSD);

	PrtPrizmSD* prizmSD = new PrtPrizmSD("PrizmSD", "PrizmHitsCollection", 0);
	SetSensitiveDetector("lPrizm",prizmSD);

	PrtTriggerSD* triggerSD = new PrtTriggerSD("TriggerSD", "TriggerHitsCollection", 0);
	SetSensitiveDetector("lTrigger",triggerSD);

	PrtBarSD* barSD = new PrtBarSD("BarSD", "BarHitsCollection", 0);
	SetSensitiveDetector("lBar",barSD);
	// Magnetic field
}

void PrtDetectorConstruction::SetRotation(G4double angle){
	fPrtRot->rotateY(-fRotAngle);
	fPrtRot->rotateY(angle);
	fRotAngle=angle;

	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void PrtDetectorConstruction::SetLens(G4int id){
 
	// if(id==0){
	//   fPrismShift.setZ(fPrismShift.z()-fLens[2]);
	// }
	// std::cout<<"id  "<<id <<std::endl;
  
	// G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void PrtDetectorConstruction::SetQuantumEfficiency(G4int id){
	const G4int num = 36;
	//ideal pmt quantum efficiency
	G4double QuantumEfficiencyIdial[num]=
		{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
		 1.0,1.0,1.0,1.0,1.0,1.0};

	// Burle PMT's 
	G4double QuantumEfficiencyB[num] =
		{0.,0.001,0.002,0.005,0.01,0.015,0.02,0.03,0.04,0.05,0.06,
		 0.07,0.09,0.1,0.13,0.15,0.17,0.2,0.24,0.26,0.28,0.282,0.284,0.286,
		 0.288,0.29,0.28,0.26,0.24,0.22,0.20,0.18,0.15,0.13,0.12,0.10};
  
	//hamamatsu pmt quantum efficiency
	G4double QuantumEfficiencyPMT[num]=
		{0.001,0.002,0.004,0.007,0.011,0.015,0.020,0.026,0.033,0.040,0.045,
		 0.056,0.067,0.085,0.109,0.129,0.138,0.147,0.158,0.170,
		 0.181,0.188,0.196,0.203,0.206,0.212,0.218,0.219,0.225,0.230,
		 0.228,0.222,0.217,0.210,0.199,0.177};
  
	if(id == 0 ) fQuantumEfficiency = QuantumEfficiencyIdial;
	if(id == 1 ) fQuantumEfficiency = QuantumEfficiencyPMT;

	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

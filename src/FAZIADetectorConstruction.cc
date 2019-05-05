#include "FAZIADetectorConstruction.hh"
#include "FAZIAPhotoDiodeSD.hh"

#include "G4SubtractionSolid.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UniformElectricField.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include <iostream>
#include "TMath.h"

using std::stringstream;
using namespace std;
using namespace CLHEP;
  FAZIADetectorConstruction::FAZIADetectorConstruction()
: G4VUserDetectorConstruction()
{
}

FAZIADetectorConstruction::~FAZIADetectorConstruction()
{
}

G4VPhysicalVolume* FAZIADetectorConstruction::Construct()
{
  //----------------Material --------------------
  G4NistManager* nist = G4NistManager::Instance();

  const G4double labTemp = CLHEP::STP_Temperature + 20.*kelvin;

  G4Element*  elCs  = new G4Element("Caesium","Cs",  55,   132.90545*g/mole);
  G4Element*  elI   = new G4Element("Iodine", "I" , 53,   126.90447*g/mole);

  G4Material* CsI = new G4Material("CsI", 4.51*g/CLHEP::cm3, 2, kStateSolid, labTemp);
  CsI -> AddElement(elCs, 1);
  CsI -> AddElement(elI,  1);

  G4double s1dist = 10.0;
  G4double s2dist = 16.0;
  G4double CsIdist = 70.0;
  G4double CsIdiode = 122.5;//1112.5

  // Quartz
  // -------
  //  density = 2.200*g/cm3; // fused quartz 
  G4Element*  elSi  = new G4Element("Silicon","Si",  14,   28.0855*g/mole);
  G4Element*  elO   = new G4Element("Oxygen", "O" , 8,   15.999*g/mole);


  G4Material *Quartz = new G4Material("Quartz",2.64*g/CLHEP::cm3 , 2, kStateSolid, labTemp);    
  Quartz->AddElement(elSi, 1) ;
  Quartz->AddElement(elO , 2) ;

  G4Material* rap_mat = nist -> FindOrBuildMaterial("G4_Al");		
  //fTargetMaterial = Quartz;
  // ------------ Generate & Add Material Properties Table ------------
  //
  G4double photonEnergy[] =
  {	1.90738*eV, 1.98368*eV, 2.06633*eV,
	2.15617*eV, 2.25418*eV, 2.36152*eV,
	2.47960*eV, 2.61011*eV, 2.75511*eV,
	2.91718*eV, 3.0995*eV};
  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  // CsI
  //fixed
  G4double refractiveIndex1[] =
  { 1.7789, 1.7820, 1.7856, 1.7897, 1.7945,
	1.8001, 1.8067, 1.8146, 1.8242, 1.8359,
	1.8506};

  assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

  G4double absorption[] =
  {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
	30.000*m, 28.500*m, 27.000*m,17.500*m, 14.500*m };

  assert(sizeof(absorption) == sizeof(photonEnergy));

  G4double scintilFast[] =
  { 1.00, 1.00, 1.00, 
	1.00, 1.00, 1.00, 
	1.00,1.00, 1.00,
	1.00, 1.00 };

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  G4double scintilSlow[] =
  { 0.01, 1.00, 2.00,
	3.00, 4.00, 5.00,
	6.00,7.00, 6.00,
	5.00, 4.00 };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

  myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
	->SetSpline(true);
  myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
	->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
	->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
	->SetSpline(true);

  myMPT1->AddConstProperty("SCINTILLATIONYIELD",10./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 0.6*us);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",3.5*us);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);

  CsI->SetMaterialPropertiesTable(myMPT1);
  // Al reflector
  G4double refractiveIndex2[] =
  { 1.7789, 1.7820, 1.7856, 1.7897, 1.7945,
	1.8001, 1.8067, 1.8146, 1.8242, 1.8359,
	1.8506};

  assert(sizeof(refractiveIndex2) == sizeof(photonEnergy));

  G4double absorption1[] =
  {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
	30.000*m, 28.500*m, 27.000*m,17.500*m, 14.500*m };

  assert(sizeof(absorption1) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();

  myMPT2->AddProperty("RINDEX",       photonEnergy, refractiveIndex2,nEntries)
	->SetSpline(true);
  myMPT2->AddProperty("ABSLENGTH",    photonEnergy, absorption1,     nEntries)
	->SetSpline(true);

  myMPT2->AddConstProperty("RESOLUTIONSCALE",1.0);
  rap_mat->SetMaterialPropertiesTable(myMPT2);
  
  // diode
  G4double refractiveIndex3[] =
  { 1.7789, 1.7820, 1.7856, 1.7897, 1.7945,
	1.8001, 1.8067, 1.8146, 1.8242, 1.8359,
	1.8506};

  assert(sizeof(refractiveIndex3) == sizeof(photonEnergy));

  G4double absorption2[] =
  {0.1*um,0.1*um,0.1*um,0.1*um,0.1*um,0.1*um,0.1*um,
  0.1*um,0.1*um,0.1*um,0.1*um,0.1*um,};

  assert(sizeof(absorption2) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();

  myMPT3->AddProperty("RINDEX",       photonEnergy, refractiveIndex3,nEntries)
	->SetSpline(true);
  myMPT3->AddProperty("ABSLENGTH",    photonEnergy, absorption2,     nEntries)
	->SetSpline(true);

  myMPT3->AddConstProperty("RESOLUTIONSCALE",1.0);
  Quartz->SetMaterialPropertiesTable(myMPT3);
  
  // -----------------------------------------------------
  // World

  G4Material* world_mat = nist -> FindOrBuildMaterial("G4_Galactic");
  G4double world_size = 10*m;

  G4Box* solidWorld =
	new G4Box("World",                       // its name
		3*world_size,                // half x
		3*world_size,                // half y
		3*world_size);               // half zNDDetectorConstruction::LANDDetectorConstruction()


  G4LogicalVolume* logicWorld =
	new G4LogicalVolume(solidWorld,          //its solid
		world_mat,           //its material
		"World");            //its name

  G4VPhysicalVolume* physWorld =
	new G4PVPlacement(0,                     //no rotation
		G4ThreeVector(),       //at (0,0,0)
		logicWorld,            //its logical volume
		"World",               //its name
		0,                     //its mother  volume
		false,                 //no boolean operation
		0,                     //copy number
		true);                 //overlaps checking


  // -----------------------------------------------------
  // Detector
  /*	 Double_t side_si = 2cm;

		 Double_t side_csi_back = 2.272cm;

		 Double_t inter_si = 0.24cm;

		 Double_t thick_si1 = 300 * KVUnits::um;
		 Double_t thick_si2 = 500 * KVUnits::um;
		 Double_t thick_csi = 10cm;*/

  G4Material* scintillator_mat = nist -> FindOrBuildMaterial("CsI");
  G4Material* Silicon_mat = nist -> FindOrBuildMaterial("G4_Si");


  // G4double sizeX = 21 * detector_size;
  // G4double sizeY = 21 * detector_size;
  // G4double sizeZ = 101 * detector_size;

  /*//Al rapping
	G4Box* outerTube = new G4Box("outerTube",sizeX/2,sizeY/2,sizeZ/2);

	G4Box* innerTube = new G4Box("innerTube",(20*mm)/2,(20*mm)/2,(100*mm)/2);

	G4SubtractionSolid*hollowTube = new G4SubtractionSolid("hollowTube",outerTube,innerTube);

  //  G4double AngleNN = -27.07*CLHEP::degree;
  //	G4RotationMatrix* yRot_SS = new G4RotationMatrix;
  //	yRot_SS -> rotateY(AngleNN);

  G4LogicalVolume* logicalDetector 
  = new G4LogicalVolume(hollowTube,rap_mat,"hollowTube");

  G4VPhysicalVolume* PhysicalDetector 
  = new G4PVPlacement(0,
  G4ThreeVector(0*mm,0*mm,-40*mm),
  logicalDetector,
  "hollowTube",
  logicWorld,
  false,
  2,
  true);*/
  G4Box* Silicon_1[4];
  G4Box* Silicon_2[4];
  G4Trd* CsIcrystal[4];
  G4Box* PhotoDiode[4];

  G4LogicalVolume* logicalDetector1[4];
  G4LogicalVolume* logicalDetector2[4];
  G4LogicalVolume* logicalDetector3[4];
  G4LogicalVolume* sensitiveDetector[4];

  G4VPhysicalVolume* PhysicalDetector1[4];
  G4VPhysicalVolume* PhysicalDetector2[4];
  G4VPhysicalVolume* PhysicalDetector3[4];
  G4PVPlacement* PhysicalSD[4];

  G4double silicon_1[4] = {11, 12, 13, 14};
  G4double silicon_2[4] = {21, 22, 23, 24};
  G4double csicrystal[4] = {31, 32, 33, 34};
  G4double csidiodenumb[4] = {41, 42, 43, 44};

  G4String SiliconName_1[4] =  {"S1Q1T1","S1Q1T2","S1Q1T3","S1Q1T4"};
  G4String SiliconName_2[4] =  {"S2Q1T1","S2Q1T2","S2Q1T3","S2Q1T4"};
  G4String CsIcrystalName[4] = {"CsQ1T1","CsQ1T2","CsQ1T3","CsQ1T4"};
  G4String CsIDiodeName[4] = {"Dio1","Dio2","Dio3","Dio4"};

  logicWorld -> SetVisAttributes (G4VisAttributes::GetInvisible());
  string TubeSurface[4] = {"Sur1","Sur2","Sur3","Sur4"};
  G4OpticalSurface* opTubeSurface[4];

  G4VisAttributes* Silicon_1VisAtt[4];
  G4VisAttributes* Silicon_2VisAtt[4];
  G4VisAttributes* CsIcrystalVisAtt[4];
  G4VisAttributes* diodeVisAtt[4];
  G4VisAttributes* CsIrapVisAtt[4];

  G4Trd* outerTube[4];
  G4Trd* innerTube[4]; 
  G4SubtractionSolid* rapping[4];
  G4LogicalVolume* csirap[4]; 
  G4VPhysicalVolume* PhysicalRap[4]; 

  G4RotationMatrix* rot1[4];
  G4RotationMatrix* rot2[4];
  G4RotationMatrix* rot3[4];

  G4SDManager* sdManager[4];  
  FAZIAPhotoDiodeSD* CsIPDSD[4];
  G4String sensername[4] = {"sd1","sd2","sd3","sd4"};

  for(int tel =0 ; tel < 1 ; tel++)
  {
	rot1[tel] = new G4RotationMatrix;
	rot2[tel] = new G4RotationMatrix;
	rot3[tel] = new G4RotationMatrix;

	//Si1
	/*rot1[tel] -> rotateX(TMath::Sin(0.0147)*TMath::Sin(pi/4+pi*(tel)/2)); 
	  rot1[tel] -> rotateY(-1*TMath::Sin(0.0147)*TMath::Cos(pi/4+pi*(tel)/2)); */

	rot1[tel] -> rotateX(0); 
	rot1[tel] -> rotateY(0); 

	Silicon_1[tel] = new G4Box(SiliconName_1[tel],(20*mm)/2,(20*mm)/2,(300*um)/2);
	logicalDetector1[tel] = new G4LogicalVolume(Silicon_1[tel] ,Silicon_mat ,SiliconName_1[tel]);
	PhysicalDetector1[tel] = new G4PVPlacement(rot1[tel],
		G4ThreeVector(s1dist*TMath::Sin(0.0)*TMath::Cos(0.0/4+0.0*(tel)/2)*mm,s1dist*TMath::Sin(0.0)*TMath::Sin(0.0/4+0.0*(tel)/2)*mm,s1dist*TMath::Cos(0.0)*mm),
		logicalDetector1[tel],
		SiliconName_1[tel],
		logicWorld,
		false,
		silicon_1[tel],
		true);

	//Si2
	/*rot2[tel] -> rotateX(TMath::Sin(0.0)*TMath::Sin(0.0/4+0.0*(tel)/2)); 
	  rot2[tel] -> rotateY(-1*TMath::Sin(0.0)*TMath::Cos(0.0/4+0.0*(tel)/2)); */
	rot2[tel] -> rotateX(0); 
	rot2[tel] -> rotateY(0); 

	Silicon_2[tel] = new G4Box(SiliconName_2[tel],(20*mm)/2,(20*mm)/2,(500*um)/2);
	logicalDetector2[tel] = new G4LogicalVolume(Silicon_2[tel] ,Silicon_mat ,SiliconName_2[tel]);
	PhysicalDetector2[tel] = new G4PVPlacement(rot2[tel],
		G4ThreeVector(s2dist*TMath::Sin(0.0)*TMath::Cos(0.0/4+0.0*(tel)/2)*mm,s2dist*TMath::Sin(0.0)*TMath::Sin(0.0/4+0.0*(tel)/2)*mm,s2dist*TMath::Cos(0.0)*mm),
		logicalDetector2[tel],
		SiliconName_2[tel],
		logicWorld,
		false,
		silicon_2[tel],
		true);

	//CsI crystal
	//rot3[tel] -> rotateX(TMath::Sin(0.0)*TMath::Sin(0.0/4+0.0*(tel)/2)); 
	//rot3[tel] -> rotateY(-1*TMath::Sin(0.0)*TMath::Cos(0.0/4+0.0*(tel)/2)); 
	rot3[tel] -> rotateX(0); 
	rot3[tel] -> rotateY(0); 

	CsIcrystal[tel] = new G4Trd(CsIcrystalName[tel],(20*mm)/2,(22.27*mm)/2,(20*mm)/2,(22.27*mm)/2,(100*mm)/2);
	logicalDetector3[tel] = new G4LogicalVolume(CsIcrystal[tel] ,scintillator_mat ,CsIcrystalName[tel]);
	PhysicalDetector3[tel] = new G4PVPlacement(rot3[tel],
		G4ThreeVector(CsIdist*TMath::Sin(0)*TMath::Cos(0.0/4+0.0*(tel)/2)*mm,CsIdist*TMath::Sin(0)*TMath::Sin(0.0/4+0.0*(tel)/2)*mm,CsIdist*TMath::Cos(0.0)*mm),
		logicalDetector3[tel],
		CsIcrystalName[tel],
		logicWorld,
		false,
		csicrystal[tel],
		true);

	//Al rapping
	outerTube[tel] = new G4Trd("outerTube",(21*mm)/2,(23.27*mm)/2,(21*mm)/2,(23.27*mm)/2,(100.5*mm)/2);
	innerTube[tel] = new G4Trd("innerTube",(20*mm)/2,(22.27*mm)/2,(20*mm)/2,(22.27*mm)/2,(100*mm)/2);
	rapping[tel] = new G4SubtractionSolid("rapping", outerTube[tel], innerTube[tel], rot3[tel], G4ThreeVector(0,0,0.25*mm));

	csirap[tel] = new G4LogicalVolume(rapping[tel],rap_mat,"rapping");

	PhysicalRap[tel]  = new G4PVPlacement(0,
		  G4ThreeVector(0,0,CsIdist-0.25*mm),
		  csirap[tel],
		  "rapping",
		  logicWorld,
		  false,
		  0,
		  true);

	//------------(Sensitive Detector)----------------------------------------------------------------------------------------------------------------
	PhotoDiode[tel] = new G4Box(CsIDiodeName[tel], 22.7*mm/2, 22.7*mm/2, 5*mm/2);
	sensitiveDetector[tel] = new G4LogicalVolume(PhotoDiode[tel],Quartz, "Dio1");
	PhysicalSD[tel] = new G4PVPlacement(rot3[tel],
		G4ThreeVector(0,0,CsIdiode),
		sensitiveDetector[tel],
		"Dio1",
		logicWorld,
		false,
		csidiodenumb[tel],
		true);


	sdManager[tel] = G4SDManager::GetSDMpointer();  

	CsIPDSD[tel] = new FAZIAPhotoDiodeSD("Dio1"/*sensername[tel]*/, "Dio1");
	sdManager[tel] -> AddNewDetector(CsIPDSD[tel]);

	sensitiveDetector[tel] -> SetSensitiveDetector(CsIPDSD[tel]);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------
	Silicon_1VisAtt[tel] = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
	Silicon_1VisAtt[tel] -> SetForceWireframe(true);
	logicalDetector1[tel] -> SetVisAttributes (Silicon_1VisAtt[tel]);

	Silicon_2VisAtt[tel] = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	Silicon_2VisAtt[tel] -> SetForceWireframe(true);
	logicalDetector2[tel] -> SetVisAttributes (Silicon_2VisAtt[tel]);

	CsIcrystalVisAtt[tel] = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
	CsIcrystalVisAtt[tel] -> SetForceWireframe(true);
	logicalDetector3[tel] -> SetVisAttributes (CsIcrystalVisAtt[tel]);

	CsIrapVisAtt[tel] = new G4VisAttributes(G4Colour(0.0,0.0,2.0));
	CsIrapVisAtt[tel] -> SetForceWireframe(true);
	csirap[tel] -> SetVisAttributes (CsIrapVisAtt[tel]);

	diodeVisAtt[tel] = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	diodeVisAtt[tel] -> SetForceWireframe(true);
	sensitiveDetector[tel] -> SetVisAttributes (diodeVisAtt[tel]);

	// ------------- Surfaces --------------
	//  
	//Csi crystal
	opTubeSurface[tel] = new G4OpticalSurface(TubeSurface[tel]);
	opTubeSurface[tel]->SetType(dielectric_metal);
	opTubeSurface[tel]->SetFinish(polished);
	opTubeSurface[tel]->SetModel(unified);

	new G4LogicalBorderSurface(TubeSurface[tel],PhysicalRap[tel],physWorld,opTubeSurface[tel]);

	//G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
	//if (opticalSurface) opticalSurface->DumpInfo();
	// Generate & Add Material Properties Table attached to the optical surfaces
	//  
	const G4int num = 2;
	G4double ephoton[num] = {2.034*eV, 4.136*eV};

	//Optical alu rap Surface
	//G4double photodiode_eff[num]  = {1., 1.};
	G4double refractiveIndex[num] = {0.48, 1.55};
	G4double specularLobe[num]    = {0.3, 0.3};
	G4double specularSpike[num]   = {0.2, 0.2};
	G4double backScatter[num]     = {0.2, 0.2};
	G4double reflecitivity[num]   = {0.90, 0.92};//0.90, 0.92

	G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

	//myST1->AddProperty("EFFICIENCY",            ephoton, photodiode_eff,  num);
	myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
	myST1->AddProperty("REFLECITIVITY",         ephoton, reflecitivity,   num);
	myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
	myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
	myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);
	//G4cout << "Tube Surface G4MaterialPropertiesTable" << G4endl;
	myST1->DumpTable();
	opTubeSurface[tel]->SetMaterialPropertiesTable(myST1);

/*	//photo diode
	opTubeSurface[tel] = new G4OpticalSurface(TubeSurface[tel]);
	opTubeSurface[tel]->SetType(dielectric_metal);
	opTubeSurface[tel]->SetFinish(polished);
	opTubeSurface[tel]->SetModel(unified);

	new G4LogicalBorderSurface(TubeSurface[tel],PhysicalDetector3[tel],physWorld,opTubeSurface[tel]);

	//G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
	//if (opticalSurface) opticalSurface->DumpInfo();
	// Generate & Add Material Properties Table attached to the optical surfaces
	//  
	const G4int num = 2;
	G4double ephoton[num] = {2.034*eV, 4.136*eV};

	//Optical alu rap Surface
	G4double photodiode_eff[num]  = {1., 1.};
	G4double refractiveIndex[num] = {0.48, 1.55};
	G4double specularLobe[num]    = {0.3, 0.3};
	G4double specularSpike[num]   = {0.2, 0.2};
	G4double backScatter[num]     = {0.2, 0.2};
	G4double reflecitivity[num]   = {0.90, 0.92};//0.90, 0.92

	G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

	myST1->AddProperty("EFFICIENCY",            ephoton, photodiode_eff,  num);
	myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
	myST1->AddProperty("REFLECITIVITY",         ephoton, reflecitivity,   num);
	myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
	myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
	myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);
	//G4cout << "Tube Surface G4MaterialPropertiesTable" << G4endl;
	myST1->DumpTable();
	opTubeSurface[tel]->SetMaterialPropertiesTable(myST1);*/
  }
  //runManager -> SetSensitiveDetector(pvp);

  //Set detector's Color


  return physWorld;
}


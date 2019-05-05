//Geant4 headers
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "FAZIAPhotoDiodeSD.hh"
#include "FAZIAPhotoDiodeHit.hh"

#include <iostream>
#include <sstream>

using namespace std;

FAZIAPhotoDiodeSD::FAZIAPhotoDiodeSD(const G4String &name, const G4String pv_name)
  :G4VSensitiveDetector(name), PVName(pv_name)
{
  G4String hitCollectionName = "HitCollection_" + PVName; 
  collectionName.insert(hitCollectionName);
//cout << "pID" << endl;
}

FAZIAPhotoDiodeSD::~FAZIAPhotoDiodeSD() 
{
}

void FAZIAPhotoDiodeSD::Initialize(G4HCofThisEvent *HCTE)
{
  hitsCollection = new G4THitsCollection<FAZIAPhotoDiodeHit>(SensitiveDetectorName, collectionName[0]);
  G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCTE -> AddHitsCollection(hcid, hitsCollection);
}

G4bool FAZIAPhotoDiodeSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
  energyDeposit = aStep -> GetTotalEnergyDeposit();
  //G4String CsIDiodeName[4] = {"Dio1","Dio2","Dio3","Dio4"};
//for(int i  = 0 ; i < 4 ; i++)
//{
  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "Dio1") && (energyDeposit!=0.))
  {
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    trackID     = aStep -> GetTrack() -> GetTrackID();
    volumeID    = aStep -> GetPreStepPoint()-> GetPhysicalVolume() -> GetCopyNo();
    parentID    = aStep -> GetTrack() -> GetParentID();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    preMomentum = aStep -> GetPreStepPoint() -> GetMomentum();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();
//cout << "pID" << endl;
    FAZIAPhotoDiodeHit *aHit = new FAZIAPhotoDiodeHit(pID ,trackID, volumeID, parentID, prePosition, preMomentum, time, energyDeposit);
    hitsCollection -> insert(aHit);
  }
// } 
  return true;
}

void FAZIAPhotoDiodeSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}

#include "FAZIASteppingAction.hh"
#include "FAZIAEventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
#include "G4Track.hh"
#include "G4Step.hh"

#include "G4ThreeVector.hh"

#include "G4EventManager.hh"

  FAZIASteppingAction::FAZIASteppingAction()
: G4UserSteppingAction()
{
}

FAZIASteppingAction::~FAZIASteppingAction()
{
}

void FAZIASteppingAction::UserSteppingAction(const G4Step* step)
{
  G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

  G4int volumeID = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetCopyNo();
  G4double edep = step -> GetTotalEnergyDeposit();
  G4double x = step -> GetDeltaPosition().x();  	
  G4double y = step -> GetDeltaPosition().y();  	
  G4double z = step -> GetDeltaPosition().z();

  //G4double moment = step -> GetDeltaMomentum();

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> FillNtupleIColumn(0, eventID);
  analysisManager -> FillNtupleIColumn(1, volumeID);
  analysisManager -> FillNtupleDColumn(2, edep);
  analysisManager -> FillNtupleDColumn(3, x);
  analysisManager -> FillNtupleDColumn(4, y);
  analysisManager -> FillNtupleDColumn(5, z);
  //analysisManager -> FillNtupleDColumn(6, moment);
  analysisManager -> AddNtupleRow();

  FAZIAEventAction *eventAction = (FAZIAEventAction *) G4EventManager::GetEventManager() -> GetUserEventAction();
if(volumeID == 11){eventAction -> AddEnergyDeposit1(edep);}
if(volumeID == 12){eventAction -> AddEnergyDeposit2(edep);}
if(volumeID == 13){eventAction -> AddEnergyDeposit3(edep);}
if(volumeID == 14){eventAction -> AddEnergyDeposit4(edep);}

if(volumeID == 21){eventAction -> AddEnergyDeposit5(edep);}
if(volumeID == 22){eventAction -> AddEnergyDeposit6(edep);}
if(volumeID == 23){eventAction -> AddEnergyDeposit7(edep);}
if(volumeID == 24){eventAction -> AddEnergyDeposit8(edep);}

if(volumeID == 31){eventAction -> AddEnergyDeposit9(edep);}
if(volumeID == 32){eventAction -> AddEnergyDeposit10(edep);}
if(volumeID == 33){eventAction -> AddEnergyDeposit11(edep);}
if(volumeID == 34){eventAction -> AddEnergyDeposit12(edep);}
}

#include "FAZIAEventAction.hh"
#include "FAZIAData.hh"
#include "FAZIAPhotoDiodeHit.hh"
#include "FAZIAPhotoDiodeSD.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "g4root.hh"

#include "TMath.h"
using namespace std;

/*  FAZIAEventAction::FAZIAEventAction()
	: G4UserEventAction()
	{
	}*/

  FAZIAEventAction::FAZIAEventAction(FAZIAData* data)
: FAZIA_data(data)
{
}

FAZIAEventAction::~FAZIAEventAction()
{
}

void FAZIAEventAction::BeginOfEventAction(const G4Event* evt)
{
  Si111edepTot = 0.;
  Si211edepTot = 0.;
  CsI11edepTot = 0.;

  Si112edepTot = 0.;
  Si212edepTot = 0.;
  CsI12edepTot = 0.;

  Si113edepTot = 0.;
  Si213edepTot = 0.;
  CsI13edepTot = 0.;

  Si114edepTot = 0.;
  Si214edepTot = 0.;
  CsI14edepTot = 0.;

  if(evt -> GetEventID()%10 == 0)  G4cout << evt -> GetEventID() << " Event Running" << G4endl;
  //G4cout << evt -> GetPrimaryVertex() -> GetPrimary() -> GetKineticEnergy() << G4endl; // Incident particle E MeV Uniti
}

void FAZIAEventAction::EndOfEventAction(const G4Event* evt)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager -> FillNtupleDColumn(1, 0, Si111edepTot);
  analysisManager -> FillNtupleDColumn(1, 1, Si112edepTot);
  analysisManager -> FillNtupleDColumn(1, 2, Si113edepTot);
  analysisManager -> FillNtupleDColumn(1, 3, Si114edepTot);

  analysisManager -> FillNtupleDColumn(1, 4, Si211edepTot);
  analysisManager -> FillNtupleDColumn(1, 5, Si212edepTot);
  analysisManager -> FillNtupleDColumn(1, 6, Si213edepTot);
  analysisManager -> FillNtupleDColumn(1, 7, Si214edepTot);

  analysisManager -> FillNtupleDColumn(1, 8, CsI11edepTot);
  analysisManager -> FillNtupleDColumn(1, 9, CsI12edepTot);
  analysisManager -> FillNtupleDColumn(1, 10, CsI13edepTot);
  analysisManager -> FillNtupleDColumn(1, 11, CsI14edepTot);

  analysisManager -> AddNtupleRow(1);
  //--------------------------------------------------------------------------------------------------------------------------------
  //detect photon energy every 10 ns

  G4int eventID = evt -> GetEventID();  
  G4double IncidentEnergy = evt -> GetPrimaryVertex() -> GetPrimary() -> GetKineticEnergy();

	  cout << " Kinetic energy :"<< IncidentEnergy << endl;
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  G4HCofThisEvent* HCTE = evt -> GetHCofThisEvent();
  if(!HCTE) return;

  G4THitsCollection<FAZIAPhotoDiodeHit>* HC_Dio1 = NULL;

  hitsCollectionID = sdManager -> GetCollectionID("HitCollection_Dio1");
  //G4cout << "hitsCollectionID : " << hitsCollectionID << G4endl;
  if(HCTE) HC_Dio1 = (G4THitsCollection<FAZIAPhotoDiodeHit> *)(HCTE -> GetHC(hitsCollectionID));
  else HC_Dio1 = NULL;

  //G4double TotalEdep = 0;
  //G4double TotalLO = 0;

  //G4int TrackIDbef = -99;
  //G4int pIDbef = 0;

  if(HC_Dio1)
  {
	G4int numHits = HC_Dio1 -> entries();
	cout << "Number of Hits : " << numHits << endl;

	for(G4int i = 0 ; i < numHits ; i++)
	{
	  G4int         pID           = (*HC_Dio1)[i] -> GetPID();
	  G4int         trackID       = (*HC_Dio1)[i] -> GetTrackID();
	  G4int         volumeID      = (*HC_Dio1)[i] -> GetCopyNo();
	  G4int         parentID      = (*HC_Dio1)[i] -> GetParentID();
	  G4ThreeVector prePosition   = (*HC_Dio1)[i] -> GetPrePosition();
	  G4ThreeVector preMomentum   = (*HC_Dio1)[i] -> GetPreMomentum();
	  G4double      time          = (*HC_Dio1)[i] -> GetTime();
	  G4double      energyDeposit = (*HC_Dio1)[i] -> GetEdep();

	  FAZIA_data -> FillSimulationData(
		  eventID,
		  pID,
		  trackID,
		  volumeID,
		  parentID,
		  IncidentEnergy,
		  prePosition.x(),
		  prePosition.y(),
		  prePosition.z(),
		  preMomentum.x(),
		  preMomentum.y(),
		  preMomentum.z(),
		  time,
		  energyDeposit);
	  
	  
	  //cout << "i :"<< i << endl;
	  //cout << "energyDeposit :"<<energyDeposit << endl;
	 // cout << "volumeID :"<< volumeID << endl;
	  // Here we go for Light output

	  //if(i == 0)
	  //{
	  //Initialize trackID and pID at the first time.
	  //pIDbef = pID;
	  //TrackIDbef = trackID;
	  //}
	  //if(pID == 22)
	  //{	
	  //if(TrackIDbef == trackID) 
	  //{
	  //TotalEdep += energyDeposit;
	  //pIDbef = pID;
	  //}
	  //if(TrackIDbef != trackID)
	  //{
	  //TotalLO += LightOutputScint(TotalEdep);
	  //pIDbef = pID;
	  //}
	}

	}
	//TotalLO += LightOutputScint(TotalEdep);
	//else {
	//continue;}
	//if(TotalLO != 0) FAZIA_data -> FillEventData(eventID, volumeID, TotalLO);
  }
  //G4cout << evt -> GetEventID() << " Event Ended" << G4endl;
  //}

  //G4double FAZIAEventAction::LightOutputScint(G4double Edep)
  //{
  // G4double LightOutput = 0;
  //LightOutput = Edep;

  //return LightOutput;
  //}		


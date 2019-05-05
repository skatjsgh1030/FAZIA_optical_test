#include "FAZIARunAction.hh"
#include "g4root.hh"
//#include "g4cvs.hh"

FAZIARunAction::FAZIARunAction()
: G4UserRunAction()
{
}

FAZIARunAction::~FAZIARunAction()
{
  delete G4AnalysisManager::Instance();

}

void FAZIARunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> OpenFile("FAZIAQua_T.root");

  analysisManager -> CreateNtuple("step", "step");
  analysisManager -> CreateNtupleIColumn("eventID");
  analysisManager -> CreateNtupleIColumn("volumeID");
  analysisManager -> CreateNtupleDColumn("edep");
  analysisManager -> CreateNtupleDColumn("x");
  analysisManager -> CreateNtupleDColumn("y");
  analysisManager -> CreateNtupleDColumn("z");    
  analysisManager -> FinishNtuple();

  analysisManager -> CreateNtuple("edep","edep");
  analysisManager -> CreateNtupleDColumn("Si111edepTot");
  analysisManager -> CreateNtupleDColumn("Si112edepTot");
  analysisManager -> CreateNtupleDColumn("Si113edepTot");
  analysisManager -> CreateNtupleDColumn("Si114edepTot");
  analysisManager -> CreateNtupleDColumn("Si211edepTot");
  analysisManager -> CreateNtupleDColumn("Si212edepTot");
  analysisManager -> CreateNtupleDColumn("Si213edepTot");
  analysisManager -> CreateNtupleDColumn("Si214edepTot");
  analysisManager -> CreateNtupleDColumn("CsI11edepTot");
  analysisManager -> CreateNtupleDColumn("CsI12edepTot");
  analysisManager -> CreateNtupleDColumn("CsI13edepTot");
  analysisManager -> CreateNtupleDColumn("CsI14edepTot");
  analysisManager -> FinishNtuple();
 
}

void FAZIARunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager -> Write();
  analysisManager -> CloseFile();
}

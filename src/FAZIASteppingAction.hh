#ifndef FAZIASTEPPINGACTION_HH
#define FAZIASTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "g4root.hh"
//#include "g4cvs.hh"

class FAZIASteppingAction : public G4UserSteppingAction
{
  public:
    FAZIASteppingAction();
    virtual ~FAZIASteppingAction();
    
	
	virtual void UserSteppingAction(const G4Step*);
	
	//virtual void BeginOfEventAction(const G4Event *);
	//virtual void EndOfEventAction(const G4Event *);
    //void AddEnergyDeposit1(G4double edep) { edepTot += edep; }
	// method from the base class
  
  //private:

    //G4int fScintillationCounter;
    //G4int fCerenkovCounter;
    //G4int fEventNumber;
	
	//G4double edepTot;
};

#endif

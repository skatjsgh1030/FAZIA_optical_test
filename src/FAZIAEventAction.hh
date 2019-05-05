#ifndef FAZIAEventAction_h
#define FAZIAEventAction_h 1

#include "G4UserEventAction.hh"
//#include "G4Event.hh"
#include "globals.hh"
#include "g4root.hh"

#include "FAZIAData.hh"

class G4Event;
class FAZIAEventAction : public G4UserEventAction
{
  public:
	FAZIAEventAction(FAZIAData* data);
	virtual ~FAZIAEventAction();

	//LANAEventAction(LANAData* data);
  	//virtual ~LANAEventAction();

	// method from the base class
	virtual void BeginOfEventAction(const G4Event *);
	virtual void EndOfEventAction(const G4Event *);

	void AddEnergyDeposit1(G4double edep)  { Si111edepTot += edep; }
	void AddEnergyDeposit2(G4double edep)  { Si112edepTot += edep; }
	void AddEnergyDeposit3(G4double edep)  { Si113edepTot += edep; }     
	void AddEnergyDeposit4(G4double edep)  { Si114edepTot += edep; }

	void AddEnergyDeposit5(G4double edep)  { Si211edepTot += edep; }
	void AddEnergyDeposit6(G4double edep)  { Si212edepTot += edep; }     
	void AddEnergyDeposit7(G4double edep)  { Si213edepTot += edep; }     
	void AddEnergyDeposit8(G4double edep)  { Si214edepTot += edep; }

	void AddEnergyDeposit9(G4double edep)  { CsI11edepTot += edep; }
	void AddEnergyDeposit10(G4double edep) { CsI12edepTot += edep; }     
	void AddEnergyDeposit11(G4double edep) { CsI13edepTot += edep; }
	void AddEnergyDeposit12(G4double edep) { CsI14edepTot += edep; }

  private:
	G4double Si111edepTot;
	G4double Si112edepTot;
	G4double Si113edepTot;
	G4double Si114edepTot;

	G4double Si211edepTot;
	G4double Si212edepTot;
	G4double Si213edepTot;
	G4double Si214edepTot;

	G4double CsI11edepTot;     
	G4double CsI12edepTot;     
	G4double CsI13edepTot;	 
	G4double CsI14edepTot;

	FAZIAEventAction & operator=(const FAZIAEventAction &right);
	FAZIAEventAction(const FAZIAEventAction&);

	//G4double LightOutputSCINFUL(G4int pID, G4double Edep);
	G4double LightOutputScint(G4double Edep);

	G4int hitsCollectionID;
	FAZIAData* FAZIA_data;

};

#endif

#ifndef FAZIAPHOTODIODESD_h
#define FAZIAPHOTODIODESD_h 1

//Geant4 headers
#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"

//lampslow headers
#include "FAZIAPhotoDiodeHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class FAZIAPhotoDiodeSD: public G4VSensitiveDetector
{
  public: 
    FAZIAPhotoDiodeSD(const G4String& name, const G4String pv_name);
    virtual ~FAZIAPhotoDiodeSD();

    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
    virtual void Initialize(G4HCofThisEvent *HCTE);
    virtual void EndOfEvent(G4HCofThisEvent *HCTE);

  private:
    G4THitsCollection<FAZIAPhotoDiodeHit> *hitsCollection;

    const G4String PVName;

    G4int pID ,trackID ,volumeID ,parentID, eventID;
    G4ThreeVector preMomentum, prePosition, postPosition;
    G4double time, energyDeposit;
};
#endif

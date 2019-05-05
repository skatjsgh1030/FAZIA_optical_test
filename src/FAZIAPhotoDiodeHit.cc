#include "FAZIAPhotoDiodeHit.hh"

G4Allocator<FAZIAPhotoDiodeHit> FAZIAPhotoDiodeHitAllocator;

// allocator
FAZIAPhotoDiodeHit::FAZIAPhotoDiodeHit()
  :pID(0) ,trackID(0), volumeID(0) ,parentID(0), prePosition(G4ThreeVector(0,0,0)), preMomentum(G4ThreeVector(0,0,0)),
  time(0), energyDeposit(0)
{
}

FAZIAPhotoDiodeHit::FAZIAPhotoDiodeHit(G4int pID0, G4int trackID0, G4int volumeID0, G4int parentID0,  G4ThreeVector prePosition0, G4ThreeVector preMomentum0,G4double time0, G4double energyDeposit0)
  
  :pID(pID0), trackID(trackID0), volumeID(volumeID0), parentID(parentID0), prePosition(prePosition0), preMomentum(preMomentum0), 
  time(time0),energyDeposit(energyDeposit0)
{
}

FAZIAPhotoDiodeHit::~FAZIAPhotoDiodeHit()
{
}

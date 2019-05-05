#ifndef FAZIAPhotoDiodeHit_h
#define FAZIAPhotoDiodeHit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class FAZIAPhotoDiodeHit: public G4VHit
{
  private:
    G4int trackID;
    G4int parentID;
    G4int volumeID;
    G4int pID;
    G4ThreeVector prePosition;
    G4ThreeVector postPosition;
    G4ThreeVector preMomentum;
    G4double time;
    G4double energyDeposit;

  public:
    FAZIAPhotoDiodeHit();
    FAZIAPhotoDiodeHit(G4int, G4int, G4int, G4int, G4ThreeVector, G4ThreeVector, G4double, G4double);
    virtual ~FAZIAPhotoDiodeHit();

    FAZIAPhotoDiodeHit(const FAZIAPhotoDiodeHit &right);
    const FAZIAPhotoDiodeHit &operator=(const FAZIAPhotoDiodeHit &right);

    void *operator new(size_t);
    void operator delete(void *aHit);

    G4int         GetPID()         const { return pID;           };
    G4int         GetTrackID()     const { return trackID;       };
    G4int         GetCopyNo()      const { return volumeID;      };
    G4int         GetParentID()    const { return parentID;      };
    G4ThreeVector GetPrePosition() const { return prePosition;   };
    G4ThreeVector GetPreMomentum() const { return preMomentum;   };
    G4double      GetTime()        const { return time;          };
    G4double      GetEdep()        const { return energyDeposit; };
};

inline FAZIAPhotoDiodeHit::FAZIAPhotoDiodeHit(const FAZIAPhotoDiodeHit &right)
  :G4VHit()
{
  pID           = right.pID;
  trackID       = right.trackID;
  volumeID      = right.volumeID;
  parentID      = right.parentID;
  prePosition   = right.prePosition;
  // postPosition   = right.postPosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;
}

inline const FAZIAPhotoDiodeHit &FAZIAPhotoDiodeHit::operator=(const FAZIAPhotoDiodeHit &right)
{
  pID           = right.pID;
  volumeID      = right.volumeID;
  parentID      = right.parentID;
  prePosition   = right.prePosition;
  // postPosition   = right.postPosition;
  preMomentum   = right.preMomentum;
  energyDeposit = right.energyDeposit;
  time          = right.time;

  return *this;
}

extern G4Allocator<FAZIAPhotoDiodeHit> FAZIAPhotoDiodeHitAllocator;

inline void *FAZIAPhotoDiodeHit::operator new(size_t)
{
  void *aHit = (void *)FAZIAPhotoDiodeHitAllocator.MallocSingle();
  return aHit;
}

inline void FAZIAPhotoDiodeHit::operator delete(void *aHit)
{
  FAZIAPhotoDiodeHitAllocator.FreeSingle((FAZIAPhotoDiodeHit *) aHit);
}

#endif

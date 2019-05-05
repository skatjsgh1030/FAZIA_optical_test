#ifndef FAZIAPRIMARYGENERATORACTION_HH
#define FAZIAPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "globals.hh"

class FAZIAPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    FAZIAPrimaryGeneratorAction();    
    virtual ~FAZIAPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);    
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
	G4double random;
	G4double phirand;
	G4double costheta;
	G4double Parti_ene;
	
	G4double PreEnergy[84] =   { 5.6,  5.8,  6.0,  6.2,  6.4,  6.6,  6.8,  7.0,  7.2,  7.4, 
								15.0, 15.2, 15.4, 15.6, 15.8 ,16.0, 16.2, 16.4, 16.6, 16.8,
								20.0, 20.2, 20.6, 20.8, 21.0, 21.2, 21.4, 22.2, 22.3, 23.0,
								30.5, 30.7, 30.9, 31.0, 31.4, 31.6, 31.9, 32.3, 32.6, 32.8,
								44.7, 45.0, 45.2, 45.4, 45.8, 46.0, 46.2, 47.0, 47.4, 47.8,
								50.6, 50.8, 51.0, 51.5, 51.9, 52.1, 52.4, 52.8, 53.0, 55.0,
								70.8, 71.4, 71.5, 71.8, 72.0, 72.5, 72.8, 73.0, 73.5, 73.7,
								80.3, 80.8, 82.4, 82.5, 83.5, 83.7, 84.0, 84.4, 84.8, 85.0,
								90.0, 92.0, 92.4, 92.5};
	G4double LatEnergy[84] =   { 5.8,  6.0,  6.2,  6.4,  6.6,  6.8,  7.0,  7.2,  7.4, 
								15.0, 15.2, 15.4, 15.6, 15.8 ,16.0, 16.2, 16.4, 16.6, 16.8,
								20.0, 20.2, 20.6, 20.8, 21.0, 21.2, 21.4, 22.2, 22.3, 23.0,
								30.5, 30.7, 30.9, 31.0, 31.4, 31.6, 31.9, 32.3, 32.6, 32.8,
								44.7, 45.0, 45.2, 45.4, 45.8, 46.0, 46.2, 47.0, 47.4, 47.8,
								50.6, 50.8, 51.0, 51.5, 51.9, 52.1, 52.4, 52.8, 53.0, 55.0,
								70.8, 71.4, 71.5, 71.8, 72.0, 72.5, 72.8, 73.0, 73.5, 73.7,
								80.3, 80.8, 82.4, 82.5, 83.5, 83.7, 84.0, 84.4, 84.8, 85.0,
								90.0, 92.0, 92.4, 92.5, 93.0};
	
	
	G4double probPro[84] = {10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							30.3, 50.6, 80.8, 50.5};
	G4double probDeu[84] = {10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							30.3, 50.6, 80.8, 50.5};
	G4double probHe3[84] = {10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							30.3, 50.6, 80.8, 50.5};
	G4double probAlp[84] = {10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							10.6, 30.3, 40.5, 50.6, 80.8, 60.5, 50.5, 30.1, 29.5, 7.5,
							30.3, 50.6, 80.8, 50.5};
	//G4double p2[5] = { 5, 30, 30, 20, 15};
	//G4double p3[5] = {20, 20, 20, 20, 20};
	
	//G4double deuteronE[5] = {17.6, 60.1 ,30.4, 40.6 ,20.9};
	//G4double He3E[5] =      {40.0, 20.3, 46.6, 73.3, 14.34};
	//G4double alphaE[5] =    {23.34, 34.5, 56.56, 62.75, 45.3};
	/*///////////////////////////////////////////////////////////////////////////
	  double p0, p1, mup, mum; 


	  double momt_avg[65];
	  double momfor[65] = {   };
	  double momlat[65];
	  }*/
    G4int eventNum = 0;
};

#endif


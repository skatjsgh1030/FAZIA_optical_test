#include "FAZIAData.hh"

#include "TFile.h"
#include "TTree.h"

//c++ headers
#include <iostream>

FAZIAData::FAZIAData()
{
  dataFile = new TFile("FAZIASimData.root","recreate");
  stepTree = new TTree("step","");
  EventTree = new TTree("event","");
  SetBranch();
}

void FAZIAData::SetBranch()
{
  stepTree -> Branch("eventID",&eventID);
  stepTree -> Branch("trackID",&trackID);
  stepTree -> Branch("volumeID",&volumeID);
  stepTree -> Branch("pID",&pID);
  stepTree -> Branch("parentID",&parentID);
  stepTree -> Branch("energyInit",&energyInit);
  stepTree -> Branch("x_pre",&preX);
  stepTree -> Branch("y_pre",&preY);
  stepTree -> Branch("z_pre",&preZ);
  stepTree -> Branch("pX_pre",&prePx);
  stepTree -> Branch("pY_pre",&prePy);
  stepTree -> Branch("pZ_pre",&prePz);
  stepTree -> Branch("time",&time);
  stepTree -> Branch("edep",&edep);

  EventTree -> Branch("eventID", &eventID);
  EventTree -> Branch("volumeID", &volumeID);
  EventTree -> Branch("LightOutput", &LightOutput);
}

FAZIAData::~FAZIAData()
{
}

void FAZIAData::FillEventData(int eventID_val, int volumeID_val, double LightOutput_val)
{
  eventID = eventID_val;
  volumeID = volumeID_val;
  LightOutput = LightOutput_val;

  dataFile -> cd();
  EventTree -> Fill();
}

void FAZIAData::FillSimulationData(
                        int    eventID_val,
                        int    pID_val,
                        int    trackID_val,
                        int    volumeID_val,
                        int    parentID_val,
                        double inEnergy_val,
                        double preX_val,
                        double preY_val,
                        double preZ_val,
                        double prePx_val,
                        double prePy_val,
                        double prePz_val,
                        double time_val,
                        double edep_val)
{
  eventID   = eventID_val;
  pID       = pID_val;
  trackID   = trackID_val;
  volumeID  = volumeID_val;
  parentID  = parentID_val;
  energyInit= inEnergy_val;
  preX      = preX_val;
  preY      = preY_val;
  preZ      = preZ_val;
  prePx     = prePx_val;
  prePy     = prePy_val;
  prePz     = prePz_val;
  time      = time_val;
  edep      = edep_val;

  dataFile -> cd();
  stepTree -> Fill();
}

/*
void FAZIAData::FillStepData(
                        int    eventID_val,
                        int    trackID_val,
                        int    parentID_val,
                        int    pID_val,
                        double edep_val,
                        double KineticEnergy_val,
                        int    isInelastic_val,
                        int    ReactionChannel_val)
{
  eventID   = eventID_val;
  trackID   = trackID_val;
  parentID  = parentID_val;
  pID       = pID_val;
  edep      = edep_val;
  KineticEnergy      = KineticEnergy_val;
  isInelastic = isInelastic_val;
  ReactionChannel      = ReactionChannel_val;
  dataFile -> cd();
  stepTree -> Fill();
}
*/

void FAZIAData::WriteFile()
{
  dataFile -> cd();
  stepTree -> Write();
  EventTree -> Write();
  std::cout << "FAZIASimData.root is create!" << std::endl;
  dataFile -> Close();
}

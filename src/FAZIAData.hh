#ifndef FAZIAData_hh
#define FAZIAData_hh 1

//Root headers
#include <TFile.h>
#include <TTree.h>

class TFile;
class TTree;

class FAZIAData
{
  public:
    FAZIAData();
    ~FAZIAData();

    TTree *GetTree();

    void FillEventData(int eventID_val, int volumeID, double LightOutput_val);
    void FillSimulationData(
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
                            double edep_val,
                            double time_val);
    void WriteFile();

  private:
    void SetBranch();

    double preX, preY, preZ, prePx, prePy, prePz, time, edep, energyInit, LightOutput;
    int    parentID,pID, trackID, volumeID , eventID;

    TFile* dataFile;
    TTree* stepTree;
    TTree* EventTree;
};

#endif

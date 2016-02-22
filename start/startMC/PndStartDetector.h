//////////// shyam kumar start detector class for start detector
#ifndef PNDSTARTDETECTOR_H
#define PNDSTARTDETECTOR_H
#include "PndSdsDetector.h" 

class PndStartDetector : public PndSdsDetector
{
public:
 /** Default constructor **/

PndStartDetector();

// Standard constructor

PndStartDetector(const char* name, Bool_t active);

//Destructor

virtual ~PndStartDetector();

// Setting in/output names for Start 

void SetBranchNames(TString outBranchname, TString folderName);
  virtual void SetBranchNames();
  virtual void SetSpecialPhysicsCuts();
  virtual void SetDefaultSensorNames();
  virtual void Initialize(){PndSdsDetector::Initialize();};

private:
  

  ClassDef(PndStartDetector,6);

};

#endif

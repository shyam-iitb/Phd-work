// -------------------------------------------------------------------------
// -----                 PndStartStripClusterTask header file             -----
// -------------------------------------------------------------------------



#ifndef PNDSTARTSTRIPCLUSTERTASK_H
#define PNDSTARTSTRIPCLUSTERTASK_H 1

#include "PndSdsStripClusterTask.h"

class PndStartStripClusterTask : public PndSdsStripClusterTask
  {
  public:
    
    /** Default constructor **/
  	PndStartStripClusterTask();
    
    /** Destructor **/
    virtual ~PndStartStripClusterTask();
    
    void SetBranchNames(TString inBranchname, TString outHitBranchname, TString outClustBranchname, TString folderName);
    virtual void SetBranchNames();
    
    virtual void SetParContainers();
    virtual void SetCalculators();
    
    ClassDef(PndStartStripClusterTask,3);
  };

#endif /* STARTCLUSTERTASK_H */



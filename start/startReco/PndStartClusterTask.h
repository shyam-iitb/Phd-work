
#ifndef PNDSTARTCLUSTERTASK_H
#define PNDSTARTCLUSTERTASK_H

#include "PndBlackBoxTask.h"

class TClonesArray;

class PndStartClusterTask : public PndBlackBoxTask
  {
  public:
    
    /** Default constructor **/
    //     PndStartClusterTask();
    
    PndStartClusterTask();
    
    /** Destructor **/
    virtual ~PndStartClusterTask();
    
    
    void SetPersistance(Bool_t p = kTRUE);
    Bool_t GetPersistance() {return fPersistance;};
    
  private:
    Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
    
    ClassDef(PndStartClusterTask,2);
    
  };

#endif /* STARTCLUSTERTASK_H */


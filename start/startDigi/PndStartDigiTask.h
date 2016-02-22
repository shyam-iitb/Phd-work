
/** PndStartDigiTask.h
 21 Nov-2013
 **
 **/


#ifndef PNDSTARTDIGITASK_H
#define PNDSTARTDIGITASK_H
#include "PndBlackBoxTask.h"

class TClonesArray;

class PndStartDigiTask : public PndBlackBoxTask
{
 public:

    /** Default constructor **/
    PndStartDigiTask();


    /** Destructor **/
    virtual ~PndStartDigiTask();


  void SetPersistance(Bool_t p = kTRUE);
  Bool_t GetPersistance() {return fPersistance;};
  void RunTimeBased();

 private:
  Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
  void Register();
  void Reset();
  void ProduceHits();
  ClassDef(PndStartDigiTask,1);

};

#endif /* STARTDIGITASK_H */

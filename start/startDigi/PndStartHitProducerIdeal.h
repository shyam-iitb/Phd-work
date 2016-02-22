// -------------------------------------------------------------------------
// -----                 CbmStartHitProducerIdeal header file
// -------------------------------------------------------------------------


/**
 ** Inherit from Sds Ideal hitproducer
 **/


#ifndef PNDSTARTHITPRODUCERIDEAL_H
#define PNDSTARTHITPRODUCERIDEAL_H 1

#include "PndSdsHitProducerIdeal.h"

class PndStartHitProducerIdeal : public PndSdsHitProducerIdeal
{
 public:

  /** Default constructor **/  
  PndStartHitProducerIdeal();


  /** Destructor **/
  virtual ~PndStartHitProducerIdeal();

  void SetBranchNames(TString inBranchname, TString outBranchname, TString folderName);
  virtual void SetBranchNames();

  ClassDef(PndStartHitProducerIdeal,4);

};

#endif

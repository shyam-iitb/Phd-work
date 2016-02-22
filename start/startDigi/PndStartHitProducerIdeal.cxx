// -------------------------------------------------------------------------
// -----               PndStartHitProducerIdeal source file             -----
// -------------------------------------------------------------------------


#include "PndStartHitProducerIdeal.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"


// -----   Default constructor   -------------------------------------------
PndStartHitProducerIdeal::PndStartHitProducerIdeal() :
  PndSdsHitProducerIdeal("Ideal START Hit Producer")
{
  fInBranchName = "STARTPoint";
  fPersistance = kTRUE;
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndStartHitProducerIdeal::~PndStartHitProducerIdeal()
{
}

void PndStartHitProducerIdeal::SetBranchNames(TString inBranchname, TString outBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outBranchname;
  fFolderName = folderName;
  SetInBranchId();
}


void PndStartHitProducerIdeal::SetBranchNames()
{
  fInBranchName = "STARTPoint";
  fOutBranchName = "STARTHit";
  fFolderName = "PndStart";
  SetInBranchId();
}



ClassImp(PndStartHitProducerIdeal)

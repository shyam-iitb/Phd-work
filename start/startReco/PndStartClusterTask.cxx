// -------------------------------------------------------------------------
// -----                     PndStartClusterTask source file             -----
// -----                  Created 07/10/08  by R. Kliemt               -----
// -------------------------------------------------------------------------


#include "PndStartClusterTask.h"
#include "PndStartStripClusterTask.h"
// #include "PndStartTimeWalkCorrTask.h"

PndStartClusterTask::PndStartClusterTask() :
PndBlackBoxTask("Start Hit Reconstruction BlackBox Task")
{
  fPersistance = kTRUE;
  this->Add(new PndStartStripClusterTask());
  // this->Add(new PndStartTimeWalkCorrTask());   // Task to correct Digi-TimeStamp from TimeWalk-Effect. Corrected digis will be saved in output-file
  SetPersistance(fPersistance);
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
PndStartClusterTask::~PndStartClusterTask()
{
}
// -------------------------------------------------------------------------

void PndStartClusterTask::SetPersistance(Bool_t pers)
{
  //TODO: This is not recursive 
  fPersistance = pers;
  TList* thistasks = this->GetListOfTasks();
  ((PndStartStripClusterTask*)thistasks->At(0))->SetPersistance(fPersistance);
  return;
}

ClassImp(PndStartClusterTask);


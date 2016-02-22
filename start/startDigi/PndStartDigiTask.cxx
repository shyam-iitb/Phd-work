// -------------------------------------------------------------------------
// -----                    PndStartDigiTask source file                 -----
// -----                          -----
// -----                  Wrapper for Start digitizing tasks             -----
// -------------------------------------------------------------------------


#include "PndStartDigiTask.h"
#include "PndStartStripHitProducer.h"
#include "PndStartNoiseProducer.h"
#include "PndSdsDigiStripSorterTask.h"
#include "PndStartTimeWalkCorrTask.h"
#include "PndSdsStripHitProducer.h"
#include "PndSdsTotChargeConversion.h"

// -----   Default constructor   -------------------------------------------
PndStartDigiTask::PndStartDigiTask() :
  PndBlackBoxTask("START Digitization BlackBox Task")
{
  this->Add(new PndStartStripHitProducer());
  this->Add(new PndStartNoiseProducer());

  fPersistance = kTRUE;
  SetPersistance(fPersistance);
}
// -------------------------------------------------------------------------

void PndStartDigiTask::SetPersistance(Bool_t pers)
{
  fPersistance = pers;
  TList* thistasks = this->GetListOfTasks();
  ((PndStartStripHitProducer*)thistasks->At(0))->SetPersistance(fPersistance);
  ((PndStartNoiseProducer*)thistasks->At(1))->SetPersistance(fPersistance);
  return;
}

void PndStartDigiTask::RunTimeBased()
{
	 TList* thistasks = this->GetListOfTasks();
	((PndStartStripHitProducer*)thistasks->At(0))->RunTimeBased();
	((PndStartNoiseProducer*)thistasks->At(1))->RunTimeBased();

	this->Add(new PndSdsDigiStripSorterTask(5000, 50, "STARTStripDigis", "STARTSortedStripDigis", "PndStart"));

	std::cout << "PndStartDigiTask: PndStartStripDigiSorterTask added" << std::endl;
}

// -----   Destructor   ----------------------------------------------------
PndStartDigiTask::~PndStartDigiTask()
{
}
// -------------------------------------------------------------------------


ClassImp(PndStartDigiTask);

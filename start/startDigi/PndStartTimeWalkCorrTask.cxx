/*
 * PndStartTimeWalkCorrectionTask.cxx
 *
 *  Created on: Aug 27, 2010
 *      Author: Simone Esch
 */

#include "PndStartTimeWalkCorrTask.h"


// -----   Default constructor   -------------------------------------------

PndStartTimeWalkCorrTask::PndStartTimeWalkCorrTask() :
PndSdsTimeWalkCorrTask("SDS TimeWalkCorrection Task")
{
fPersistance=true;

}



PndStartTimeWalkCorrTask::~PndStartTimeWalkCorrTask() {

}

// -----   Default I/O folder/branches   ----------------------------------------------------
void PndStartTimeWalkCorrTask::SetBranchNames()
{
 // fInBranchName = "STARTStripDigis";                 // Name in digi_complete
  //fOutBranchName = "STARTDigisCorr";                 // Name in reco_complete
  //fFolderName = "PndStart";
}

void PndStartTimeWalkCorrTask::SetParContainers(){

	FairRun* ana = FairRun::Instance();
	FairRuntimeDb* rtdb=ana->GetRuntimeDb();
	//fDigiPar = (PndSdsStripDigiPar*)(rtdb->getContainer("STARTStripDigiPar"));
	//fDigiTotPar = (PndSdsTotDigiPar*)(rtdb->getContainer("STARTStripTotDigiPar"));
	PndSdsTimeWalkCorrTask::SetParContainers();

}

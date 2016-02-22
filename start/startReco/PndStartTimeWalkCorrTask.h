/*
 * PndMvdTimeWalkCorrctionTask.h
 *
 *  Created on: Aug 27, 2010
 *      Author: Simone Esch
 */

#ifndef PNDSTARTTIMEWALKCORRTASK_H_
#define PNDSTARTTIMEWALKCORRTASK_H_

#include "PndSdsTimeWalkCorrTask.h"
#include "TString.h"
#include "FairRuntimeDb.h"
#include "FairRun.h"

class PndStartTimeWalkCorrTask: public PndSdsTimeWalkCorrTask {
public:
	PndStartTimeWalkCorrTask();
	virtual ~PndStartTimeWalkCorrTask();

	void SetBranchNames();

	void SetParContainers();

        ClassDef(PndStartTimeWalkCorrTask, 1);
};

#endif /* PNDSTARTTIMEWALKCORRTASK_H_ */

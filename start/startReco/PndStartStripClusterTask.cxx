// -------------------------------------------------------------------------
// -----                PndStartStripClusterTask source file             -----
// -------------------------------------------------------------------------

#include "PndStartStripClusterTask.h"
#include "PndStartContFact.h"
#include "FairRuntimeDb.h"
#include "FairRunAna.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsChargeWeightingAlgorithms.h"
#include "PndSdsSimpleStripClusterFinder.h"
#include "PndSdsStripAdvClusterFinder.h"
#include "PndSdsTotDigiPar.h"

// -----   Default constructor   -------------------------------------------
PndStartStripClusterTask::PndStartStripClusterTask() :
PndSdsStripClusterTask("START Strip Clusterisation Task")
{
}

// -----   Destructor   ----------------------------------------------------
PndStartStripClusterTask::~PndStartStripClusterTask()
{
}

// -----   Manual I/O folders/branches   ----------------------------------------------------
void PndStartStripClusterTask::SetBranchNames(TString inBranchname, TString outHitBranchname, TString outClustBranchname, TString folderName)
{
  fInBranchName = inBranchname;
  fOutBranchName = outHitBranchname;
  fClustBranchName = outClustBranchname;
  fFolderName = folderName;
}

// -----   Default I/O folder/branches   ----------------------------------------------------
void PndStartStripClusterTask::SetBranchNames()
{
	if (FairRunAna::Instance()->IsTimeStamp())
		fInBranchName = "STARTSortedStripDigis";
	else
		fInBranchName = "STARTStripDigis";
//  fInBranchName = "STARTStripDigis";
  fOutBranchName = "STARTHitsStrip";
  fClustBranchName = "STARTStripClusterCand";
  fFolderName = "PndStart";
}

// -----   Initialization  of Parameter Containers -------------------------
void PndStartStripClusterTask::SetParContainers()
{
  // called from the FairRun::Init()
  // Caution: The Parameter Set is not filled from the DB IO, yet. 
  // This will be done just before this Tasks Init() is called.
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  PndStartContFact* thestartcontfact = (PndStartContFact*)rtdb->getContFactory("PndStartContFact");
  fDigiParameterList->Clear();
  fChargeDigiParameterList->Clear();
  TList* theContNames = thestartcontfact->GetDigiParNames();
  Info("SetParContainers()","The container names list contains %i entries",theContNames->GetEntries());
  TIter cfIter(theContNames);
  fDigiParameterList->Clear();
  fChargeDigiParameterList->Clear();
  while (TObjString* contname = (TObjString*)cfIter()) {
    TString parsetname = contname->String();
    Info("SetParContainers()","%s",parsetname.Data());
    if(parsetname.BeginsWith("STARTStripDigiParTrapL")){
      PndSdsStripDigiPar* digipar = (PndSdsStripDigiPar*)(rtdb->getContainer(parsetname.Data()));
      if ( ! digipar ) Fatal("SetParContainers","No DIGI parameter found: %s",parsetname.Data());
      fDigiParameterList->Add(digipar);
    }
    if(parsetname.BeginsWith("STARTStripDigiParTrapS")){
          PndSdsStripDigiPar* digipar = (PndSdsStripDigiPar*)(rtdb->getContainer(parsetname.Data()));
          if ( ! digipar ) Fatal("SetParContainers","No DIGI parameter found: %s",parsetname.Data());
          fDigiParameterList->Add(digipar);
        }
    if(parsetname.BeginsWith("STARTStripTotDigiParTrapL")){
      PndSdsTotDigiPar* totdigipar = (PndSdsTotDigiPar*)(rtdb->getContainer(parsetname.Data()));
      if ( ! totdigipar ) Fatal("SetParContainers","No TOT parameter found: %s",parsetname.Data());
      fChargeDigiParameterList->Add(totdigipar);
    }
    if(parsetname.BeginsWith("STARTStripTotDigiParTrapS")){
         PndSdsTotDigiPar* totdigipar = (PndSdsTotDigiPar*)(rtdb->getContainer(parsetname.Data()));
         if ( ! totdigipar ) Fatal("SetParContainers","No TOT parameter found: %s",parsetname.Data());
         fChargeDigiParameterList->Add(totdigipar);
       }
  }//while
  PndSdsStripClusterTask::SetParContainers();
}

void PndStartStripClusterTask::SetCalculators()
{
  Info("SetCalculators","start");
	PndSdsStripClusterTask::SetCalculators();
	TIter params(fDigiParameterList);
	TIter totparams(fChargeDigiParameterList);
	while( PndSdsStripDigiPar* digipar = (PndSdsStripDigiPar*)params() ){
		PndSdsTotDigiPar* totdigipar = (PndSdsTotDigiPar*) totparams();
		if ( 0==digipar ) continue;
		const char* senstype = digipar->GetSensType();
		if ( digipar->GetChargeConvMethod() == 1 ){
			if(fVerbose>0)	Info("SetCalculators()","Use Tot charge conversion for %s sensors",senstype);
			fChargeConverter[senstype] = new PndSdsTotChargeConversion(
                                                                 totdigipar->GetChargingTime(),
                                                                 totdigipar->GetConstCurrent(),
                                                                 digipar->GetThreshold(),
                                                                 totdigipar->GetClockFrequency(),
                                                                 fVerbose);
		}
		else{
			if(fVerbose>0)	Info("SetCalculators()","Use Ideal charge conversion for %s sensors",senstype);
			fChargeConverter[senstype] = new PndSdsIdealChargeConversion(digipar->GetNoise());
    }
    //fChargeAlgos[senstype] = new PndSdsChargeWeightingAlgorithms(fDigiArray, digipar->GetRaisingTime(),digipar->GetFallingRatio(),digipar->GetThreshold());
    Int_t ClusterMod = digipar->GetClusterMod(); 
    Int_t RadChannel = digipar->GetRadChannel(); 
    Int_t RadTime    = digipar->GetRadTime(); 
    if(0==ClusterMod) { 
      fClusterFinderList[senstype] = new PndSdsSimpleStripClusterFinder(fInBranchId, RadChannel ); //search radius in channel no.
    } else if(1==ClusterMod) { 
      fClusterFinderList[senstype] = new PndSdsStripAdvClusterFinder(fInBranchId, RadChannel, RadTime);
    } 
	}
}


ClassImp(PndStartStripClusterTask);



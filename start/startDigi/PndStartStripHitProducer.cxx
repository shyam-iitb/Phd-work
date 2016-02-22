// -------------------------------------------------------------------------
// -----                PndStartStripHitProducer source file             -----
// -----                Shyam Kumar                                   -----
// -------------------------------------------------------------------------

//This Class
#include "PndStartStripHitProducer.h"
//START
#include "PndStartContFact.h"
//SDS
#include "PndSdsIdealChargeConversion.h"
#include "PndSdsTotChargeConversion.h"
#include "PndSdsTotDigiPar.h"
//FAIR
#include "FairRun.h"
#include "FairRuntimeDb.h"
//ROOT
#include "TList.h"

// -----   Default constructor   -------------------------------------------
PndStartStripHitProducer::PndStartStripHitProducer() :
PndSdsStripHitProducer("START Strip Digi Producer(PndStartStripHitProducer)")
{
}
// -------------------------------------------------------------------------


// -----   Destructor   ----------------------------------------------------
PndStartStripHitProducer::~PndStartStripHitProducer()
{
}

// -------------------------------------------------------------------------
void PndStartStripHitProducer::SetBranchNames()
{
  fInBranchName = "STARTPoint";
  fOutBranchName = "STARTStripDigis";
  fFolderName = "PndStart";
  SetInBranchId();
}
// -------------------------------------------------------------------------
void PndStartStripHitProducer::SetCalculators()
{
	PndSdsStripHitProducer::SetCalculators();
  //calculator for TOT charge conversion:
	TIter params(fDigiParameterList);
	TIter totparams(fChargeDigiParameterList);
	while( PndSdsStripDigiPar* digipar = (PndSdsStripDigiPar*)params() ){
		PndSdsTotDigiPar* totdigipar = (PndSdsTotDigiPar*) totparams();
		if ( 0==digipar ) continue;
		const char* senstype = digipar->GetSensType();
		if ( digipar->GetChargeConvMethod() == 0 ){
			if(fVerbose>0)	Info("SetCalculators()","Use Ideal charge conversion for %s sensors",senstype);
			fChargeConverter[senstype] = new PndSdsIdealChargeConversion(digipar->GetNoise());
		}
		else if (digipar->GetChargeConvMethod() == 1){
			if(fVerbose>0)	Info("SetCalculators()","Use Tot charge conversion for %s sensors",senstype);
			      fChargeConverter[senstype] = new PndSdsTotChargeConversion(
			                                                                 totdigipar->GetChargingTime(),
			                                                                 totdigipar->GetConstCurrent(),
			                                                                 digipar->GetThreshold(),
			                                                                 totdigipar->GetClockFrequency(),
			                                                                 fVerbose);
		}
		else Fatal ("SetCalculators()","charge conversion method not defined!");
	}
}
// -------------------------------------------------------------------------
// -----   Initialization  of Parameter Containers -------------------------
void PndStartStripHitProducer::SetParContainers()
{
  // called from the FairRun::Init()
  // Caution: The Parameter Set is not filled from the DB IO, yet. 
  // This will be done just before this Tasks Init() is called.
  
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  PndStartContFact* thestartcontfact = (PndStartContFact*)rtdb->getContFactory("PndStartContFact");
  TList* theContNames = thestartcontfact->GetDigiParNames();
  Info("SetParContainers()","The container names list contains %i entries",theContNames->GetEntries());
  TIter cfIter(theContNames);
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
  }
  PndSdsStripHitProducer::SetParContainers();
}

// -------------------------------------------------------------------------
ClassImp(PndStartStripHitProducer);


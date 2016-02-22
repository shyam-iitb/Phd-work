// -------------------------------------------------------------------------
// -----                PndStartNoiseProducer source file                -----
// -----                  Created 01.07.08  by Shyam Kumar               -----
// -------------------------------------------------------------------------

//#include <cmath>

#include "TClonesArray.h"
#include "TGeoNode.h"

#include "FairRootManager.h"
#include "FairGeoVolume.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairGeoNode.h"

#include "PndStartNoiseProducer.h"
#include "PndSdsMCPoint.h"
#include "PndSdsDigiStrip.h"
//#include "PndSdsDigiPixel.h"
#include "PndStringSeparator.h"

#include "PndSdsIdealChargeConversion.h"
#include "PndSdsTotChargeConversion.h"
#include<iostream>
#include "PndDetectorList.h"

// -----   Default constructor   -------------------------------------------
PndStartNoiseProducer::PndStartNoiseProducer() :
FairTask("Charge Noise Producer"), fGeoH(0)
{
  fBranchName 	= "STARTStripDigis";
  fPersistance = kTRUE;
  //  fGeoH = NULL;

  fTimeOrderedDigi = kFALSE;
  fBranchName = "";
  fDigiStripArray = NULL;
 // fDigiPixelArray = NULL;
  //fDigiPixelBuffer = NULL;
  fDigiStripBuffer = NULL;
  //fDigiParRect = NULL;
  fDigiParTrapL = NULL;
  fDigiParTrapS = NULL;
  //fDigiParPix = NULL;
 // fTotDigiParRect = NULL;
  fTotDigiParTrapL = NULL;
  fTotDigiParTrapS = NULL;
 // fTotDigiParPix = NULL;
  fMCEventheader = NULL;
  //fStripRectChargeConv = NULL;
  fStripTrapChargeConv = NULL;
  fCurrentChargeConv = NULL;
  //fPixChargeConv = NULL;
  fNoiseSpread = 0;
  fThreshold = 0;
  fPreviousTime = 0.;
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PndStartNoiseProducer::~PndStartNoiseProducer()
{
	//if (fStripRectChargeConv) delete fStripRectChargeConv;
	if (fStripTrapChargeConv) delete fStripTrapChargeConv;
	//if (fPixChargeConv) delete fPixChargeConv;
}

// -----   Public method Init   --------------------------------------------
InitStatus PndStartNoiseProducer::Init()
{
 // Get RootManager
  FairRootManager* ioman = FairRootManager::Instance();
  
  if ( ! ioman )
  {
	std::cout << " -E- PndStartNoiseProducer::Init: RootManager not instantiated!" << std::endl;
	return kFATAL;
  }
  
  // Get input array

  fDigiStripBuffer = (PndSdsDigiStripWriteoutBuffer*)FairRootManager::Instance()->RegisterWriteoutBuffer("STARTStripDigis", new PndSdsDigiStripWriteoutBuffer("STARTStripDigis", "START", kTRUE));
  
//  fDigiPixelArray = (TClonesArray*) ioman->GetObject("MVDPixelDigis");
  //fDigiPixelBuffer = new PndSdsDigiPixelWriteoutBuffer("MVDPixelDigis", "MVD", kTRUE);
  //fDigiPixelBuffer = (PndSdsDigiPixelWriteoutBuffer*)FairRootManager::Instance()->RegisterWriteoutBuffer("MVDPixelDigis", fDigiPixelBuffer);
  //fDigiPixelBuffer->ActivateBuffering(fTimeOrderedDigi);

  
  fMCEventheader = (FairMCEventHeader*) ioman->GetObject("MCEventHeader.");
  if ( ! fMCEventheader ){
	Warning("Init","Did not find the MC event header, assume 50ns of noise clockticks per call of Exec().");
  }
  fPreviousTime=0.;
  
  FillSensorLists();
  
//  fFEModel = new PndSdsFESimple();

  if(fVerbose>0)
  {
	std::cout <<" -I- PndStartNoiseProducer: Registered Sensors: "
	<<fStripTrapIds.size()<<"xStripTrap "
	<<std::endl;
  }
  std::cout << " -I- PndStartNoiseProducer: Intialisation successfull" << std::endl;
  
  if (fDigiParTrapL->GetChargeConvMethod() == 0){
    if(fVerbose>0) Info("Init()","ideal charge conversion for Large trap. strips");
    fStripTrapChargeConv = new PndSdsIdealChargeConversion(fDigiParTrapL->GetNoise());
  }
  if (fDigiParTrapS->GetChargeConvMethod() == 0){
     if(fVerbose>0) Info("Init()","ideal charge conversion for Large trap. strips");
     fStripTrapChargeConv = new PndSdsIdealChargeConversion(fDigiParTrapS->GetNoise());
   }
  else if (fDigiParTrapL->GetChargeConvMethod() == 1){
    if(fVerbose>0) Info("Init()","use TOT charge conversion for trap. strips");
    fStripTrapChargeConv = new PndSdsTotChargeConversion(
							 fTotDigiParTrapL->GetChargingTime(),
							 fTotDigiParTrapL->GetConstCurrent(),
							 fDigiParTrapL->GetThreshold(),
							 fTotDigiParTrapL->GetClockFrequency(),
							 fVerbose);
  }
  else if (fDigiParTrapS->GetChargeConvMethod() == 1){
     if(fVerbose>0) Info("Init()","use TOT charge conversion for trap. strips");
     fStripTrapChargeConv = new PndSdsTotChargeConversion(
 							 fTotDigiParTrapS->GetChargingTime(),
 							 fTotDigiParTrapS->GetConstCurrent(),
 							 fDigiParTrapS->GetThreshold(),
 							 fTotDigiParTrapS->GetClockFrequency(),
 							 fVerbose);
   }
  else Fatal ("Init()","trap. strips: charge conversion method not defined!");
  
  return kSUCCESS;
}

void PndStartNoiseProducer::FillSensorLists()
{
  TObjArray* sensorNames = fGeoH->GetSensorNames();

  for (int i = 0; i < sensorNames->GetEntries(); i++)
  {
		TString volpath = ((TObjString*)(sensorNames->At(i)))->GetString();
    if(!volpath.Contains("Start")) continue;
		PndStringSeparator sep(volpath.Data(), "/");
		std::vector<std::string> volvec = sep.GetStringVector();
		TString volname = volvec[volvec.size()-1].c_str();
		if(fVerbose>2)std::cout << "VolName: " << volname.Data();
		if(volname.Contains("Active"))
		{
		//  if(volname.Contains("RectL")) {fStripRectLIds.push_back(i); if(fVerbose>2)std::cout << " \tAdded to StripRectL" << std::endl;}
		 // if(volname.Contains("RectS")) {fStripRectSIds.push_back(i); if(fVerbose>2)std::cout << " \tAdded to StripRectS" << std::endl;}
		  if(volname.Contains("Trap")) {fStripTrapIds.push_back(i); if(fVerbose>2)std::cout << " \tAdded to StripTrap" << std::endl;}
		 // if(volname.Contains("Pixel"))
		//  {
        //if(volname.Contains("2")) {fPixelIds2.push_back(i); if(fVerbose>2)std::cout << " \tAdded to Pixel 2" << std::endl;}
        //if(volname.Contains("4")) {fPixelIds4.push_back(i); if(fVerbose>2)std::cout << " \tAdded to Pixel 4" << std::endl;}
        //if(volname.Contains("5")) {fPixelIds5.push_back(i); if(fVerbose>2)std::cout << " \tAdded to Pixel 5" << std::endl;}
        //if(volname.Contains("6")) {fPixelIds6.push_back(i); if(fVerbose>2)std::cout << " \tAdded to Pixel 6" << std::endl;}
		 // }
		}
	}
}

// -------------------------------------------------------------------------
void PndStartNoiseProducer::SetParContainers()
{
  if ( fGeoH == NULL ) {
    fGeoH = PndGeoHandling::Instance();
  }

  fGeoH->SetParContainers();
  // Get Base Container
  FairRun* ana = FairRun::Instance();
  FairRuntimeDb* rtdb=ana->GetRuntimeDb();
  //fDigiParRect = (PndSdsStripDigiPar*)(rtdb->getContainer("MVDStripDigiParRect"));
  fDigiParTrapL = (PndSdsStripDigiPar*)(rtdb->getContainer("STARTStripDigiParTrapL"));
  fDigiParTrapS = (PndSdsStripDigiPar*)(rtdb->getContainer("STARTStripDigiParTrapS"));
  //fDigiParPix  = (PndSdsPixelDigiPar*)(rtdb->getContainer("MVDPixelDigiPar"));
  //fTotDigiParRect = (PndSdsTotDigiPar*)(rtdb->getContainer("MVDStripTotDigiParRect"));
  fTotDigiParTrapL = (PndSdsTotDigiPar*)(rtdb->getContainer("STARTStripTotDigiParTrapL"));
  fTotDigiParTrapL = (PndSdsTotDigiPar*)(rtdb->getContainer("STARTStripTotDigiParTrapL"));
  //fTotDigiParPix  = (PndSdsTotDigiPar*)(rtdb->getContainer("MVDPixelTotDigiPar"));
}


// -----   Public method Exec   --------------------------------------------
void PndStartNoiseProducer::Exec(Option_t* opt)
{
  //   TObjArray* activeSensors = fGeoPar->GetGeoSensitiveNodes();
  Int_t nrCh=0,rnd=0,
  nrFE=0,sens=0,
  nrSensors=0,fe=0,
  chanmax=0,chan=0,
  col=0,row=0,
  chanwhite=0,
  charge=0,
  nNoisyStripTraps=0;
  Double_t xfrac=0.;
  Double_t cycles=1.;
  Int_t did=-1;
  
  // *** Large Strip Trapezoids ***
  if(!fDigiParTrapL){
  fDigiParTrapL= fDigiParTrapS;
  }
  nrCh = fDigiParTrapL->GetNrFECh();
  nrFE = fDigiParTrapL->GetNrBotFE() + fDigiParTrapL->GetNrTopFE();
  nrSensors = fStripTrapIds.size();
  chanmax = nrCh * nrFE * nrSensors;
  xfrac = CalcDistFraction(fDigiParTrapL->GetNoise(),fDigiParTrapL->GetThreshold());
  cycles = CalcReadoutCycles(fDigiParTrapL->GetFeBusClock());
  chanwhite = gRandom->Poisson(xfrac*cycles*chanmax);
  if(fVerbose>1) std::cout << " -I- PndStartNoiseProducer: TRAP <N> = " << xfrac*cycles*chanmax
    << " leading to " << chanwhite << " noisy digis of " << chanmax
    << " total channels" << std::endl;
  for(Int_t i = 0;i < chanwhite;i++)
  {
    rnd = gRandom->Integer(chanmax);
    sens = rnd/(nrFE*nrCh);
    rnd = rnd % (nrFE*nrCh);
    fe = rnd/nrCh;
    chan = rnd % nrCh;
    charge = CalcChargeAboveThreshold(fDigiParTrapL->GetNoise(),fDigiParTrapL->GetThreshold());
    did = fStripTrapIds[sens];
    fCurrentChargeConv = fStripTrapChargeConv;
    AddDigiStrip(nNoisyStripTraps,-1,did,fe,chan,charge);
  }
  



  fPreviousTime = FairRootManager::Instance()->GetEventTime();

  // *** The End ***
  if(fVerbose>0)
  {
    std::cout <<" -I- PndStartNoiseProducer: Noise produced\t"
    <<nNoisyStripTraps <<"xStripTrap\t"<<std::endl;
  }
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
Double_t PndStartNoiseProducer::CalcDistFraction(Double_t spread, Double_t threshold)
{
  // mean fraction of fireing digis
  return TMath::Erfc( threshold / (TMath::Sqrt2()*spread) );
}

Int_t PndStartNoiseProducer::CalcChargeAboveThreshold(Double_t spread,Double_t threshold)
{
  // pick any charge from the gaussian tail above threshold
  Double_t temp=0.;
  temp = TMath::Gaus(threshold,0,spread); // maximum gauss at threshold
  temp = gRandom->Uniform(0.,temp);       // random value in y
  temp = -2.*spread*spread*log(temp);     // get x value (recalc charge)
  temp = sqrt(temp);
  return (Int_t)ceil(temp);
}

Double_t PndStartNoiseProducer::CalcReadoutCycles(Double_t clock)
{ // time [ns], clock [MHz]
  Double_t cycles=1.;
  Double_t timewindow=0.;
  if (clock > 0){
    if (fMCEventheader!=0) {
      timewindow = FairRootManager::Instance()->GetEventTime();
      timewindow -= fPreviousTime;
    } else {
      timewindow = 1.; // how many ns do we suppress readout of zeros? Initially value is 50changed by me
    }
  }
  if(fVerbose>1) printf(" -I- PndStartNoiseProducer::CalcReadoutCycles(): %g cycles (%gMHz,%gns)\n",cycles,clock,timewindow);
  return cycles;
}

void PndStartNoiseProducer::AddDigiStrip(Int_t &noisies, Int_t iPoint, Int_t sensorID, Int_t fe, Int_t chan, Double_t charge)
{
  //Double_t tempcharge = 0.;
  //Bool_t found = kFALSE;
  Int_t detID = -1; // no source mc branch
  //PndSdsDigiStrip* aDigi = 0;
//  FairMCEventHeader* MCevtHeader = (FairMCEventHeader*)FairRootManager::Instance()->GetObject("MCEventHeader.");

//  if (fTimeOrderedDigi == kFALSE){
//	  Int_t iStrip = fDigiStripArray->GetEntriesFast();
//
//	  for(Int_t kstr = 0; kstr < iStrip && found == kFALSE; kstr++)
//	  {
//		aDigi = (PndSdsDigiStrip*)fDigiStripArray->At(kstr);
//		if (aDigi->GetSensorID() == sensorID &&
//			aDigi->GetFE() == fe &&
//			aDigi->GetChannel() == chan )
//		{
//		  tempcharge = fCurrentChargeConv->DigiValueToCharge(*aDigi);
//		  aDigi->SetCharge( fCurrentChargeConv->ChargeToDigiValue(charge + tempcharge) );
//		  aDigi->AddIndex(iPoint);
//		  found = kTRUE;
//		}
//	  }
//	  if(found == kFALSE){
//		  //TODO: get a reasonable timestamp fake for the noise
//		std::vector<Int_t> indices;
//		indices.push_back(iPoint);
//		new ((*fDigiStripArray)[iStrip]) PndSdsDigiStrip(indices,detID,sensorID,fe,chan,fCurrentChargeConv->ChargeToDigiValue(charge), FairRootManager::Instance()->GetEventTime()) ;
//		noisies++;
//		if(fVerbose>2) std::cout
//		  << " -I- PndSdsNoiseProducer: Added StripTrap Digi at: FE=" << fe
//		  << ", channel=" << chan << ", charge=" << charge<< " e"
//		  << ", in sensor \n" << sensorID <<std::endl;
//	  }
//  }
//  else{
		std::vector<Int_t> indices;
		indices.push_back(iPoint);
		PndSdsDigiStrip* tempStrip = new PndSdsDigiStrip(indices,detID,sensorID,fe,chan,fCurrentChargeConv->ChargeToDigiValue(charge), FairRootManager::Instance()->GetEventTime()) ;
		noisies++;
		fDigiStripBuffer->FillNewData(tempStrip, FairRootManager::Instance()->GetEventTime(), FairRootManager::Instance()->GetEventTime() + 10);
//  }
}


void PndStartNoiseProducer::FinishEvent()
{
  // called after all Tasks did their Exex() and the data is copied to the file

  FinishEvents();
}
// -------------------------------------------------------------------------




ClassImp(PndStartNoiseProducer)

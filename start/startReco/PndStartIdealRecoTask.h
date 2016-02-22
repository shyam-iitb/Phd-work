// -------------------------------------------------------------------------
// -----                 PndStartIdealRecoTask header file             -----
// -----                            -----
// -------------------------------------------------------------------------


/** PndStartIdealRecoTask.h
 *@author R.Kliemt <r.kliemt@physik.tu-dresden.de>
 **
 ** The ideal tracking produces tracks of type PndSdsHit by using MC information
 ** directly, but with the correct data interface.
 **/


#ifndef PNDSTARTIDEALRECOTASK_H
#define PNDSTARTIDEALRECOTASK_H

// Root includes
#include "TVector3.h"
#include "TRandom.h"
#include "TString.h"
#include "TGeoManager.h"

// framework includes
#include "FairTask.h"

// PndStart includes
#include "PndSdsMCPoint.h"
#include "PndGeoHandling.h"

class TClonesArray;

class PndStartIdealRecoTask : public FairTask
{
 public:

  /** Default constructor **/
  PndStartIdealRecoTask();

  PndStartIdealRecoTask(Double_t sx, Double_t sy, Double_t sz);


  /** Destructor **/
  virtual ~PndStartIdealRecoTask();


  /** Virtual method Init **/
  virtual void SetParContainers();
  virtual InitStatus Init();


  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);


  void SetPersistance(Bool_t p = kTRUE){fPersistance=p;};
  Bool_t GetPersistance() {return fPersistance;};
  
private:
  Bool_t fPersistance; // switch to turn on/off storing the arrays to a file
  
  TString fBranchName;
  PndGeoHandling* fGeoH;
  /** Input array of Points **/
  TClonesArray* fPointArray;
  TClonesArray* fMctruthArray;

  /** Output array of Hits **/
  TClonesArray* fHitOutputArray;
  /** Properties **/
  Double_t fSigmaX;       // Variance vector of sensor smearing
  Double_t fSigmaY;       // Variance vector of sensor smearing
  Double_t fSigmaZ;       // Variance vector of sensor smearing
  PndSdsMCPoint* fCurrentPndStartMCPoint;
  TGeoHMatrix* fCurrentTransMat;
  TMatrixT<Double_t> fHitCovMatrix;
  /** smearing and geometry access **/
  void InitTransMat();
  void smear(TVector3& pos);
  void smearLocal(TVector3& pos);
  void CalcDetPlane(TVector3& o,TVector3& u,TVector3& v);


  void Register();

  void Reset();

  void ProduceHits();

  ClassDef(PndStartIdealRecoTask,1);

};

#endif

/* This class can be used for Pid by Stof+Ftof which was intially for Ftof
 The Fts1 last plane is defined in PndPidCorrpar.h and PndPidCorrpar.cxx as
 Float_t GetFts1LastPlane()    { return fFTS1LastPlane; }; and also used the value of FTS1LastPlane as 290 cm
*/
#include "PndDetectorList.h"
#include "PndPidCorrelator.h"
#include "PndPidCandidate.h"
#include "PndMCTrack.h"
#include "PndTrack.h"
#include "PndTrackID.h"

#include "PndFtofHit.h"
#include "PndFtofPoint.h"

#include "FairTrackParH.h"
#include "FairMCApplication.h"
#include "FairRunAna.h"
#include "FairRootManager.h"
#include "FairRuntimeDb.h"
#include <cmath>
#include<iostream>
using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
 double c= 3* std::pow(10.,10.); //speed of light cm/sec
	
 // All particle masses are in GeV/c^2
	               
Double_t mel = 0.00051099891; // Mass of electron and positron
	               
Double_t mmu = 0.1056583715;   // Mass of muons
	               
Double_t mpi = 0.13957018;   // mass of charged pions
	               
Double_t mk = 0.493667;   // mass of charged kaons
	               
Double_t mp = 0.938272046;  // mass of protons and antiprotons

Bool_t PndPidCorrelator::GetFtofInfo(FairTrackParH* helix, PndPidCandidate* pidCand)
{
  if(!helix)
    {
      std::cerr << "<Error> PndPidCorrelator::GetFtofInfo: FairTrackParH NULL pointer parameter."<<std::endl;
      return kFALSE;
    }
  if(!pidCand)
    {
      std::cerr << "<Error> PndPidCorrelator::GetFtofInfo: pidCand NULL pointer parameter."<<std::endl;
      return kFALSE;
    }
 
  if(helix->GetZ() < fCorrPar->GetFts1LastPlane())
    {
      if (fVerbose>0) std::cout << "-W- PndPidCorrelator::GetFtofInfo: Skipping tracks not reaching the FTS1" << std::endl;//changed for stof
      return kFALSE;
    }
  
  if(helix->GetPz() <= 0.)
    {
      std::cout << "-W- PndPidCorrelator::GetFtofInfo: Skipping tracks going backward" << std::endl;
      return kFALSE;
    }
 
  FairGeanePro *fProTof = new FairGeanePro();
  if (!fCorrErrorProp) fProTof->PropagateOnlyParameters(); 
  FairGeanePro *fProVertex = new FairGeanePro();
  fProVertex->PropagateOnlyParameters();

  PndFtofHit *tofHit = NULL;
  Int_t tofEntries = fFtofHit->GetEntriesFast();
  Int_t tofIndex = -1;
  Float_t tofTof = 0., tofLength = -1000, tofGLength = -1000, tofTrackLength = -1000;
  Float_t tofQuality = 1000000;
  Float_t tmeas=0., te=0.,tmu=0.,tpi=0.,tk=0.,tp=0.;

  Float_t chi2 = 0;
  TVector3 vertex(0., 0., -10000.);
  TVector3 vertexrec(0., 0., -10000.); 
  TVector3 momrec(0., 0., -10000.);
  TVector3 tofPos(0., 0., 0.);
  TVector3 momentum(0., 0., 0.);
  TVector3 hitPoint; //changed for stof

  if (fGeanePro) // Overwrites vertex if Geane is used
    {
      // calculates track length from (0,0,0) to last point
      fProVertex->SetPoint(TVector3(0,0,0));
      fProVertex->PropagateToPCA(1, -1);
      FairTrackParH *fRes= new FairTrackParH();
      Bool_t rc =  fProVertex->Propagate(helix, fRes, fPidHyp*pidCand->GetCharge());
      if (rc) 
	{
	  tofTrackLength = fProVertex->GetLengthAtPCA(); 
	  vertexrec.SetXYZ(fRes->GetX(), fRes->GetY(), fRes->GetZ()); 
	  momrec.SetXYZ(fRes->GetPx(), fRes->GetPy(), fRes->GetPz());
	}
    }
  
  for (Int_t tt = 0; tt<tofEntries; tt++)
    {
      tofHit = (PndFtofHit*)fFtofHit->At(tt);
      if ( fIdeal && ( ((PndFtofPoint*)fFtofPoint->At(tofHit->GetRefIndex()))->GetTrackID() !=pidCand->GetMcIndex()) ) continue;
      tofHit->Position(tofPos);

      hitPoint=tofHit->GetPosition(); //changed for stof
      Float_t propX = helix->GetX() + (hitPoint.z()- helix->GetZ()) * helix->GetPx() / helix->GetPz(); //changed for Stof
      Float_t propY = helix->GetY() + (hitPoint.z() - helix->GetZ()) * helix->GetPy() / helix->GetPz(); //changed for Stof
      Float_t propZ = hitPoint.z(); //changed for Stof
      vertex.SetXYZ(propX, propY, propZ);
      tofGLength = (vertex-helix->GetPosition()).Mag();
      
      if (fGeanePro) // Overwrites vertex if Geane is used
	{ 
	  fProTof->SetPoint(tofPos);
	  fProTof->PropagateToPCA(1, 1);
	  FairTrackParH *fRes= new FairTrackParH();
	  Bool_t rc =  fProTof->Propagate(helix, fRes, fPidHyp*pidCand->GetCharge());	
	  if (!rc) continue;
	  tofGLength = fProTof->GetLengthAtPCA(); 
      	  vertex.SetXYZ(fRes->GetX(), fRes->GetY(), fRes->GetZ());
	}
      
      Float_t dist = (tofPos-vertex).Mag2();
      
      if ( tofQuality > dist)
        {
          tofIndex = tt;
          tofQuality = dist;
          tmeas = tofHit->GetTime();
	  tofLength = tofTrackLength+tofGLength;
	  //-----Calculating theortical time [ns] of Particles using tracklength [cm] and Momentum---------------------
	  te= (tofLength*std::pow(10.,9.)*std::sqrt (helix->GetMomentum().Mag()*helix->GetMomentum().Mag()+mel*mel))/(c*helix->GetMomentum().Mag());
	  tmu= (tofLength*std::pow(10.,9.)*std::sqrt (helix->GetMomentum().Mag()*helix->GetMomentum().Mag()+mmu*mmu))/(c*helix->GetMomentum().Mag());
	  tpi= (tofLength*std::pow(10.,9.)*std::sqrt (helix->GetMomentum().Mag()*helix->GetMomentum().Mag()+mpi*mpi))/(c*helix->GetMomentum().Mag());
	  tk= (tofLength*std::pow(10.,9.)*std::sqrt (helix->GetMomentum().Mag()*helix->GetMomentum().Mag()+mk*mk))/(c*helix->GetMomentum().Mag());
	  tp= (tofLength*std::pow(10.,9.)*std::sqrt (helix->GetMomentum().Mag()*helix->GetMomentum().Mag()+mp*mp))/(c*helix->GetMomentum().Mag());
	  std::cout<<"The Geane Calculated Tracklength:"<<"  "<<tofLength<<"  cm"<<std::endl;
	  std::cout<<"The Momentum:"<<"  "<<helix->GetMomentum().Mag()<<"  GeV/c"<<std::endl;
	  std::cout<<"The measured time:"<<"  "<<tmeas<<"  ns"<<std::endl;
	  std::cout<<"Theortical Time for electron"<<"  "<<te<<"  ns"<<std::endl;
	  std::cout<<"Theortical Time for muon"<<"  "<<tmu<<"  ns"<<std::endl;
	  std::cout<<"Theortical Time for pion"<<"  "<<tpi<<"  ns"<<std::endl;
	  std::cout<<"Theortical Time for kaon"<<"  "<<tk<<"  ns"<<std::endl;
	  std::cout<<"Theortical Time for Proton"<<"  "<<tp<<"  ns"<<std::endl;
	  std::cout<<""<<std::endl;
	  std::vector<Double_t> a,b;
	  a.push_back(te); 
	  a.push_back(tmu);
	  a.push_back(tpi);
	  a.push_back(tk);
	  a.push_back(tp);
	  //--Comparing the measured time with theortical predicted time and getting the time for which difference is minimum-------
	  Double_t small=0.;
	  for (Int_t i = 0; i < a.size(); i++)
	  {
	      Double_t tth=a[i];
	      Double_t td= fabs(tth-tmeas);
	      b.push_back(td);
	       small=b[0];
	     }
	      for (Int_t j = 1; j < b.size(); j++){
	     std::cout<<"b["<<j<<"] "<<b[j]<<std::endl;
	      if (b[j]<small)
	      small=b[j];
	      }
	      std::cout<<" The small time difference"<<"  "<<fabs(small)<<"  ns"<<std::endl;
	      if (fabs(small)<0.1){ //100 ps
	      tofTof= tmeas;
	      std::cout<<" The real time of flight"<<"  "<<tofTof<<"  ns"<<std::endl;
	      std::cout<<""<<std::endl;
	      }
	  b.clear();
	  a.clear();
	}
      
      if (fDebugMode)
        {
	  Float_t ntuple[] = {static_cast<Float_t>(vertex.X()), static_cast<Float_t>(vertex.Y()), static_cast<Float_t>(vertex.Z()),
			      static_cast<Float_t>(vertexrec.X()), static_cast<Float_t>(vertexrec.Y()), static_cast<Float_t>(vertexrec.Z()),
			      static_cast<Float_t>(momrec.X()), static_cast<Float_t>(momrec.Y()), static_cast<Float_t>(momrec.Z()),
			      static_cast<Float_t>(helix->GetMomentum().Mag()), static_cast<Float_t>(helix->GetQ()), static_cast<Float_t>(helix->GetMomentum().Theta()), static_cast<Float_t>(helix->GetZ()),
			      static_cast<Float_t>(tofPos.X()), static_cast<Float_t>(tofPos.Y()), static_cast<Float_t>(tofPos.Z()),
			      dist, tofLength, tofGLength, tofTrackLength};
          
          ftofCorr->Fill(ntuple);
        }
    }
 if (tofTof!=0.){
  if ( (tofQuality<fCorrPar->GetFTofCut()) || (fIdeal && tofIndex!=-1) )
    {
	  std::cout<<"The Set Value of Time of flight"<<"    "<<tofTof<<std::endl;
      pidCand->SetTofQuality(tofQuality);
      pidCand->SetTofStopTime(tofTof);
      pidCand->SetTofTrackLength(tofLength);
      pidCand->SetTofIndex(tofIndex);
      if (tofLength>0.)
	{
	  // mass^2 = p^2 * ( 1/beta^2 - 1 )
	  Float_t mass2 = helix->GetMomentum().Mag()*helix->GetMomentum().Mag()*(30.*30.*tofTof*tofTof/tofLength/tofLength-1.);
	  pidCand->SetTofM2(mass2);
	}
    }
 }
  
  return kTRUE;
}

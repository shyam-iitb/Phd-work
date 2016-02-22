/*
The input files for this macro is from the output of macro materialbudgetlambdassim.C 
root macro for analysing the material budget for start detector and lambda disks 
{For calculation of material budget go to
 gconfig folder there is a g3Config.C file (if you are using geant3, g4Config.C if with geant4), please edit it and modify the line:
st->SetMinPoints(1);
with
st->SetMinPoints(0); suggested by Stefano Spataro}*/
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <TGeoNode.h>
#include "TGeoVolume.h"
#include <TFile.h>
#include <TTree.h>
#include <TGeoManager.h>
#include <TClonesArray.h>
#include <TH1D.h>
#include <TROOT.h> 
#include <TH2D.h>
#include <TVector3.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TStopwatch.h>
#include <THStack.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TColor.h>
#include "/home/shyam/pandaroot/base/event/FairRadLenPoint.h"
#include "/home/shyam/pandaroot/pnddata/PndMCTrack.h"
#include "/home/shyam/pandaroot/macro/run/Tools.C"

void materialbudgetlambdas(int nEvents=200000)
{

     LoadPandaStyle();
   //gStyle->SetOptStat("nemruoi");
   gStyle->SetPalette(1);
   gStyle->SetOptTitle(0);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
   gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);

// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------

  TFile* f = new TFile("geantinosimLambdaGe.root"); //
  TTree *t=(TTree *) f->Get("cbmsim") ;
  TFile* f1 = new TFile("geantinoparamsLambdaGe.root");
  f1->Get("FairGeoParSet"); // if it is not working use FairBaseParSet
  TClonesArray* mc_array=new TClonesArray("PndMCTrack");
  t->SetBranchAddress("MCTrack",&mc_array);//Branch names
  TClonesArray* rad_array=new TClonesArray("FairRadLenPoint");
  t->SetBranchAddress("RadLen",&rad_array);

  // histos
  int res = 200; int angres = 180;
  TH1D* hRadLenDistMat = new TH1D("radldm","Material thicknesses",100,0,5);
  hRadLenDistMat->SetTitle("Effective distance ;Effective distance");
  TH1D* hRadLenDistEff = new TH1D("radlde","Effective Radiation length",100,0,0.5);
  hRadLenDistEff->SetTitle("Effective radiation length (X/X_{0}) ;X/X_{0}");
  TH2D* hisxy = new TH2D("hisxy","MC Points, xy view",res,-15.,15.,res,-15.,15.);
  hisxy->SetTitle("X-Y View;X Points;Y Points");
  TH2D* hisrz = new TH2D("hisrz","MC Points, rz view",res,38,62.,res,-15.,15.);
  hisrz->SetTitle("R-Z View;Z Points;r Points");
  

  TProfile* thetaprofile = new TProfile("thetaprof","Radiaion length (#theta)",angres,0.,(TMath::Pi())*25/180);
  thetaprofile->SetTitle("Effective radiation length (X/X_{0}) vs #theta ;#theta;X/X_{0}");
  TProfile* phiprofile = new TProfile("phiprof","Radiaion length (#phi)",angres,-1.*TMath::Pi(),TMath::Pi());
  phiprofile->SetTitle("Effective radiation length (X/X_{0}) vs #phi;#phi;X/X_{0}");

  TProfile2D* histhephi = new TProfile2D("hThePhi","",90,0.,(TMath::Pi())*25/180,90,-1.*TMath::Pi(),TMath::Pi());
  histhephi->SetTitle("Effective radiation length (X/X_{0}) vs #theta & #phi;#theta;#phi");
  TH1D* hisz = new TH1D("hZ","Z",100,38.,62.);
  hisz->SetTitle("Z View;Z Points");

  TString detname,volname;
  double radlen=0.,effradl=0.,effradlsum=0.,theta=0.,phi=0.,d=0.;
  TVector3 in, out, dist, point, mom;
//-----------------Main part of code-----------------------------------
  for (Int_t event=0; event<nEvents&&t->GetEntriesFast(); event++)// Reading the entries in tree
  {
    t->GetEntry(event);
   for (Int_t trackno=0; trackno<mc_array->GetEntriesFast();trackno++){
      PndMCTrack* aTrack = (PndMCTrack*)mc_array->At(trackno);
      mom = aTrack->GetMomentum();
      theta = mom.Theta(); phi = mom.Phi();
      effradl=0.;  effradlsum=0.; d=0.;
      for (Int_t k=0; k<rad_array->GetEntriesFast(); k++){
        FairRadLenPoint* radpoint = (FairRadLenPoint*)rad_array->At(k);
          if (radpoint->GetTrackID() != trackno) continue;
         in = radpoint->GetPosition();
         out = radpoint->GetPositionOut();
        point.SetXYZ(0.5*(in.x()+out.x()),0.5*(in.y()+out.y()),0.5*(in.z()+out.z()));
       TGeoNode* node = gGeoManager->FindNode(point.x(),point.y(),point.z());
        if(!node) continue;
        node->cd();
        volname = node->GetVolume()->GetName();
        if((out.z()-in.z())<0) continue;
 //if( "CarbonFoam"!= volname && "CarbonFiber"!= volname && "SiliconReadout"!= volname && "AluCables"!= volname && "CarbonFoamSmall"!= volname && "CarbonFiberSmall"!= volname && "SiliconReadoutSmall"!= volname && "AluCablesSmall"!= volname )continue;
    // if( "CarbonFoam"!= volname && "CarbonFiber"!= volname && "SiliconReadout"!= volname && "AluCables"!= volname && "CarbonFoamSmall"!= volname && "CarbonFiberSmall"!= volname && "SiliconReadoutSmall"!= volname && "AluCablesSmall"!= volname )continue;
       if( "StripSensorActiveLargeTrap"!= volname &&"StripSensorActiveSmallTrap"!= volname )continue;
//if( "StripSensorActiveLargeTrap"== volname || "StripSensorActiveSmallTrap"== volname || "cave"== volname )continue; //(uncomment for only support)
           radlen = radpoint->GetRadLength();
           dist = in - out;
           effradl = dist.Mag()/radlen;
           d+=dist.Mag();
           //if(d<0.06)continue;
           effradlsum+=effradl;
    	   cout<<"In Position\t"<<in.X()<<"\t"<<in.Y()<<"\t"<<in.Z()<<endl;
    	   cout<<"Out Position\t"<<out.X()<<"\t"<<out.Y()<<"\t"<<out.Z()<<endl;
    	   cout<<"Radiation Length material\t"<<radlen<<endl;
    	   cout<<"Distance\t"<<dist.Mag()<<endl;
    	   cout<<"Effective Distance"<<d<<endl;
    	   cout<<"Volume Name\t"<<volname<<endl;
    	   cout<<"Radiation length"<<effradl<<endl;
    	   cout<<"Effective Radiation Length"<<effradlsum<<endl;
    	   cout<<"\t"<<endl;
        hRadLenDistMat->Fill(d);
        hRadLenDistEff->Fill(effradlsum);
        hisz->Fill(in.Z(),effradlsum);
        hisxy->Fill(in.X(),in.Y());
        if(in.Y()>0.) hisrz->Fill(in.Z(),in.Perp());
        else hisrz->Fill(in.Z(),-1.*in.Perp());
      thetaprofile->Fill(theta,effradlsum);
      phiprofile->Fill(phi,effradlsum);
      histhephi->Fill(theta,phi,effradlsum);

      } //radiation points

    }//tracks

  }// end for event
//------------------------------End of the main part of code--
Int_t a=2,b=2;
int resol = 250;
TPad* mypad = (TPad*) gPad;
TCanvas* can1 = new TCanvas("can1","MCHit view in LMBD",0,0,a*resol,b*resol);
can1->Divide(a,b);
can1->cd(1);
hisxy->SetStats(true);
hisxy->DrawCopy("colz");
can1->cd(2);
hisrz->SetStats(true);
hisrz->DrawCopy("colz");
can1->cd(3);
hisz->SetFillColor(38);
hisz->DrawCopy();
can1->cd(4);
gPad->SetLogy();
hRadLenDistMat->SetFillColor(38);
hRadLenDistMat->DrawCopy();

TCanvas* can2 = new TCanvas("can2","Radiation Length for start detector",0,0,a*resol,b*resol);
/*can2->Divide(a,b);
can2->cd(1);
gPad->SetLogy();
hRadLenDistEff->SetFillColor(38);
hRadLenDistEff->DrawCopy();
can2->cd(2);
gPad->SetLogy();
phiprofile->SetFillColor(kYellow);
phiprofile->SetLineColor(kBlue);
phiprofile->Draw("hist");
can2->cd(3);
gPad->SetLogy();
thetaprofile->SetFillColor(kRed);
thetaprofile->SetLineColor(kBlue);
thetaprofile->Draw("hist");
can2->cd(4);*/
//histhephi->SetFillColor(kBlack);
histhephi->SetStats(true);
histhephi->DrawCopy("lego2Z");
// -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------

}



///////////// code for checking the basic things works in ALICE and also in PANDA of particles by shyam kumar

#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"

void checknew()
   {

////////////////////////////////////////////////////// style of the plot
   gStyle->SetPalette(1);
   gStyle->SetOptTitle(0);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
   gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);
///////////////////////////////////////////////Reading the root file
 TFile *f = TFile::Open("sim_complete.root");
 TTree *cbmsim = (TTree*)f->Get("cbmsim"); 
  
TCanvas* c1 = new TCanvas("Simple plot", "Simulation", 100, 100, 800, 800);
c1->Divide(2,2);

//////////////////////////////////////////////////////////////
c1->cd(1);
cbmsim->Draw("MCTrack.fPdgCode>> Pdg(100,0,2300)");
Pdg->GetXaxis()->SetTitle("MCTrack.Pdgcode");
//////////////////////////////////////////////////////////////////////
c1->cd(2);
cbmsim->Draw("STARTPoint.fX:STARTPoint.fY>> Points(100,-14,14,100,-14,14)","","colz");
Points->GetXaxis()->SetTitle("X hits");
Points->GetYaxis()->SetTitle("Y hits");
/////////////////////////////////////////////////////////////////////
c1->cd(3);
cbmsim->Draw("STARTPoint.fZ>> Zpoints(100,38,41)");
Zpoints->GetXaxis()->SetTitle("Z Points");
///////////////////////////////////////////////////////////////////////////////////
c1->cd(4);
cbmsim->Draw("STARTPoint.fELoss*1000000:TMath::Sqrt(STARTPoint.fPx*STARTPoint.fPx+STARTPoint.fPy*STARTPoint.fPy+STARTPoint.fPz*STARTPoint.fPz)>> Eloss(100,0,2.0,100,100,1000)","","colz");
Eloss->GetXaxis()->SetTitle("Energy Loss (KeV)");

//else
//exit();
}

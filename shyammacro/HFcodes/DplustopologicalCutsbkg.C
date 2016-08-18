/* Macro for Dplus Topological Cuts */
// Shyam Kumar 16-04-2016
#include <Riostream.h>
#include <TStyle.h>
#include <TFile.h>
#include <TList.h>
#include <TDirectoryFile.h>
#include "THnSparse.h"
#include <TClonesArray.h>
#include <TH1F.h>
#include <TCanvas.h>
#include </home/shyam/alice/aliphysics/master/src/PWGHF/vertexingHF/AliHFMassFitter.h>
#include <fstream>
#include <cmath>
//-----------------Function---------------------------------------------
void DplustopologicalCuts()
{
 TCanvas *c1 = new TCanvas("c1", "D Plus Topological Cuts",0,52,2500,1200);
 TCanvas *c2 = new TCanvas("c2", "D Plus Topological Cuts",0,52,2500,1200);
 c1->Divide(2,2);
 c2->Divide(2,2);
 //------------Root Style----------------------------------------
        gStyle->SetOptTitle(1);
        //gStyle->SetTitleOffset(1.20,"X");
      //  gStyle->SetTitleOffset(1.20,"Y");
	gStyle->SetTitleSize(0.5,"X");
        gStyle->SetTitleSize(0.5,"Y");
	gStyle->SetLabelSize(1.0,"X");
        gStyle->SetLabelSize(1.0,"Y");
	gStyle->SetHistLineWidth(2);
	gStyle->SetOptFit(1);
       // gStyle->SetOptFit(0111);
       // gStyle->SetOptStat("nemroui");
 // -----   Timer   --------------------------------------------------------
	 TStopwatch timer;
	 timer.Start();
   gSystem->Exec(Form("mkdir -p DplusCuts/root"));	  
 //--------------Reading the file--------------------
    TString filename="AnalysisResults.root";
    TFile* f = new TFile(filename,"READ");
    if(!f->IsOpen()){
    cout<<"File "<<filename.Data()<<" not found"<<endl;
    return;
    }
  TString DirectoryoutputSE="PP_DPlusHadCorr_SE_wTrkEff_wDkEff_PoolbyPool_Pass4SE";
  TString objectoutputSE="coutBasicPlots_PP_DPlusHadCorr_SE_wTrkEff_wDkEff_PoolbyPool_Pass4SE";
    //Fatching D+ Correlations task directory
    TDirectoryFile *DplusCutdirectory = (TDirectoryFile*)f->Get(DirectoryoutputSE.Data());
    if(!DplusCutdirectory){
        Printf("No Dplus Corr directory SE %s .. Exiting", DirectoryoutputSE.Data());
        return;
    }
    TList *DCutlist = (TList*)DplusCutdirectory->Get(objectoutputSE);
    if(!DCutlist){
        Printf("No Dplus Corr list %s found, exiting... ", objectoutputSE.Data());
        return;
    }
    
 
  //-------------------D Plus Invariant Mass for Tight Cuts-----------------------
 
  TString Events="fHistNEvents";
  TString Dplus="fHistNDplus"; 
  TString phi="AssoTrkPhi"; 
  TString eta="AssoTrkEta"; 
  TString pt="AssoTrkPt"; 
  TString mphi="DplusMVsPhi";
  TString meta="DplusMVsEta";
  TString multi="h2SPDTrkVsTrkMult";
  //------Basic Histograms-----------------------
  
  TH1F *hEvents=(TH1F*)DCutlist->FindObject(Events); 
  TH1F *hDplus=(TH1F*)DCutlist->FindObject(Dplus); 
  TH1F *hPhi=(TH1F*)DCutlist->FindObject(phi); 
  TH1F *hEta=(TH1F*)DCutlist->FindObject(eta);
  TH1F *hpt=(TH1F*)DCutlist->FindObject(pt);
  TH2F *hmphi=(TH2F*)DCutlist->FindObject(mphi);
  TH2F *hmeta=(TH2F*)DCutlist->FindObject(meta);
  TH2F *hmulti=(TH2F*)DCutlist->FindObject(multi);
  c1->cd(1);
  hEvents->GetXaxis()->SetTitle("NEvents"); 
  hEvents->GetYaxis()->SetTitle("Entries");
  hEvents->GetXaxis()->CenterTitle(true);
  hEvents->GetYaxis()->CenterTitle(true);
  hEvents->SetLabelSize(0.045,"X");
  hEvents->SetTitleOffset(0.9,"X");
  hEvents->SetTitleOffset(1.10,"Y");
  hEvents->SetTitleSize(0.05,"X");
  hEvents->SetTitleSize(0.05,"Y");
  hEvents->Draw();
  c1->cd(2);
  hDplus->GetXaxis()->SetTitle("NDplus");
  hDplus->GetYaxis()->SetTitle("Entries");
  hDplus->GetXaxis()->CenterTitle(true);
  hDplus->GetYaxis()->CenterTitle(true);
  hDplus->SetLabelSize(0.045,"X");
  hDplus->SetTitleOffset(0.9,"X");
  hDplus->SetTitleOffset(1.10,"Y");
  hDplus->SetTitleSize(0.05,"X");
  hDplus->SetTitleSize(0.05,"Y");
  hDplus->Draw();
  c1->cd(3);
  hPhi->GetXaxis()->SetTitle("#phi");
  hPhi->GetYaxis()->SetTitle("Entries");
  hPhi->GetXaxis()->CenterTitle(true);
  hPhi->GetYaxis()->CenterTitle(true);
  hPhi->SetLabelSize(0.045,"X");
  hPhi->SetTitleOffset(0.9,"X");
  hPhi->SetTitleOffset(1.10,"Y");
  hPhi->SetTitleSize(0.05,"X");
  hPhi->SetTitleSize(0.05,"Y");
  hPhi->Draw("hist");
  c1->cd(4);
  hEta->GetXaxis()->SetTitle("#eta");
  hEta->GetYaxis()->SetTitle("Entries");
  hEta->GetXaxis()->CenterTitle(true);
  hEta->GetYaxis()->CenterTitle(true);
  hEta->SetLabelSize(0.045,"X");
  hEta->SetTitleOffset(0.9,"X");
  hEta->SetTitleOffset(1.10,"Y");
  hEta->SetTitleSize(0.05,"X");
  hEta->SetTitleSize(0.05,"Y");
  hEta->Draw("hist");
  c1->SaveAs("DplusCuts/looseBasiccuts1Pass4.png");
  c1->SaveAs("DplusCuts/root/looseBasiccuts1Pass4.root");
  c2->cd(1);
  hpt->GetXaxis()->SetTitle("Pt (GeV/c)"); 
  hpt->GetYaxis()->SetTitle("Entries");
  hpt->GetXaxis()->CenterTitle(true);
  hpt->GetYaxis()->CenterTitle(true);
  hpt->SetLabelSize(0.045,"X");
  hpt->SetTitleOffset(0.9,"X");
  hpt->SetTitleOffset(1.10,"Y");
  hpt->SetTitleSize(0.05,"X");
  hpt->SetTitleSize(0.05,"Y");
  hpt->Draw("hist");
  c2->cd(2);
  hmphi->GetXaxis()->SetTitle("D^{+} Inv Mass");
  hmphi->GetYaxis()->SetTitle("#phi");
  hmphi->GetXaxis()->CenterTitle(true);
  hmphi->GetYaxis()->CenterTitle(true);
  hmphi->SetLabelSize(0.045,"X");
  hmphi->SetTitleOffset(0.9,"X");
  hmphi->SetTitleOffset(1.10,"Y");
  hmphi->SetTitleSize(0.05,"X");
  hmphi->SetTitleSize(0.05,"Y");
  hmphi->SetStats(false);
  hmphi->Draw("colz");
  c2->cd(3);
  hmeta->GetXaxis()->SetTitle("D^{+} Inv Mass");
  hmeta->GetYaxis()->SetTitle("#eta");
  hmeta->GetXaxis()->CenterTitle(true);
  hmeta->GetYaxis()->CenterTitle(true);
  hmeta->SetLabelSize(0.045,"X");
  hmeta->SetTitleOffset(0.9,"X");
  hmeta->SetTitleOffset(1.10,"Y");
  hmeta->SetTitleSize(0.05,"X");
  hmeta->SetTitleSize(0.05,"Y");
  hmeta->SetStats(false);
  hmeta->Draw("colz");
  c2->cd(4);
  hmulti->GetXaxis()->SetTitle("SPD Tracklets");
  hmulti->GetYaxis()->SetTitle("Track Multiplicity");
  hmulti->GetXaxis()->CenterTitle(true);
  hmulti->GetYaxis()->CenterTitle(true);
  hmulti->SetLabelSize(0.045,"X");
  hmulti->SetTitleOffset(0.9,"X");
  hmulti->SetTitleOffset(1.10,"Y");
  hmulti->SetTitleSize(0.05,"X");
  hmulti->SetTitleSize(0.05,"Y");
  hmulti->SetStats(false);
  hmulti->Draw("colz");
  c2->SaveAs("DplusCuts/looseBasiccuts2Pass4.png");
  c2->SaveAs("DplusCuts/root/looseBasiccuts2Pass4.root");
//--------Topological cuts for Pt Bins---------

 const Int_t n=15; //Number of Histos
 TCanvas *canvas1[n]; //Declaration of canvas
 TCanvas *canvas2[n]; //Declaration of canvas
 TCanvas *canvas3[n]; //Declaration of canvas
 TCanvas *canvas4[n]; //Declaration of canvas
 for(Int_t i=0;i<n;i++){ //n Pt Bins
          canvas1[i] = 0x0; //Initialization
          canvas1[i] = new TCanvas(Form("Dpluscutsc1_%d",i),Form("Dpluscutsc1_%d",i),2500,1200);
          canvas1[i]->Divide(3,2);
          canvas2[i] = 0x0; //Initialization
          canvas2[i] = new TCanvas(Form("Dpluscutsc2_%d",i),Form("Dpluscutsc2_%d",i),2500,1200);
          canvas2[i]->Divide(3,2);
          canvas3[i] = 0x0; //Initialization
          canvas3[i] = new TCanvas(Form("Dpluscutsc3_%d",i),Form("Dpluscutsc3_%d",i),2500,1200);
          canvas3[i]->Divide(3,1);
          canvas4[i] = 0x0; //Initialization
          canvas4[i] = new TCanvas(Form("Dpluscutsc4_%d",i),Form("Dpluscutsc4_%d",i),2500,1200);
          canvas4[i]->Divide(2,2);
          TString ptdaukaon=Form("hPtDaughterKaon_Bin%d", i);
	  TString ptdaupion1=Form("hPtDaughterPion1_Bin%d", i);
	  TString ptdaupion2=Form("hPtDaughterPion2_Bin%d", i);
          TString d0daukaon=Form("hd0DaughterKaon_Bin%d", i);
          TString d0daupion1=Form("hd0DaughterPion1_Bin%d", i);
          TString d0daupion2=Form("hd0DaughterPion2_Bin%d", i);
          TString dist12=Form("hdist12_Bin%d", i);
          TString dist23=Form("hdist23_Bin%d", i);
          TString sigmaV=Form("hSigmaVert_Bin%d", i);
	  TString CosPA=Form("hCosPA_Bin%d", i);
	  TString CosPAXY=Form("hCosPAXY_Bin%d", i);
          TString Ndecaylen=Form("hNDeacyLenXY_Bin%d", i); 
	  TString decaylen=Form("hDecayLen_Bin%d", i);
	  TString decaylenxy=Form("hDecayLenXY_Bin%d", i);
          TString dca=Form("hDCA_Bin%d", i);
	  TString d0square=Form("hd0square_Bin%d", i);
          TString drapidty=Form("hDrapidty_Bin%d",i);
          TString CosPAvsdPS=Form("hCosPAvsdPS_Bin%d", i);
          TString d0KvsPtK=Form("hd0DaughterKaonvsPtK_Bin%d", i);
          TString d0Pi1vsPtPi1=Form("hd0DaughterPion1vsPtPi1_Bin%d", i); //here should be hd0 instead of hPt
          TString d0Pi2vsPtPi2=Form("hd0DaughterPion2vsPtPi2_Bin%d", i); //here should be hd0 instead of hPt
          TH1F *hptdaukaon=(TH1F*)DCutlist->FindObject(ptdaukaon);
          TH1F *hptdaupion1=(TH1F*)DCutlist->FindObject(ptdaupion1);
          TH1F *hptdaupion2=(TH1F*)DCutlist->FindObject(ptdaupion2);
          TH1F *hd0daukaon=(TH1F*)DCutlist->FindObject(d0daukaon);
          TH1F *hd0daupion1=(TH1F*)DCutlist->FindObject(d0daupion1);
          TH1F *hd0daupion2=(TH1F*)DCutlist->FindObject(d0daupion2);
          TH1F *hdist12=(TH1F*)DCutlist->FindObject(dist12);
          TH1F *hdist23=(TH1F*)DCutlist->FindObject(dist23);
          TH1F *hsigmaV=(TH1F*)DCutlist->FindObject(sigmaV);
          TH1F *hcosPA=(TH1F*)DCutlist->FindObject(CosPA);
          TH1F *hcosPAXY=(TH1F*)DCutlist->FindObject(CosPAXY);
          //TH1F *hNdecaylen=(TH1F*)DCutlist->FindObject(Ndecaylen);
          TH1F *hdecaylenxy=(TH1F*)DCutlist->FindObject(decaylenxy);
          TH1F *hdecaylen=(TH1F*)DCutlist->FindObject(decaylen);
          TH1F *hdca=(TH1F*)DCutlist->FindObject(dca);
          TH1F *hd0square=(TH1F*)DCutlist->FindObject(d0square);
	//  TH1F *hdrapidty=(TH1F*)DCutlist->FindObject(drapidty);
          TH2F *hCosPAvsdPS=(TH2F*)DCutlist->FindObject(CosPAvsdPS);
          TH2F *hd0KvsPtK=(TH2F*)DCutlist->FindObject(d0KvsPtK);
          TH2F *hd0Pi1vsPtPi1=(TH2F*)DCutlist->FindObject(d0Pi1vsPtPi1);
          TH2F *hd0Pi2vsPtPi2=(TH2F*)DCutlist->FindObject(d0Pi2vsPtPi2);
          canvas1[i]->cd(1);
          hptdaukaon->GetXaxis()->SetTitle("P_{t} Kaon [GeV/c]"); 
	  hptdaukaon->GetYaxis()->SetTitle("Entries");
          hptdaukaon->GetXaxis()->SetRangeUser(0.0,40.0);
	  hptdaukaon->GetXaxis()->CenterTitle(true);
	  hptdaukaon->GetYaxis()->CenterTitle(true);
	  hptdaukaon->SetLabelSize(0.045,"X");
	  hptdaukaon->SetTitleOffset(0.9,"X");
	  hptdaukaon->SetTitleOffset(1.0,"Y");
	  hptdaukaon->SetTitleSize(0.05,"X");
	  hptdaukaon->SetTitleSize(0.05,"Y");
          hptdaukaon->Draw();
          canvas1[i]->cd(2);
          hptdaupion1->GetXaxis()->SetTitle("P_{t} Pion1 [GeV/c]"); 
	  hptdaupion1->GetYaxis()->SetTitle("Entries");
          hptdaupion1->GetXaxis()->SetRangeUser(0.0,40.0);
	  hptdaupion1->GetXaxis()->CenterTitle(true);
	  hptdaupion1->GetYaxis()->CenterTitle(true);
	  hptdaupion1->SetLabelSize(0.045,"X");
	  hptdaupion1->SetTitleOffset(0.9,"X");
	  hptdaupion1->SetTitleOffset(1.0,"Y");
	  hptdaupion1->SetTitleSize(0.05,"X");
	  hptdaupion1->SetTitleSize(0.05,"Y");
          hptdaupion1->Draw();
          canvas1[i]->cd(3);
          hptdaupion2->GetXaxis()->SetTitle("P_{t} Pion2 [GeV/c]"); 
	  hptdaupion2->GetYaxis()->SetTitle("Entries");
          hptdaupion2->GetXaxis()->SetRangeUser(0.0,40.0);
	  hptdaupion2->GetXaxis()->CenterTitle(true);
	  hptdaupion2->GetYaxis()->CenterTitle(true);
	  hptdaupion2->SetLabelSize(0.045,"X");
	  hptdaupion2->SetTitleOffset(0.9,"X");
	  hptdaupion2->SetTitleOffset(1.0,"Y");
	  hptdaupion2->SetTitleSize(0.05,"X");
	  hptdaupion2->SetTitleSize(0.05,"Y");
          hptdaupion2->Draw();
          canvas1[i]->cd(4);
          hd0daukaon->GetXaxis()->SetTitle("d_{0} Kaon [mm]"); 
	  hd0daukaon->GetYaxis()->SetTitle("Entries");
          hd0daukaon->GetXaxis()->SetRangeUser(0.0,4.0);
	  hd0daukaon->GetXaxis()->CenterTitle(true);
	  hd0daukaon->GetYaxis()->CenterTitle(true);
	  hd0daukaon->SetLabelSize(0.045,"X");
	  hd0daukaon->SetTitleOffset(0.9,"X");
	  hd0daukaon->SetTitleOffset(1.0,"Y");
	  hd0daukaon->SetTitleSize(0.05,"X");
	  hd0daukaon->SetTitleSize(0.05,"Y");
          hd0daukaon->Draw();
          canvas1[i]->cd(5);
          hd0daupion1->GetXaxis()->SetTitle("d_{0} Pion1 [mm]"); 
	  hd0daupion1->GetYaxis()->SetTitle("Entries");
          hd0daupion1->GetXaxis()->SetRangeUser(0.0,4.0);
	  hd0daupion1->GetXaxis()->CenterTitle(true);
	  hd0daupion1->GetYaxis()->CenterTitle(true);
	  hd0daupion1->SetLabelSize(0.045,"X");
	  hd0daupion1->SetTitleOffset(0.9,"X");
	  hd0daupion1->SetTitleOffset(1.0,"Y");
	  hd0daupion1->SetTitleSize(0.05,"X");
	  hd0daupion1->SetTitleSize(0.05,"Y");
          hd0daupion1->Draw();
          canvas1[i]->cd(6);
          hd0daupion2->GetXaxis()->SetTitle("d_{0} Pion2 [mm]"); 
	  hd0daupion2->GetYaxis()->SetTitle("Entries");
          hd0daupion2->GetXaxis()->SetRangeUser(0.0,4.0);
	  hd0daupion2->GetXaxis()->CenterTitle(true);
	  hd0daupion2->GetYaxis()->CenterTitle(true);
	  hd0daupion2->SetLabelSize(0.045,"X");
	  hd0daupion2->SetTitleOffset(0.9,"X");
	  hd0daupion2->SetTitleOffset(1.0,"Y");
	  hd0daupion2->SetTitleSize(0.05,"X");
	  hd0daupion2->SetTitleSize(0.05,"Y");
          hd0daupion2->Draw();
          canvas2[i]->cd(1);
          hdist12->GetXaxis()->SetTitle("dist 12 (mm)"); 
	  hdist12->GetYaxis()->SetTitle("Entries");
          hdist12->GetXaxis()->SetRangeUser(0.0,35.0);
	  hdist12->GetXaxis()->CenterTitle(true);
	  hdist12->GetYaxis()->CenterTitle(true);
	  hdist12->SetLabelSize(0.045,"X");
	  hdist12->SetTitleOffset(0.9,"X");
	  hdist12->SetTitleOffset(1.0,"Y");
	  hdist12->SetTitleSize(0.05,"X");
	  hdist12->SetTitleSize(0.05,"Y");
          hdist12->Draw();
          canvas2[i]->cd(2);
          hdist23->GetXaxis()->SetTitle("dist 23 (mm)"); 
	  hdist23->GetYaxis()->SetTitle("Entries");
          hdist23->GetXaxis()->SetRangeUser(0.0,35.0);
	  hdist23->GetXaxis()->CenterTitle(true);
	  hdist23->GetYaxis()->CenterTitle(true);
	  hdist23->SetLabelSize(0.045,"X");
	  hdist23->SetTitleOffset(0.9,"X");
	  hdist23->SetTitleOffset(1.0,"Y");
	  hdist23->SetTitleSize(0.05,"X");
	  hdist23->SetTitleSize(0.05,"Y");
          hdist23->Draw();
          canvas2[i]->cd(3);
          hsigmaV->GetXaxis()->SetTitle("#sigma_{vertex} (mm)"); 
	  hsigmaV->GetYaxis()->SetTitle("Entries");
          hsigmaV->GetXaxis()->SetRangeUser(0.0,1.0);
	  hsigmaV->GetXaxis()->CenterTitle(true);
	  hsigmaV->GetYaxis()->CenterTitle(true);
	  hsigmaV->SetLabelSize(0.045,"X");
	  hsigmaV->SetTitleOffset(0.9,"X");
	  hsigmaV->SetTitleOffset(1.0,"Y");
	  hsigmaV->SetTitleSize(0.05,"X");
	  hsigmaV->SetTitleSize(0.05,"Y");
          hsigmaV->Draw();
          canvas2[i]->cd(4);
          hcosPA->GetXaxis()->SetTitle("Cos #theta_{p}"); 
	  hcosPA->GetYaxis()->SetTitle("Entries");
          hcosPA->GetXaxis()->SetRangeUser(0.0,1.0);
	  hcosPA->GetXaxis()->CenterTitle(true);
	  hcosPA->GetYaxis()->CenterTitle(true);
	  hcosPA->SetLabelSize(0.045,"X");
	  hcosPA->SetTitleOffset(0.9,"X");
	  hcosPA->SetTitleOffset(1.0,"Y");
	  hcosPA->SetTitleSize(0.05,"X");
	  hcosPA->SetTitleSize(0.05,"Y");
          hcosPA->SetStats(false);
          hcosPA->Draw();
          canvas2[i]->cd(5);
          hcosPAXY->GetXaxis()->SetTitle("Cos #theta_{pxy}"); 
	  hcosPAXY->GetYaxis()->SetTitle("Entries");
          hcosPAXY->GetXaxis()->SetRangeUser(0.0,1.0);
	  hcosPAXY->GetXaxis()->CenterTitle(true);
	  hcosPAXY->GetYaxis()->CenterTitle(true);
	  hcosPAXY->SetLabelSize(0.045,"X");
	  hcosPAXY->SetTitleOffset(0.9,"X");
	  hcosPAXY->SetTitleOffset(1.0,"Y");
	  hcosPAXY->SetTitleSize(0.05,"X");
	  hcosPAXY->SetTitleSize(0.05,"Y");
          hcosPAXY->SetStats(false);
          hcosPAXY->Draw();
          canvas2[i]->cd(6);
          hdecaylenxy->GetXaxis()->SetTitle("Decay Length XY (mm)"); 
	  hdecaylenxy->GetYaxis()->SetTitle("Entries");
          hdecaylenxy->GetXaxis()->SetRangeUser(0.0,20.0);
	  hdecaylenxy->GetXaxis()->CenterTitle(true);
	  hdecaylenxy->GetYaxis()->CenterTitle(true);
	  hdecaylenxy->SetLabelSize(0.045,"X");
	  hdecaylenxy->SetTitleOffset(0.9,"X");
	  hdecaylenxy->SetTitleOffset(1.0,"Y");
	  hdecaylenxy->SetTitleSize(0.05,"X");
	  hdecaylenxy->SetTitleSize(0.05,"Y");
          hdecaylenxy->Draw();
          canvas3[i]->cd(1);
          hdecaylen->GetXaxis()->SetTitle("Decay Length (mm)"); 
	  hdecaylen->GetYaxis()->SetTitle("Entries");
          hdecaylen->GetXaxis()->SetRangeUser(0,25.0);
	  hdecaylen->GetXaxis()->CenterTitle(true);
	  hdecaylen->GetYaxis()->CenterTitle(true);
	  hdecaylen->SetLabelSize(0.045,"X");
	  hdecaylen->SetTitleOffset(0.9,"X");
	  hdecaylen->SetTitleOffset(1.0,"Y");
	  hdecaylen->SetTitleSize(0.05,"X");
	  hdecaylen->SetTitleSize(0.05,"Y");
          hdecaylen->Draw();
          canvas3[i]->cd(2);
          hdca->GetXaxis()->SetTitle("DCA (mm)"); 
	  hdca->GetYaxis()->SetTitle("Entries");
          hdca->GetXaxis()->SetRangeUser(0,2.0);
	  hdca->GetXaxis()->CenterTitle(true);
	  hdca->GetYaxis()->CenterTitle(true);
	  hdca->SetLabelSize(0.045,"X");
	  hdca->SetTitleOffset(0.9,"X");
	  hdca->SetTitleOffset(1.0,"Y");
	  hdca->SetTitleSize(0.05,"X");
	  hdca->SetTitleSize(0.05,"Y");
          hdca->Draw();
          canvas3[i]->cd(3);
          hd0square->GetXaxis()->SetTitle("#Sigma d_{0}^{2} (mm^{2})"); 
	  hd0square->GetYaxis()->SetTitle("Entries");
          hd0square->GetXaxis()->SetRangeUser(0,5.0);
	  hd0square->GetXaxis()->CenterTitle(true);
	  hd0square->GetYaxis()->CenterTitle(true);
	  hd0square->SetLabelSize(0.045,"X");
	  hd0square->SetTitleOffset(0.9,"X");
	  hd0square->SetTitleOffset(1.0,"Y");
	  hd0square->SetTitleSize(0.05,"X");
	  hd0square->SetTitleSize(0.05,"Y");
          hd0square->Draw();
          canvas4[i]->cd(1);
          hCosPAvsdPS->GetXaxis()->SetTitle("d_{PS} (mm)"); 
	  hCosPAvsdPS->GetYaxis()->SetTitle("CosPA");
          hCosPAvsdPS->GetXaxis()->SetRangeUser(0.0,35.0);
          hCosPAvsdPS->GetYaxis()->SetRangeUser(0.0,1.0);
	  hCosPAvsdPS->GetXaxis()->CenterTitle(true);
	  hCosPAvsdPS->GetYaxis()->CenterTitle(true);
	  hCosPAvsdPS->SetLabelSize(0.045,"X");
	  hCosPAvsdPS->SetTitleOffset(0.9,"X");
	  hCosPAvsdPS->SetTitleOffset(1.0,"Y");
	  hCosPAvsdPS->SetTitleSize(0.05,"X");
	  hCosPAvsdPS->SetTitleSize(0.05,"Y");
          hCosPAvsdPS->Draw();          
          canvas4[i]->cd(2);
          hd0KvsPtK->GetXaxis()->SetTitle("P_{t} Kaon [GeV/c]"); 
	  hd0KvsPtK->GetYaxis()->SetTitle("d_{0} Kaon [mm]");
          hd0KvsPtK->GetXaxis()->SetRangeUser(0.0,25.0);
          hd0KvsPtK->GetYaxis()->SetRangeUser(0.0,4.0);
	  hd0KvsPtK->GetXaxis()->CenterTitle(true);
	  hd0KvsPtK->GetYaxis()->CenterTitle(true);
	  hd0KvsPtK->SetLabelSize(0.045,"X");
	  hd0KvsPtK->SetTitleOffset(0.9,"X");
	  hd0KvsPtK->SetTitleOffset(1.0,"Y");
	  hd0KvsPtK->SetTitleSize(0.05,"X");
	  hd0KvsPtK->SetTitleSize(0.05,"Y");
          hd0KvsPtK->Draw();
          canvas4[i]->cd(3);
          hd0Pi1vsPtPi1->GetXaxis()->SetTitle("P_{t} Pion1 [GeV/c]"); 
	  hd0Pi1vsPtPi1->GetYaxis()->SetTitle("d_{0} Pion1 [mm]");
          hd0Pi1vsPtPi1->GetXaxis()->SetRangeUser(0.0,25.0);
          hd0Pi1vsPtPi1->GetYaxis()->SetRangeUser(0.0,4.0);
	  hd0Pi1vsPtPi1->GetXaxis()->CenterTitle(true);
	  hd0Pi1vsPtPi1->GetYaxis()->CenterTitle(true);
	  hd0Pi1vsPtPi1->SetLabelSize(0.045,"X");
	  hd0Pi1vsPtPi1->SetTitleOffset(0.9,"X");
	  hd0Pi1vsPtPi1->SetTitleOffset(1.0,"Y");
	  hd0Pi1vsPtPi1->SetTitleSize(0.05,"X");
	  hd0Pi1vsPtPi1->SetTitleSize(0.05,"Y");
          hd0Pi1vsPtPi1->Draw();
          canvas4[i]->cd(4);
          hd0Pi2vsPtPi2->GetXaxis()->SetTitle("P_{t} Pion2 [GeV/c]"); 
	  hd0Pi2vsPtPi2->GetYaxis()->SetTitle("d_{0} Pion2 [mm]");
          hd0Pi2vsPtPi2->GetXaxis()->SetRangeUser(0.0,25.0);
          hd0Pi2vsPtPi2->GetYaxis()->SetRangeUser(0.0,4.0);
	  hd0Pi2vsPtPi2->GetXaxis()->CenterTitle(true);
	  hd0Pi2vsPtPi2->GetYaxis()->CenterTitle(true);
	  hd0Pi2vsPtPi2->SetLabelSize(0.045,"X");
	  hd0Pi2vsPtPi2->SetTitleOffset(0.9,"X");
	  hd0Pi2vsPtPi2->SetTitleOffset(1.0,"Y");
	  hd0Pi2vsPtPi2->SetTitleSize(0.05,"X");
	  hd0Pi2vsPtPi2->SetTitleSize(0.05,"Y");
          hd0Pi2vsPtPi2->Draw();
          
          canvas1[i]->SaveAs(Form("DplusCuts/Dpluscutsc1Pass4%d.png",i));
          canvas1[i]->SaveAs(Form("DplusCuts/root/Dpluscutsc1Pass4%d.root",i));
          canvas2[i]->SaveAs(Form("DplusCuts/Dpluscutsc2Pass4%d.png",i));
          canvas2[i]->SaveAs(Form("DplusCuts/root/Dpluscutsc2Pass4%d.root",i));
          canvas3[i]->SaveAs(Form("DplusCuts/Dpluscutsc3Pass4%d.png",i));
          canvas3[i]->SaveAs(Form("DplusCuts/root/Dpluscutsc3Pass4%d.root",i));
          canvas4[i]->SaveAs(Form("DplusCuts/Dpluscutsc4Pass4%d.png",i));
          canvas4[i]->SaveAs(Form("DplusCuts/root/Dpluscutsc4Pass4%d.root",i));
       }
  
  // -----  Finish   -------------------------------------------------------
        timer.Stop();
         Double_t rtime = timer.RealTime();
	 Double_t ctime = timer.CpuTime();
	 cout << endl << endl;
	 cout << "Macro finished succesfully." << endl;
	 cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
	  cout << endl;	

}	  

//------New Macro for comparison for Pass4 old Eff vs Pass4 New Eff-------------

#include<TString.h>
//using namespace std::
const Int_t nhistos=19; //Number of histograms
//--------Change the setting below--------------
 // there are four canvas write their names
//----------------------------------------------
TString *filenames = new TString[nhistos];

void Compare_Pass4_Data_MC(){
    gStyle->SetOptStat(1);
     gSystem->Exec(Form("mkdir -p DPlusTopoCuts/"));
    for (Int_t Bin=2; Bin<15; Bin++)
    {	
    for (Int_t canvasno=1; canvasno<4; canvasno++)
    {
    DoAllPlots(canvasno, Bin);
    }
    }
    
   }

//1D_pp_DplusCorr_______________________________________________________________________
  void DoAllPlots(Int_t canvasno, Int_t Bin){
        gStyle->SetTitleSize(0.05,"");
   // gStyle->SetPalette(1);
        TString s1=Form("hPtDaughterKaon_Bin%d_MC",Bin); //
        TString b1=Form("hPtDaughterKaon_Bin%d",Bin);// 
        TString s2=Form("hPtDaughterPion1_Bin%d_MC",Bin); //
        TString b2=Form("hPtDaughterPion1_Bin%d",Bin);// 
        TString s3=Form("hPtDaughterPion2_Bin%d_MC",Bin); //
        TString b3=Form("hPtDaughterPion2_Bin%d",Bin);// 
        TString s4=Form("hd0DaughterKaon_Bin%d_MC",Bin); //
        TString b4=Form("hd0DaughterKaon_Bin%d",Bin);// 
        TString s5=Form("hd0DaughterPion1_Bin%d_MC",Bin); //
        TString b5=Form("hd0DaughterPion1_Bin%d",Bin);// 
        TString s6=Form("hd0DaughterPion2_Bin%d_MC",Bin); //
        TString b6=Form("hd0DaughterPion2_Bin%d",Bin);// 
        TString s7=Form("hdist12_Bin%d_MC",Bin); //
        TString b7=Form("hdist12_Bin%d",Bin);//
        TString s8=Form("hdist23_Bin%d_MC",Bin); //
        TString b8=Form("hdist23_Bin%d",Bin);//
        TString s9=Form("hSigmaVert_Bin%d_MC",Bin); //
        TString b9=Form("hSigmaVert_Bin%d",Bin);//
        TString s10=Form("hCosPA_Bin%d_MC",Bin); //
        TString b10=Form("hCosPA_Bin%d",Bin);//
        TString s11=Form("hCosPAXY_Bin%d_MC",Bin); //
        TString b11=Form("hCosPAXY_Bin%d",Bin);//
        TString s12=Form("hDecayLenXY_Bin%d_MC",Bin); //
        TString b12=Form("hDecayLenXY_Bin%d",Bin);//
        TString s13=Form("hDecayLen_Bin%d_MC",Bin); //
        TString b13=Form("hDecayLen_Bin%d",Bin);//
        TString s14=Form("hDCA_Bin%d_MC",Bin); //
        TString b14=Form("hDCA_Bin%d",Bin);//
        TString s15=Form("hd0square_Bin%d_MC",Bin); //
        TString b15=Form("hd0square_Bin%d",Bin);//
        TString s16=Form("hCosPAvsdPS_Bin%d_MC",Bin); //
        TString b16=Form("hCosPAvsdPS_Bin%d",Bin);//
        TString s17=Form("hd0DaughterKaonvsPtK_Bin%d_MC",Bin); //
        TString b17=Form("hd0DaughterKaonvsPtK_Bin%d",Bin);//
        TString s18=Form("hd0DaughterPion1vsPtPi1_Bin%d_MC",Bin); //
        TString b18=Form("hd0DaughterPion1vsPtPi1_Bin%d",Bin);//
        TString s19=Form("hd0DaughterPion2vsPtPi2_Bin%d_MC",Bin); //
        TString b19=Form("hd0DaughterPion2vsPtPi2_Bin%d",Bin);//
    
       LoadFileNamesPPDMeson(canvasno, Bin);
       TCanvas ** Canvas = new TCanvas *[nhistos];
       TH2F *hDraw;
       TH1F *hSignal1[nhistos],*hData1[nhistos], *hratioLow[2], *hratioMid[2], *hratioHigh[2];
       TH2F *hSignal[nhistos], *hData[nhistos];
       
       Canvas[0]=GetCanvasBFD(0,"corrMECorrected",canvasno,Bin); //Canvas[0]->Draw();
       hSignal1[0]=(TH1F*)Canvas[0]->FindObject(s1);
       hSignal1[1]=(TH1F*)Canvas[0]->FindObject(s2);
       hSignal1[2]=(TH1F*)Canvas[0]->FindObject(s3);
       hSignal1[3]=(TH1F*)Canvas[0]->FindObject(s4);
       hSignal1[4]=(TH1F*)Canvas[0]->FindObject(s5);
       hSignal1[5]=(TH1F*)Canvas[0]->FindObject(s6);
       hSignal1[6]=(TH1F*)Canvas[0]->FindObject(s7);
       hSignal1[7]=(TH1F*)Canvas[0]->FindObject(s8);
       hSignal1[8]=(TH1F*)Canvas[0]->FindObject(s9);
       hSignal1[9]=(TH1F*)Canvas[0]->FindObject(s10);
       hSignal1[10]=(TH1F*)Canvas[0]->FindObject(s11);
       hSignal1[11]=(TH1F*)Canvas[0]->FindObject(s12);
       hSignal1[12]=(TH1F*)Canvas[0]->FindObject(s13);
       hSignal1[13]=(TH1F*)Canvas[0]->FindObject(s14);
       hSignal1[14]=(TH1F*)Canvas[0]->FindObject(s15);
       hSignal[15]=(TH2F*)Canvas[0]->FindObject(s16);
       hSignal[16]=(TH2F*)Canvas[0]->FindObject(s17);
       hSignal[17]=(TH2F*)Canvas[0]->FindObject(s18);
       hSignal[18]=(TH2F*)Canvas[0]->FindObject(s19);
       
       Canvas[1]=GetCanvasBFD(1,"corrMECorrected",canvasno,Bin);
       hData1[0]=(TH1F*)Canvas[1]->FindObject(b1);
       hData1[1]=(TH1F*)Canvas[1]->FindObject(b2);
       hData1[2]=(TH1F*)Canvas[1]->FindObject(b3);
       hData1[3]=(TH1F*)Canvas[1]->FindObject(b4);
       hData1[4]=(TH1F*)Canvas[1]->FindObject(b5);
       hData1[5]=(TH1F*)Canvas[1]->FindObject(b6);
       hData1[6]=(TH1F*)Canvas[1]->FindObject(b7);
       hData1[7]=(TH1F*)Canvas[1]->FindObject(b8);
       hData1[8]=(TH1F*)Canvas[1]->FindObject(b9);
       hData1[9]=(TH1F*)Canvas[1]->FindObject(b10);
       hData1[10]=(TH1F*)Canvas[1]->FindObject(b11);
       hData1[11]=(TH1F*)Canvas[1]->FindObject(b12);
       hData1[12]=(TH1F*)Canvas[1]->FindObject(b13);
       hData1[13]=(TH1F*)Canvas[1]->FindObject(b14);
       hData1[14]=(TH1F*)Canvas[1]->FindObject(b15);
       hData[15]=(TH2F*)Canvas[1]->FindObject(b16);
       hData[16]=(TH2F*)Canvas[1]->FindObject(b17);
       hData[17]=(TH2F*)Canvas[1]->FindObject(b18);
       hData[18]=(TH2F*)Canvas[1]->FindObject(b19);
    
 //----------------------------------------------------------------------------------------------
   
    if(canvasno==1){
    TCanvas *Comparison1=new TCanvas(Form("Comparison1_Bin%d",Bin)," Toplogical Cuts1 for MC and Bkg Data",2500,1200);
    Comparison1->Divide(3,2);
    Comparison1->SetMargin(0.01, 0.01 ,0.1,0.01);
    for (Int_t n=1; n<7;n++)
    { 
    Comparison1->cd(n);
    TPad *p1= Comparison1->cd(n);
    p1->SetLogy();
    //p1->SetLogx();
  //  hSignal1[n-1]->SetMaximum(hSignal1[n-1]->GetMaximum()*1.50);
   // hSignal1[n-1]->SetMaximum(1000000.0);
    Int_t nbins=hSignal1[n-1]->GetNbinsX();
    Double_t integral= hSignal1[n-1]->Integral(1,nbins);// first bin is always =1;
  //  Int_t entries=hSignal1[n-1]->GetEntries();
 //   std::cout<<"Signal Integral is:"<<integral<<std::endl;
   // std::cout<<"Entries is:"<<entries<<std::endl;
    hSignal1[n-1]->Scale(1/integral);
    hSignal1[n-1]->GetYaxis()->CenterTitle(true);
    hSignal1[n-1]->GetXaxis()->CenterTitle(true);
    hSignal1[n-1]->SetTitleSize(0.045,"X");
    hSignal1[n-1]->SetTitleOffset(1.0,"X");
    hSignal1[n-1]->SetStats(false);
    hSignal1[n-1]->SetTitleOffset (1.0,"Y");
    hSignal1[n-1]->SetMarkerColor(kRed);
    hSignal1[n-1]->SetMarkerStyle(8);
    hSignal1[n-1]->SetMarkerSize(0.80);
    hSignal1[n-1]->Draw();
    hData1[n-1]->SetMarkerColor(kBlue);
    hData1[n-1]->SetMarkerStyle(8);
    hData1[n-1]->SetMarkerSize(0.80);
    hData1[n-1]->SetStats(false);
    Int_t nbins=hData1[n-1]->GetNbinsX();
    Double_t integral= hData1[n-1]->Integral(1,nbins);// first bin is always =1;
    hData1[n-1]->Scale(1/integral);
   // std::cout<<"Background Integral is:"<<integral<<std::endl;
   // Int_t entries=hData1[n-1]->GetEntries();
   // hData1[n-1]->Scale(1/entries);
    hData1[n-1]->Draw("same");
   // hData1[n-1]->Draw("samehist");
    leg = new TLegend(0.4,0.65,0.9,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
   Comparison1->SaveAs(Form("DPlusTopoCuts/Topologicalcutsc%dforBin%d.png",canvasno,Bin));
  }
   if(canvasno==2){
    TCanvas *Comparison2=new TCanvas(Form("Comparison2_Bin%d",Bin)," Toplogical Cuts2 for MC and Bkg Data",2500,1200);
    Comparison2->SetMargin(0.01, 0.01 ,0.1,0.01);
    Comparison2->Divide(3,2);
    for (Int_t n=7; n<13; n++)
    { 
    Comparison2->cd(n-6);
    TPad *p2= Comparison2->cd(n-6);
    p2->SetLogy();
    hSignal1[6]->GetXaxis()->SetRangeUser(0.0,18.0);
    hSignal1[7]->GetXaxis()->SetRangeUser(0.0,18.0);
    hSignal1[8]->GetXaxis()->SetRangeUser(0.0,0.7);
    hSignal1[9]->GetXaxis()->SetRangeUser(0.6,1.0);
    hSignal1[10]->GetXaxis()->SetRangeUser(0.7,1.0);
    hSignal1[11]->GetXaxis()->SetRangeUser(0.0,13.0);
    Int_t nbins=hSignal1[n-1]->GetNbinsX();
    Double_t integral= hSignal1[n-1]->Integral(1,nbins);// first bin is always =1;
    hSignal1[n-1]->Scale(1/integral);
    hSignal1[n-1]->SetMinimum(0.001);
    hSignal1[n-1]->GetYaxis()->CenterTitle(true);
    hSignal1[n-1]->GetXaxis()->CenterTitle(true);
    hSignal1[n-1]->SetTitleSize(0.045,"X");
    hSignal1[n-1]->SetTitleOffset(1.0,"X");
    hSignal1[n-1]->SetStats(false);
    hSignal1[n-1]->SetTitleOffset (1.0,"Y");
    hSignal1[n-1]->SetMarkerColor(kRed);
    hSignal1[n-1]->SetMarkerStyle(8);
    hSignal1[n-1]->SetMarkerSize(0.80);
    hSignal1[n-1]->Draw();
    hData1[6]->GetXaxis()->SetRangeUser(0.0,18.0);
    hData1[7]->GetXaxis()->SetRangeUser(0.0,18.0);
    hData1[9]->GetXaxis()->SetRangeUser(0.6,1.0);
    hData1[10]->GetXaxis()->SetRangeUser(0.7,1.0);
    hData1[11]->GetXaxis()->SetRangeUser(0.0,13.0);
    hData1[n-1]->SetMarkerColor(kBlue);
    hData1[n-1]->SetMarkerStyle(8);
    hData1[n-1]->SetMarkerSize(0.80);
    hData1[n-1]->SetStats(false);
    Int_t nbins=hData1[n-1]->GetNbinsX();
    Double_t integral= hData1[n-1]->Integral(1,nbins);// first bin is always =1;
    hData1[n-1]->Scale(1/integral);
    hData1[n-1]->Draw("same");
    if (n==7){
    leg = new TLegend(0.15,0.65,0.65,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    if (n==8){
    leg = new TLegend(0.15,0.65,0.65,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    if (n==9){
    leg = new TLegend(0.45,0.65,0.90,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    if (n==10){
    leg = new TLegend(0.12,0.65,0.62,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    if (n==11){
    leg = new TLegend(0.12,0.65,0.62,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    if (n==12){
    leg = new TLegend(0.45,0.65,0.90,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    }
    Comparison2->SaveAs(Form("DPlusTopoCuts/Topologicalcutsc%dforBin%d.png",canvasno,Bin));
    }
    
    if(canvasno==3){
    TCanvas *Comparison3=new TCanvas(Form("Comparison3_Bin%d",Bin)," Toplogical Cuts3 for MC and Bkg Data",2500,1200);
    Comparison3->SetMargin(0.01, 0.01 ,0.1,0.01);
    Comparison3->Divide(3,1);
    
    for (Int_t n=13; n<16; n++)
    { 
    Comparison3->cd(n-12);
    TPad *p3= Comparison3->cd(n-12);
    p3->SetLogy();
   //hSignal1[0]->SetMaximum(hSignal1[0]->GetMaximum()*1.50);
    hSignal1[12]->GetXaxis()->SetRangeUser(0.0,18.0);
    hSignal1[13]->GetXaxis()->SetRangeUser(0.0,0.9);
    Int_t nbins=hSignal1[n-1]->GetNbinsX();
    Double_t integral= hSignal1[n-1]->Integral(1,nbins);// first bin is always =1;
    hSignal1[n-1]->Scale(1/integral);
    hSignal1[n-1]->GetYaxis()->CenterTitle(true);
    hSignal1[n-1]->GetXaxis()->CenterTitle(true);
    hSignal1[n-1]->SetTitleSize(0.045,"X");
    hSignal1[n-1]->SetTitleOffset(1.0,"X");
    hSignal1[n-1]->SetStats(false);
    hSignal1[n-1]->SetTitleOffset (1.0,"Y");
    hSignal1[n-1]->SetMarkerColor(kRed);
    hSignal1[n-1]->SetMarkerStyle(8);
    hSignal1[n-1]->SetMarkerSize(0.80);
    hSignal1[n-1]->Draw();
    hData1[12]->GetXaxis()->SetRangeUser(0.0,18.0);
    hData1[12]->GetXaxis()->SetRangeUser(0.0,0.9);
    hData1[n-1]->SetMarkerColor(kBlue);
    hData1[n-1]->SetMarkerStyle(8);
    hData1[n-1]->SetMarkerSize(0.80);
    hData1[n-1]->SetStats(false);
    Int_t nbins=hData1[n-1]->GetNbinsX();
    Double_t integral= hData1[n-1]->Integral(1,nbins);// first bin is always =1;
    hData1[n-1]->Scale(1/integral);
    hData1[n-1]->Draw("same");
    leg = new TLegend(0.37,0.75,0.90,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal1[n-1],"True Dplus from MC");
    leg->AddEntry(hData1[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
    Comparison3->SaveAs(Form("DPlusTopoCuts/Topologicalcutsc%dforBin%d.png",canvasno,Bin));
    }
    if(canvasno==4){
    TCanvas *Comparison4=new TCanvas(Form("Comparison4_Bin%d",Bin)," Toplogical Cuts4 for MC and Bkg Data",2500,1200);
    Comparison4->Divide(2,2);
    for (Int_t n=16; n<20; n++)
    { 
    Comparison4->cd(n-15);
   // hSignal1[0]->SetMaximum(hSignal1[0]->GetMaximum()*1.50);
    hSignal[n-1]->GetYaxis()->CenterTitle(true);
    hSignal[n-1]->GetXaxis()->CenterTitle(true);
    hSignal[n-1]->SetTitleSize(0.045,"X");
    hSignal[n-1]->SetTitleOffset(1.0,"X");
    hSignal[n-1]->SetStats(false);
    hSignal[n-1]->SetTitleOffset (1.0,"Y");
    hSignal[n-1]->SetMarkerColor(kRed);
    hSignal[n-1]->SetMarkerStyle(8);
    hSignal[n-1]->SetMarkerSize(0.80);
    hSignal[n-1]->Draw();
    hData[n-1]->SetMarkerColor(kBlue);
    hData[n-1]->SetMarkerStyle(8);
    hData[n-1]->SetMarkerSize(0.80);
    hData[n-1]->SetStats(false);
    hData[n-1]->Draw("same");
    leg = new TLegend(0.6,0.65,0.9,0.9);
    leg->SetHeader(Form("[MC vs Background] pT_Bin%d", Bin));
    leg->AddEntry(hSignal[n-1],"True Dplus from MC");
    leg->AddEntry(hData[n-1],"Background from Data");
    leg->SetTextSize(0.04);
    leg->Draw();
    }
   //Comparison4->SaveAs(Form("DPlusTopoCuts/Topologicalcutsc%dforBin%d.png",canvasno,Bin));
    }
   }

////1D_pp_DplusCorr_______________________________________________________________________
void LoadFileNamesPPDMeson(Int_t canvasno, Int_t Bin){

    TString file1= Form("./MC/root/Dpluscutsc%dPass4%d_MC.root",canvasno,Bin);
    TString file2= Form("./SBJuly/DplusCuts/root/Dpluscutsc%dPass4%d.root",canvasno,Bin);
      
    filenames[0] = file1;
    filenames[1] =file2;
        
    
}


//1D_pp_DplusCorr_______________________________________________________________________
     TCanvas * GetCanvasBFD(Int_t i, TString canvasname = "corrMECorrected",Int_t canvasno, Int_t Bin){
    
     TString canvasname=Form("Dpluscutsc%d_%d",canvasno,Bin);
    //load the histogram with
    TString path = filenames[i];
    
    TFile * file = TFile::Open(path.Data(),"WRITE");
    TCanvas * c = (TCanvas*)file->Get(canvasname.Data()); // c->Draw();
    return c;
}
    

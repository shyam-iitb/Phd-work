//------New Macro for comparison for Pass4 old Eff vs Pass4 New Eff-------------


//using namespace std::
TString directory = "";
const Int_t nhistos=4; //pPb !! IMPORTANT to change -->9 for pp
TString *filenames = new TString[nhistos];
TString assocpT = "0.3GeV";
TString path;
void PlotEff(){
        gStyle->SetOptStat(0);
     //   gStyle->SetOptTitle(0);
        gStyle->SetTitleSize(0.06, "t");
        gStyle->SetTitleSize(0.05, "XY");
    DoAllPlotsin1Canvas("Dplus", assocpT);
    
}

//1D_pp_DplusCorr_______________________________________________________________________
void DoAllPlotsin1Canvas(TString particle ="Dplus",TString assocpT = "dot3"){
   // gStyle->SetPalette(1);
    LoadFileNamespPbDMeson(particle,assocpT);
    TCanvas ** Canvas = new TCanvas *[nhistos];
    TH2F *hDraw;
    TH1F *hSignal1[nhistos], *hratioLow[2], *hratioMid[2], *hratioHigh[2];
    TGraphAsymmErrors *grAS1[nhistos],*grAS2[nhistos],*grAS3[nhistos];
   
   for(Int_t k = 0; k<4; k++){
        Canvas[k]=GetCanvasBFD(k,"corrMECorrected");
        std::cout<<" The code is working"<<std::endl;
        hSignal1[k]=(TH1F*)Canvas[k]->FindObject("hdraw");
        hSignal1[k]->SetMarkerSize(.60);
        grAS3[k]=(TGraphAsymmErrors*)Canvas[k]->FindObject("gFPromptCombined");
    }
    
   
    
   TCanvas *Comparison=new TCanvas("Online Correlation","Online Correlation",2000,1200);
  // Comparison->SetMargin(1.0,0.01,0.01,0.01);
    Comparison->cd();
    
    grAS3[0]->GetYaxis()->SetRangeUser(0.91,0.97);
    grAS3[0]->SetMarkerSize(1.0);
    grAS3[0]->SetMarkerColor(kBlue);
    grAS3[0]->SetMarkerStyle(20);
    grAS3[0]->SetFillStyle(0);
    grAS3[0]->Draw("AP");
 
    hSignal1[0]->SetName("fprompt Nb + fc, Eloss range considered");
    hSignal1[0]->SetTitle("fprompt Nb + fc, Eloss range considered");
    hSignal1[0]->GetYaxis()->CenterTitle(true);
    hSignal1[0]->GetXaxis()->CenterTitle(true);
    hSignal1[0]->GetYaxis()->SetTitle("f_{Prompt}");
    hSignal1[0]->GetXaxis()->SetTitle("Pt (GeV/c)");
    hSignal1[0]->GetXaxis()->SetTitleSize(0.05);
    hSignal1[0]->GetYaxis()->SetTitleSize(0.05);
    hSignal1[0]->SetTitleOffset (1.0,"X");
    hSignal1[0]->SetTitleOffset (1.0,"Y");
    hSignal1[0]->SetStats(0);
    hSignal1[0]->Draw("PE1SAME");
    
   

    hSignal1[1]->SetStats(0);
    hSignal1[1]->Draw("PE1SAME");
    grAS3[1]->SetMarkerSize(1.0);
    grAS3[1]->SetMarkerColor(kRed);
    grAS3[1]->SetMarkerStyle(21);
    grAS3[1]->SetFillStyle(0);
    grAS3[1]->Draw("PE1SAME");

    hSignal1[2]->SetStats(0);
    hSignal1[2]->Draw("PE1SAME");
    grAS3[2]->SetMarkerSize(1.0);
    grAS3[2]->GetYaxis()->SetRangeUser(0.91,0.98);
    grAS3[2]->SetMarkerColor(kMagenta);
    grAS3[2]->SetMarkerStyle(22);
    grAS3[2]->SetFillStyle(0);
    grAS3[2]->Draw("PE1SAME");

    hSignal1[3]->SetStats(0);
    hSignal1[3]->Draw("PE1SAME");
    grAS3[3]->GetYaxis()->SetRangeUser(0.91,0.98);
    grAS3[3]->SetMarkerSize(1.0);
    grAS3[3]->SetMarkerColor(kGreen);
    grAS3[3]->SetMarkerStyle(34);
    grAS3[3]->SetFillStyle(0);
    grAS3[3]->Draw("PE1SAME");

    leg_hist1 = new TLegend(0.45, 0.65,0.65, 0.85);
    leg_hist1->SetTextSize(0.05);
    leg_hist1->SetBorderSize(0.0);
    leg_hist1->AddEntry(grAS3[0],"0-100 %","p");
    leg_hist1->AddEntry(grAS3[1],"0-20 %","p");
    leg_hist1->AddEntry(grAS3[2],"20-60 %","p");
    leg_hist1->AddEntry(grAS3[3],"60-100 %","p");
    leg_hist1->Draw();
   
    
}


////1D_pp_DplusCorr_______________________________________________________________________
void LoadFileNamespPbDMeson(TString Part ="Dplus",TString assocpT = "dot5"){
    
    
    if(Part == "Dplus"){
        
        if(assocpT == "0.3GeV"){
            cout << " -------------------> Adding Dplus-pp 7TeV 0.3  GeV/c!!! " <<endl;
            filenames[0] += "./NicePlotsfiles/fPrompt_0_100.root";
            filenames[1] += "./NicePlotsfiles/fPrompt_0_20.root";
            filenames[2] += "./NicePlotsfiles/fPrompt_20_60.root";
            filenames[3] += "./NicePlotsfiles/fPrompt_20_60.root";
                   
        }
            
            
        }
        
        }

//1D_pp_DplusCorr_______________________________________________________________________
TCanvas * GetCanvasBFD(Int_t i, TString canvasname = "corrMECorrected"){
    
    //load the histogram with
    TString path = filenames[i];
     if (assocpT == "0.3GeV") canvasname="c1";
     
    TFile * file = TFile::Open(path.Data(),"WRITE");
    TCanvas * c = (TCanvas*)file->Get(canvasname.Data());
    if(!c) std::cout<<"Canvas name not found !!!!!!!!!"<<std::endl;
    return c;
    
}










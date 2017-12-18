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
    TGraphAsymmErrors *grAS1[nhistos];
   
   for(Int_t k = 0; k<4; k++){
        Canvas[k]=GetCanvasBFD(k,"corrMECorrected");
        std::cout<<" The code is working"<<std::endl;
        grAS1[k]=(TGraphAsymmErrors*)gFPromptCombined;
    }
    
   
    
   TCanvas *Comparison=new TCanvas("Online Correlation","Online Correlation",2000,1200);
  // Comparison->SetMargin(1.0,0.01,0.01,0.01);
    Comparison->cd();
    
    grAS1[0]->GetYaxis()->SetRangeUser(0.91,0.97);
    grAS1[0]->SetMarkerSize(1.5);
    grAS1[0]->SetMarkerColor(kBlue);
    grAS1[0]->SetMarkerStyle(20);
    grAS1[0]->SetFillStyle(0);
    grAS1[0]->Draw("AP");

    
    grAS1[1]->SetMarkerSize(1.5);
    grAS1[1]->SetMarkerColor(kRed);
    grAS1[1]->SetMarkerStyle(21);
    grAS1[1]->SetFillStyle(0);
    grAS1[1]->Draw("PE1SAME");

    grAS1[2]->SetMarkerSize(1.5);
    grAS1[2]->GetYaxis()->SetRangeUser(0.91,0.98);
    grAS1[2]->SetMarkerColor(kMagenta);
    grAS1[2]->SetMarkerStyle(22);
    grAS1[2]->SetFillStyle(0);
    grAS1[2]->Draw("PE1SAME");

    grAS1[3]->GetYaxis()->SetRangeUser(0.91,0.98);
    grAS1[3]->SetMarkerSize(1.5);
    grAS1[3]->SetMarkerColor(kGreen);
    grAS1[3]->SetMarkerStyle(34);
    grAS1[3]->SetFillStyle(0);
    grAS1[3]->Draw("PE1SAME");

    leg_hist1 = new TLegend(0.45, 0.65,0.65, 0.85);
    leg_hist1->SetTextSize(0.05);
    leg_hist1->SetBorderSize(0.0);
    leg_hist1->AddEntry(grAS1[0],"0-100 %","p");
    leg_hist1->AddEntry(grAS1[1],"0-20 %","p");
    leg_hist1->AddEntry(grAS1[2],"20-60 %","p");
    leg_hist1->AddEntry(grAS1[3],"60-100 %","p");
    leg_hist1->Draw();
   
    
}


////1D_pp_DplusCorr_______________________________________________________________________
void LoadFileNamespPbDMeson(TString Part ="Dplus",TString assocpT = "dot5"){
    
    
    if(Part == "Dplus"){
        
        if(assocpT == "0.3GeV"){
            cout << " -------------------> Adding Dplus-pp 7TeV 0.3  GeV/c!!! " <<endl;
            filenames[0] += "./FDIngradients_0_100/fPrompt_Final_Nb.root";
            filenames[1] += "./FDIngradients_0_20/fPrompt_Final_Nb.root";
            filenames[2] += "./FDIngradients_20_60/fPrompt_Final_Nb.root";
            filenames[3] += "./FDIngradients_60_100/fPrompt_Final_Nb.root";
                   
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










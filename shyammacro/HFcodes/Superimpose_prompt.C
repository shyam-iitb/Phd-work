// Macro for Superimposing fPrompt:Shyam Kumar

const Int_t nhistos=4; //pPb 
TString *filenames = new TString[nhistos];

void Superimpose_prompt(){
       gStyle->SetOptStat(0);
   //   gStyle->SetOptTitle(0);
       gStyle->SetTitleOffset(0.84, "XY");
       gStyle->SetTitleSize(0.06, "t");
       gStyle->SetTitleSize(0.05, "XY");
       DoAllPlotsin1Canvas();
    
}

//______________________Plot in Single canvas_________________________________________________
void DoAllPlotsin1Canvas(){
   
    LoadFileNamespPbDMeson();
    TGraphAsymmErrors *grAS1[nhistos];
   
    for(Int_t k = 0; k<4; k++){
       TString path = filenames[k];
       TFile * file = TFile::Open(path.Data(),"WRITE");
        grAS1[k]=(TGraphAsymmErrors*)gFPromptCombined;
    }
    
   
    
   TCanvas *Comparison=new TCanvas("Online Correlation","fPrompt",1500,800);
  Comparison->SetMargin(0.9,0.01,0.9,0.9);
   Comparison->cd();
    grAS1[0]->GetYaxis()->SetTitle("fPrompt");
    grAS1[0]->GetXaxis()->SetTitle("Pt (GeV/c)");
    grAS1[0]->GetXaxis()->CenterTitle();
    grAS1[0]->GetYaxis()->CenterTitle();
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
    Comparison->SaveAs("fPrompt.png");
   
    
}


////fPrompt Files with Path_______________________________________________________________________
void LoadFileNamespPbDMeson(){
            filenames[0] += "./FDIngradients_0_100/fPrompt_Final_Nb.root";
            filenames[1] += "./FDIngradients_0_20/fPrompt_Final_Nb.root";
            filenames[2] += "./FDIngradients_20_60/fPrompt_Final_Nb.root";
            filenames[3] += "./FDIngradients_60_100/fPrompt_Final_Nb.root";
         }


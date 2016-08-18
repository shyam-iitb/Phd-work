//------New Macro for comparison for Pass4 old Eff vs Pass4 New Eff-------------


//using namespace std::
TMultiGraph *mg = new TMultiGraph();
void doPlots(){
  DoAllPlotsin1Canvas();
    
   }

//1D_pp_DplusCorr_______________________________________________________________________
  void DoAllPlotsin1Canvas(){
    gStyle->SetOptStat(0);
   // gStyle->SetPalette(1);
         gStyle->SetTitleSize(0.06,"");
         gStyle->SetTitleSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"Y");
         gStyle->SetTitleSize(0.05,"Y");
         gStyle->SetOptTitle(0);
         gStyle->SetOptStat(111111);
    TFile *file1 = new TFile("FraSilicon.root","READ");
    TFile *file2 = new TFile("FraGe.root","READ");
    TFile *file3 = new TFile("FraDiamond.root","READ");
    TCanvas* comp = new TCanvas("comp","",2000,1500);
    comp->SetMargin(0.09, 0.02 ,0.1,0.03);
    TPad *p1 = comp->cd(1);
    p1->SetLogx();
    p1->SetLogy();
  //  comp->Clear();
    comp->cd();
    TGraph* graph1 = (TGraph*) file1 -> Get("gr");
    TGraph* graph2 = (TGraph*) file1 -> Get("gr1");
    TGraph* graph3 = (TGraph*) file2 -> Get("gr");
    TGraph* graph4 = (TGraph*) file2 -> Get("gr1");
    TGraph* graph5 = (TGraph*) file3 -> Get("gr");
    TGraph* graph6 = (TGraph*) file3 -> Get("gr1");
    graph1->SetMarkerStyle(22);
    graph1->SetMarkerSize (2.0);
    graph2->SetMarkerStyle(22);
    graph2->SetMarkerSize (2.0);
    graph3->SetMarkerStyle(21);
    graph3->SetMarkerSize (2.0);
    graph4->SetMarkerStyle(21);
    graph4->SetMarkerSize (2.0);
    graph5->SetMarkerStyle(20);
    graph5->SetMarkerSize (2.0);
    graph6->SetMarkerStyle(20);
    graph6->SetMarkerSize (2.0);
    mg->Add( graph1 );
    mg->Add( graph2 );
    mg->Add( graph3 );
    mg->Add( graph4 );
    mg->Add( graph5 );
    mg->Add( graph6 );
    mg->Draw("ACP");
    mg->SetName("gr2");
    mg->SetTitle("Frankel pairs in per particle");
    mg->GetXaxis()->SetTitle("Energy (GeV)");
    mg->GetXaxis()->CenterTitle(true);
    mg->GetYaxis()->SetTitle("Frankel Pairs");
    mg->GetYaxis()->CenterTitle(true);
    mg->GetYaxis()->SetTitleOffset(0.85);
    mg->GetXaxis()->SetTitleOffset(0.90);
    mg->GetYaxis()->SetRangeUser(1.0,10000);
    leg_hist = new TLegend(0.78, 0.8,0.98, 0.97);
    leg_hist->SetTextSize(0.05);
    leg_hist->SetHeader("Particles");
    leg_hist->AddEntry(graph1,"Proton","l");
    leg_hist->AddEntry(graph2,"Pion","l");
    leg_hist->Draw();
    leg_hist1 = new TLegend(0.45, 0.75,0.65, 0.97);
    leg_hist1->SetTextSize(0.05);
    leg_hist1->SetHeader("Material");
    leg_hist1->AddEntry(graph1,"Silicon","pl");
    leg_hist1->AddEntry(graph3,"Germanium","pl");
    leg_hist1->AddEntry(graph5,"Diamond","pl");
    leg_hist1->Draw();
    comp->Print("Frankelpairs.eps", "eps");




    /*  for(Int_t k = 0; k<6; k++){
       
        Canvas[k]=GetCanvasBFD(k,"corrMECorrected");
        hSignal1[k]=(TH2F*)Canvas[k]->FindObject(signal); //hME_Sign_PtInt_p%d for S+B region Pool by Pool
        hSignal1[k]->SetMarkerSize(.60);
    }
   
    
 //----------------------------------------------------------------------------------------------
    TCanvas *Ratio=new TCanvas("Ratio","Ratio",2000,400);
    Ratio->Divide(3,1);
    Ratio->cd(1);
    hratioLow[0]=(TH2F*)hSignal1[0]->Clone(Form("ratioLow_%i", 0));
    hratioLow[0]->SetName(Form("[Side Bands] Pass4 Split10/Split20 ME Ratio Pool %d (D^{+})LowpT - (h)>%s",Pool,assocpT.Data()));
    hratioLow[0]->SetTitle(Form("[S+B] Pass4 Split10/Split20 ME Ratio Pool %d  (D^{+})LowpT - (h)>%s",Pool,assocpT.Data()));
   // hratioLow[0]->GetZaxis()->SetRangeUser(0.9,1.1);
    //hratioLow[0]->GetZaxis()->SetTitle("#frac{1}{N^{trig}} #frac{SE}{ME}");
    //hratioLow[0]->GetZaxis()->CenterTitle(true);
    hratioLow[0]->GetYaxis()->CenterTitle(true);
    hratioLow[0]->GetXaxis()->CenterTitle(true);
    hratioLow[0]->SetTitleOffset (1.5,"X");
    hratioLow[0]->SetTitleOffset (2.0,"Y");
    // hratioLow[0]->SetTitle("test");
   //  gStyle->SetTitleFont(132,"");
    //     cout << "default size = > " << hratioLow[0]->GetTitleSize() << endl;
    // gStyle->SetTitleFontSize(0.085);


   // hratioLow[0]->SetTitleSize(0.055);
    hratioLow[0]->Divide(hSignal1[1]);  ///ratio of two signals
    hratioLow[0]->SetMarkerColor(kBlue);
    hratioLow[0]->SetMarkerSize(0.90);
    hratioLow[0]->Draw("lego2Z");
    //leg1 = new TLegend(0.10,0.80,0.88,0.9);
    //leg1->SetHeader("Ratio: Pass4 Side Bands 5 Jan/14 Dec ");
    //leg1->AddEntry(hratioLow[0]," Pass4 Vs New Eff","");
    //leg1->Draw();
    
    Ratio->cd(2);
    hratioMid[0]=(TH2F*)hSignal1[2]->Clone(Form("ratioLow_%i", 0));
    hratioMid[0]->SetName(Form("[Side Bands] Pass4 Split10/Split20 ME Ratio Pool %d  (D^{+})MidpT - (h)>%s",Pool,assocpT.Data()));
    hratioMid[0]->SetTitle(Form("[S+B] Pass4 Split10/Split20 ME Ratio Pool %d  (D^{+})MidpT - (h)>%s",Pool,assocpT.Data()));
   // hratioMid[0]->GetZaxis()->SetRangeUser(0.9,3.5);
    hratioMid[0]->Divide(hSignal1[3]);  ///ratio of two signals
    //hratioMid[0]->GetZaxis()->SetTitle("#frac{1}{N^{trig}} #frac{SE}{ME}");
    //hratioMid[0]->GetZaxis()->CenterTitle(true);
    hratioMid[0]->GetYaxis()->CenterTitle(true);
    hratioMid[0]->GetXaxis()->CenterTitle(true);
    hratioMid[0]->SetTitleOffset (1.5,"X");
    hratioMid[0]->SetTitleOffset (2.0,"Y");
    hratioMid[0]->SetMarkerColor(kBlue);
    hratioMid[0]->SetMarkerSize(0.90); 
    hratioMid[0]->Draw("lego2Z");
    Ratio->cd(3);
    hratioHigh[0]=(TH2F*)hSignal1[4]->Clone(Form("ratioLow_%i", 0));
    hratioHigh[0]->SetName(Form("[Side Bands] Pass4 Split10/Split20 ME Ratio Pool %d  (D^{+})HighpT - (h)>%s",Pool,assocpT.Data()));
    hratioHigh[0]->SetTitle(Form("[S+B] Pass4 Split10/Split20 ME Ratio Pool %d  (D^{+})HighpT - (h)>%s",Pool,assocpT.Data()));
  //  hratioHigh[0]->GetZaxis()->SetRangeUser(0.9,1.1);
    hratioHigh[0]->Divide(hSignal1[5]);  ///ratio of two signals
    //hratioHigh[0]->GetZaxis()->SetTitle("#frac{1}{N^{trig}} #frac{SE}{ME}");
   // hratioHigh[0]->GetZaxis()->CenterTitle(true);
    hratioHigh[0]->GetYaxis()->CenterTitle(true);
    hratioHigh[0]->GetXaxis()->CenterTitle(true);
    hratioHigh[0]->SetTitleOffset (1.5,"X");
    hratioHigh[0]->SetTitleOffset (2.0,"Y");
    hratioHigh[0]->SetMarkerColor(kBlue);
    hratioHigh[0]->SetMarkerSize(0.90);
    hratioHigh[0]->Draw("lego2Z");
    Ratio->SaveAs(Form("BRatio_Pass4_NewVsOldEff_DPlusCorr_%s.png",assocpT.Data()));*/
   
    
}








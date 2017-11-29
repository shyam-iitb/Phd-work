


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
         gStyle->SetLabelSize(0.04,"X");
         gStyle->SetLabelSize(0.05,"Y");
         gStyle->SetTitleSize(0.05,"Y");
         gStyle->SetOptTitle(0);
         gStyle->SetOptStat(111111);
    TFile *file1 = new TFile("NIESilicon.root","READ");
    TFile *file2 = new TFile("NIEGe.root","READ");
    TFile *file3 = new TFile("NIEDiamond.root","READ");
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
    mg->GetXaxis()->SetTitle("Kinetic Energy (GeV)");
    mg->GetXaxis()->CenterTitle(true);
    mg->GetYaxis()->SetTitle("NIEL [KeV/cm^{3}]"); //NIEL [KeV/cm^{3}], DPA
    mg->GetYaxis()->CenterTitle(true);
    mg->GetYaxis()->SetTitleOffset(0.75);
    mg->GetXaxis()->SetTitleOffset(0.90);
    mg->GetYaxis()->SetRangeUser(4e-2,10.0);
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
    //comp->Print("DOS.eps", "eps");

   
    
}








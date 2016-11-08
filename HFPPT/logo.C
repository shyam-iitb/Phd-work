void logo()
{


  
  TCanvas *c6 = new TCanvas("c6", "S*#sigma",320,22,691,653);
  gStyle->SetOptStat(0);
  c6->Range(-0.3373713,-2.125,3.036341,9.125);
  c6->SetFillColor(0);
  c6->SetBorderMode(0);
  c6->SetBorderSize(2);
  c6->SetLogx();
  c6->SetFrameBorderMode(0);
  c6->SetFrameBorderMode(0);
     
  Float_t Y[4]={4.6,2.1,3.9,1.0  }; 
  Float_t X[4]={150.,26.,9.8,6.6};
  Float_t Yerr[4]={0.24,0.746,0.5809,1.29};
  Float_t Xerr[4]={0.0};
  
  TGraphErrors *hm3sta = new TGraphErrors(4,X,Y,Xerr,Yerr);
  gStyle -> SetCanvasBorderMode(0);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  
  TH2F *h2 = new TH2F("npart_ave","",1000,0.,1000.,900,-1.,8.);
  npart_ave->GetXaxis()->SetMoreLogLabels();
  npart_ave->GetXaxis()->SetNdivisions(-503);
  npart_ave->GetXaxis()->SetTitleOffset(1.1);
  npart_ave->GetYaxis()->CenterTitle(true);
  npart_ave->GetYaxis()->SetNdivisions(40603);
  
  h2->GetXaxis()->SetTitle("X-axis");
  h2->GetYaxis()->SetTitle("Y-axis");
  h2->GetXaxis()->SetTitleOffset(1.1);
  h2->GetYaxis()->SetTitleOffset(1.2);
  h2->Draw();
  
  hm3sta->SetMarkerStyle(25);
  hm3sta->SetMarkerColor(2);
  hm3sta->SetLineColor(6);
  hm3sta->SetMarkerSize(2.0);
  hm3sta->Draw("P");
   DrawLogo();
}

void DrawLogo(){
   
   TImage *img = TImage::Open("14939407_1200841999974739_4076278138872154125_o.jpg");
   
   if (!img) {
      printf("Could not create an image... exit\n");
      return;
   }
   TPad *l = new TPad("l","l",0.1,0.1,0.9,1.);
   //gPad->cd(0);
   l->Draw();
   l->cd();
   img->Draw();
}

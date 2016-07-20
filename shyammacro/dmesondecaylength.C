/* Macro for checking the decay length of D-meson at different momentum by putting its mean decay time from Pdg Booklet*/
// shyam Kumar

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void dmesondecaylength()
{

     
   //gStyle->SetOptStat("nemruoi");
   gStyle->SetTitleSize(.04,"S");
   gStyle->SetOptTitle(1);
   gStyle->SetTitleOffset(1.0,"X");gStyle->SetTitleOffset(.88,"Y");
   gStyle->SetTitleSize(.04,"X");gStyle->SetTitleSize(.04,"Y");
   gStyle->SetLabelSize(.035,"X");gStyle->SetLabelSize(.035,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------
 double c= 3* std::pow(10.,8.);
 double mt= 1040*std::pow(10.,-15.); // mean decay time
 double mass= 1.869; // rest mass in GeV/c^2
//TCanvas* can = new TCanvas("can","Radiation Length for start detector",0,0,100,100);
TCanvas *c1 = new TCanvas("c1", "c1",0,52,1191,692);
TH1D* h = new TH1D("hist","D-meson, D-meson decay length",24,0,24);
h->SetTitle("D^{+} meson decay length = c#tau#sqrt{(#gamma_{D^{+}}^{2}-1)};Momentum (GeV/c); Decay length (mm)");
 Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
 for (int p=1; p<=24; p++)
    {
 double E = p*p + mass*mass;
 E= std:: sqrt(E);

 double gamma = E/mass;
 double decaylength = c* std::sqrt(gamma*gamma -1)*mt*1000;
 std:: cout<<" Decay length=" <<decaylength<<std::endl;
   h->SetLineColor(ci);
   h->GetXaxis()->CenterTitle(true);
   h->GetYaxis()->CenterTitle(true);
   h->SetMarkerColor(2);
   h->SetMarkerStyle(20);
   h->SetBinContent(p,decaylength);
   h->Draw("E2-text");
    }   
// -----  Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------

}



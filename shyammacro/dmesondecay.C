/* Macro for checking the decay length of D-meson at different momentum by putting its mean decay time from Pdg Booklet*/
// shyam Kumar

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void dmesondecay()
{

     
   //gStyle->SetOptStat("nemruoi");
   gStyle->SetOptTitle(0);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
   gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);

// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------
 double c= 3* std::pow(10.,8.);
 double mt= 1040*std::pow(10.,-15.); // mean decay time
 double mass= 1.869; // rest mass in GeV/c^2
//TCanvas* can = new TCanvas("can","Radiation Length for start detector",0,0,100,100);
TCanvas *c1 = new TCanvas("c1", "c1",0,52,1191,692);
TH2D* h = new TH2D("hist","D-meson, D-meson decay length",100,0,11,100,0,2);
h->SetTitle("Decay length of D-meson vs Momentum;momentum (GeV/c); decaylength (mm)");
 Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
 for (int p=1; p<=10; p++)
    {
 double E = p*p + mass*mass;
 E= std:: sqrt(E);

 double gamma = E/mass;
 double decaylength = c* std::sqrt(gamma*gamma -1)*mt*1000;
 std:: cout<<" Decay length=" <<decaylength<<std::endl;
   h->SetLineColor(ci);
   h->SetMarkerColor(2);
   h->SetMarkerStyle(20);
  h->Fill(p,decaylength);
  h-> DrawCopy();
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



//-- The Macro can be used for checking momentum up to which Particles can be identified by FToF
//---------- At a particular momentum for n sigma separation (time difference) delT>=n*sigma_t, where sigma_t is the required time resolution of detector, I have used sigma_t =100 ps for checking separation of different particles
//----The macro can also be used to check the separation for Stof and Btof, just put the most probabale tracklength by Shyam Kumar
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void EbyPratio()
	{
//------------------Style format---------------------------------
//gStyle->SetOptStat("nemruoi");
   gStyle->SetOptTitle(1);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
   gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);

// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1", "c1",2000,1200);
  c1->SetMargin(0.90,0.02,0.9,0.1);
                 c1->SetGrid();
                Double_t c= 3.0e+8; //speed of light 

	       // All particle masses are in MeV/c^2
	       
	        Double_t mel = 0.51099891; // Mass of electron and positron
	       
	        Double_t mmu = 105.6583715;   // Mass of muons
	        
	        Double_t mpi = 139.57018;   // mass of charged pions
	        
	        Double_t mk = 493.667;   // mass of charged kaons
	        
	        Double_t mp = 938.272046;  // mass of protons and antiprotons
	        Double_t Eel=0.,Emu=0.,Epi=0.,Ek=0.,Ep=0.;
	        Double_t E2=0.;
	        Int_t ci;   // for color index setting
	        ci = TColor::GetColor("#000099");
	        std::vector<Double_t> x,y1,y2,y3,y4,y5; 
         
 //------------------Proton-pion Separation by Forward Time of flight------------------------
              for (Double_t p=100; p<=10000; p=p+5)
                 {
                  Double_t Eel = p*p + mel*mel; // 
                  Double_t Emu = p*p + mmu*mmu;
                  Double_t Epi = p*p + mpi*mpi;
                  Double_t Ek =  p*p + mk*mk;
                  Double_t Ep =  p*p + mp*mp;
                  Eel= std::sqrt(Eel);
                  Emu= std::sqrt(Emu);
                  Epi= std::sqrt(Epi);
                  Ek= std::sqrt(Ek);
                  Ep= std::sqrt(Ep);
                  x.push_back(p*0.001);
                  y1.push_back(Eel/p);
                  y2.push_back(Emu/p);
                  y3.push_back(Epi/p);
                  y4.push_back(Ek/p);
                  y5.push_back(Ep/p);
               }   
             const Int_t n=x.size();
	     Double_t a[n],b1[n],b2[n],b3[n],b4[n],b5[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b1[i]=y1[i];
	     b2[i]=y2[i];
	     b3[i]=y3[i];
	     b4[i]=y4[i];
	     b5[i]=y5[i];
	     }    
           gr = new TGraph(n,a,b1);
           gr->SetLineColor(2);
           gr->SetLineWidth(2);
           gr->SetMarkerColor(2);
           gr->SetMarkerStyle(6);
           gr->SetTitle("E/P ratio for Particles as a function of Momentum");
           gr->GetXaxis()->SetTitle("Momentum (GeV/c)");
           gr->GetXaxis()->CenterTitle(true);
           gr->GetYaxis()->SetTitle("E/P ratio");
           gr->GetYaxis()->CenterTitle(true);
           gr->GetYaxis()->SetRangeUser(0.8,2.0);
           gr->GetXaxis()->SetRangeUser(0.0,10.0);
           gr->Draw("ACP"); 
           gr1 = new TGraph(n,a,b2);
           gr1->SetLineColor(3);
           gr1->SetLineWidth(2);
           gr1->SetMarkerColor(3);
           gr1->SetMarkerStyle(6);
           gr1->Draw("same");
           gr2 = new TGraph(n,a,b3);
           gr2->SetLineColor(4);
           gr2->SetLineWidth(2);
           gr2->SetMarkerColor(4);
           gr2->SetMarkerStyle(6);
           gr2->Draw("same"); 
           gr3 = new TGraph(n,a,b4);
           gr3->SetLineColor(6);
           gr3->SetLineWidth(2);
           gr3->SetMarkerColor(6);
           gr3->SetMarkerStyle(6);
           gr3->Draw("same"); 
           gr4 = new TGraph(n,a,b5);
           gr4->SetLineColor(kYellow);
           gr4->SetLineWidth(2);
           gr4->SetMarkerColor(kYellow);
           gr4->SetMarkerStyle(6);
           gr4->Draw("same"); 
           
       //--------------Legend Draw----------------------
          leg_hist = new TLegend(0.5,0.5,0.75,0.90);
          leg_hist->SetHeader("E/P of Particles");
          leg_hist->SetTextSize(0.05);
          leg_hist->AddEntry(gr,"Electron","l"); 
          leg_hist->AddEntry(gr1,"Muon","l");
          leg_hist->AddEntry(gr2,"Pion","l");
          leg_hist->AddEntry(gr3,"Kaon","l");
          leg_hist->AddEntry(gr4,"Proton","l");
          leg_hist->Draw();
         	        
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

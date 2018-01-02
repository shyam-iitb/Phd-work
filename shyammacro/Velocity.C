//-- The Macro can be used for checking momentum up to which Particles can be identified by CherenKov Pid
//Author: Shyam Kumar
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void Velocity()
	{
//------------------Style format---------------------------------
//gStyle->SetOptStat("nemruoi");
         gStyle->SetOptStat(0);
   // gStyle->SetPalette(1);
         gStyle->SetTitleSize(0.06,"");
         gStyle->SetTitleSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"Y");
         gStyle->SetTitleSize(0.05,"Y");
         gStyle->SetTitleOffset(0.88,"Y");
         gStyle->SetOptTitle(0);
         gStyle->SetOptStat(111111);

// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------
	TCanvas *c1 = new TCanvas("c1", "c1",2000,1500);
	c1->SetMargin(0.09, 0.02 ,0.1,0.06);
              
               Double_t c= 3.0e8; //speed of light 

	       // All particle masses are in GeV/c^2
	       
	        Double_t mel = 0.00051099891; // Mass of electron and positron
	       
	        Double_t mmu = 0.1056583715;   // Mass of muons
	        
	        Double_t mpi = 0.13957018;   // mass of charged pions
	        
	        Double_t mk = 0.493667;   // mass of charged kaons
	        
	        Double_t mp = 0.938272046;  // mass of protons and antiproton
	        Double_t E=0.;
	        Int_t ci;   // for color index setting
	        ci = TColor::GetColor("#000099");
	        
	       std::vector<Double_t> x1,y1,y2,y3,y4,y5;
	         
	        for (Double_t p=0.2; p<=5; p=p+0.05) {  
	         
	          x1.push_back(p);    
               
         //-------------Electron--------------------------
                 Double_t E = p*p + mel*mel;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mel/E)*(mel/E));
                  Double_t v=x; 
                  y1.push_back(v); 
         //-------------Muon--------------------------
                 Double_t E = p*p + mmu*mmu;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mmu/E)*(mmu/E));
                  Double_t v=x; 
                  y2.push_back(v); 
           //------------------Pion------------------------
                  Double_t E = p*p + mpi*mpi;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mpi/E)*(mpi/E));
                  Double_t v=x; 
                  y3.push_back(v);
           //-------------Kaon--------------------------
                 Double_t E = p*p + mk*mk;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mk/E)*(mk/E));
                  Double_t v=x; 
                  y4.push_back(v);
           //-------------Proton--------------------------
                 Double_t E = p*p + mp*mp;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mp/E)*(mp/E));
                  Double_t v=x; 
                  y5.push_back(v);
            }
          const Int_t n=x1.size();
          Double_t a[n],b[n],c[n],d[n],e[n],f[n];
          
        //======Electron====================== 
          for (Int_t i=0; i<n; i++){
           
             a[i]=x1[i];
             b[i]=y1[i];
         }
           
            gr1 = new TGraph(n,a,b);
            gr1->SetLineColor(kRed);
            gr1->SetLineWidth(1.0);
            gr1->SetMarkerColor(kRed);
            gr1->SetMarkerSize(0);
            gr1->SetMarkerStyle(1);
          //  gr1->SetTitle("Separation by Energy loss in Germanium for different particles");
            gr1->GetXaxis()->SetTitle("Momentum (GeV/c)");
            gr1->GetXaxis()->CenterTitle(true);
            gr1->GetYaxis()->SetTitle("#beta");
            gr1->GetYaxis()->SetRangeUser(0.0,1.1);
            gr1->GetXaxis()->SetRangeUser(0.0,5.0);
            gr1->GetYaxis()->CenterTitle(true);
            gr1->Draw("ACP"); 
        //======Muon====================== 
          for (Int_t i=0; i<n; i++){
           
             a[i]=x1[i];
             b[i]=y2[i];
           }
            gr2 = new TGraph(n,a,b);
            gr2->SetLineColor(kBlack);
            gr2->SetLineWidth(1);
            gr2->SetMarkerColor(kBlack);
            gr2->SetMarkerStyle(1);
            gr2->Draw("same"); 
            
       //======Muon====================== 
          for (Int_t i=0; i<n; i++){
           
             a[i]=x1[i];
             b[i]=y3[i];
           }
            gr3 = new TGraph(n,a,b);
            gr3->SetLineColor(kBlue);
            gr3->SetLineWidth(1);
            gr3->SetMarkerColor(kBlue);
            gr3->SetMarkerSize(0);
            gr3->SetMarkerStyle(1);
            gr3->Draw("same"); 
            
            
     //======Pion====================== 
          for (Int_t i=0; i<n; i++){
           
             a[i]=x1[i];
             b[i]=y4[i];
           }
            gr4 = new TGraph(n,a,b);
            gr4->SetLineColor(kMagenta);
            gr4->SetLineWidth(1);
            gr4->SetMarkerColor(kMagenta);
            gr4->SetMarkerStyle(1);
            gr4->Draw("same"); 
     //======Kaon====================== 
          for (Int_t i=0; i<n; i++){
           
             a[i]=x1[i];
             b[i]=y5[i];
           }
            gr5 = new TGraph(n,a,b);
            gr5->SetLineColor(kGreen);
            gr5->SetLineWidth(1);
            gr5->SetMarkerColor(kGreen);
            gr5->SetMarkerStyle(1);
            gr5->Draw("same"); 
         
          leg_hist = new TLegend(0.8,0.4,0.95,0.75);
          leg_hist->SetHeader("Particles");
          leg_hist->AddEntry(gr1,"Electron","l");
          leg_hist->AddEntry(gr2,"Muon","l");
          leg_hist->AddEntry(gr3,"Pion","l");
          leg_hist->AddEntry(gr4,"Kaon","l");
          leg_hist->AddEntry(gr5,"Proton","l");
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
	        

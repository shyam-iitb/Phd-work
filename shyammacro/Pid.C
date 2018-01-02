//-- The Macro can be used for checking momentum up to which Particles can be identified by CherenKov Pid
//Author: Shyam Kumar
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void Pid()
	{
//------------------Style format---------------------------------
//gStyle->SetOptStat("nemruoi");
   gStyle->SetOptTitle(1);
   gStyle->SetOptStat(0);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
   gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
   gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
   gStyle->SetHistLineWidth(2);
   gStyle->SetOptFit(1);

// -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1", "c1",0,52,1191,692);
TH2D* h1 = new TH2D("hist","Velocity of Particles",100,0,12.0,2000,2.2,3.05);
h1->SetTitle("Velocity of Particles vs Momentum;momentum (GeV/c); Velocity*10^{8} (m/sec)");
TH2D* h2 = new TH2D("hist1","Time resolution of Ftof",100,0,12.0,2000,2.2,3.05);
TH2D* h3 = new TH2D("hist2","Time resolution of Ftof",100,0,12.0,2000,2.2,3.05);
TH2D* h4 = new TH2D("hist3","Time resolution of Ftof",100,0,12.0,2000,2.2,3.05);
TH2D* h5 = new TH2D("hist4","Time resolution of Ftof",100,0,12.0,2000,2.2,3.05);

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
	        
	   
	         
	        for (Double_t p=1; p<=12; p=p+0.05)
   {      
         //-------------Electron--------------------------
                 Double_t E = p*p + mel*mel;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mel/E)*(mel/E));
                  Double_t v=c*x; 
                  Double_t v=v/1.0e8;
                  h1->SetMarkerColor(2); //Red
         	  h1->SetMarkerStyle(7);
                  h1->Fill(p,v);
                  h1-> Draw("C"); 
         //-------------Muon--------------------------
                 Double_t E = p*p + mmu*mmu;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mmu/E)*(mmu/E));
                  Double_t v=c*x; 
                  Double_t v=v/1.0e8;
                  h2->SetMarkerColor(3); //Red
         	  h2->SetMarkerStyle(7);
                  h2->Fill(p,v);
                  h2-> Draw("same");    
           //------------------Pion------------------------
                  Double_t E = p*p + mpi*mpi;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mpi/E)*(mpi/E));
                  Double_t v=c*x; 
                  Double_t v=v/1.0e8;
                  h3->SetMarkerColor(4); //Red
         	  h3->SetMarkerStyle(7);
                  h3->Fill(p,v);
                  h3-> Draw("same");
           //-------------Kaon--------------------------
                 Double_t E = p*p + mk*mk;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mk/E)*(mk/E));
                  Double_t v=c*x; 
                  Double_t v=v/1.0e8;
                  h4->SetMarkerColor(5); //Red
         	  h4->SetMarkerStyle(7);
                  h4->Fill(p,v);
                  h4-> Draw("same");
           //-------------Proton--------------------------
                 Double_t E = p*p + mp*mp;
                  E= std:: sqrt(E);
                  Double_t x= std::sqrt(1-(mp/E)*(mp/E));
                  Double_t v=c*x; 
                  Double_t v=v/1.0e8;
                  h5->SetMarkerColor(6); //Red
         	  h5->SetMarkerStyle(7);
                  h5->Fill(p,v);
                  h5-> Draw("same");
                 
                  
                  
              
                            
                 }
              h1->SetLineColor(2);  // green
              h2->SetLineColor(3);  // blue  
              h3->SetLineColor(4);  // blue  
              h4->SetLineColor(5);  // blue 
              h5->SetLineColor(6);  // blue  
              leg_hist = new TLegend(0.5,0.6,0.75,0.75);
              leg_hist->SetHeader("Particles");
              leg_hist->AddEntry(h1,"Electron","l");
              leg_hist->AddEntry(h2,"Muon","l");
              leg_hist->AddEntry(h3,"Pion","l");
              leg_hist->AddEntry(h4,"Kaon","l");
              leg_hist->AddEntry(h5,"Proton","l");
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
	        

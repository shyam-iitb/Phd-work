//-- The Macro can be used for checking momentum up to which Particles can be identified by FToF
//---------- At a particular momentum for n sigma separation (time difference) delT>=n*sigma_t, where sigma_t is the required time resolution of detector, I have used sigma_t =100 ps for checking separation of different particles
//----The macro can also be used to check the separation for Stof and Btof, just put the most probabale tracklength by Shyam Kumar
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void separation_sigma()
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
  TCanvas *c1 = new TCanvas("c1", "c1",0,52,1191,692);
TH2D* h1 = new TH2D("hist","Separation for the Particles hitting Ftof for 100 ps time resolution",100,2.0,7.0,100,0,10);
h1->SetTitle("Separation for the Particles hitting Ftof vs Momentum for 100 ps time resolution;momentum (GeV/c); Separation (sigma)");
TH2D* h2 = new TH2D("hist","Time resolution of Ftof",100,2.0,7.0,100,0,10);
TH2D* h3 = new TH2D("hist","Time resolution of Ftof",100,2.0,7.0,100,0,10);
TH2D* h4 = new TH2D("hist","Time resolution of Ftof",100,2.0,7.0,100,0,10);
TH2D* h5 = new TH2D("hist","Time resolution of Ftof",100,2.0,7.0,100,0,10);

                double c= 3* std::pow(10.,8.); //speed of light 

	       // All particle masses are in MeV/c^2
	       
	        Double_t mel = 0.51099891; // Mass of electron and positron
	       
	        Double_t mmu = 105.6583715;   // Mass of muons
	        
	        Double_t mpi = 139.57018;   // mass of charged pions
	        
	        Double_t mk = 493.667;   // mass of charged kaons
	        
	        Double_t mp = 938.272046;  // mass of protons and antiprotons
	        Double_t delT=0.;
	        Double_t E1=0.;
	        Double_t E2=0.;
	        Int_t ci;   // for color index setting
	        ci = TColor::GetColor("#000099");
	        
	        //-------------Most probable tracklength for the particle for Forward time of flight----------------------
	         Double_t L= 7.8; // distance in m
	         
	        for (Double_t p=50; p<=7000; p=p+10)
   {           
           //------------------Pion-Kaon Separation by Forward Time of flight------------------------
                  Double_t E1 = p*p + mk*mk; // E1= E1^2/c^2
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mpi*mpi;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  //std::cout<<"Time difference="<<delT<<std::endl;
                  h1->SetMarkerColor(2); //Red
         	  h1->SetMarkerStyle(7);
                  h1->Fill(p*0.001,delT);
                  h1-> Draw("C");
                 // h->Fit("pol6");
                 //------------------Electron-Muon Separation by Forward Time of flight------------------------
                /*  Double_t E1 = p*p + mmu*mmu;
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mel*mel;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  //std::cout<<"Time difference="<<delT<<std::endl;
                  h2->SetMarkerColor(3); //Green
         	  h2->SetMarkerStyle(7);
                  h2->Fill(p*0.001,delT);
                  h2-> Draw("same");
                 // h->Fit("pol6");*/
                 //------------------Proton-pion Separation by Forward Time of flight------------------------
                  Double_t E1 = p*p + mp*mp;
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mpi*mpi;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  delT= delT/0.1; 
                  //std::cout<<"Time difference="<<delT<<std::endl;
                  h3->SetMarkerColor(4); //Blue
         	  h3->SetMarkerStyle(7);
                  h3->Fill(p*0.001,delT);
                  h3-> Draw("same");
                   //------------------Kaon-Muon Separation by Forward Time of flight------------------------
                 /* Double_t E1 = p*p + mk*mk;
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mmu*mmu;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  //std::cout<<"Time difference="<<delT<<std::endl;
                  h4->SetMarkerColor(5); // yellow
         	  h4->SetMarkerStyle(7);
                  h4->Fill(p*0.001,delT);
                  h4-> Draw("same");*/
                  //------------------Proton-kaon Separation by Forward Time of flight------------------------
                  Double_t E1 = p*p + mp*mp;
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mk*mk;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  delT= delT/0.1;
                  //std::cout<<"Time difference="<<delT<<std::endl;
                  h5->SetMarkerColor(6); //Pink
         	  h5->SetMarkerStyle(7);
                  h5->Fill(p*0.001,delT);
                  h5-> Draw("same");
               
              
                            
                 }
              h1->SetLineColor(2);  
              h3->SetLineColor(4);   
              h5->SetLineColor(6);   
              leg_hist = new TLegend(0.5,0.6,0.75,0.75);
              leg_hist->SetHeader("Particles");
              leg_hist->AddEntry(h1,"#pi/K","l");
              leg_hist->AddEntry(h3,"#pi/Proton","l");
              leg_hist->AddEntry(h5,"K/Proton","l");
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
	        

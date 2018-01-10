//-- The Macro can be used for checking momentum up to which Particles can be identified by FToF
//---------- At a particular momentum for n sigma separation (time difference) delT>=n*sigma_t, where sigma_t is the required time resolution of detector, I have used sigma_t =100 ps for checking separation of different particles
//----The macro can also be used to check the separation for Stof and Btof, just put the most probabale tracklength by Shyam Kumar
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
void separation_sigma1()
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
               //  c1->SetGrid();
                c1->SetMargin(0.09, 0.02 ,0.1,0.06);
                Double_t c= 3.0e+8; //speed of light 

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
	        std::vector<Double_t> x,y; 
	        //-------------Most probable tracklength for the particle for Forward time of flight----------------------
	         Double_t L= 3.7; // distance in m
                     for (Double_t p=1000; p<=10000; p=p+10)
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
                  std::cout<<"Delta T"<<delT<<std::endl;
                 delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  x.push_back(p*0.001);
                  y.push_back(delT);
              
          
              }
	     const Int_t n=x.size();
	     Double_t a[n], b[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b[i]=y[i];
	     }  
           gr = new TGraph(n,a,b);
           gr->SetLineColor(2);
           gr->SetLineWidth(1);
           gr->SetMarkerColor(2);
           gr->SetMarkerStyle(6);
           gr->SetTitle("Time difference of the Particles hitting Ftof");
           gr->GetXaxis()->SetTitle("Momentum (GeV/c)");
           gr->GetXaxis()->CenterTitle(true);
         // gr->GetXaxis()->SetRangeUser(0.,10.0);
           gr->GetYaxis()->SetTitle("Separation (#sigma)");
           gr->GetYaxis()->CenterTitle(true);
           gr->Draw("ACP"); 
           x.clear();
           y.clear();
 //------------------Proton-pion Separation by Forward Time of flight------------------------
              for (Double_t p=1000; p<=10000; p=p+10)
                             {
                  Double_t E1 = p*p + mp*mp; // E1= E1^2/c^2
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mpi*mpi;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  std::cout<<"Delta T"<<delT<<std::endl;
                  delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  x.push_back(p*0.001);
                  y.push_back(delT);
              
          
              }   
               const Int_t n=x.size();
	     Double_t a[n], b[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b[i]=y[i];
	     }    
           gr1 = new TGraph(n,a,b);
           gr1->SetLineColor(3);
           gr1->SetLineWidth(1);
           gr1->SetMarkerColor(3);
           gr1->SetMarkerStyle(6);
           gr1->Draw("same"); 
           x.clear();
           y.clear();
            //------------------Proton-Kaon Separation by Forward Time of flight------------------------
              for (Double_t p=1000; p<=10000; p=p+10)
                             {
                  Double_t E1 = p*p + mp*mp; // E1= E1^2/c^2
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mk*mk;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  std::cout<<"Delta T"<<delT<<std::endl;
                  delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  x.push_back(p*0.001);
                  y.push_back(delT);
              
          
              }   
               const Int_t n=x.size();
	     Double_t a[n], b[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b[i]=y[i];
	     }    
           gr2 = new TGraph(n,a,b);
           gr2->SetLineColor(4);
           gr2->SetLineWidth(1);
           gr2->SetMarkerColor(4);
           gr2->SetMarkerStyle(6);
           gr2->Draw("same"); 
           x.clear();
           y.clear();
           //------------------Electron-Muon Separation by Forward Time of flight------------------------
           for (Double_t p=1000; p<=10000; p=p+10)
                             {
                  Double_t E1 = p*p + mmu*mmu; // E1= E1^2/c^2
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mel*mel;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  std::cout<<"Delta T"<<delT<<std::endl;
                  delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  x.push_back(p*0.001);
                  y.push_back(delT);
              
          
              }   
               const Int_t n=x.size();
	     Double_t a[n], b[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b[i]=y[i];
	     }    
           gr3 = new TGraph(n,a,b);
           gr3->SetLineColor(6);
           gr3->SetLineWidth(1);
           gr3->SetMarkerColor(6);
           gr3->SetMarkerStyle(6);
           gr3->Draw("same"); 
           x.clear();
           y.clear();
    /*  //------------------Kaon-Muon Separation by Forward Time of flight------------------------
       for (Double_t p=1000; p<=10000; p=p+10)
                             {
                  Double_t E1 = p*p + mk*mk; // E1= E1^2/c^2
                  E1= std:: sqrt(E1);
                  Double_t E2 = p*p + mel*mel;
                  E2= std:: sqrt(E2);
                  std:: cout<<"E1="<<E1<<std::endl;
                  std:: cout<<"E2="<<E2<<std::endl;
                  delT=L*(E1-E2)/(p*c);
                  delT*=1.0E9;
                  std::cout<<"Delta T"<<delT<<std::endl;
                  delT= delT/0.1; //separation 0.1 ns means 100 ps time resolution of detector
                  x.push_back(p*0.001);
                  y.push_back(delT);
              
          
              }   
               const Int_t n=x.size();
	     Double_t a[n], b[n];
	     for(Int_t i=0;i<n;i++){
	     a[i]=x[i];
	     b[i]=y[i];
	     }    
           gr4 = new TGraph(n,a,b);
           gr4->SetLineColor(6);
           gr4->SetLineWidth(1);
           gr4->SetMarkerColor(6);
           gr4->SetMarkerStyle(6);
           gr4->Draw("same"); 
           x.clear();
           y.clear();*/
           
       //--------------Legend Draw----------------------
          leg_hist = new TLegend(0.5,0.55,0.75,0.94);
           leg_hist->SetHeader("Particles");
           leg_hist->SetTextSize(0.05);
           leg_hist->AddEntry(gr,"#pi/K","l"); 
           leg_hist->AddEntry(gr1,"#pi/Proton","l");
           leg_hist->AddEntry(gr2,"K/Proton","l");
           leg_hist->AddEntry(gr3,"Muon/Electron","l");
            //leg_hist->AddEntry(gr3,"Kaon/Electron","l");
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
	        

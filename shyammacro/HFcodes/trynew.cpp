#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <TFile.h>
#include <TMultiGraph.h>
#include <TGraph.h>

//-------Macro for simple Plots: Shyam Kumar August 2016
// main(); It will run the program and will give the mean and sigma of distribuition
int trynew()
{
         gStyle->SetTitleSize(0.06,"");
         gStyle->SetTitleSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"X");
         gStyle->SetLabelSize(0.05,"Y");
         gStyle->SetTitleSize(0.05,"Y");
         gStyle->SetOptTitle(0);
         gStyle->SetOptStat(111111);
// -----   Timer   -------------------------------------
	  TStopwatch timer;
	  timer.Start();
	  
//-------------Setting-----------------------------------
        TMultiGraph * mg = new TMultiGraph("mg","mg");
        TCanvas *canvas = new TCanvas("canvas","Displacement Per Atom",0,0,2000,1500);
        TPad *p1 = canvas->cd(1);
        p1->SetLogy();
        canvas->SetMargin(0.09, 0.02 ,0.1,0.02);
        canvas->SetLogx();
        Bool_t Debug=kFALSE;
        TString Particle1="Proton"; //Pion,Neutron
        TString Particle2="Pion";
        TString material="Diamond"; //Select material==> Silicon,Ge,GaN,Diamond
        TString quantity="Frankel Pairs"; //Select==>DPA, NIEL [KeV/cm^{3}], DOSE [GeV/g], Frankel Pairs
        if((quantity=="Frankel Pairs"||quantity=="DPA") && material=="Diamond" ){
        TString filename="rad_dam_21_plot.dat";
        }
        else if(quantity=="NIEL [KeV/cm^{3}]" && material=="Diamond" ){
        TString filename="rad_dam_23_plot.dat";
        }
        else if(quantity=="DOSE [GeV/g]" && material=="Diamond" ){
        TString filename="rad_dam_24_plot.dat";
        }
        
        else if((quantity=="Frankel Pairs"||quantity=="DPA") && material=="Silicon" ){
        TString filename="damageSi_21_plot.dat";
        }

        else if(quantity=="NIEL [KeV/cm^{3}]" && material=="Silicon" ){
        TString filename="damageSi_22_plot.dat";
        }
        
        else if(quantity=="DOSE [GeV/g]" && material=="Silicon" ){
        TString filename="damageSi_23_plot.dat";
        }

        else if((quantity=="Frankel Pairs"||quantity=="DPA") && material=="Ge" ){
        TString filename="elossGe_21_plot.dat";
        }
        
        else if(quantity=="NIEL [KeV/cm^{3}]" && material=="Ge" ){
        TString filename="elossGe_22_plot.dat";
        }

        else if(quantity=="DOSE [GeV/g]" && material=="Ge" ){
        TString filename="elossGe_23_plot.dat";
        }
        
        else if((quantity=="Frankel Pairs"||quantity=="DPA") && material=="GaN" ){
        TString filename="eloss_21_plot.dat";
        }

        else if(quantity=="NIEL [KeV/cm^{3}]" && material=="GaN" ){
        TString filename="eloss_22_plot.dat";
        }
     
        else if(quantity=="DOSE [GeV/g]" && material=="GaN" ){
        TString filename="eloss_23_plot.dat";
        }

        TString path=Form("/home/shyam/Documents/damagediamond/damagemarch/June2016/%s",material.Data());
	std::vector<Double_t> a,b,c;
        a.push_back(0.01); a.push_back(0.1); a.push_back(1.0); a.push_back(5.0); a.push_back(10.0); a.push_back(100.0); a.push_back(1000.0);
        const Int_t n=a.size();
	Double_t l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14;
        std::string str1,str2,str3,str4,str5,str6,str7,str8,str9,str10,str11,str12,str13,str14;

//===========Path====================================================================================
	std::fstream fstrm1(path+Form("/%s/0.01/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm2(path+Form("/%s/0.1/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm3(path+Form("/%s/1.0/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm4(path+Form("/%s/5.0/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm5(path+Form("/%s/10.0/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm6(path+Form("/%s/100.0/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm7(path+Form("/%s/1000.0/%s",Particle1.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm8(path+Form("/%s/0.01/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm9(path+Form("/%s/0.1/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm10(path+Form("/%s/1.0/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm11(path+Form("/%s/5.0/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm12(path+Form("/%s/10.0/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm13(path+Form("/%s/100.0/%s",Particle2.Data(),filename.Data()),std::fstream::in);
	std::fstream fstrm14(path+Form("/%s/1000.0/%s",Particle2.Data(),filename.Data()),std::fstream::in);

//----------------1------------------------------------------------
	TH1F* hist1=new TH1F("DPA1 ","DPA1",100,0,1.0e6);
	while(getline(fstrm1,str1))
	{
	const char* c1=str1.c_str();
        sscanf(c1,"%*lf %*lf %lf %*f ",&(l1));
       //if(l3==0) continue;
      //  std::cout<<"Line:==>"<<l1<<std::endl;
      //  sscanf(c," %lf",&l3);
        hist1->Fill(l1);
	}
	Double_t integral1=hist1->Integral(1,100);
	Double_t mean1=hist1->GetMean();
	Double_t sigma1=hist1->GetStdDev();
//----------------2------------------------------------------------
	TH1F* hist2=new TH1F("DPA2 ","DPA2",100,0,1.0e6);
	while(getline(fstrm2,str2))
	{
	const char* c2=str2.c_str();
        sscanf(c2,"%*lf %*lf %lf %*f ",&(l2));
       //if(l3==0) continue;
        hist2->Fill(l2);
	}
	Double_t integral2=hist2->Integral(1,100);
	Double_t mean2=hist2->GetMean();
	Double_t sigma2=hist2->GetStdDev();
//----------------3------------------------------------------------
	TH1F* hist3=new TH1F("DPA3 ","DPA3",100,0,1.0e6);
	while(getline(fstrm3,str3))
	{
	const char* c3=str3.c_str();
        sscanf(c3,"%*lf %*lf %lf %*f ",&(l3));
       //if(l3==0) continue;
        hist3->Fill(l3);
	}
	Double_t integral3=hist3->Integral(1,100);
	Double_t mean3=hist3->GetMean();
	Double_t sigma3=hist3->GetStdDev();
//----------------4------------------------------------------------
	TH1F* hist4=new TH1F("DPA4 ","DPA4",100,0,1.0e6);
	while(getline(fstrm4,str4))
	{
	const char* c4=str4.c_str();
        sscanf(c4,"%*lf %*lf %lf %*f ",&(l4));
       //if(l3==0) continue;
        hist4->Fill(l4);
	}
	Double_t integral4=hist4->Integral(1,100);
	Double_t mean4=hist4->GetMean();
	Double_t sigma4=hist4->GetStdDev();
//----------------5------------------------------------------------
	TH1F* hist5=new TH1F("DPA5 ","DPA5",100,0,1.0e6);
	while(getline(fstrm5,str5))
	{
	const char* c5=str5.c_str();
        sscanf(c5,"%*lf %*lf %lf %*f ",&(l5));
       //if(l3==0) continue;
        hist5->Fill(l5);
	}
	Double_t integral5=hist5->Integral(1,100);
	Double_t mean5=hist5->GetMean();
	Double_t sigma5=hist5->GetStdDev();
//----------------6------------------------------------------------
	TH1F* hist6=new TH1F("DPA6 ","DPA6",100,0,1.0e6);
	while(getline(fstrm6,str6))
	{
	const char* c6=str6.c_str();
        sscanf(c6,"%*lf %*lf %lf %*f ",&(l6));
       //if(l3==0) continue;
        hist6->Fill(l6);
	}
	Double_t integral6=hist6->Integral(1,100);
	Double_t mean6=hist6->GetMean();
	Double_t sigma6=hist6->GetStdDev();
//----------------7------------------------------------------------
	TH1F* hist7=new TH1F("DPA7 ","DPA7",100,0,1.0e6);
	while(getline(fstrm7,str7))
	{
	const char* c7=str7.c_str();
        sscanf(c7,"%*lf %*lf %lf %*f ",&(l7));
       //if(l3==0) continue;
        hist7->Fill(l7);
	}
	Double_t integral7=hist7->Integral(1,100);
	Double_t mean7=hist7->GetMean();
	Double_t sigma7=hist7->GetStdDev();
//----------------8---------------------------------------------
	TH1F* hist8=new TH1F("DPA8 ","DPA8",100,0,1.0e6);
	while(getline(fstrm8,str8))
	{
	const char* c8=str8.c_str();
        sscanf(c8,"%*lf %*lf %lf %*f ",&(l8));
       //if(l3==0) continue;
        hist8->Fill(l8);
	}
	Double_t integral8=hist8->Integral(1,100);
	Double_t mean8=hist8->GetMean();
	Double_t sigma8=hist8->GetStdDev();
//----------------9------------------------------------------------
	TH1F* hist9=new TH1F("DPA9 ","DPA9",100,0,1.0e6);
	while(getline(fstrm9,str9))
	{
	const char* c9=str9.c_str();
        sscanf(c9,"%*lf %*lf %lf %*f ",&(l9));
       //if(l3==0) continue;
        hist9->Fill(l9);
	}
	Double_t integral9=hist9->Integral(1,100);
	Double_t mean9=hist9->GetMean();
	Double_t sigma9=hist9->GetStdDev();
//----------------10------------------------------------------------
	TH1F* hist10=new TH1F("DPA10","DPA10",100,0,1.0e6);
	while(getline(fstrm10,str10))
	{
	const char* c10=str10.c_str();
        sscanf(c10,"%*lf %*lf %lf %*f ",&(l10));
      // std::cout<<"Line10....="<<l10<<std::endl;
       //if(l3==0) continue;
        hist10->Fill(l10);
	}
	Double_t integral10=hist10->Integral(1,100);
	Double_t mean10=hist10->GetMean();
	Double_t sigma10=hist10->GetStdDev();
//----------------11------------------------------------------------
	TH1F* hist11=new TH1F("DPA11 ","DPA11",100,0,1.0e6);
	while(getline(fstrm11,str11))
	{
	const char* c11=str11.c_str();
        sscanf(c11,"%*lf %*lf %lf %*f ",&(l11));
       //if(l3==0) continue;
        hist11->Fill(l11);
	}
	Double_t integral11=hist11->Integral(1,100);
	Double_t mean11=hist11->GetMean();
	Double_t sigma11=hist11->GetStdDev();
//----------------12------------------------------------------------
	TH1F* hist12=new TH1F("DPA12 ","DPA12",100,0,1.0e6);
	while(getline(fstrm12,str12))
	{
	const char* c12=str12.c_str();
        sscanf(c12,"%*lf %*lf %lf %*f ",&(l12));
       //if(l3==0) continue;
        hist12->Fill(l12);
	}
	Double_t integral12=hist12->Integral(1,100);
	Double_t mean12=hist12->GetMean();
	Double_t sigma12=hist12->GetStdDev();
//----------------13------------------------------------------------
	TH1F* hist13=new TH1F("DPA13 ","DPA13",100,0,1.0e6);
	while(getline(fstrm13,str13))
	{
	const char* c13=str13.c_str();
        sscanf(c13,"%*lf %*lf %lf %*f ",&(l13));
       //if(l3==0) continue;
        hist13->Fill(l13);
	}
	Double_t integral13=hist13->Integral(1,100);
	Double_t mean13=hist13->GetMean();
	Double_t sigma13=hist13->GetStdDev();
//----------------14------------------------------------------------
	TH1F* hist14=new TH1F("DPA14 ","DPA14",100,0,1.0e6);
	while(getline(fstrm14,str14))
	{
	const char* c14=str14.c_str();
        sscanf(c14,"%*lf %*lf %lf %*f ",&(l14));
       //if(l3==0) continue;
        hist14->Fill(l14);
	}
	Double_t integral14=hist14->Integral(1,100);
	Double_t mean14=hist14->GetMean();
	Double_t sigma14=hist14->GetStdDev();
        b.push_back(mean1);b.push_back(mean2);b.push_back(mean3);b.push_back(mean4);b.push_back(mean5);b.push_back(mean6);b.push_back(mean7);
        c.push_back(mean8);c.push_back(mean9);c.push_back(mean10);c.push_back(mean11);c.push_back(mean12);c.push_back(mean13);c.push_back(mean14);
 
        Double_t x[7],y[7],y1[7];
//=========Graph and Plotting==============================
  
     
        for(Int_t m=0;m<n;m++)
        {
         x[m]=a[m];
     if(quantity=="NIEL [KeV/cm^{3}]"){
         y[m]=b[m]*1.0e6;
         y1[m]=c[m]*1.0e6;
     }
     else if (quantity=="Frankel Pairs" && material=="Diamond")
     {
         y[m]=b[m]*1.75990707851e23;
         y1[m]=c[m]*1.75990707851e23;
     }
     else if (quantity=="Frankel Pairs" && material=="Silicon")
     {
         y[m]=b[m]*4.9938819157e22;
         y1[m]=c[m]*4.9938819157e22;
     }
     else if (quantity=="Frankel Pairs" && material=="Ge")
     {
         y[m]=b[m]*4.41297319e22;
         y1[m]=c[m]*4.41297319e22;
     }
     else if (quantity=="Frankel Pairs" && material=="GaN")
     {
         y[m]=b[m]*4.3873212e22;
         y1[m]=c[m]*4.3873212e22;
     }
     else{
         y[m]=b[m];
         y1[m]=c[m];
    }

}
        TGraph * gr = new TGraph( n, x, y );
	gr->SetName("gr");
	gr->SetTitle("Proton");
	gr->SetDrawOption("ACP");
	gr->SetFillStyle(0);
        gr->SetLineColor(2);
	gr->SetLineWidth(2);
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(1);
	TGraph * gr1 = new TGraph( n, x, y1 );
	gr1->SetName("gr1");
	gr1->SetTitle("Pion");
	gr1->SetDrawOption("ACP");
	gr1->SetFillStyle(0);
	gr1->SetLineColor(4);
	gr1->SetLineWidth(2);
	gr1->SetMarkerColor(4);
	gr1->SetMarkerStyle(1);
	gr1->SetLineStyle(7);
	mg->Add( gr );
	mg->Add( gr1 );
	mg->Draw("ACP");
	mg->SetName("gr2");
        mg->SetTitle(Form("Frankel pairs in %s per particle",material.Data()));
        mg->SetTitle(Form("Frankel pairs in %s per particle",material.Data()));
        mg->GetXaxis()->SetTitle("Energy (GeV)");
	mg->GetXaxis()->CenterTitle(true);
	mg->GetYaxis()->SetTitle(Form("%s", quantity.Data()));
        mg->GetYaxis()->CenterTitle(true);
        mg->GetYaxis()->SetTitleOffset(0.90);
        mg->GetXaxis()->SetTitleOffset(0.90);
        if((material=="GaN" || material=="Ge") && quantity=="NIEL [KeV/cm^{3}]"){
        mg->GetYaxis()->SetRangeUser(0.0,120);
}
	canvas->BuildLegend (0.60, 0.60,0.90, 0.90,"Particles");
        quantity.Resize(3);
	canvas->Print(Form("%s%s.eps",quantity.Data(),material.Data()), "eps");	
	TFile * fileout = new TFile(Form("%s%s.root",quantity.Data(),material.Data()), "recreate");
        fileout->cd();
	gr->Write();
	gr1->Write();
	mg->Write();
	fileout->Close();
//===========Print all mean======================================
       if(Debug){
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean1<<std::endl;
        std::cout<<"Sigma="<<sigma1<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean2<<std::endl;
        std::cout<<"Sigma="<<sigma2<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean3<<std::endl;
        std::cout<<"Sigma="<<sigma3<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean4<<std::endl;
        std::cout<<"Sigma="<<sigma4<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean5<<std::endl;
        std::cout<<"Sigma="<<sigma5<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean6<<std::endl;
        std::cout<<"Sigma="<<sigma6<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean7<<std::endl;
        std::cout<<"Sigma="<<sigma7<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean8<<std::endl;
        std::cout<<"Sigma="<<sigma8<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean9<<std::endl;
        std::cout<<"Sigma="<<sigma9<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean10<<std::endl;
        std::cout<<"Sigma="<<sigma10<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean11<<std::endl;
        std::cout<<"Sigma="<<sigma11<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean12<<std::endl;
        std::cout<<"Sigma="<<sigma12<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean13<<std::endl;
        std::cout<<"Sigma="<<sigma13<<std::endl;
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	std::cout<<"Mean="<<mean14<<std::endl;
        std::cout<<"Sigma="<<sigma14<<std::endl;
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
        fstrm1.close();
        fstrm2.close();
        fstrm3.close();
        fstrm4.close();
        fstrm5.close();
        fstrm6.close();
        fstrm7.close();
        fstrm8.close();
        fstrm9.close();
        fstrm10.close();
        fstrm11.close();
        fstrm12.close();
        fstrm13.close();
        fstrm14.close();
        a.clear();
        b.clear();
        c.clear();

}






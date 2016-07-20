#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
// Run this macro on root 
// Type root -l
// .L try.cpp
// main(); It will run the program and will give the mean and sigma of distribuition
int try()
{
        gStyle->SetOptStat(111111);
	//std::vector<double> l1,l2,l3,l4;
	double l3;
	std::fstream fstrm("/home/shyam/Documents/damagediamond/damagemarch/June2016/Silicon/Proton/1.0/damageSi_21_plot.dat",std::fstream::in);
	//std::fstream fstrm("/home/shobhit/bolshoi/mhalo.dat",std::fstream::in);
	std::string str;
	TH1F* hist=new TH1F("DPA ","DPA",100,0,1.0e-17);
	while(getline(fstrm,str))
	{
	const char* c=str.c_str();
        sscanf(c,"%*lf %*lf %lf %*f ",&(l3));
       //if(l3==0) continue;
        std::cout<<"Line:==>"<<l3<<std::endl;
      //  sscanf(c," %lf",&l3);
        hist->Fill(l3);
	}
	Double_t integral=hist->Integral(1,100);
	Double_t mean=hist->GetMean();
	Double_t sigma=hist->GetStdDev();
	Std::cout<<"+++++++++++++Results++++++++++++"<<std::endl;
	//std::cout<<"Integral="<<mean<<std::endl;
	std::cout<<"Mean="<<mean<<std::endl;
        std::cout<<"Sigma="<<sigma<<std::endl;
	hist->Draw();
	fstrm.close();
}






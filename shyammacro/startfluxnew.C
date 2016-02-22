// This codes is for counting the tracks passing through the detector by using the MC point information of detector 
//Total flux of particles per unit area in one year (fluence)= (Totntracks*2*10^7)*365*24*3600*dutycycle/(Events*area) particles/cm^2
// Some times one track can create more than one MC point on the detector (if detector has more than one plane), I have taken care of that.
// Shyam Kumar
#include<iostream>
//#include "/home/shyam/pandaroot/start/PndStartPoint.h"

void startfluxnew()
{
	Int_t Events=0;
	Int_t l=0;
        Int_t p=0;
        Int_t temp,j,ntracks, Totntracks;
        Double_t flux,Evtyear;
        Double_t dutycycle=0.5; //50%
        Double_t eventrate=2*1E7; //2*10^7 /seconds
//----------------------------Reading the root file-------------------------------

	TFile* f = new TFile("sim_completestart70cm.root"); // the sim file you want to analyse
	TTree *t=(TTree *) f->Get("cbmsim") ;
	TClonesArray *start_array=new TClonesArray("PndStartPoint");
	t->SetBranchAddress("STARTPoint",&start_array);//Branch name

	Int_t nEntries =  t->GetEntriesFast();
Totntracks = 0;
	for (Int_t j=0; j< nEntries; j++)
	{
		std::vector<Int_t> a, b;	
		t->GetEntry(j);
		cout<<"Event="<<j<<endl;
                         Events++;
		//--------------------Start detector Entries--------------------
		for (Int_t k=0; k<start_array->GetEntriesFast(); k++)
		{
			PndStartPoint* startpoint = (PndStartPoint*)start_array->At(k);
			  
			//m++;
			a.push_back(startpoint->GetTrackID());
		}
	       
              //---------------Sorting the array of MC points on Detector for each event----------
                    Int_t n=a.size();
                ntracks = 0;
               for(Int_t i=0;i<n;i++)
                             for(Int_t p=0;p<n-i-1;p++){
                       
		                 if(a[p]>a[p+1])
		                  {
		                     temp=a[p];
		                     a[p]=a[p+1];
		                     a[p+1]=temp;
		                  }
		                                      }
	   //----------------------Sorted array of MC points-----------------
		          for(Int_t i=0;i<n;i++)
  	   std::cout<<"sorted Track ID for MC points="<<a[i]<<std::endl;
	   //-----------------------Matching Track ID for counting Tracks---------------------
                         if( n==0)  continue;

                       if (n >= 1) ntracks = 1;
                                Int_t k = 0;
				while (k < n-1) {
				if (a[k] != a[k+1])  ntracks++;
				k++;

				}
	       Totntracks = Totntracks + ntracks;
	     Std::cout<<"Total number of Tracks up to Event Nr:"<<Events<<" "<<Totntracks<<std::endl; 
                               a.clear();       
                   }
              //--------------------Total Number of events per year---------------------------------------------
                 Evtyear=eventrate*365.*24.*3600.*dutycycle;
             //---------------Tracks passing throgh the detector per unit area in one year----------------------  
                flux=Totntracks*eventrate*365.*24.*3600.*dutycycle/(Events*3.1416*165);    // Area =3.1416(13^2-2^2)cm^2 of lambda disk
             //---------------Printing values-----------------------------------------------   
     std::cout<<"Number of Events ="<<Events<<std::endl;  
     std::cout<<"Total Number of Events per Year ="<<Evtyear<<std::endl;
     std:: cout<<" Total number of tracks hitting START="<<Totntracks<<std::endl;
     std:: cout<<"The flux of particle passing through the detector per year (Fluence (Φ))="<<flux<<" "<<"Particles/cm²"<<std::endl;
          
	             
}

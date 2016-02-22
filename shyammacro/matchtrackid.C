///////////// code for checking the basic things of particles by shyam kumar
/*//cout<<"Entry number="<<j<<endl;
      t->GetEntry(j);
//For-----------------MC Points---------------------------------// using mc-array
//
//if(mcpoint->GetPdgCode()!=211) continue; 
*/

//----------------------------Matching Track Id of Entries by shyam kumar----------
#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TClonesArray.h"
//#include "/home/shyam/pandaroot/start/PndStartPoint.h"

void matchtrackid()
{
	Int_t m=0;
	Int_t l=0;
	Int_t q=0;

////////////////loading basic library
	//gROOT->LoadMacro("$VMCWORKDIR/gconfig/rootlogon.C");
	//rootlogon();

///////////////////////////////////////////////Reading the root file

	TFile* f = new TFile("sim_complete.root"); // the sim file you want to analyse
	TTree *t=(TTree *) f->Get("cbmsim") ;
	TClonesArray* mc_array=new TClonesArray("PndMCTrack");
	t->SetBranchAddress("MCTrack", &mc_array);
	TClonesArray *start_array=new TClonesArray("PndStartPoint");
	t->SetBranchAddress("STARTPoint",&start_array);//Branch names
	TClonesArray *ftof_array=new TClonesArray("PndFtofPoint");
	t->SetBranchAddress("FtofPoint",&ftof_array);//Branch names

	Int_t nEntries =  t->GetEntriesFast();
	for (Int_t j=0; j< nEntries; j++)
	{
		std::vector<Int_t> a, b;	
		t->GetEntry(j);
		cout<<"Event="<<j<<endl;
		//--------------------Start detector Entries--------------------
		for (Int_t k=0; k<start_array->GetEntriesFast(); k++)
		{
			PndStartPoint* startpoint = (PndStartPoint*)start_array->At(k);
			  
			m++;
			a.push_back(startpoint->GetTrackID());
		}
	//------------------------ Ftof Entries---------------------------      
		for (Int_t n=0; n<ftof_array->GetEntriesFast(); n++)
		{
			PndFtofPoint* ftofpoint = (PndFtofPoint*)ftof_array->At(n);
		                
			l++;
			b.push_back(ftofpoint->GetTrackID());
		}  
	 
	//-------------------Matching the Track ID-----
	
	        cout<<"The value of k="<<"\t"<<k<<endl;
	        cout<<"The value of n="<<"\t"<<n<<endl;          
		for (int startPoints = 0; startPoints < a.size(); startPoints++){
			std::cout << "Stardetector Track ID: " << startPoints << " : " << a[startPoints] << std::endl;
			for (int ftofPoints = 0; ftofPoints < b.size(); ftofPoints++){
				std::cout << "FToF Track ID: " << ftofPoints << " : "  << b[ftofPoints] << std::endl;
				if (a[startPoints] == b[ftofPoints]){
					std::cout << "Match!" << std::endl;				
					q++;
				}
			}
			std::cout << std::endl;
		}
	}
	cout<<" Total number of Events="<<j<< endl;
	cout<<" Total number of Points on start ="<<m<< endl; 
	cout<<" Total number of Points on Ftof ="<<l<< endl;

 	cout<<" Total number of Tracks with same Track ID= "<< q << endl;

}

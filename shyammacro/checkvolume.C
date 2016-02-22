///////////// code for checking the volume information of detector by shyam kumar

//----------------------------Matching Track Id of Entries by shyam kumar----------
#include "TGraphErrors.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TClonesArray.h"
#include<iostream>
#include <TGeoNode.h>
#include "TGeoVolume.h"
//#include "/home/shyam/pandaroot/start/PndStartPoint.h"

void checkvolume()
{
        int temp;
	Int_t m=0;
	Int_t l=0;
	Int_t q=0;
        Int_t n=0;
        Int_t p=0;


///////////////////////////////////////////////Reading the root file

	TFile* f = new TFile("../sim_complete.root"); // the sim file you want to analyse
	TTree *t=(TTree *) f->Get("cbmsim") ;
        TFile* f1 = new TFile("../simparams.root");	  
        f1->Get("FairGeoParSet");
	TClonesArray* mc_array=new TClonesArray("PndMCTrack");
	t->SetBranchAddress("MCTrack", &mc_array);
	TClonesArray *start_array=new TClonesArray("PndStartPoint");
	t->SetBranchAddress("STARTPoint",&start_array);//Branch names

	Int_t nEntries =  t->GetEntriesFast();
       // Int_t Entries = 2;
	for (Int_t j=0; j< nEntries; j++)
	{
		std::vector<Int_t> a, b;	
		t->GetEntry(j);
		cout<<"Event="<<j<<endl;
		//--------------------Start detector Entries--------------------
		for (Int_t k=0; k<start_array->GetEntriesFast(); k++)
		{
			PndStartPoint* startpoint = (PndStartPoint*)start_array->At(k);
                        Double_t xin= startpoint->GetX(); Double_t yin= startpoint->GetY(); Double_t zin= startpoint->GetZ();
                        std::cout<<"In Position="<<xin<<" "<<yin<<" "<<zin<<std::endl;
                        TGeoNode* node = gGeoManager->FindNode(xin,yin,zin);
                        if(!node) continue;
	                   node->cd();
	             TString volname = node->GetVolume()->GetName();
                      std::cout<<"Volume Name of Detector:"<<volname<<std::endl;
                        
		}
	              
                        
                                 
          }
         
	

}

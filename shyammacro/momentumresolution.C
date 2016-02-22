void momentumresolution()
{

  gStyle->SetOptTitle(0);
  gStyle->SetFillColor(0);
  gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
  gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
  gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
  gStyle->SetHistFillColor(0);
  gStyle->SetHistLineWidth(2);
  gStyle->SetOptFit(1);
  TFile *inFile = TFile::Open("pid_completeprotonFtofcut2500.root");
  cbmsim->AddFriend("cbmsim"," sim_completeproton.root");
  
  TCanvas* c1 = new TCanvas("Charged Candidate", "Charged Candidate", 100, 100, 1200, 800);
  

  TH1F *charg_mom = new TH1F("charg_mom","charg_mom",100,-0.2,0.2);
  charg_mom->GetXaxis()->SetTitle("(P_{MC} - P_{track}) / P_{MC}");
  cbmsim.Draw("(MCTrack.GetMomentum().Mag()[PidChargedCand.GetMcIndex()]-PidChargedCand.GetMomentum().Mag())/MCTrack.GetMomentum().Mag()[PidChargedCand.GetMcIndex()]>>charg_mom","PidChargedCand.GetMcIndex()!=-1","");
  /*TH1F *charg_mom = new TH1F("Tracklength","Tracklength",100,-10,50);
  charg_mom->GetXaxis()->SetTitle("(P_{MC} - P_{track}) / P_{MC}");
  cbmsim.Draw("(PidChargedCand.GetTofTrackLength()-FtofPoint.GetLength())/FtofPoint.GetLength()>>charg_mom(100,-10,10)");*/
 
 

}

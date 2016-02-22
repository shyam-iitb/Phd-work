{
   gStyle->SetOptTitle(0);
   gStyle->SetTitleOffset(.85,"X");gStyle->SetTitleOffset(.85,"Y");
  gStyle->SetTitleSize(.05,"X");gStyle->SetTitleSize(.05,"Y");
  gStyle->SetLabelSize(.05,"X");gStyle->SetLabelSize(.05,"Y");
  gStyle->SetHistLineWidth(2);
  gStyle->SetOptFit(1);
  TFile *inFile = TFile::Open("pid_complete.root");

  TCanvas* c1 = new TCanvas("PID", "PID", 100, 100, 800, 800);

  c1.Divide(2,1);
  c1.cd(1);
  cbmsim->Draw("PidChargedCand.GetTofBeta():PidChargedCand.GetMomentum().Mag()>>tof_pid(100,0,4.5,100,0,1.1)","PidChargedCand.GetTofIndex()>-1","colz");
  tof_pid->GetXaxis()->SetTitle("Momentum [GeV/c]");
  tof_pid->GetYaxis()->SetTitle("#beta");
c1.cd(2);
  cbmsim->Draw("PidChargedCand.GetTofM2()>>tof_pid1(100,-0.5,1.5)","PidChargedCand.GetTofIndex()>-1");
  tof_pid1->GetXaxis()->SetTitle("m_{0}^{2} [GeV^{2}/c^{4}]");
 /* cbmsim->Draw("PidChargedCand.GetTofM2():PidChargedCand.GetTofTrackLength()>>tof_pid(100,0,1000,100,-0.5,1)","PidChargedCand.GetTofIndex()>-1","colz");
  tof_pid->GetXaxis()->SetTitle("Tracklength (cm)");
  tof_pid->GetYaxis()->SetTitle("m_{0}^{2} [GeV^{2}/c^{4}]");*/
  c1.cd();
}

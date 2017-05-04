int isto(){

 FILE *leggi=fopen("Lista6.txt","r");

 char testo[250];
 TH1F *isto= new TH1F("isto","isto",500,0,0.0007);
 isto->GetXaxis()->SetTitle("[a.u.]");
 sprintf(testo,"Events/%.3f",isto->GetBinWidth(2));
 isto->GetYaxis()->SetTitle(testo);
 isto->GetYaxis()->SetTitleOffset(1.2);

 double a;
 
 while(!feof(leggi)){
   fscanf(leggi,"%lf",&a);
   isto->Fill(a);
 }
 
 fclose(leggi);

 TCanvas *c1 = new TCanvas("c1","c1",1600,800);
 c1->SetLogy(); 
 isto->Draw("pl");

 return;
}


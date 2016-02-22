
//--Macro for drawing Geometry from root file in pandaroot/geometry/ by shyam kumar
rootgeo()
{
  
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/rootlogon.C");
  rootlogon();
   TFile* file = new TFile("/home/shyam/pandaroot/geometry/gem_3Stations.root");//Put the root geometry file
   new TGeoManager("Geometry", "default geometry");
   gGeoManager->SetTopVolume(Gem); // set the top volume name by opening the root file in TBrowser AS for above geometry file top volume is Gem
   gGeoManager->SetVisLevel(4); // change it if required
   gGeoManager->GetTopVolume()->Draw("ogl");
  
}

  
  




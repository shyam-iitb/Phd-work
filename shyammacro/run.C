{
gSystem->SetIncludePath("-I. -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include -I$ALICE_ROOT/ANALYSIS/macros -I$ROOTSYS/include");
gROOT->LoadMacro("AliDhCorrelationExtractionoff.cxx++g");
gROOT->ProcessLine(".x ExtractOutputoff.C");
}

// $Id: StartLinkDef.h,v 1.0 Ralf Kliemt 08.Jan.2007 $

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
//data
 #pragma link C++ class PndSdsMCPoint+;
 //mc
#pragma link C++ class PndStartContFact+;
#pragma link C++ class PndStartDetector+;
#pragma link C++ class  PndStartPoint+;
//digi
#pragma link C++ class PndStartStripHitProducer+;
#pragma link C++ class PndStartDigiTask+;
#pragma link C++ class PndStartHitProducerIdeal+;
#pragma link C++ class PndStartNoiseProducer+;
#endif


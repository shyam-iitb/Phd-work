#ifndef PNDSTARTCONTFACT_H
#define PNDSTARTCONTFACT_H 1

#include "FairContFact.h"

class FairContainer;
//class FairParIo;

class PndStartContFact : public FairContFact {
public:
  PndStartContFact();
  ~PndStartContFact();
  FairParSet* createContainer(FairContainer* c);
  TList* GetDigiParNames() {return fDigiParNames;};
private:
  void setAllContainers();
  TList* fDigiParNames; //!
  ClassDef( PndStartContFact,3); // Factory for all START parameter containers
};

#endif  /* !STARTCONTFACT_H */

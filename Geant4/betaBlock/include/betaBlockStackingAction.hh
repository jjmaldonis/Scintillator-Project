

#ifndef betaBlockStackingAction_H
#define betaBlockStackingAction_H 1

#include "G4UserStackingAction.hh"

class betaBlockStackingAction : public G4UserStackingAction
{
  public:
    betaBlockStackingAction();
    virtual ~betaBlockStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:

};

#endif

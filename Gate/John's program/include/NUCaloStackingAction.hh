

#ifndef NUCaloStackingAction_H
#define NUCaloStackingAction_H 1

#include "G4UserStackingAction.hh"

class NUCaloStackingAction : public G4UserStackingAction
{
  public:
    NUCaloStackingAction();
    virtual ~NUCaloStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:

};

#endif

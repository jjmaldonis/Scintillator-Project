#include "NUCaloStackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"

#include "RootIO.hh"


static int gammaCounter = 0;


NUCaloStackingAction::NUCaloStackingAction()
{;}

NUCaloStackingAction::~NUCaloStackingAction()
{;}

G4ClassificationOfNewTrack
NUCaloStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

  return fUrgent;
}

void NUCaloStackingAction::NewStage()
{

}

void NUCaloStackingAction::PrepareNewEvent()
{ 
}

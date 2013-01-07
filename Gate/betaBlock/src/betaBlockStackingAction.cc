#include "betaBlockStackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"

#include "RootIO.hh"


static double energyCounter = 0;


betaBlockStackingAction::betaBlockStackingAction()
{;}

betaBlockStackingAction::~betaBlockStackingAction()
{;}

G4ClassificationOfNewTrack
betaBlockStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
	return fUrgent;
}

void betaBlockStackingAction::NewStage()
{

}

void betaBlockStackingAction::PrepareNewEvent()
{

}

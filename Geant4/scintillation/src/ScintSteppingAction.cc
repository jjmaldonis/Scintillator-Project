#include "ScintDetectorConstruction.hh"
#include "ScintEventAction.hh"
#include "ScintSteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

#include <iomanip>

////#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt)
:detector(det), eventaction(evt)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep/*, EventAction* evt, DetectorConstruction* det*/)
{
	G4StepPoint* pPreStepPoint = aStep->GetPreStepPoint();
	G4StepPoint* pPostStepPoint = aStep->GetPostStepPoint();
	G4VPhysicalVolume* thePrePV = pPreStepPoint->GetPhysicalVolume();
	G4VPhysicalVolume* thePostPV = pPostStepPoint->GetPhysicalVolume();

	G4VPhysicalVolume* theScintVol = detector->GetPlasticPV();
	G4VPhysicalVolume* thePMTVol = detector->GetPMTPV();
	
// 	eventaction->Photon();

// 	G4cout << thePrePV << " =? " << theScintVol << " and " << thePostPV << " =? " << thePMTVol << G4endl;
	
	if(thePrePV == theScintVol && thePostPV == thePMTVol)
	{
		eventaction->PhotonHit();
		/*if(pPreStepPoint->GetMomentumDirection() == pPostStepPoint->GetMomentumDirection())
			G4cout << pPreStepPoint->GetMomentumDirection() << " " << pPostStepPoint->GetMomentumDirection() << G4endl;
		if(aStep->GetTrack()->GetStepLength()>kCarTolerance/2)
			G4cout << aStep->GetStepLength()/mm <<G4endl;*/
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

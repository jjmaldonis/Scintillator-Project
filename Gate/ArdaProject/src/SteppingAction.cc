#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4SteppingManager.hh"


SteppingAction::SteppingAction(DetectorConstruction* det, EventAction* evt)
:detector(det),event(evt),counter(0)
{

}

SteppingAction::~SteppingAction()
{

}

 void SteppingAction::UserSteppingAction(const G4Step* st)
{
	G4StepPoint* postStep = st->GetPostStepPoint();
	G4StepPoint* preStep = st->GetPreStepPoint();
if(counter == 0){
	G4cout << "The world volume is " << detector->GetWorld() << G4endl;
}
counter++;
	for(G4int i = 0; i < 20; i++)
	{
		/*if (preStep->GetPhysicalVolume() == detector->physScint2[i].physVol && preStep->GetPhysicalVolume() != postStep->GetPhysicalVolume() && postStep->GetPhysicalVolume() != detector->GetWorld())
			G4cout << "  A particle was in one of the scintillators. " << detector->physScint2[i].physVol
			<< "   Its postvolume is " << postStep->GetPhysicalVolume() << G4endl;
		if (postStep->GetPhysicalVolume() == detector->physSiPM2[i].physVol && postStep->GetPhysicalVolume() != detector->GetWorld())
			G4cout << "  A particle got into one of the PMTs. " <<  detector->physSiPM2[i].physVol
			<< "   Its prevolume was " << preStep->GetPhysicalVolume() << G4endl;
		*/
		if ((postStep->GetPhysicalVolume() == detector->physSiPM2[i].physVol) && (preStep->GetPhysicalVolume() == detector->physScint2[i].physVol) && preStep->GetPhysicalVolume() != detector->GetWorld())
		{
// 			G4cout << "A new hit." << G4endl;
				event->IncrementPhotonHitNum(i);
		}
	}
// 	if ((postStep->GetPhysicalVolume() == detector->GetPM()) && (postStep->GetPhysicalVolume() == preStep->GetPhysicalVolume()))
// 	{
// // 		counter++;
// 		G4cout << G4endl << counter << "  " << st->GetStepLength()/mm << G4endl << G4endl;
// 	}
}

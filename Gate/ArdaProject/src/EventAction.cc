#include "EventAction.hh"
#include "PMHit.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4HCofThisEvent.hh"


EventAction::EventAction()
{
	scintNum = 0;
}

EventAction::~EventAction()
{

}

void EventAction::BeginOfEventAction(const G4Event*)
{
	ResetPhotonHitNum();
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
	G4cout << ">>> Event " << evt->GetEventID() << G4endl;
// 	G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
// 	G4String collectionName;
// 	PMCollectionID = SDmanager->GetCollectionID(collectionName = "PMHitsCollection");
// 	G4int event_id = evt->GetEventID();
	
	G4cout << "  The number of photons that hit the PMT(s) was " << photonHitCount << G4endl;

	RunAction::GetInstance()->WriteToFile(photonHitCount, scintNum);
	
// 	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
// 	PMHitsCollection* PMHC = 0;
// 	if (HCE)
// 	{
// 		PMHC = (PMHitsCollection*)(HCE->GetHC(PMCollectionID));
// 	}
// 	
// 	if (PMHC)
// // // 	{
// 		G4int nHits = PMHC->entries();
// 		G4cout << "     " << nHits << " hits are stored" << G4endl << G4endl;
// 	}
	
	/*G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();	
	
	G4int n_trajs = 0;
	if (trajectoryContainer)
		n_trajs = trajectoryContainer->entries();
	
	if (event_id < 100 || event_id%100 == 0)
	{

		G4cout << "     " << n_trajs << " trajectories stored in this event" << G4endl;
	}*/
}
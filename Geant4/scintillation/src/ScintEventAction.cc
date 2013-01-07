#include "ScintEventAction.hh"
#include "ScintRunAction.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4HCofThisEvent.hh"
#include "Hit.hh"
#include "G4SDManager.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run)
:runAct(run)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{
	G4cout << "---Event " << evt->GetEventID() << " Started---" << G4endl;
	photonCount = 0;
	hitPhotonCount = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
// 	G4double percent = (double) hitPhotonCount/photonCount*100;
// 	G4cout << "---Event " << evt->GetEventID() << " Finished---" << G4endl;
	
	G4HCofThisEvent* HC = evt->GetHCofThisEvent();
	PMHitsCollection* PMHC = 0;
	G4SDManager* sdManager = G4SDManager::GetSDMpointer();
	if (HC)
	{
		G4int collID = sdManager->GetCollectionID("my_PMT_SD");
		PMHC = (PMHitsCollection*)(HC->GetHC(collID));
	}

// 	G4cout << "Entries: " << PMHC->entries() << G4endl;

// 	G4cout << "The number of photons that reached the PMT was " << hitPhotonCount << G4endl;

  // Writing to file:
	RunAction::GetInstance()->WriteToFile(hitPhotonCount); // OR
// 	RunAction::GetInstance()->WriteToFile(PMHC->entries());
	
// 	<< " out of a total of " << photonCount<< " photons. "
// 	<< " That is ~" << (int) percent << "%."<< G4endl;

	runAct->AvgPhoton(hitPhotonCount);
	
}

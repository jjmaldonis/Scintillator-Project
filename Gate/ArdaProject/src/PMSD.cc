#include "PMHit.hh"
#include "PMSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

PMSD::PMSD(G4String name) : G4VSensitiveDetector(name)
{
	G4String HCname;
	collectionName.insert(HCname = "PMHitsCollection");
}

PMSD::~PMSD()
{
	
}

//-------------------------
void PMSD::Initialize(G4HCofThisEvent* HCE)
{
	PMHCollection = new PMHitsCollection(SensitiveDetectorName, collectionName[0]);
	
	static G4int HCID = -1;
	if (HCID < 0)
	{
		HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}
	HCE->AddHitsCollection(HCID, PMHCollection);
}

//-------------------------If there was energy loss, then there was phys interaction
//---------------we create a hit then, to keep info about that and add it to HitsCollection
G4bool PMSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	G4double  eDep = aStep->GetTotalEnergyDeposit();
	
	if (eDep == 0. )
		return false;
	
	PMHit* newHit = new PMHit();
	newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
 	newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()																								->GetCopyNumber());
	newHit->SetEnergyDep(eDep);
	newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
	PMHCollection->insert(newHit);
	
	newHit->Draw();
	
	return true;
}

void PMSD::EndOfEvent(G4HCofThisEvent* )
{
	if (verboseLevel>0)
	{
		G4int NbHits = PMHCollection->entries();
		G4cout << "\n--------------->Hits Collection: in this event they are "
					 << NbHits << " hits in the tracker chambers: " << G4endl;
		for (G4int i=0; i<NbHits; i++)
			{
				(*PMHCollection)[i]->Print();
			}
	}
}

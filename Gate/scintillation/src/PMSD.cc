#include "PMSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

PMSD::PMSD(G4String name,G4VPhysicalVolume* physiPMT) : G4VSensitiveDetector(name)
{
// 	G4String HCname;
	collectionName.insert(name);
	physicalPMT = physiPMT;
	test = 1;
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
G4bool PMSD::ProcessHits(G4Step* aStep, G4TouchableHistory* hist)
{
	return ProcessHits_ConstStep(aStep, hist);
}

G4bool PMSD::ProcessHits_ConstStep(G4Step* aStep, G4TouchableHistory*)
{
// 	G4cout << "Beginning" << G4endl;
	if (aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
		return false;
//
// 	G4cout << "Hits" << G4endl;
	PMHit* newHit = new PMHit();
	newHit->SetPhysicalVolume(aStep->GetPreStepPoint()->GetPhysicalVolume());
	PMHCollection->insert(newHit);
	aStep->GetTrack()->SetTrackStatus(fStopAndKill);
// 	G4cout << "Track killed." << G4endl;
	/*if( !(aStep->IsFirstStepInVolume()) ){  //This doesn't work because the track isn't destroyed, and not immediately either.
		if(physicalPMT == aStep->GetPreStepPoint()->GetPhysicalVolume()){
			if(aStep->GetPreStepPoint()->GetPhysicalVolume() == aStep->GetPostStepPoint()->GetPhysicalVolume()){
				G4cout << "A track was not killed in volume " << aStep->GetPreStepPoint()->GetPhysicalVolume()
				<< ". The step # was " << aStep->GetTrack()->GetCurrentStepNumber()
				<< ". The prevolume was " << aStep->GetPreStepPoint()->GetPhysicalVolume() << " and the postvolume was "
				<< aStep->GetPostStepPoint()->GetPhysicalVolume() << G4endl;
			}
		}
	}*/
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







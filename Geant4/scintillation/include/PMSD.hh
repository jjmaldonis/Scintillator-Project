#include "G4VSensitiveDetector.hh"

#include "globals.hh"

#include "Hit.hh"

class G4Step;
class G4HCofThisEvent;

class PMSD : public G4VSensitiveDetector
{
	public:
		PMSD(G4String,G4VPhysicalVolume* physiPMT);
		~PMSD();
		
		void Initialize(G4HCofThisEvent* );                      
		G4bool ProcessHits(G4Step* , G4TouchableHistory* );
		G4bool ProcessHits_ConstStep(G4Step* , G4TouchableHistory* );
		void EndOfEvent(G4HCofThisEvent*);                   
		G4bool test;
		
	private:
		PMHitsCollection* PMHCollection;         // Collection of Hits
		G4VPhysicalVolume* physicalPMT;
	
};
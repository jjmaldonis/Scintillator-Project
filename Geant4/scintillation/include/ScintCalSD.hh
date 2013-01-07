#ifndef ScintCalSD_h
#define ScintCalSD_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MyCalSD : public G4VSensitiveDetector
{
  public:
		MyCalSD(G4String /*name of the SD*/);
		~MyCalSD();

		void Initialize(G4HCofThisEvent*);
		G4bool ProcessHits(G4Step*, G4TouchableHistory*);
		void EndOfEvent(G4HCofThisEvent*);

  private:
	  G4double eCount;
	  G4String name;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


#include "G4UserEventAction.hh"
#include "globals.hh"
// #include "RunAction.hh"

class EventAction : public G4UserEventAction
{
	public:
		EventAction();
		~EventAction();
		
	public:
		void BeginOfEventAction(const G4Event* );
		void EndOfEventAction(const G4Event* );
		void IncrementPhotonHitNum(G4int val) {photonHitCount++; scintNum = val;};
		void ResetPhotonHitNum() {photonHitCount = 0;};
		
	private:
		G4int PMCollectionID;
		G4int photonHitCount;
		G4int scintNum;
};
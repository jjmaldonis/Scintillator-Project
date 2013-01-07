#include "G4UserSteppingAction.hh"

#include "globals.hh"

class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
	public:
		SteppingAction(DetectorConstruction*, EventAction*);
		~SteppingAction();
		
		void UserSteppingAction(const G4Step* );
		
	private:
		DetectorConstruction* detector;
		EventAction* event;
		G4int counter;
};
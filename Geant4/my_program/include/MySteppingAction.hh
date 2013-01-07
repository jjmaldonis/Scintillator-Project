#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(DetectorConstruction*, EventAction*);
  virtual ~SteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  DetectorConstruction* detector;
  EventAction*          eventaction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
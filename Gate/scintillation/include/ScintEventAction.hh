#ifndef ScintEventAction_h
#define ScintEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class RunAction;
// class EventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction*);
  virtual ~EventAction();

  void  BeginOfEventAction(const G4Event*);
  void    EndOfEventAction(const G4Event*);
	void Photon() {photonCount++;};
	void PhotonHit() {hitPhotonCount++;};
  std::string IntToString(int n);
  G4int Digits(const int number);
  
private:
   RunAction*  runAct;
	 G4int photonCount;
	 G4int hitPhotonCount;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

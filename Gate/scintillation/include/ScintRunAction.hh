#ifndef ScintRunAction_h
#define ScintRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <iostream>
#include <fstream>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class RunAction : public G4UserRunAction
{
public:
  RunAction();
  virtual ~RunAction();

  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);

	void AvgPhoton(G4double value) {avgHitPhotonCount += value;};

	void WriteToFile(G4double val);
	static RunAction* GetInstance();
	ofstream outfile;
  
private:
	G4double avgHitPhotonCount;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


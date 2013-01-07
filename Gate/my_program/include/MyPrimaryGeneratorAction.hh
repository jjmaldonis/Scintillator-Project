#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
// class PrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(DetectorConstruction*);    
  virtual ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event*);
  void SetSeed(unsigned long);

private:
  G4ParticleGun*           particleGun;	 //pointer a to G4  class
  DetectorConstruction*    Detector;     //pointer to the geometry
  unsigned long seed;
    
  // PrimaryGeneratorMessenger* gunMessenger;   //messenger of this class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



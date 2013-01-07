#ifndef ScintPrimaryGeneratorAction_h
#define ScintPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SingleParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class G4SingleParticleSource;
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
	G4int use_gun;
	G4int use_source;
  G4ParticleGun*           	particleGun;	 //pointer a to G4  class
  G4SingleParticleSource* 	particleSrc;
  DetectorConstruction*    	Detector;     //pointer to the geometry
  unsigned long seed;
    
  // PrimaryGeneratorMessenger* gunMessenger;   //messenger of this class
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



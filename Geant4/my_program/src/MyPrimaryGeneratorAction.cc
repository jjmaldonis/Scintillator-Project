#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* DC)
:Detector(DC)
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  
  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleName="tau-";
  G4ParticleDefinition* particle
                    = particleTable->FindParticle(particleName);
  particleGun->SetParticleDefinition(particle);
  G4cout << "particle name: " << particleName << G4endl;
  particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  particleGun->SetParticleEnergy(1.*MeV);
  G4double position = -0.5*(Detector->GetWorldSizeX());
  particleGun->SetParticlePosition(G4ThreeVector(position,0.*cm,0.*cm));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  // 
  G4double x0 = -0.5*(Detector->GetWorldSizeX());
  G4double y0 = 0.*cm;
  G4double z0 = 0.*cm;

  particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetSeed(unsigned long inputSeed)
{
	seed = inputSeed;
}


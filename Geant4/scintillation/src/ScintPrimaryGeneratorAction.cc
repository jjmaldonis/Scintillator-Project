#include "ScintPrimaryGeneratorAction.hh"
#include "ScintDetectorConstruction.hh"

#include "G4UImanager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSRandomGenerator.hh"
#include "G4SPSPosDistribution.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* DC)
:Detector(DC)
{
	use_gun = 1;
	use_source = 0;
	
  G4int n_particle = 1;
  
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "e-";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	G4cout << "particle name: " << particleName << G4endl;

	//The Gun
	if(use_gun){
		particleGun  = new G4ParticleGun(n_particle);
		particleGun->SetParticleDefinition(particle);
		particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
		particleGun->SetParticleEnergy(546.*keV);
		particleGun->SetParticlePosition(G4ThreeVector(-70 *cm,0.*cm,0.*cm));}

	//Complex Particle Source
	if(use_source){
		particleSrc  = new G4SingleParticleSource();
		particleSrc->SetNumberOfParticles(n_particle);
		particleSrc->SetParticleDefinition(particle);
	// 	particleSrc->SetParticleEnergy(511.*keV);
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	if(use_gun)
		delete particleGun;
	if(use_source)
		delete particleSrc;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of event
  // 
  G4double x0 = -1*(Detector->GetWorldSize());
  G4double y0 = 0.*cm;
  G4double z0 = 0.*cm;

	//The rest of the gun
	if(use_gun){
		particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
		particleGun->GeneratePrimaryVertex(anEvent);}

	
// 	Set up Sr90 Source
	if(use_source){
	// 	particleSrc->AddaSource(1.0);  //add Sr90
		particleSrc->SetVerbosity(0);

		particleSrc->GetPosDist()->SetCentreCoords(G4ThreeVector(x0,y0,z0));
	// 	particleSrc->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));

		particleSrc->GetAngDist()->SetAngDistType("planar");
		particleSrc->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1,0,0));

		//set energy spectrum
		particleSrc->GetEneDist()->SetEnergyDisType("Arb");
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(0.1*keV, 0.85,0));
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(109.2*keV, 1,0));
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(218.4*keV, 0.85,0));
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(327.6*keV, 0.65,0));
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(436.8*keV, 0.3,0));
		particleSrc->GetEneDist()->ArbEnergyHisto(G4ThreeVector(545.9*keV, 0.1,0));
		particleSrc->GetEneDist()->ArbInterpolate("Lin");

		particleSrc->SetNumberOfParticles(1);


		particleSrc->GeneratePrimaryVertex(anEvent);

// 		G4cout << "The particle is: " << particleSrc->GetParticleDefinition()->GetParticleName() << G4endl;
// 		G4cout << "The min/max energy particle is: " << particleSrc->GetEneDist()->GetEmin()/keV << "  " << particleSrc->GetEneDist()->GetEmax()/keV  << G4endl;
	}
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::SetSeed(unsigned long inputSeed)
{
	seed = inputSeed;
}


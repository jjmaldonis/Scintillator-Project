/*
	Implementation of PrimaryGeneratoraction.hh
*/

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "globals.hh"
#include "G4SPSEneDistribution.hh"
#include "G4ThreeVector.hh"
#include "G4SPSPosDistribution.hh"
#include "G4SPSAngDistribution.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* dc)
{
	G4int n_particles = 1;

	/*//Gun - for testing the program only only
	particleGun  = new G4ParticleGun(n_particles);
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e+";
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
	particleGun->SetParticleDefinition(particle);
	G4cout << "particle name: " << particleName << G4endl;
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
	particleGun->SetParticleEnergy(0.01*MeV);*/

	//Source
	particleSource = new G4GeneralParticleSource();
	
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle("e+");
	
	particleSource->SetParticleDefinition(particle);
	particleSource->GetCurrentSource()->SetNumberOfParticles(n_particles);
	
	//*********************Mono-Energetic
	G4SPSEneDistribution* eneDist = particleSource->GetCurrentSource()->GetEneDist();
	eneDist->SetVerbosity(0); //Jason changed from 2 to 0
	eneDist->SetEnergyDisType("Gauss");
	eneDist->SetMonoEnergy(2*keV);
	eneDist->SetBeamSigmaInE(0.1*keV);
	eneDist->Calculate();
	
	//********************Set Position Distribution
	G4SPSPosDistribution* posDist = particleSource->GetCurrentSource()->GetPosDist();
	posDist->SetVerbosity(0); //Jason changed from 2 to 0
	posDist->SetPosDisType("Surface");
	posDist->SetPosDisShape("Cylinder");
	posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.));
	posDist->SetRadius(1.*cm);
	posDist->SetHalfZ(2*cm);
	posDist->SetBeamSigmaInX(50.*cm);
	posDist->SetBeamSigmaInY(50.*cm);
 	posDist->ConfineSourceToVolume("HumanPhantom");

	
	G4SPSAngDistribution* angDist = particleSource->GetCurrentSource()->GetAngDist();
// 	angDist->SetAngDistType("beam2d");
// 	angDist->SetVerbosity(2);
// 	angDist->DefineAngRefAxes("angref1", G4ThreeVector(1., 0., 0.));  // set X-axis
//   angDist->DefineAngRefAxes("angref2", G4ThreeVector(0., 0., -1.)); // set Y-axis
// 	angDist->SetBeamSigmaInAngX(0.2);
// 	angDist->SetBeamSigmaInAngY(0.1);
	angDist->SetAngDistType("iso");
	angDist->SetVerbosity(0); //Jason changed from 2 to 0
	angDist->DefineAngRefAxes("angref1", G4ThreeVector(1., 0., 0.));  // set X-axis
  angDist->DefineAngRefAxes("angref2", G4ThreeVector(0., 0., -1.)); // set Y-axis
	angDist->SetMinTheta(0.*deg);
	angDist->SetMinPhi(0.*deg);
	angDist->SetMaxTheta(180.*deg);
	angDist->SetMaxPhi(360.*deg);
	

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleSource;
// 	delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	/*//Gun
	G4double x0 = 0.*cm;
	G4double y0 = 0.*cm;
	G4double z0 = 0.*cm;
	particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
	particleGun->GeneratePrimaryVertex(anEvent);*/
	

// 	Source
	particleSource->GeneratePrimaryVertex(anEvent);


// 	G4PrimaryParticle* particle = anEvent->GetPrimaryVertex( 0 )->GetPrimary( 0 );
//   G4PrimaryParticle* particle1 = anEvent->GetPrimaryVertex( 0 )->GetPrimary( 1 );
	
// 	G4double px = particle->GetMomentum().x();
// 	G4double py = particle->GetMomentum().y();
// 	G4double pz = particle->GetMomentum().z();
// 	particle1->SetMomentum(-5*px, -py, -20*pz);
}
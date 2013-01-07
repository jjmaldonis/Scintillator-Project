//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: betaBlockPrimaryGeneratorAction.cc,v 1.7 2006/06/29 17:48:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "betaBlockPrimaryGeneratorAction.hh"
#include "betaBlockDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomTools.hh"
#include "RootIO.hh"

#include "G4UImanager.hh"

#include <math.h>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

betaBlockPrimaryGeneratorAction::betaBlockPrimaryGeneratorAction(
                                               betaBlockDetectorConstruction* myDC)
:myDetector(myDC)
{
	G4int n_particle = 1;
	particleGun = new G4ParticleGun(n_particle);

	//Complex Particle Source
	particleSrc = new G4GeneralParticleSource();
	

	////Set up Sr90 Source
	//particleSrc->AddaSource(1.0);  //add Sr90

	//G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition* particle = particleTable->FindParticle("e-");
	//particleSrc->SetParticleDefinition(particle); //set to electron

	//G4ThreeVector pos;
	//pos.setZ(5*cm);

	//G4ThreeVector mom(0,0,-1*m);

	//particleSrc->SetParticlePosition(pos);  
	//UI->ApplyCommand("/gps/direction 0 0 -1");  //set pos and momentum
	////set energy spectrum
	//UI->ApplyCommand("/gps/ene/type Arb");
	//UI->ApplyCommand("/gps/hist/type arb");
	//UI->ApplyCommand("/gps/hist/point/ 0.1 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 109.2 1");
	//UI->ApplyCommand("/gps/hist/point/ 218.4 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 327.6 0.65");
	//UI->ApplyCommand("/gps/hist/point/ 436.8 0.3"); 
	//UI->ApplyCommand("/gps/hist/point/ 545.9 0.1");
	//UI->ApplyCommand("/gps/hist/inter Spline");
	//particleSrc->SetNumberOfParticles(1);

	////Set up the Y90 Source
	//particleSrc->AddaSource(1.0);  //add Y90

	//G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition* particle = particleTable->FindParticle("e-");
	//particleSrc->SetParticleDefinition(particle); //set to electron

	//G4ThreeVector pos;
	//pos.setZ(5*cm);

	//G4ThreeVector mom(0,0,-1*m);

	//particleSrc->SetParticlePosition(pos);  
	//particleSrc->SetParticleMomentumDirection(mom);  //set pos and momentum
	////set energy spectrum
	//UI->ApplyCommand("/gps/ene/type Arb");
	//UI->ApplyCommand("/gps/hist/type arb");
	//UI->ApplyCommand("/gps/hist/point/ 0.1 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 109.2 1");
	//UI->ApplyCommand("/gps/hist/point/ 218.4 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 327.6 0.65");
	//UI->ApplyCommand("/gps/hist/point/ 436.8 0.3"); 
	//UI->ApplyCommand("/gps/hist/point/ 545.9 0.1");
	//UI->ApplyCommand("/gps/hist/inter Spline");
	//particleSrc->SetNumberOfParticles(1);

	//seed = 0;

	//// default particle

	//G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	//G4ParticleDefinition* particle = particleTable->FindParticle("e-");

	//particleGun->SetParticleDefinition(particle);
	//particleGun->SetParticlePolarization(G4ThreeVector(0.,-1.,0));
	//particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

betaBlockPrimaryGeneratorAction::~betaBlockPrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void betaBlockPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
	//printf("Beginning Primary Generation..\n");
	G4UImanager * UI = G4UImanager::GetUIpointer();

	//Set up Sr90 Source
	//UI->ApplyCommand("/gps/source/add 1.0");  //add Sr90

	//UI->ApplyCommand("/gps/particle e-");//set to electron

	//G4ThreeVector pos;
	//pos.setZ(5*cm);

	//G4ThreeVector mom(0,0,-1*m);

	//UI->ApplyCommand("/gps/position 0 0 5 cm"); 

	//printf("Setting Direction..\n");
	//UI->ApplyCommand("/gps/direction 0 0 -1");  //set pos and momentum

	////set energy spectrum
	//printf("Setting Energy Spectrum..\n");
	//UI->ApplyCommand("/gps/ene/type Arb");
	//UI->ApplyCommand("/gps/hist/type arb");
	//UI->ApplyCommand("/gps/hist/point/ 0.1 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 109.2 1");
	//UI->ApplyCommand("/gps/hist/point/ 218.4 0.85");
	//UI->ApplyCommand("/gps/hist/point/ 327.6 0.65");
	//UI->ApplyCommand("/gps/hist/point/ 436.8 0.3"); 
	//UI->ApplyCommand("/gps/hist/point/ 545.9 0.1");
	//UI->ApplyCommand("/gps/hist/inter Lin");

	//printf("Setting Num particles..\n");
	//UI->ApplyCommand("/gps/number 1");

	//CLHEP::HepRandom::setTheSeed(seed + anEvent->GetEventID() );
	//CLHEP::HepRandom::setTheSeed(anEvent->GetEventID());
	//G4ThreeVector pos;
	//pos.setZ(5*cm);

	//G4ThreeVector mom(0,0,-1*m);

	//particleGun->SetParticlePosition(pos);
	//particleGun->SetParticleMomentumDirection(mom);

	//double energy;
	//double rand = G4UniformRand()*1;  //flip for Sr or Y

	//energy = G4UniformRand()*2281; //is Y beta

	//RootIO::GetInstance()->SetIncidentEnergy(energy);

	//printf("Electron energy: %f keV\n", energy);

	//particleGun->SetParticleEnergy(energy*keV);

	//printf("Generating Primary..");
	//particleGun->GeneratePrimaryVertex(anEvent);
	particleSrc->GeneratePrimaryVertex(anEvent);
	//printf(" Pew!\n");

}

void betaBlockPrimaryGeneratorAction::SetSeed(unsigned long inputSeed)
{
	seed = inputSeed;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


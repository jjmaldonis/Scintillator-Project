#include "globals.hh"
#include "ScintPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4ProcessManager.hh"

#include "G4OpticalPhysics.hh"
	// #include "G4Cerenkov.hh"
	// #include "G4Scintillation.hh"
	// #include "G4OpAbsorption.hh"
	// #include "G4OpRayleigh.hh"
	// #include "G4OpMieHG.hh"
	// #include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList() :  G4VUserPhysicsList()
{
	theCerenkovProcess           = NULL;
	theScintillationProcess      = NULL;
	theAbsorptionProcess         = NULL;
	theRayleighScatteringProcess = NULL;
	theMieHGScatteringProcess    = NULL;
	theBoundaryProcess           = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructParticle()
{
	// In this method, static member functions should be called
	// for all particles which you want to use.
	// This ensures that objects of these particle types will be
	// created in the program.
	
	ConstructBosons();
	ConstructLeptons();
	ConstructMesons();
	ConstructBaryons();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructBosons()
{
	// pseudo-particles
	G4Geantino::GeantinoDefinition();
	G4ChargedGeantino::ChargedGeantinoDefinition();
	
	// gamma
	G4Gamma::GammaDefinition();
	
	// optical photon
	G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructLeptons()
{
	// leptons
	//  e+/-
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();
	// mu+/-
	G4MuonPlus::MuonPlusDefinition();
	G4MuonMinus::MuonMinusDefinition();
	// nu_e
	G4NeutrinoE::NeutrinoEDefinition();
	G4AntiNeutrinoE::AntiNeutrinoEDefinition();
	// nu_mu
	G4NeutrinoMu::NeutrinoMuDefinition();
	G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructMesons()
{
	//  mesons
	G4PionPlus::PionPlusDefinition();
	G4PionMinus::PionMinusDefinition();
	G4PionZero::PionZeroDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructBaryons()
{
	//  barions
	G4Proton::ProtonDefinition();
	G4AntiProton::AntiProtonDefinition();
	
	G4Neutron::NeutronDefinition();
	G4AntiNeutron::AntiNeutronDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructGeneral(); //Decay
	ConstructEM();
	ConstructOp();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructGeneral()
{
	// Add Decay Process
	G4Decay* theDecayProcess = new G4Decay();
	theParticleIterator->reset();
	while( (*theParticleIterator)() ){
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		if (theDecayProcess->IsApplicable(*particle)) {
			pmanager ->AddProcess(theDecayProcess);
			// set ordering for PostStepDoIt and AtRestDoIt
			pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
			pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
		}
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructEM()
{

	gammaConversion = new G4GammaConversion(); gammaConversion->SetVerboseLevel(0);
	comptonScattering = new G4ComptonScattering(); comptonScattering->SetVerboseLevel(0);
	photoElectricEffect = new G4PhotoElectricEffect(); photoElectricEffect->SetVerboseLevel(0);
	eMultipleScattering = new G4eMultipleScattering(); eMultipleScattering->SetVerboseLevel(0);
	eIonisation = new G4eIonisation(); eIonisation->SetVerboseLevel(0);
	eBremsstrahlung = new G4eBremsstrahlung(); eBremsstrahlung->SetVerboseLevel(0);
	eplusAnnihilation = new G4eplusAnnihilation(); eplusAnnihilation->SetVerboseLevel(0);
	muMultipleScattering = new G4MuMultipleScattering(); muMultipleScattering->SetVerboseLevel(0);
	muIonisation = new G4MuIonisation(); muIonisation->SetVerboseLevel(0);
	muBremsstrahlung = new G4MuBremsstrahlung(); muBremsstrahlung->SetVerboseLevel(0);
	muPairProduction = new G4MuPairProduction(); muPairProduction->SetVerboseLevel(0);
	hMultipleScattering = new G4hMultipleScattering(); hMultipleScattering->SetVerboseLevel(0);
	hIonisation = new G4hIonisation(); hIonisation->SetVerboseLevel(0);
	
	
	theParticleIterator->reset();
	while( (*theParticleIterator)() ){
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		
		if (particleName == "gamma") {
			// gamma
			// Construct processes for gamma
			pmanager->AddDiscreteProcess(gammaConversion);
			pmanager->AddDiscreteProcess(comptonScattering);
			pmanager->AddDiscreteProcess(photoElectricEffect);
			
		} else if (particleName == "e-") {
			//electron
			// Construct processes for electron
			pmanager->AddProcess(eMultipleScattering,-1, 1, 1);
			pmanager->AddProcess(eIonisation,       -1, 2, 2);
			pmanager->AddProcess(eBremsstrahlung,   -1, 3, 3);
			
		} else if (particleName == "e+") {
			//positron
			// Construct processes for positron
			pmanager->AddProcess(eMultipleScattering,-1, 1, 1);
			pmanager->AddProcess(eIonisation,       -1, 2, 2);
			pmanager->AddProcess(eBremsstrahlung,   -1, 3, 3);
			pmanager->AddProcess(eplusAnnihilation,  0,-1, 4);
			
		} else if( particleName == "mu+" ||
			particleName == "mu-"    ) {
			//muon
			// Construct processes for muon
			pmanager->AddProcess(muMultipleScattering,-1, 1, 1);
		pmanager->AddProcess(muIonisation,      -1, 2, 2);
		pmanager->AddProcess(muBremsstrahlung,  -1, 3, 3);
		pmanager->AddProcess(muPairProduction,  -1, 4, 4);
		
			} else {
				if ((particle->GetPDGCharge() != 0.0) &&
					(particle->GetParticleName() != "chargedgeantino")) {
						// all others charged particles except geantino
						pmanager->AddProcess(hMultipleScattering,-1,1,1);
						pmanager->AddProcess(hIonisation,       -1,2,2);
			}
	}
}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructOp()
{
	theCerenkovProcess           = new G4Cerenkov("Cerenkov");
	theScintillationProcess      = new G4Scintillation("Scintillation");
	theAbsorptionProcess         = new G4OpAbsorption();
	theRayleighScatteringProcess = new G4OpRayleigh();
	theMieHGScatteringProcess    = new G4OpMieHG();
	theBoundaryProcess           = new G4OpBoundaryProcess();
	
	//  theCerenkovProcess->DumpPhysicsTable();
	//  theScintillationProcess->DumpPhysicsTable();
	//  theRayleighScatteringProcess->DumpPhysicsTable();
	
	SetVerbose(0);
	
	theCerenkovProcess->SetMaxNumPhotonsPerStep(20);
	theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
	theCerenkovProcess->SetTrackSecondariesFirst(true);
	
	theScintillationProcess->SetScintillationYieldFactor(1.);
	theScintillationProcess->SetTrackSecondariesFirst(true);
	
	// Use Birks Correction in the Scintillation process
	
	G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
	theScintillationProcess->AddSaturation(emSaturation);
	
	G4Op
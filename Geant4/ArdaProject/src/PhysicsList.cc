/*
	Implementation of PhysicsList.hh
*/


#include "PhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

PhysicsList::PhysicsList() : G4VUserPhysicsList()
{
	
}

PhysicsList::~PhysicsList()
{
	
}

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4NeutrinoE.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoE.hh"
#include "G4AntiNeutrinoMu.hh"
#include "G4ChargedGeantino.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4OpticalPhoton.hh"
//#include ""

void PhysicsList::ConstructParticle()
{
		G4Electron* electron;
		electron->ElectronDefinition();
		
		G4Positron* positron;
		positron->PositronDefinition();
		
		G4Geantino* geantino;
		geantino->GeantinoDefinition();
		
		G4Gamma* photon;
		photon->GammaDefinition();
		
		G4NeutrinoE* neutrinoE;
		neutrinoE->NeutrinoEDefinition();
		
		G4NeutrinoMu* neutrinoMu;
		neutrinoMu->NeutrinoMuDefinition();
		
		G4AntiNeutrinoE* antineutrino;
		antineutrino->AntiNeutrinoEDefinition();
		
		G4AntiNeutrinoMu* antineutrinoMu;
		antineutrinoMu->AntiNeutrinoMuDefinition();
		
		G4ChargedGeantino* chgeantino;
		chgeantino->ChargedGeantinoDefinition();
		
		G4MuonPlus* muplus;
		muplus->MuonPlusDefinition();
		
		G4MuonMinus* muminus;
		muminus->MuonMinusDefinition();
		
		G4OpticalPhoton* optphoton;
		optphoton->OpticalPhotonDefinition();
}

//****************************Process Construction

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
	ConstructGeneral();
	ConstructOptical();
}

//*****************************Processes

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
#include "G4ionIonisation.hh"

void PhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
	{
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);  
      pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung,     -1, 3, 3);
      pmanager->AddProcess(new G4MuPairProduction,     -1, 4, 4);       
             
    } else if( particleName == "proton" ||
               particleName == "pi-" ||
               particleName == "pi+"    ) {
      //proton  
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4hBremsstrahlung,     -1, 3, 3);
      pmanager->AddProcess(new G4hPairProduction,     -1, 4, 4);       
     
    } else if( particleName == "alpha" || 
	       particleName == "He3" )     {
      //alpha 
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
     
    } else if( particleName == "GenericIon" ) { 
      //Ions 
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
                 
    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
    }
  }
}

#include "G4Decay.hh"

void PhysicsList::ConstructGeneral()
{
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

#include "G4OpticalPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

void PhysicsList::ConstructOptical()
{
	G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
	
	//SetVerbose(1);
	
	G4Scintillation* theScintillationProcess = new G4Scintillation();
	G4Cerenkov* theCerenkovProcess = new G4Cerenkov();
	G4OpWLS* theOpWLSProcess = new G4OpWLS();
	G4OpAbsorption* theOpAbsorptionProcess = new G4OpAbsorption();
	G4OpRayleigh* theOpRayleighProcess = new G4OpRayleigh();
	G4OpMieHG* theOpMieHGProcess = new G4OpMieHG();
	G4OpBoundaryProcess* theOpBoundaryProcess = new G4OpBoundaryProcess();
  
	theCerenkovProcess->SetMaxNumPhotonsPerStep(100);
  theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  theCerenkovProcess->SetTrackSecondariesFirst(true);
  theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process
  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theScintillationProcess->AddSaturation(emSaturation);
  G4OpticalSurfaceModel themodel = unified;
  theOpBoundaryProcess->SetModel(themodel);
	
	//***********************Iterate which particle
	theParticleIterator->reset();
  while( (*theParticleIterator)() )
	{
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
		
    if (theCerenkovProcess->IsApplicable(*particle)) 
		{
			//pmanager->AddContinuousProcess(theCerenkovProcess);
      pmanager->AddProcess(theCerenkovProcess);
      pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
    }
    if (theScintillationProcess->IsApplicable(*particle)) 
		{
      pmanager->AddProcess(theScintillationProcess);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") 
		{
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      pmanager->AddDiscreteProcess(theOpAbsorptionProcess);
      pmanager->AddDiscreteProcess(theOpRayleighProcess);
      pmanager->AddDiscreteProcess(theOpMieHGProcess);
      pmanager->AddDiscreteProcess(theOpBoundaryProcess);
    }
  }
}


void PhysicsList::SetCuts()
{
	// the default cut value
	G4int temp = GetVerboseLevel();                                                
	SetVerboseLevel(0);                                                           
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
}

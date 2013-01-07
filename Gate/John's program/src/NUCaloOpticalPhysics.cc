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
// $Id: NUCaloPhysicsList.cc,v 1.26 2008/10/31 08:35:52 maire Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "NUCaloOpticalPhysics.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NUCaloOpticalPhysics::NUCaloOpticalPhysics(G4String aS):  G4VPhysicsConstructor(aS)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NUCaloOpticalPhysics::~NUCaloOpticalPhysics()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloOpticalPhysics::ConstructParticle()
{
	G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloOpticalPhysics::ConstructProcess()
{
  ConstructOp();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpWLS.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloOpticalPhysics::ConstructOp()
{
	G4Cerenkov*          theCerenkovProcess;
	G4Scintillation*     theScintillationProcess;
	G4OpAbsorption*      theAbsorptionProcess;
	G4OpRayleigh*        theRayleighScatteringProcess;
	G4OpBoundaryProcess* theBoundaryProcess;
	G4OpWLS*			 theWLSProcess;

	theCerenkovProcess           = new G4Cerenkov("Cerenkov");
	theScintillationProcess = new G4Scintillation("Scintillation");
	theAbsorptionProcess     = new G4OpAbsorption();
	theRayleighScatteringProcess = new G4OpRayleigh();
	theBoundaryProcess  = new G4OpBoundaryProcess();

	theWLSProcess = new G4OpWLS();
	theWLSProcess->UseTimeProfile("exponential");


	theCerenkovProcess->SetMaxNumPhotonsPerStep(300.0);
	theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
	//theCerenkovProcess->SetTrackSecondariesFirst(true);

	theScintillationProcess->SetScintillationYieldFactor(1.);
	theScintillationProcess->SetScintillationExcitationRatio(1.0);
	//theScintillationProcess->SetTrackSecondariesFirst(true);

	G4OpticalSurfaceModel themodel = unified;
	theBoundaryProcess->SetModel(themodel);
	
	theParticleIterator->reset();
	while( (*theParticleIterator)() ){
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4ProcessManager* pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		if (theCerenkovProcess->IsApplicable(*particle)) {
			  pmanager->AddProcess(theCerenkovProcess);
			  pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
		}
		if (theScintillationProcess->IsApplicable(*particle)) {
			  pmanager->AddProcess(theScintillationProcess);
			  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
			  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
		}
		if (particleName == "opticalphoton") {
			  pmanager->AddDiscreteProcess(theAbsorptionProcess);
			  pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
			  pmanager->AddDiscreteProcess(theBoundaryProcess);
			  pmanager->AddDiscreteProcess(theWLSProcess);
		}
	}																									
}

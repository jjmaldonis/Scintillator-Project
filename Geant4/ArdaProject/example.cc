/*
 Main Program For Arda's Project.
 Simulation of a PET Detector. 
*/


// Include mandatory classes
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// Include redefined classes 
#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#include "G4ios.hh"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{	
	
	G4RunManager* runManager = new G4RunManager;
	G4VisManager* visManager = new G4VisExecutive;
	DetectorConstruction* detector = new DetectorConstruction;
	PhysicsList* physics = new PhysicsList;
	runManager->SetUserInitialization(detector);
	runManager->SetUserInitialization(physics);
	
	PrimaryGeneratorAction* genAction = new PrimaryGeneratorAction(detector);
	runManager->SetUserAction(genAction);
	
	RunAction* runAction = new RunAction;	
	runManager->SetUserAction(runAction);
	
	EventAction* eventAction = new EventAction();
	runManager->SetUserAction(eventAction);
	
	SteppingAction* steppingAction = new SteppingAction(detector, eventAction);
	runManager->SetUserAction(steppingAction);
	
	visManager->Initialize();
	runManager->Initialize();
	
	G4UImanager* UI = G4UImanager::GetUIpointer();
	UI->ApplyCommand("/control/execute vis.mac");
	if (argc > 1)
	{
		G4String runtimes = argv[1];
		UI->ApplyCommand("/run/beamOn "+runtimes);
	}
	G4UIExecutive* ui = new G4UIExecutive(argc, argv);
	ui->SessionStart();
	delete ui;
	
	delete runManager;
	delete visManager;
	
	return 0;
	
}

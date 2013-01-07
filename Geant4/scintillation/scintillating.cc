#include <stdlib.h>

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "ScintDetectorConstruction.hh"
#include "ScintPhysicsList.hh"
#include "ScintPrimaryGeneratorAction.hh"
#include "ScintRunAction.hh"
#include "ScintEventAction.hh"
#include "ScintSteppingAction.hh"
#include "RootIO.hh"

#include "LHEP.hh"
#include "QGSP_BERT_EMV.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Choose random number generator
  CLHEP::HepRandom::setTheEngine(new CLHEP::HepJamesRandom);
     
  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
//   QGSP_BERT_EMV* thePhysics = new QGSP_BERT_EMV;
//   runManager->SetUserInitialization(thePhysics);

	PhysicsList* thePhysics = new PhysicsList;
	runManager->SetUserInitialization(thePhysics);
    
  // Set user action classes
  //
  PrimaryGeneratorAction* gen_action = 
                          new PrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //
  RunAction* run_action = new RunAction;
  runManager->SetUserAction(run_action);
  //
  EventAction* event_action = new EventAction(run_action);
  runManager->SetUserAction(event_action);
  //
  SteppingAction* stepping_action =
                    new SteppingAction(detector, event_action);
  runManager->SetUserAction(stepping_action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
  
  
#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

//   Input: my_program | particle | energy(in GeV) | #ofEvents | allow vis? | allow idle?
// That is:  argv[0]   |  argv[1] |     argv[2]    |  argv[3]  |  argv[4]   |  argv[5]  
  
  unsigned long seed = strtoul(argv[3],NULL,0);  //set seed for process number and offset 
//   int seed = atoi(argv[4]);  //set seed for process number and offset 
//   int seed = 1;
  

  seed *= strtoul(argv[3],NULL,10);  //multiply by events in a run for seeding

  gen_action->SetSeed(seed);
  
  
  if (argc < 5)
    G4cout << "Enter the correct number of arguments (4+). 4 are necessary, the next is to enable visualization and the following is to enable idle" << G4endl;
  else
  {
    G4String particle = argv[1];
    G4String energy = argv[2];
    G4String runtimes = argv[3]; //# of Events
    if(argc > 4){ if(*argv[4] == '1'){
			UImanager->ApplyCommand("/control/execute visOn.mac");
		}else{
			UImanager->ApplyCommand("/control/execute vis.mac");
		}}
    UImanager->ApplyCommand("/gun/particle "+particle);
    UImanager->ApplyCommand("/gun/energy "+ energy +" keV");
    UImanager->ApplyCommand("/run/beamOn "+runtimes);

		if(argc > 5){ if(*argv[5] == '1'){
//     // now start interactive mode
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
      if (ui->IsGUI())
	UImanager->ApplyCommand("/control/execute gui.mac");
      ui->SessionStart();
      delete ui;
#endif
			}}
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

	//Here is where I will make the histogram since the runManager is closed and therefore the output file is closed
	RootIO* rootIO = new RootIO();
	rootIO->Histogram();
	
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

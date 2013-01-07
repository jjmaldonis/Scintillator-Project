/**************************************************************************************
**  
**
**
**
**
**
***************************************************************************************/

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "NUCaloDetectorConstruction.hh"
#include "NUCaloOpticalPhysics.hh"
#include "LHEP.hh"
#include "QGSP_BERT_EMV.hh"
#include "NUCaloPrimaryGeneratorAction.hh"
#include "NUCaloRunAction.hh"
#include "NUCaloEventAction.hh"
#include "NUCaloSteppingAction.hh"
#include "NUCaloSteppingVerbose.hh"
#include "NUCaloStackingAction.hh"

#include "RootIO.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UIExecutive.hh"

//#if defined(G4UI_USE_WIN32)
//#include "G4UIWin32.hh"
//#include "G4UIterminal.hh"
//#else
//#include "G4UIterminal.hh"
//#endif


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{

  // usage: NUCalo Energy(GeV) Particle Events Process, 
  // e.g. NUCalo 10 e- 10000 0 writes e-/10GeV/0.root, runs 10K events at 10geV, seeds w/ 0-9999

  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new NUCaloSteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  NUCaloDetectorConstruction* detector = new NUCaloDetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  //LHEP * thePhysics = new LHEP;
  QGSP_BERT_EMV * thePhysics = new QGSP_BERT_EMV;
  //thePhysics->RegisterPhysics(new NUCaloOpticalPhysics("Optical"));
  runManager->SetUserInitialization(thePhysics);
   
  // User Action classes
  //
  NUCaloPrimaryGeneratorAction* gen_action = new NUCaloPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //
  NUCaloRunAction* run_action = new NUCaloRunAction;
  runManager->SetUserAction(run_action);
  //
  NUCaloEventAction* event_action = new NUCaloEventAction;
  runManager->SetUserAction(event_action);
  //
  NUCaloSteppingAction* stepping_action = new NUCaloSteppingAction;
  runManager->SetUserAction(stepping_action);
  //
  NUCaloStackingAction* stacking_action = new NUCaloStackingAction;
  runManager->SetUserAction(stacking_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();
      
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#endif 

  // Get the pointer to the User Interface manager
  //
  G4UImanager * UI = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode  
    {
		UI->ApplyCommand("/vis/verbose 0");
		UI->ApplyCommand("/event/verbose 0");
		UI->ApplyCommand("/run/verbose 0");
		UI->ApplyCommand("/process/verbose 0");
		UI->ApplyCommand("/material/verbose 0");
		UI->ApplyCommand("/geometry/verbose 0");
		UI->ApplyCommand("/tracking/verbose 0");

		unsigned long seed = strtoul(argv[4],NULL,10);  //set seed for process number and offset

		char dirname[256];
		sprintf(dirname,"%s/%sGeV/%04d",argv[2],argv[1],seed);
		RootIO::GetInstance()->SetDirName(dirname);

		seed *= strtoul(argv[3],NULL,10);  //multiply by events in a run for seeding

		gen_action->SetSeed(seed);

		G4String energy;
		G4String particle;
		G4String runs;

		UI->ApplyCommand("/gps/pos/type Beam");  //particle beam
		UI->ApplyCommand("/gps/pos/shape Circle");  //circular aperature
		UI->ApplyCommand("/gps/pos/centre 0. 0. 1. m");  //centered on z axis
		UI->ApplyCommand("/gps/pos/radius 3 cm");  //3 cm radius
		UI->ApplyCommand("/gps/pos/sigma_r 2 mm");  //2mm std dev on the radius
		UI->ApplyCommand("/gps/direction 0. 0. -1.");  //pointed in -z
		UI->ApplyCommand("/gps/ang/type beam1d");
		UI->ApplyCommand("/gps/ene/type Mono");

		energy = argv[1];
		UI->ApplyCommand("/gps/ene/mono " + energy + " GeV");  //set energy (in GeV)
		particle = argv[2];
		UI->ApplyCommand("/gps/particle " + particle);  //set particle

		runs = argv[3];
		UI->ApplyCommand("/run/beamOn " + runs);  //run
    }
    
  else           // interactive mode : define visualization and UI terminal
    { 
   
      //G4UIsession* session = 0;   
//#if defined(G4UI_USE_WIN32)
      //session = new G4UIWin32();
	  G4UIExecutive* session = new G4UIExecutive(argc, argv);
      UI->ApplyCommand("/control/execute gui.mac");
//#else
      //session = new G4UIterminal();
//#endif
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute vis.mac");     
#endif
		G4String dirname = "test";
		RootIO::GetInstance()->SetDirName(dirname);
		session->SessionStart();
		delete session;
    }
     
#ifdef G4VIS_USE
      delete visManager;
#endif     

  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;
  delete verbosity;

  return 0;
}

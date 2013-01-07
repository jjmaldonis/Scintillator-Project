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

#include "betaBlockDetectorConstruction.hh"
#include "betaBlockOpticalPhysics.hh"
#include "LHEP.hh"
#include "QGSP_BERT_EMV.hh"
#include "betaBlockPrimaryGeneratorAction.hh"
#include "betaBlockRunAction.hh"
#include "betaBlockEventAction.hh"
#include "betaBlockSteppingAction.hh"
#include "betaBlockSteppingVerbose.hh"
#include "betaBlockStackingAction.hh"

#include "RootIO.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//#include "G4UIterminal.hh"
#include "G4UIWin32.hh"

//#if defined(G4UI_USE_WIN32)
//#include "G4UIWin32.hh"
//#include "G4UIterminal.hh"
//#else
//#include "G4UIterminal.hh"
//#endif


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  //usage:: betaBlock (disc thickness in cm) (runs)
  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new betaBlockSteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);
  
  // Run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // User Initialization classes (mandatory)
  //
  betaBlockDetectorConstruction* detector;
  if(argc != 1)
  {
	double thick = atof(argv[1]);
	detector = new betaBlockDetectorConstruction(thick);
  } else
	detector = new betaBlockDetectorConstruction(10);

  runManager->SetUserInitialization(detector);
  //
  //QGSP_BERT_EMV * thePhysics = new QGSP_BERT_EMV;
  LHEP * thePhysics = new LHEP;
  thePhysics->RegisterPhysics(new betaBlockOpticalPhysics("Optical"));  //add optical physics
  runManager->SetUserInitialization(thePhysics);
   
  // User Action classes
  //
  betaBlockPrimaryGeneratorAction* gen_action = new betaBlockPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //
  betaBlockRunAction* run_action = new betaBlockRunAction;
  runManager->SetUserAction(run_action);
  //
  betaBlockEventAction* event_action = new betaBlockEventAction;
  runManager->SetUserAction(event_action);
  //
  betaBlockSteppingAction* stepping_action = new betaBlockSteppingAction;
  runManager->SetUserAction(stepping_action);
  //
  betaBlockStackingAction* stacking_action = new betaBlockStackingAction;
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

  if (argc == 3)   // batch mode  
    {
		UI->ApplyCommand("/vis/verbose 0");
		UI->ApplyCommand("/event/verbose 0");
		UI->ApplyCommand("/run/verbose 0");
		UI->ApplyCommand("/process/verbose 0");
		UI->ApplyCommand("/material/verbose 0");
		UI->ApplyCommand("/geometry/verbose 0");
		UI->ApplyCommand("/tracking/verbose 0");

		char dirname[256];
		sprintf(dirname,"%.3fcm",atof(argv[1]));
		RootIO::GetInstance()->SetDirName(dirname);

		UI->ApplyCommand("/control/execute beam.mac");

		G4String command = "/run/beamOn ";
		G4String runs = argv[2];
		UI->ApplyCommand(command+runs);
    }
    
  else           // interactive mode : define visualization and UI terminal
    { 
   
      //G4UIsession* session = 0;   
//#if defined(G4UI_USE_WIN32)
      G4UIsession* session = new G4UIWin32();
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

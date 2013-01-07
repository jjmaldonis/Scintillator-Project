#include "MyEventAction.hh"
#include "MyRunAction.hh"
#include "RootIO.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* run)
:runAct(run)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4String eventID = IntToString(evt->GetEventID());
  G4String zeros = "";
  
  for(int i = 0; i < Digits(RootIO::GetInstance()->GetNumOfEvents()) - Digits(evt->GetEventID()); i++)
  {
    zeros = zeros + "0";
  }
  
  RootIO::GetInstance()->BeginEvent(zeros + eventID, evt);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
  G4String eventID = IntToString(evt->GetEventID());
  G4String zeros = "";

  for(int i = 0; i < Digits(RootIO::GetInstance()->GetNumOfEvents()) - Digits(evt->GetEventID()); i++)
  {
     zeros = zeros + "0";
  }
  //The filename that I put into WriteEvent should have a .txt file extension
  RootIO::GetInstance()->EventEnd(evt, RootIO::GetInstance()->GetDirName() + "/" + zeros + eventID + ".txt");

	G4cout << "---Event " << evt->GetEventID() << " Finished---" << G4endl;
}


std::string EventAction::IntToString(int n)
{
  std::stringstream out;
  out << n;
  return out.str();
}

G4int EventAction::Digits(const int number)
{
  G4int digits = 0;
  G4int step = 1;
  while (step <= number) 
  {
    digits++;
    step *= 10;
  }
  return digits ? digits : 1;
}

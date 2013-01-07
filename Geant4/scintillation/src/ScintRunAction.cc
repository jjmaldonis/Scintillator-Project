#include <sstream>

#include "ScintRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "G4ParticleDefinition.hh"

static RunAction* instance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
	outfile.open("output.txt",ios::out);
	G4cout << "Ouput file opened." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
	outfile.close();
	G4cout << "Ouput file closed." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
	avgHitPhotonCount = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
	G4int numEvents = aRun->GetNumberOfEvent();
	G4cout << "### Run " << aRun->GetRunID() << " finished." << G4endl;
	G4cout << "Average number of photons that hit the PMT was " << avgHitPhotonCount/numEvents << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction* RunAction::GetInstance()
{
	if (instance == 0)
		instance = new RunAction();
	return instance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::WriteToFile(G4double val)
{
	// 	outfile.open("output.txt",ios::out | ios::app | ios::ate);
	if( outfile.is_open() )
		outfile << val << G4endl;
	else
		G4cout << "    The ouput file is not open!!!" << G4endl;
}
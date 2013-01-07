#include "MyCalSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyCalSD::MyCalSD(G4String name, int layer_in)
:G4VSensitiveDetector(name)
{
	layer = layer_in;
	eCount = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyCalSD::~MyCalSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyCalSD::Initialize(G4HCofThisEvent* HCE)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool MyCalSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  name = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit();
  eCount += edep/MeV;
	
//   G4cout << "  " << aStep->GetTotalEnergyDeposit() << " energy deposited"
//          << "   (layer " << layer << ")"
// 	 << "  (" << name << ")" << G4endl;

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyCalSD::EndOfEvent(G4HCofThisEvent*)
{
//   if(name != "")
//     G4cout << "  Energy deposited was " << eCount << " in layer " << layer << G4endl;
//   else
//     G4cout << "  No particles entered layer " << layer << "." << G4endl;

  RootIO::GetInstance()->WriteLayer(eCount, layer);
  eCount = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyCalSD::SetLayer(int newlayer)
{
	layer = newlayer;
}
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
// $Id: NUCaloTrackerSD.cc,v 1.9 2006/06/29 17:48:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NUCaloTrackerHit.hh"
#include "NUCaloTrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "NUCaloStackingAction.hh"

#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NUCaloTrackerSD::NUCaloTrackerSD(G4String name, int layer_in)
:G4VSensitiveDetector(name)
{
	layer = layer_in;
	eCount = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NUCaloTrackerSD::~NUCaloTrackerSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloTrackerSD::Initialize(G4HCofThisEvent* HCE)
{
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool NUCaloTrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4String name = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit();
  eCount += edep/MeV;

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloTrackerSD::EndOfEvent(G4HCofThisEvent*)
{

	RootIO::GetInstance()->WriteLayer(eCount, layer);
	eCount = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NUCaloTrackerSD::SetLayer(int newlayer)
{
	layer = newlayer;
}
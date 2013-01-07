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
// $Id: betaBlockTrackerSD.cc,v 1.9 2006/06/29 17:48:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "betaBlockTrackerHit.hh"
#include "betaBlockDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "betaBlockStackingAction.hh"

#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

betaBlockDetectorSD::betaBlockDetectorSD(G4String name,bool hf)
:G4VSensitiveDetector(name)
{
	nume = 0;
	numphotons = 0;

	G4String HCname = name;
	//collectionName.insert(HCname);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

betaBlockDetectorSD::~betaBlockDetectorSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void betaBlockDetectorSD::Initialize(G4HCofThisEvent* HCE)
{
/*  trackerCollection = new betaBlockTrackerHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, trackerCollection );*/ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool betaBlockDetectorSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4String name = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();
  //double en = aStep->GetTotalEnergyDeposit();

  //energy += en/keV;

  if(aStep->GetTrack()->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition())
  {
	  numphotons++;
	  aStep->GetTrack()->SetTrackStatus(fStopAndKill);
  }

   if(aStep->GetTrack()->GetDefinition()==G4Electron::ElectronDefinition())
  {
	  nume++;
  }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void betaBlockDetectorSD::EndOfEvent(G4HCofThisEvent*)
{
	//G4int NbHits = trackerCollection->entries();
	//std::vector<betaBlockTrackerHit*> hitsVector;

	//for (G4int i=0;i<NbHits;i++) 
	//{
	//	(*trackerCollection)[i]->Print();
	//	hitsVector.push_back((*trackerCollection)[i]);
	//}

	//printf("Energy leakage: %f GeV out of %f GeV\n",eLeak,energy);
	//RootIO::GetInstance()->WriteEnergy(energy);
	//RootIO::GetInstance()->WritePhotons(numphotons);
	//if(energy > 600)
	RootIO::GetInstance()->DetectSignal(numphotons,nume);
	nume = 0;
	numphotons = 0;

}

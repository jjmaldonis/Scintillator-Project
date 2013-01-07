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
// $Id: betaBlockTrackerHit.hh,v 1.8 2006/06/29 17:47:53 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef betaBlockTrackerHit_h
#define betaBlockTrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class betaBlockTrackerHit : public G4VHit
{
  public:

      betaBlockTrackerHit();
     ~betaBlockTrackerHit();
      betaBlockTrackerHit(const betaBlockTrackerHit&);
      const betaBlockTrackerHit& operator=(const betaBlockTrackerHit&);
      G4int operator==(const betaBlockTrackerHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)      { trackID = track; }; 
      void SetEdep     (G4double de)      { edep = de; };
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
	  void SetID      (G4String name){ particleID = name; };
      
      G4int GetTrackID()    { return trackID; };
      G4double GetEdep()    { return edep; };      
      G4ThreeVector GetPos(){ return pos; };
	  G4String GetID(){ return particleID; };
      
  private:
  
      G4int         trackID;
      G4double      edep;
      G4ThreeVector pos;
	  G4String		particleID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<betaBlockTrackerHit> betaBlockTrackerHitsCollection;

extern G4Allocator<betaBlockTrackerHit> betaBlockTrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* betaBlockTrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) betaBlockTrackerHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void betaBlockTrackerHit::operator delete(void *aHit)
{
  betaBlockTrackerHitAllocator.FreeSingle((betaBlockTrackerHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

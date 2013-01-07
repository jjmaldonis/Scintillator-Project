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
// $Id: RootIO.hh,v 1.3 2006/06/29 17:39:12 gunter Exp $
#ifndef INCLUDE_ROOTIO_HH 
#define INCLUDE_ROOTIO_HH 1

// Include files
#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include "TF2.h"
#include "TSystem.h"

#include "G4Run.hh"
#include "betaBlockTrackerHit.hh"

/** @class rootio rootio.hh include/rootio.hh
 *   
 *
 *  @author Witold POKORSKI
 *  @date   2005-10-27
 */

class RootIO 
{
public: 
  virtual ~RootIO();
  
  static RootIO* GetInstance();
  void SetDirName(G4String name);
  void OpenFile(const G4Run* thisRun);
  void CountDeposit(double energy, int photons);
  void DetectSignal(int photons, int electrons);
  void WriteEvent();
  void CloseFile();
  void SetIncidentEnergy(double energy);

protected:
  RootIO(); 
  
private:

  TFile* fo;
  char fname[256];
  TH1F* energy_histo;
  TH1F* photon_c_histo;
  TH1F* photon_d_histo;
  TH1F* eff_histo;
  TH1F* sig_histo;
  G4String dirname;
  double en_abs;
  int photons_created;
  int photons_detected;
  int e_detected;
  
};
#endif // INCLUDE_ROOTIO_HH

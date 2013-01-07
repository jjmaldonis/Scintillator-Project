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
#include <sstream>
#include <time.h>

#include "RootIO.hh"
//
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

#include "betaBlockStackingAction.hh"
//

static RootIO* instance = 0;

RootIO::RootIO()
{

}

RootIO::~RootIO()
{}

void RootIO::SetDirName(G4String name)
{
	dirname = name;
}

void RootIO::OpenFile(const G4Run* thisRun)
{
	sprintf(fname,"C:/Geant4/projects/betaBlock/%s.root", dirname.c_str());
	//sprintf(fname,"/uscms_data/d2/jneuhaus/Geant4/projects/betaBlock/%s.root", dirname.c_str());
	fo = new TFile(fname,"RECREATE");  //make Root file

	char hist_name[256];

	//energy histo
	sprintf(hist_name, "Energy Deposited");
	energy_histo = new TH1F(hist_name,hist_name,1024,0,1024);
	energy_histo->SetBit(TH1::kCanRebin);

	//photons created histo
	sprintf(hist_name, "Photons Created");
	photon_c_histo = new TH1F(hist_name,hist_name,4096,0,1024);
	photon_c_histo->SetBit(TH1::kCanRebin);

	//photons detected histo
	sprintf(hist_name, "Photons Detected");
	photon_d_histo = new TH1F(hist_name,hist_name,4096,0,1024);
	photon_d_histo->SetBit(TH1::kCanRebin);

	//expected signal histo
	sprintf(hist_name, "Recorded Charge");
	sig_histo = new TH1F(hist_name,hist_name,4096,0,409.6);
	sig_histo->SetBit(TH1::kCanRebin);

	//detector efficiency histo
	sprintf(hist_name, "Pct Photons Detected");
	eff_histo = new TH1F(hist_name,hist_name,1024,0,1.01);
	eff_histo->SetBit(TH1::kCanRebin);

	std::cout << "Writing " << fname << std::endl;
}

RootIO* RootIO::GetInstance()
{
  if (instance == 0 )
  {
    instance = new RootIO();
  }
  return instance;
}

void RootIO::CountDeposit(double energy, int photons)
{
	en_abs = energy;
	photons_created = photons;
}

void RootIO::DetectSignal(int photons, int electrons)
{
	photons_detected = photons;
	e_detected = electrons;
}

void RootIO::WriteEvent()
{
	energy_histo->Fill(en_abs);  //Energy absorbed
	photon_c_histo->Fill(photons_created);  //Photon production by scint
	photon_d_histo->Fill(photons_detected);  //Photons detected by "PMT"
	sig_histo->Fill( ((float)photons_detected * 0.25 /*+ (float)e_detected*5.0*/) * 1.6E-19 * 1E12 * 1E5 * 10);  //Convert photons and electrons to pC
	
	float pct = (float)photons_detected  / (float)photons_created;
	if(photons_created > 0)
		eff_histo->Fill(pct);  //Efficiency of detector

	//printf("Electrons Detected: %d\t",e_detected);
	//printf("Photons Detected: %d\t",photons_detected);
	//printf("Signal Detected: %f\n",((float)photons_detected * 0.25 + (float)e_detected*5.0) * 1.6E-19 * 1E12 * 1E5);

}

void RootIO::CloseFile()
{
	energy_histo->GetXaxis()->SetTitle("Energy Deposited in Material");

	photon_c_histo->GetXaxis()->SetTitle("Photons Created");

	photon_d_histo->GetXaxis()->SetTitle("Photons Detected");

	eff_histo->GetXaxis()->SetTitle("% Photons Detected");

	sig_histo->GetXaxis()->SetTitle("Charge (pC)");

	std::cout << "\nClosing " << fname << std::endl;
	fo->Write();
	fo->Close();  //Write, and close Root file

}

void RootIO::SetIncidentEnergy(double energy)
{
	//en_inc = energy;
}

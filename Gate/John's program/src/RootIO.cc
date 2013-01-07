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

#include "NUCaloStackingAction.hh"

//system specific includes for mkdir
#ifdef __GNUC__
  #include <sys/stat.h>
#else
  #ifdef _WIN32
  #include <direct.h>
  #endif
#endif

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
	sprintf(fname,"C:/Geant4/projects/NUCalo/%s.root", dirname.c_str());
	//sprintf(fname,"/uscms_data/d2/jneuhaus/Geant4/projects/rodCalo/%s.root", dirname.c_str());

	char dir_str[256];
	strncpy(dir_str,fname,strlen(fname)-strlen("/0000.root"));

	//make directory structure if doesn't exist
	#ifdef __GNUC__
		mkdir(dir_str,0777);
	#endif
	#ifdef _WIN32
		mkdir(dir_str);
	#endif

	fo = new TFile(fname,"RECREATE");  //make Root file

	char hist_name[256];

	sprintf(hist_name, "Energy Deposit");
	e_histo = new TH1F(hist_name,hist_name,1000,0,1000);
	e_histo->SetBit(TH1::kCanRebin);

	for(int i = 0; i<18; i++)
	{
		sprintf(hist_name, "Layer %d",i+1);
		layer_histo[i] = new TH1F(hist_name,hist_name,1000,0,1000);
		layer_histo[i]->SetBit(TH1::kCanRebin);
	}

	std::cout << "Writing " << fname << std::endl;

}

RootIO* RootIO::GetInstance()
{
  if (instance == 0 )
    instance = new RootIO();
  return instance;
}

void RootIO::WriteLayer(double energy, int layer)
{
	en_dep[layer-1] = energy;
	layer_histo[layer-1]->Fill(energy);
}

void RootIO::WriteEvent()
{
	float e_total = 0;
	for(int i = 0; i < 18; i++)
	{
		e_total += en_dep[i];
	}
	e_histo->Fill(e_total);
}

void RootIO::CloseFile()
{
	e_histo->GetXaxis()->SetTitle("Energy (MeV)");
	e_histo->GetZaxis()->SetTitle("Counts");
	std::cout << "\nClosing " << fname << std::endl;
	fo->Write();
	fo->Close();  //Title, write, and close Root file

}

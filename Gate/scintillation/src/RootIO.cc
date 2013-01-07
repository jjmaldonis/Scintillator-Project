//C++
#include <string>
#include <iostream>
#include <fstream>
//My files
#include "RootIO.hh"
//ROOT
#include "TTree.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TH1.h"
#include "TApplication.h"
//Geant4
#include "G4ios.hh"
#include "globals.hh"

//system specific includes for mkdir
#ifdef __GNUC__
  #include <sys/stat.h>
#else
  #ifdef _WIN32
  #include <direct.h>
  #endif
#endif

RootIO::RootIO()
{
}

RootIO::~RootIO()
{}

void RootIO::Histogram()
{
	TApplication* theApp = new TApplication("App", 0, 0);
	
// 	TH1::AddDirectory(kFALSE);
	TCanvas *c1 = new TCanvas("c1","Simulated scintillation",200,10,600,400);  //create a canvas for the histogram
		c1->SetGrid();
		c1->SetLogy();
	histo = new TH1F("hp0","",1000,0,0.00000000005);  //create new histogram
	histo->SetBit(TH1::kCanRebin);
// 	histo->SetDirectory(0);
	
	
	
	int num;
	double charge;
	ifstream inData;
	inData.open("output.txt");
	G4cout << "Input file opened." << G4endl;


	const int gain = 1000000; //10^6
	
	
	inData >> num; //Get the first value
	while(inData)
	{
		//Put data into histogram
		charge = num*0.27*gain*1.6*0.0000000000000000001;
		G4cout << "# of photons that hit: " << num << " Charge value stored: " << charge << G4endl;
		histo->Fill(charge);
		inData >> num; //get another value
	}
	
	inData.close();
	G4cout << "Input file closed." << G4endl
	<< "Drawing histogram..." << G4endl;
	histo->Draw();
	histo->Print();
// 	histo->Paint();
	c1->Modified();
	c1->Update();

	TFile f("histo.root","recreate"); //Open file, then write histo to it.
	histo->Write();

	theApp->Run();
	gSystem->ProcessEvents();
	
}



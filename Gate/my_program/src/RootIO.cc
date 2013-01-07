//C++
#include <sstream>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
//My files
#include "RootIO.hh"
//ROOT
#include "TTree.h"
#include "TCanvas.h"
//Geant4
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

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
{}

RootIO::~RootIO()
{}

RootIO* RootIO::GetInstance()
{
	if (instance == 0 )
	{
		instance = new RootIO();
	}
	return instance;
}

void RootIO::SetDirName(G4String name)
{
	dirname = name;
}

void RootIO::BeginRun(const G4Run* thisRun)
{ //Create directories, create tree, open/recreate file
	sprintf(fname,"/home/jason/geant4/geant4.9.4.p01/my_program/%s.root", dirname.c_str());
	
	char dir_str[512];
	strncpy(dir_str,fname,strlen(fname)-strlen(".root"));
	//make directory structure if doesn't exist
	#ifdef __GNUC__
	  struct stat St;
	  G4String dir_substr;
	  G4String sdir_str = dir_str;
	  G4int pos = 0;
	  while(pos != -1)
	  {
	    if(pos != 0)
	    {
	      dir_substr = sdir_str.erase(pos);
	      sdir_str = dir_str;
	      bool exists = ( stat( dir_substr, &St ) == 0 );
	      if(!exists)
	      {
		mkdir(dir_substr,0777);
		G4cout << "Directory " << dir_substr << " created." << G4endl;
	      }
	    }
	    pos = sdir_str.find("/",pos+1);
	  }
	  mkdir(dir_str,0777);
	  G4cout << "\nDirectory " << dir_str << "  created." << G4endl;
	#endif

	// Create new ROOT file to save the tree in
	sprintf(fname,"/home/jason/geant4/geant4.9.4.p01/my_program/%s/data.root", dirname.c_str());
	fo = new TFile(fname,"RECREATE");  //make Root file
	std::cout << "   Writing to " << fname << std::endl;

	// Create new tree
	tree = new TTree("Data", "Title");
}

void RootIO::BeginEvent(G4String filename, const G4Event* evt)
{ //set e_total to 0
	e_total = 0;}

void RootIO::WriteLayer(double energy, int layer)
{	//Adds the data to en_dep[layer-1]
	en_dep[layer-1] = energy;}

void RootIO::EventEnd(const G4Event* evt, G4String filename)
{	//filename is a filename with a .txt extension and with the correct path
	//this function (re)creates a .txt file, does a normal cout to the .txt file, and adds the data to a .root file

	write = false;  //set condition to false if you do not want to create the .txt files

	
	ofstream writeto_file;
	if(write)
		writeto_file.open(filename); //.txt file is (re)created
	

	e_total = 0;
	for(int i = 0; i < 20; i++)
	{
		if(write)
			writeto_file << en_dep[i] << G4endl; //writes en_dep[i] to the .txt file so I have that info in #s
		e_total += en_dep[i]; //totals the energy so I can write it to the histogram in a second
	}
// 	G4cout << "e_total is " << e_total << G4endl;

	if(write)
		writeto_file.close();


	//Creating branches
	G4String eventID = IntToStr( evt->GetEventID() );
	
	G4String branchName = "Event" + eventID + "LayerData";
	tree->Branch(branchName,en_dep,"en_dep[20]/F");
	tree->GetBranch(branchName)->Fill();
	
	branchName = "Event" + eventID + "Total";
	tree->Branch(branchName,&e_total,"e_total/F"); //floats and ints both have to have & before their names in branches, arrays do not
	tree->GetBranch(branchName)->Fill();

	/*//I can also add an entire event to a branch. See page 196 of the Trees documentation for ROOT
	Event *event = new Event()
	tree->Branch("EventBranch","Event",&event,32000,99*/

// 	G4cout << "   Total energy in event is " << e_total << G4endl;
}

void RootIO::RunEnd()
{
	tree->SetEntries();
	tree->Write();
// 	tree->Print();
	G4cout << "Closing " << fname << G4endl;
	fo->Close();
}

std::string RootIO::CharArrToString(char name[256])
{
  G4int i = 0;
  std::string str = "";
  while(name[i] != strlen(name))
  {
    str = str + name[i];
    i++;
  }
  return str;
}

G4String RootIO::IntToStr(int number)
{
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}
#ifndef INCLUDE_ROOTIO_HH 
#define INCLUDE_ROOTIO_HH 1

//ROOT
#include "TTree.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TSystem.h"

#include "G4Run.hh"

#include <string>
#include <sstream>



class RootIO 
{
public: 
  virtual ~RootIO();
  
  static RootIO* GetInstance();
  void SetDirName(G4String name);
  std::string GetDirName() {  return dirname;};
  std::string Getfname() { return fname;};
	
  void BeginRun(const G4Run* thisRun);
	void BeginEvent(G4String filename, const G4Event*);
	
  void WriteLayer(double energy, int layer);
	void EventEnd(const G4Event* evt, G4String filename);
	
	void RunEnd();
  
  void SetNumOfEvents(G4int num) {numOfEvents = num;};
  G4int GetNumOfEvents() {return numOfEvents;};

  std::string CharArrToString(char name[256]);
	G4String IntToStr(int number);

protected:
  RootIO(); 
  
private:

	TTree *tree;

	Float_t e_total;
	
	bool write;
  TFile* fo;
  char fname[256];
  float en_dep[20];
  G4String dirname;
  G4int numOfEvents;
  
};
#endif // INCLUDE_ROOTIO_HH

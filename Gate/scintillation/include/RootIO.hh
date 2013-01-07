#ifndef INCLUDE_ROOTIO_HH 
#define INCLUDE_ROOTIO_HH 1

//ROOT
#include "TTree.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TF1.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TH1.h"


class RootIO 
{
public:
	RootIO();
  virtual ~RootIO();

	void Histogram();

protected:

  
private:
// 	TCanvas* c1;
	TH1F* histo;
  
};
#endif // INCLUDE_ROOTIO_HH

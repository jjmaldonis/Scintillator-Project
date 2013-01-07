#include <iostream>
#include <string>
#include <sstream>

#include "TROOT.h"
#include <TFile.h>
#include <TTree.h>
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

using namespace std;

string ItS(int number);

void Linearity()
{

		gROOT->Reset();

		//Open file
		TFile *f = new TFile("/home/jason/geant4/geant4.9.4.p01/my_program/tau-/1GeV/data.root");

		//Set up tree
		TTree *tree = (TTree*)f->Get("Data"); //points from the tree "Data" in the file to 'tree' that I use here

		//Set up other stuff
		Int_t nevent = 1000;
	// 	Int_t nevent = (Int_t) tree->GetEntries(); //initilize the number of events
	// 	cout << nevent << " = num of events." << endl;
		Float_t e_inc; //the initialized incident energy (put in Geant program by me, directory name GeV)
		Float_t total_absorbed_energy; //per event, will be the mean of the layer values
		Float_t layer_energy[20]; //per layer

		string branchName;
		TBranch *b_e_total; //buffer?

		TH1F *hist_e_total   = new TH1F("hist_e_total","Total Energy Deposited per Event",1000,0,1); //histogram
		hist_e_total->SetBit(TH1::kCanRebin);

		//Go through the data and parse
		for(Int_t i = 0; i < nevent; i++)
		{
			branchName = "Event" + ItS(i) + "Total";
			b_e_total = tree->GetBranch(branchName.c_str());
			tree->ResetBranchAddresses();
			b_e_total->SetAddress(&total_absorbed_energy);

			b_e_total->GetEntry(0);
			hist_e_total->Fill(total_absorbed_energy);


	/*		branchName = "Event" + ItS(i) + "LayerData";

			b_e_total = tree->GetBranch(branchName.c_str());
			tree->ResetBranchAddresses();
			b_e_total->SetAddress(layer_energy);

			b_e_total->GetEntry(0);

			for(Int_t ii = 0; ii < 20; ii++)
				cout << ii << "   " << layer_energy[ii] << endl;
	*/
		}
		hist_e_total->Draw();
	//	tree->Print();
	// 	tree->StartViewer();

}
// .x /home/jason/root/tutorials/tree/tree1.C
// .x /home/jason/geant4/geant4.9.4.p01/my_program/root_analysis/Linearity.C




string ItS(int number)
{
	stringstream ss;  //create a stringstream
	ss << number;  //add number to the stream
	return ss.str();  //return a string with the contents of the stream
}
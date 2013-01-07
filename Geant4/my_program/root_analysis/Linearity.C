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

	const num_of_energies = 7;
	Float_t energies[num_of_energies] = {1,2,5,10,20,50,100}; //this is the array where the incident energies will go so i can iterate over them
	Float_t mean_total_absorbed_energy[num_of_energies]; //The size of this is the # of different incident energies I will be using, it will store the mean total_absorbed_energy for each of the incident energies

	TH2F *hist_linearity = new TH2F("hist_linearity","Total Energy Deposited per Event",1000,0,1,1000,0,1); //histogram

	TTree *tree_graph;

	Float_t e_inc; //the initialized incident energy (put in Geant program by me, directory name GeV)
	Float_t e_abs;
	tree_graph = new TTree("Linearity_Graph", "Title");
	tree_graph->Branch("Incident",&e_inc,"e_inc/F");
	tree_graph->Branch("Absorbed",&e_abs,"e_abs/F");
	
	
	//LOOP START
	for(Int_t j = 0; j < num_of_energies; j++)
	{
		mean_total_absorbed_energy[j] = 0; //initialze to 0
		
		gROOT->Reset();

		char filepath[512];
		sprintf(filepath,"/home/jason/geant4/geant4.9.4.p01/my_program/tau-/%dGeV/data.root",energies[j]);

		//Open file
		TFile *f = new TFile(filepath);

		//Set up tree
		TTree *tree = (TTree*)f->Get("Data"); //points from the tree "Data" in the file to 'tree' that I use here
		
		
		//Set up other stuff
		Int_t nevent = 1000;
	// 	Int_t nevent = (Int_t) tree->GetEntries(); //initilize the number of events
	// 	cout << nevent << " = num of events." << endl;
		Float_t total_absorbed_energy; //per event, will be the mean of the layer values
		Float_t layer_energy[20]; //per layer

		string branchName;
		TBranch *b_hist_linearity; //buffer?

// 		hist_linearity->SetBit(TH1::kCanRebin);

		//Go through the data and parse
		for(Int_t i = 0; i < nevent; i++)
		{
			branchName = "Event" + ItS(i) + "Total";
			b_hist_linearity = tree->GetBranch(branchName.c_str());
// 			tree->ResetBranchAddresses();
			b_hist_linearity->SetAddress(&total_absorbed_energy);

			b_hist_linearity->GetEntry(0);
// 			cout << "Total energy is " << total_absorbed_energy << endl;

			mean_total_absorbed_energy[j] += total_absorbed_energy;
// 			cout << "  " << total_absorbed_energy << " energy added to the mean." << endl;

		}
// 		cout << "The mean_total_absorbed_energy[" << j << "] is " << mean_total_absorbed_energy[j] << endl;
		mean_total_absorbed_energy[j] /= nevent;
		
// 		hist_linearity->Fill(energies[j],mean_total_absorbed_energy[j]);
		e_inc = energies[j];
		e_abs = mean_total_absorbed_energy[j];
		

// 		tree_graph->GetBranch("Incident")->Fill();
// 		cout << e_inc << endl;
// 		tree_graph->GetBranch("Absorbed")->Fill();
// 		cout << e_abs << endl;
		tree_graph->Fill();

// 		f->Close;		
		
// 		cout << endl << "  Plotted " << energies[j] << " agaisnt " << mean_total_absorbed_energy[j] << endl;
		cout << "  Incident energy " << energies[j] << "GeV file completed." << endl;
	}//end the big for loop that goes over the incident energies

// for (Int_t i = 0; i < num_of_energies; i++)	cout << energies[i] << " : " << mean_total_absorbed_energy[i] << endl;

// tree_graph->GetListOfBranches()->Print();
// tree_graph->Fill();
// tree_graph->Print();
// cout << tree_graph->GetBranch("Incident")->GetEntries() << endl; //returns 1
// cout << tree_graph->GetBranch("Absorbed")->GetEntries() << endl; //returns 1

tree_graph->Draw("e_abs:e_inc");

for(Int_t jj = 0; jj < 7; jj++)
	{
		tree_graph->GetBranch("Incident")->GetEntry(jj);
		tree_graph->GetBranch("Absorbed")->GetEntry(jj);
		cout << "Coordinate: (" << e_inc << "," << e_abs << ")" << endl;
	}
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
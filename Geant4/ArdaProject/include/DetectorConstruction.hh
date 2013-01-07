/*
	Construction of all necessary materials and geometry
*/


#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class PMHit;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVPlacement;
class G4Material;
class G4Element;
class G4VisAttributes;
class G4OpticalSurface;

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
		~DetectorConstruction();
			
		G4VPhysicalVolume* Construct();
		
			struct modules
		{
			G4LogicalVolume* logVol;
		};
		struct physPMs
		{
			G4VPhysicalVolume* physVol;
		};
// 	G4int n_modules = 10;
// 	physPMs physSiPM;
		physPMs physSiPM2[20];
		physPMs physScint2[20];
		
		physPMs* GetPM() {return physSiPM2;};
		physPMs* GetScintillator() {return physScint2;};
		G4VPhysicalVolume* GetWorld() {return physWorld;};
		
		
			
	private:
		void DefineMaterials();
		G4VPhysicalVolume* ConstructWorld();
		void ConstructHumanPhantom();
		void ConstructDetectorModules();
		void ConstructDetectorModules2();
		void ConstructOpticalSurface();
		

		

	private:
		//**************Elements
		
		G4Element* H_e;
		G4Element* He_e;
		G4Element* Li_e;
		G4Element* Be_e;
		G4Element* B_e;
		G4Element* C_e;
		G4Element* N_e;
		G4Element* O_e;
		G4Element* F_e;
		G4Element* Ne_e;
		G4Element* Na_e;
		G4Element* Mg_e;
		G4Element* Al_e;
		G4Element* Si_e;
		G4Element* P_e;
		G4Element* S_e;
		G4Element* Cl_e;
		G4Element* Ar_e;
		G4Element* K_e;
		G4Element* Ca_e;
		G4Element* Sc_e;
		G4Element* Ti_e;
		G4Element* V_e;
		G4Element* Cr_e;
		G4Element* Mn_e;
		G4Element* Fe_e;
		G4Element* Co_e;
		G4Element* Ni_e;
		G4Element* Cu_e;
		G4Element* Zn_e;
		G4Element* Ga_e;
		G4Element* Ge_e;
		G4Element* Y_e;
		G4Element* Cd_e;
		G4Element* Te_e;
		G4Element* I_e;
		G4Element* Cs_e;
		G4Element* Gd_e;
		G4Element* Lu_e;
		G4Element* W_e;
		G4Element* Tl_e;
		G4Element* Pb_e;
		G4Element* Bi_e;
		G4Element* U_e;
		G4Element* Ce_e;
		
		//**************Materials
		G4Material* Air_m;
		G4Material* Ge_m;
		G4Material* Bi_m;
		G4Material* Ce_m;
		G4Material* Si_m;
		G4Material* SilicaOxide_m;
		G4Material* CeriumOxide_m;
		G4Material* SilicateGlass_m;
		G4Material* ArgonGas_m;
		G4Material* Al_m;
		G4Material* BGO_m;
		G4Material* Water_m;
		G4Material* Vacuum_m;
		G4Material* PMMA_m;
		G4Material* Pethylene_m;
		G4Material* Pstyrene_m;
		G4Material* DopedPethylene_m;
		G4Material* Plastic_m;
		G4Material* Quartz_m;
	
		//**************World Declaration
		G4LogicalVolume* logicWorld;
		G4VPhysicalVolume* physWorld;
		
		//**************Human Body Declaration
		G4LogicalVolume* logicHuman;
		G4VPhysicalVolume* physHuman;
		G4VisAttributes* VisAttr_Human;
		
		//**************Detector Module : Basis
		G4LogicalVolume* logicDetectorModule;
		G4VPhysicalVolume* physDetectorModule[4];
		G4VisAttributes* VisAttr_DetectorModule;
		
		//**************Detector Module : Crystall Scintillator
		G4LogicalVolume* logicScintillator;
		G4VPhysicalVolume* physScintillator;
		G4VisAttributes* VisAttr_Scintillator;
		
		//**************Detector Module : Silica PM
		G4LogicalVolume* logicSiPM;
		G4VPhysicalVolume* physSiPM;
		G4VisAttributes* VisAttr_SiPM;
		
		//**************Optical Surface 
		G4OpticalSurface* OpSurface;
		G4VisAttributes* VisAttr_OpSurface;
};


#endif
/*
	Implementation of DetectorConstruction.cc
*/

#include "DetectorConstruction.hh"
#include "PMHit.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "globals.hh"
#include <cmath>
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"


DetectorConstruction::DetectorConstruction() 
	: logicWorld(0), physWorld(0),
	  ArgonGas_m(0)
{
	
}

DetectorConstruction::~DetectorConstruction()
{
	
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	DefineMaterials();
	G4VPhysicalVolume* phys = ConstructWorld();
	ConstructDetectorModules2();
 	ConstructHumanPhantom();
	ConstructOpticalSurface();
	return phys;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

void DetectorConstruction::DefineMaterials()
{
	//************************Material Constants
	G4int polyPMMA = 1;
	G4int nC_PMMA = 3+2*polyPMMA;
	G4int nH_PMMA = 6+2*polyPMMA;
	
	G4int polyeth = 1;
	G4int nC_eth = 2*polyeth;
	G4int nH_eth = 4*polyeth;
	
	
	//************************Material Variables
	G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
	G4double pressure;
	G4double temperature;
	G4String name;
	G4String symbol;
	G4int nElements;
	G4int nAtoms;
	G4double weightRatio; 
	
	//**************************Elements
	a = 14.01*g/mole;
	N_e = new G4Element(name="Nitrogen", symbol="N", z=7., a);
	
	a=16.00*g/mole;
	O_e = new G4Element(name="Oxygen", symbol="O", z=8., a);
	
	a= 1.01*g/mole;
	H_e = new G4Element(name="Hydrogen", symbol="H", z=1., a);
	
	a = 12.01*g/mole;
	C_e = new G4Element(name="Carbon", symbol="C", z=6., a);
	
	a = 72.61*g/mole;
	Ge_e = new G4Element(name="Germanium", symbol="Ge", z=32., a);
	
	a = 4.003*g/mole;
	z = 2.;
	He_e = new G4Element(name="Helium", symbol="He", z, a);
	
	a = 6.941*g/mole;
	z = 3;
	Li_e = new G4Element(name="Lithium", symbol="Li", z, a);
	
	a = 9.012*g/mole;
	z = 4;
	Be_e = new G4Element(name="Beryllium", symbol="Be", z, a);
		
	a = 10.811*g/mole;
	z= 5.;
	B_e = new G4Element(name="Boron", symbol="B", z, a);
	
// 	a = 
// 	z = 
//	F_e = new G4Element(name="Fluorine", symbol="F", z, a);
	
	a = 140.116*g/mole;
	z = 58.;
	Ce_e =  new G4Element(name="Cerium", symbol="Ce", z, a);
/*	
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
*/	
	
	//****************************************Materials
	//**************************air
	density = 1.29*mg/cm3;
	Air_m = new G4Material(name="Air", density, nElements=2);
	Air_m->AddElement(N_e, weightRatio=0.7);
	Air_m->AddElement(O_e, weightRatio=0.3);
	
	//*************************Agron Gas
	ArgonGas_m = new G4Material("ArgonGas", z= 18., a= 39.95*g/mole, density= 1.782*mg/cm3);
	
	//*************************Aluminum
	Al_m 			 = new G4Material(name="Aluminum", z=13., a=26.98*g/mole, density=2.7*g/cm3);
	
	//*************************Bismuth
	Bi_m 			 = new G4Material(name="Bismuth", z=83., a=208.98*g/mole, density=9.78*g/cm3);
	
	//*************************Germanium
	Ge_m 			 = new G4Material(name="Germanium", z=32, a=72.63*g/mole, density=5.323*g/cm3);
	
	//*************************Cerium
	Ce_m 			 = new G4Material(name="Cerium", z=58, a=140.116*g/mole, density=6.773*g/cm3);
	
	//**************************Silicon
	Si_m			 = new G4Material(name="Silicon", z=14., z=28.086*g/mole, density=2.329*g/cm3);
	
	
	//**********************Silicon Oxide
	density = 2.648*g/cm3;
	SilicaOxide_m = new G4Material(name="SiliconOxide", density, nElements=2);
	SilicaOxide_m->AddMaterial(Si_m, nAtoms=1);
	SilicaOxide_m->AddElement(O_e, nAtoms=2);
	
	//**********************Cerium Oxide
	density = 6.2*g/cm3;
	CeriumOxide_m = new G4Material("CeriumOxide", density, nElements=2);
	CeriumOxide_m->AddMaterial(Ce_m, nAtoms=2);
	CeriumOxide_m->AddElement(O_e, nAtoms=3);
	
	//**********************SiO2-Ce2O3 Glass
	density = 2.719*g/cm3;
	SilicateGlass_m = new G4Material("SiO2-Ce2O3Glass", density, nElements=2);
	SilicateGlass_m->AddMaterial(SilicaOxide_m, weightRatio=0.98);
	SilicateGlass_m->AddMaterial(CeriumOxide_m, weightRatio=0.02);
	
	//**********************BGO Crystall
	density = 7.13*g/cm3;
	BGO_m = new G4Material(name="BGO", density, nElements=3);
	BGO_m->AddMaterial(Bi_m, nAtoms = 4);
	BGO_m->AddMaterial(Ge_m, nAtoms = 3);
	BGO_m->AddElement(O_e, nAtoms=12);
	
	//******************Water
	Water_m = new G4Material("Water", density=1.000*g/cm3, nElements=2);
	Water_m->AddElement(H_e, nAtoms=2);
	Water_m->AddElement(O_e, nAtoms=1);
	//H2O->GetIonization()->SetMeanExcitationEnergy(75.*eV);
	
	//******************Vacuum
	density = universe_mean_density;
	pressure = 1.e-19*pascal;
	temperature = 0.1*kelvin;
	Vacuum_m = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density, kStateGas, temperature, pressure);
	
	//*****************Polystyrene
	Pstyrene_m = new G4Material("Polystyrene", density= 1.03*g/cm3, 2);
  Pstyrene_m->AddElement(C_e, 8);
  Pstyrene_m->AddElement(H_e, 8);
	
	//******************Plastic
	Plastic_m = new G4Material("Plastic", density=1.18*g/cm3, nElements=3);
	Plastic_m->AddElement(C_e, nAtoms=5);
	Plastic_m->AddElement(H_e, nAtoms=8);
	Plastic_m->AddElement(O_e, nAtoms=2);
	
	//********************Quartz
	Quartz_m = new G4Material(name="Quartz", density=2.200*g/cm3, nElements=2);
	Quartz_m->AddMaterial(Si_m, nAtoms=1);
	Quartz_m->AddElement(O_e, nAtoms=2);
	
	//******************Fiber Material
	PMMA_m = new G4Material("PMMA", density=1.190*g/cm3, nElements=3);
	PMMA_m->AddElement(H_e, nH_PMMA);
	PMMA_m->AddElement(C_e, nC_PMMA);
	PMMA_m->AddElement(O_e, 2);
	
	//*******************Cladding
	Pethylene_m = new G4Material("pethylene", density=1200*kg/m3, 2);
	Pethylene_m->AddElement(H_e, nH_eth);
	Pethylene_m->AddElement(C_e, nC_eth);
	
	//******************New Core(BGO combined with core material)
	G4double Crystaldensity = 1.03*g/cm3;
	G4double Pethylenedensity = 1.2*g/cm3;
	G4double weightCrystal = 1;
	G4double weightPethylene = 0;
	DopedPethylene_m = new G4Material("DopedPethylene", density = weightCrystal*Crystaldensity + weightPethylene*Pethylenedensity, nElements=2);
	DopedPethylene_m->AddMaterial(Pethylene_m, weightRatio = weightPethylene);
	DopedPethylene_m->AddMaterial(Pstyrene_m, weightRatio = weightCrystal);
		
	
	
	//*******************Material's Properties Tables
		//******************Quartz Properties Table
	const G4int NUMENTRIES = 3;	
	G4double Quartz_ABSENERGY[NUMENTRIES] = {2.*eV, 2.433*eV, 2.9*eV};
	G4double Quartz_RINDEX[NUMENTRIES] = {1.4435, 1.444, 1.46};
	G4double Quartz_ABSLENGTH[NUMENTRIES] = {3.45*m, 10.*m, 15.*m};
	
	G4MaterialPropertiesTable* MPT_Quartz = new G4MaterialPropertiesTable();
	MPT_Quartz->AddProperty("RINDEX", Quartz_ABSENERGY, Quartz_RINDEX, NUMENTRIES);
	MPT_Quartz->AddProperty("ABSLENGTH", Quartz_ABSENERGY, Quartz_ABSLENGTH, NUMENTRIES);
	Quartz_m->SetMaterialPropertiesTable(MPT_Quartz);
	
		//******************BGO Properties Table
	G4double BGO_ABSENERGY[NUMENTRIES] = { 2.*eV , 2.87*eV, 2.9*eV};
	G4double BGO_RINDEX[NUMENTRIES] = {2.15 , 2.15, 2.15 };
	G4double BGO_ABSLENGTH[NUMENTRIES] = { 24.*cm, 24.*cm, 24.*cm};
	G4double BGO_SCINTILFAST[NUMENTRIES]={0.00, 0.00, 1.00};
	
	G4MaterialPropertiesTable* MPT_BGO = new G4MaterialPropertiesTable();
	MPT_BGO->AddProperty("RINDEX", BGO_ABSENERGY, BGO_RINDEX, NUMENTRIES);
	MPT_BGO->AddProperty("ABSLENGTH", BGO_ABSENERGY, BGO_ABSLENGTH, NUMENTRIES);
	MPT_BGO->AddProperty("FASTCOMPONENT",BGO_ABSENERGY, BGO_SCINTILFAST, NUMENTRIES);
	MPT_BGO->AddConstProperty("SCINTILLATIONYIELD", 2000./MeV);
  MPT_BGO->AddConstProperty("RESOLUTIONSCALE", 1.0);
  MPT_BGO->AddConstProperty("FASTTIMECONSTANT", 100.*ns);
	BGO_m->SetMaterialPropertiesTable(MPT_BGO);
	
		//******************************Plastic Properties Table
	G4MaterialPropertiesTable* MPT_Plastic = new G4MaterialPropertiesTable();
	G4double Plastic_RINDEX[NUMENTRIES] = {1.6, 1.6, 1.6};
	G4double Plastic_ABSENERGY[NUMENTRIES] = {2.*eV, 2.87*eV, 2.9*eV};
	MPT_Plastic->AddProperty("RINDEX", Plastic_ABSENERGY, Plastic_RINDEX, NUMENTRIES);
	Plastic_m->SetMaterialPropertiesTable(MPT_Plastic);
	
		//*******************************Silicate Glass Properties Table
	G4MaterialPropertiesTable* MPT_SilicateGlass = new G4MaterialPropertiesTable();
	G4double SilicateGlass_RINDEX[NUMENTRIES] = {1.7, 1.7, 1.7};
	G4double SilicateGlass_ABSENERGY[NUMENTRIES] = {2.*eV, 2.87*eV, 2.9*eV};
	G4double SilicateGlass_ABSLENGTH[NUMENTRIES] = {9.*m, 9.*m, 9.*m};
	G4double SilicateGlass_SCINTILFAST[NUMENTRIES] = {0.00, 0.00, 1.00};
	G4double SilicateGlass_SCINTILSLOW[NUMENTRIES] = {0.00, 0.00, 0.05};
	
	MPT_SilicateGlass->AddProperty("ABSLENGTH", SilicateGlass_ABSENERGY, SilicateGlass_ABSLENGTH, NUMENTRIES);
	MPT_SilicateGlass->AddProperty("FASTCOMPONENT",SilicateGlass_ABSENERGY, SilicateGlass_SCINTILFAST, NUMENTRIES);
// 	MPT_SilicateGlass->AddProperty("SLOWCOMPONENT",SilicateGlass_ABSENERGY, SilicateGlass_SCINTILSLOW, NUMENTRIES);
	MPT_SilicateGlass->AddConstProperty("SCINTILLATIONYIELD", 10000./MeV);
  MPT_SilicateGlass->AddConstProperty("RESOLUTIONSCALE", 1.0);
  MPT_SilicateGlass->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
//  	MPT_SilicateGlass->AddConstProperty("SLOWTIMECONSTANT", 10.*ns);
// 	MPT_SilicateGlass->AddConstProperty("YIELDRATIO", 0.8);
	MPT_SilicateGlass->AddProperty("RINDEX", SilicateGlass_ABSENERGY, SilicateGlass_RINDEX, NUMENTRIES);
	SilicateGlass_m->SetMaterialPropertiesTable(MPT_SilicateGlass);
	
		//********************Polystyrene Properties Table
	G4double Energy[NUMENTRIES] = {2.00*eV, 2.87*eV, 2.90*eV};
	
	G4double Pstyrene_RINDEX[NUMENTRIES]={ 1.5, 1.5, 1.5};
  G4double Pstyrene_ABSLENGTH[NUMENTRIES]={2.*cm, 2.*cm, 2.*cm};
  G4double Pstyrene_ScintilFast[NUMENTRIES]={0.00, 0.00, 1.00};
  G4MaterialPropertiesTable* MPT_Pstyrene = new G4MaterialPropertiesTable();
  MPT_Pstyrene->AddProperty("RINDEX",Energy,Pstyrene_RINDEX,NUMENTRIES);
  MPT_Pstyrene->AddProperty("ABSLENGTH",Energy,Pstyrene_ABSLENGTH,NUMENTRIES);
  MPT_Pstyrene->AddProperty("FASTCOMPONENT",Energy, Pstyrene_ScintilFast, NUMENTRIES);
	MPT_Pstyrene->AddConstProperty("SCINTILLATIONYIELD",10./keV);
  MPT_Pstyrene->AddConstProperty("RESOLUTIONSCALE",1.0);
  MPT_Pstyrene->AddConstProperty("FASTTIMECONSTANT", 10.*ns);
  Pstyrene_m->SetMaterialPropertiesTable(MPT_Pstyrene);
	
		//******************AIR and VACUUM properties table
	G4double Vacuum_Energy[NUMENTRIES]={2.0*eV,7.0*eV,7.14*eV};
  G4double Vacuum_RINDEX[NUMENTRIES]={1.,1.,1.};  
  G4MaterialPropertiesTable* MPT_Vacuum = new G4MaterialPropertiesTable();
  MPT_Vacuum->AddProperty("RINDEX", Vacuum_Energy, Vacuum_RINDEX,NUMENTRIES);
  Vacuum_m->SetMaterialPropertiesTable(MPT_Vacuum);
  Air_m->SetMaterialPropertiesTable(MPT_Vacuum);//Give air the same rindex
		
		//******************PMMA Prperties Table
	G4double PMMA_RINDEX[NUMENTRIES] = {1.6, 1.6, 1.6};
	G4double PMMA_ABSLENGTH[NUMENTRIES]={9.00*mm,9.00*mm,0.1*mm};
	G4MaterialPropertiesTable* MPT_PMMA = new G4MaterialPropertiesTable();
	MPT_PMMA->AddProperty("RINDEX", Energy, PMMA_RINDEX, NUMENTRIES);
//  G4double EmissionFib[NUMENTRIES]={1.0, 1.0, 0.0};
//  PMMA_MT->AddProperty("FIBERABSLENGTH",Energy,AbsFiber,NUMENTRIES);
//  PMMA_MT->AddProperty("COMPONENT", Energy, EmissionFib, NUMENTRIES);
//  PMMA_MT->AddConstProperty("TIMECONSTANT", 0.5*ns);
 	PMMA_m->SetMaterialPropertiesTable(MPT_PMMA);
	
		//******************pethylene Properties Table	
  G4double Pethylene_RINDEX[NUMENTRIES]={ 1.49, 1.49, 1.49};
  G4MaterialPropertiesTable* MPT_Pethylene = new G4MaterialPropertiesTable();
  MPT_Pethylene->AddProperty("RINDEX",Energy,Pethylene_RINDEX,NUMENTRIES);
  //MPTClad1->AddProperty("ABSLENGTH",Energy,AbsFiber,NUMENTRIES);
  Pethylene_m->SetMaterialPropertiesTable(MPT_Pethylene);
	
		//*****************Doped Pethylene Material
	G4double DopedPethylene_RINDEX[NUMENTRIES] = {1.3, 1.3, 1.3};
	G4MaterialPropertiesTable* MPT_DopedPethylene = new G4MaterialPropertiesTable();
	MPT_DopedPethylene->AddProperty("RINDEX", Energy, DopedPethylene_RINDEX, NUMENTRIES);
	DopedPethylene_m->SetMaterialPropertiesTable(MPT_DopedPethylene);

	//**********************************Output Materials Table
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


/////////////////////////////////////////////////////////////
//*****************************Construct a New Geometry******
//***Human Body contains a source.
//***Crystals + Silicon-PM
/////////////////////////////////////////////////////////////

//**********************************Constructs a new World
G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{
	//******************* World
	G4double sWorldX = 100.0*cm; // half-length in X
	G4double sWorldY = 100.0*cm; // half-length in Y
	G4double sWorldZ = 100.0*cm; // half-length in Z

	G4Box* solidWorld = new G4Box("World", sWorldX, sWorldY, sWorldZ);
	logicWorld = new G4LogicalVolume(solidWorld, Vacuum_m, "World");	
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);
	
	return physWorld;
}

//******************************Construct a Human Phantom - Cylinder
void DetectorConstruction::ConstructHumanPhantom()
{
	G4String name = "HumanPhantom";
	G4double RMin = 0.*cm;
	G4double RMax = 5*cm;
	G4double Dz   = 10.0*cm;
 	G4double SPhi = 0;
 	G4double DPhi = 2*pi;
	
	G4Tubs* solidHuman = new G4Tubs(name, RMin, RMax, Dz, SPhi, DPhi);
	logicHuman = new G4LogicalVolume(solidHuman, Water_m, name);
	physHuman = new G4PVPlacement(0, G4ThreeVector(), logicHuman, name, logicWorld, false, 0);
	
	VisAttr_Human = new G4VisAttributes(G4Color(0.0, 0.0, 1.0)); //blue
	VisAttr_Human->SetForceWireframe(true);
	VisAttr_Human->SetForceSolid(false);
	logicHuman->SetVisAttributes(VisAttr_Human);
}

//*****************************Construct Detector Modules
void DetectorConstruction::ConstructDetectorModules()
{
	//***************************Detector Module : Basis
	G4String name = "DetectorModule";
	G4double sDetectorModuleX = 2*cm;
	G4double sDetectorModuleY = 5*cm;
	G4double sDetectorModuleZ = 5*cm;
	G4double posX;
	G4double posY;
	G4double posZ;
	
	G4Box* solidDetectorModule = new G4Box(name, sDetectorModuleX, sDetectorModuleY, sDetectorModuleZ);
	logicDetectorModule = new G4LogicalVolume(solidDetectorModule, Vacuum_m, name);
// 	G4RotationMatrix* rotationMatrix[3];
	
// 	physDetectorModule[0] = new G4PVPlacement(0, G4ThreeVector(0., 0., 35.*cm), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[0] = new G4RotationMatrix();
// 	rotationMatrix[0]->rotateY(-90*deg);
// 	physDetectorModule[1] = new G4PVPlacement(rotationMatrix[0], G4ThreeVector(35.*cm, 0., 0.), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[1] = new G4RotationMatrix();
// 	rotationMatrix[1]->rotateY(-180*deg);
// 	physDetectorModule[2] = new G4PVPlacement(rotationMatrix[1], G4ThreeVector(0., 0., -35.*cm), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[2] = new G4RotationMatrix();
// 	rotationMatrix[2]->rotateY(-270*deg);
// 	physDetectorModule[3] = new G4PVPlacement(rotationMatrix[2], G4ThreeVector(-35.*cm, 0., 0.), logicDetectorModule, name, logicWorld, false, 0);
	
// 	physDetector = new CylRepeat(40.*cm, G4ThreeVector(), "y", 100, solidDetectorModule, logicDetectorModule, logicWorld);
	G4int n_modules = 10.;
	G4double dphi = ((G4double)360./n_modules)*deg;
	G4double x_coor, z_coor;
	G4double Radius = 40.*cm;
	G4double phi;
//	
	//*************rotation around the y-axis
	for (G4int counter = 0; counter < n_modules; counter++)
	{
		G4RotationMatrix* rm = new G4RotationMatrix();
		phi = counter*dphi;
//		
		x_coor = Radius*cos(phi);
		z_coor = Radius*sin(phi);
//
		G4cout << "  Rotation Angle " << counter << " is " << phi/deg << " " << dphi << G4endl;
//
		rm = new G4RotationMatrix();
		rm->rotateY(phi);
		new G4PVPlacement(rm, G4ThreeVector(x_coor, 0, z_coor), logicDetectorModule, name, logicWorld, false, 0);
	}
	
	//***************************Detector Module : Crystal Scintillator
//	
	name = "Scintillator";
 	G4double sScintillatorX = 1.5*cm;
 	G4double sScintillatorY = 5*cm;
 	G4double sScintillatorZ = 5*cm;
//
	G4RotationMatrix* rm = new G4RotationMatrix();
	rm->rotateY(0*deg);
 	G4Box* solidScintillator = new G4Box(name, sScintillatorX, sScintillatorY, sScintillatorZ);
 	logicScintillator = new G4LogicalVolume(solidScintillator, Pstyrene_m, name);
 	physScintillator = new G4PVPlacement(rm, G4ThreeVector(-0.5*cm, 0., 0*cm), logicScintillator, name, logicDetectorModule, false, 0);
// 	
 	VisAttr_Scintillator = new G4VisAttributes(G4Color(0.0, 0.0, 1.0)); //blue
 	VisAttr_Scintillator->SetForceWireframe(true);
 	VisAttr_Scintillator->SetForceSolid(false);
 	logicScintillator->SetVisAttributes(VisAttr_Scintillator);
//	
	//****************************Detector Module : Silicon PM
 	name = "SilicaPhotoMultiplier";
 	G4double sSiPMX = 0.5*cm;
 	G4double sSiPMY = 5*cm;
 	G4double sSiPMZ = 5*cm;
// 	
 	G4Box* solidSiPM = new G4Box(name, sSiPMX, sSiPMY, sSiPMZ);
 	logicSiPM = new G4LogicalVolume(solidSiPM, Vacuum_m, name);
 	physSiPM = new G4PVPlacement(rm, G4ThreeVector(1.5*cm, 0., 0*cm), logicSiPM, name, logicDetectorModule, false, 0);	
//	
 	VisAttr_SiPM = new G4VisAttributes(G4Color(1.0, 0.0, 0.0)); //red
 	VisAttr_SiPM->SetForceWireframe(true);
 	VisAttr_SiPM->SetForceSolid(false);
 	logicSiPM->SetVisAttributes(VisAttr_SiPM); 
//	
}


//*****************************Construct Detector Modules #2 - made by Jason
void DetectorConstruction::ConstructDetectorModules2()
{
	//***************************Detector Module : Basis
	G4String name = "DetectorModule";
	G4double sDetectorModuleX = 2*cm;
	G4double sDetectorModuleY = 5*cm;
	G4double sDetectorModuleZ = 5*cm;
	G4double posX;
	G4double posY;
	G4double posZ;
	
	G4Box* solidDetectorModule = new G4Box(name, sDetectorModuleX, sDetectorModuleY, sDetectorModuleZ);
// 	G4RotationMatrix* rotationMatrix[3];
	
// 	physDetectorModule[0] = new G4PVPlacement(0, G4ThreeVector(0., 0., 35.*cm), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[0] = new G4RotationMatrix();
// 	rotationMatrix[0]->rotateY(-90*deg);
// 	physDetectorModule[1] = new G4PVPlacement(rotationMatrix[0], G4ThreeVector(35.*cm, 0., 0.), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[1] = new G4RotationMatrix();
// 	rotationMatrix[1]->rotateY(-180*deg);
// 	physDetectorModule[2] = new G4PVPlacement(rotationMatrix[1], G4ThreeVector(0., 0., -35.*cm), logicDetectorModule, name, logicWorld, false, 0);
// 	rotationMatrix[2] = new G4RotationMatrix();
// 	rotationMatrix[2]->rotateY(-270*deg);
// 	physDetectorModule[3] = new G4PVPlacement(rotationMatrix[2], G4ThreeVector(-35.*cm, 0., 0.), logicDetectorModule, name, logicWorld, false, 0);
	
// 	physDetector = new CylRepeat(40.*cm, G4ThreeVector(), "y", 100, solidDetectorModule, logicDetectorModule, logicWorld);
	const G4int n_modules = 10.; // NOW DEFINED IN HEADER
	G4double dphi = ((G4double)360./n_modules)*deg;
	G4double x_coor, z_coor;
	G4double Radius = 40.*cm;
	G4double phi;
	

	
	//***************************Detector Module : Crystal Scintillator
//	
	name = "Scintillator";
 	G4double sScintillatorX = 1.5*cm;
 	G4double sScintillatorY = 5*cm;
 	G4double sScintillatorZ = 5*cm;
//
	G4RotationMatrix* rm = new G4RotationMatrix();
	rm->rotateY(0*deg);
 	G4Box* solidScintillator = new G4Box(name, sScintillatorX, sScintillatorY, sScintillatorZ);
 	logicScintillator = new G4LogicalVolume(solidScintillator, Pstyrene_m, name);
//  	physScintillator = new G4PVPlacement(rm, G4ThreeVector(-0.5*cm, 0., 0*cm), logicScintillator, name, logicDetectorModule[counter].logVol, false, 0);
// 	
 	VisAttr_Scintillator = new G4VisAttributes(G4Color(0.0, 0.0, 1.0)); //blue
 	VisAttr_Scintillator->SetForceWireframe(true);
 	VisAttr_Scintillator->SetForceSolid(false);
 	logicScintillator->SetVisAttributes(VisAttr_Scintillator);
//	
	//****************************Detector Module : Silicon PM
 	name = "SilicaPhotoMultiplier";
 	G4double sSiPMX = 0.5*cm;
 	G4double sSiPMY = 5*cm;
 	G4double sSiPMZ = 5*cm;
// 	
 	G4Box* solidSiPM = new G4Box(name, sSiPMX, sSiPMY, sSiPMZ);
 	logicSiPM = new G4LogicalVolume(solidSiPM, Vacuum_m, name);
//  	physSiPM = new G4PVPlacement(rm, G4ThreeVector(1.5*cm, 0., 0*cm), logicSiPM, name, logicDetectorModule, false, 0);	
//	
 	VisAttr_SiPM = new G4VisAttributes(G4Color(1.0, 0.0, 0.0)); //red
 	VisAttr_SiPM->SetForceWireframe(true);
 	VisAttr_SiPM->SetForceSolid(false);
 	logicSiPM->SetVisAttributes(VisAttr_SiPM); 
//	
	
	modules logicDetectorModule[n_modules];
		//physSiPM2 declared in header
// 		physPMs physSiPM2[n_modules];
//	
	//*************rotation around the y-axis
	for (G4int counter = 0; counter < n_modules; counter++)
	{
		logicDetectorModule[counter].logVol = new G4LogicalVolume(solidDetectorModule, Vacuum_m, name);
		
		G4RotationMatrix* rm = new G4RotationMatrix();
		phi = counter*dphi;
//		
		x_coor = Radius*cos(phi);
		z_coor = Radius*sin(phi);
//
		G4cout << "  Rotation Angle " << counter << " is " << phi/deg << " " << dphi << G4endl;
//
		rm = new G4RotationMatrix();
		rm->rotateY(phi);
		new G4PVPlacement(rm, G4ThreeVector(x_coor, 0, z_coor), logicDetectorModule[counter].logVol, name, logicWorld, false, 0);
		
	 	physScint2[counter].physVol = new G4PVPlacement(0, G4ThreeVector(-0.5*cm, 0., 0*cm), logicScintillator, name, logicDetectorModule[counter].logVol, false, 0);
		physSiPM2[counter].physVol = new G4PVPlacement(0, G4ThreeVector(1.5*cm, 0., 0*cm), logicSiPM, name, logicDetectorModule[counter].logVol, false, 0);	
	}
	
}

void DetectorConstruction::ConstructOpticalSurface()
{
	G4String name = "Wrap";
//
	OpSurface = new G4OpticalSurface(name);
	new G4LogicalBorderSurface(name, physScintillator, physWorld, OpSurface);
// 	new G4LogicalBorderSurface("Wrap", physWorld, physScintillator, OpSurface);
// 	
	OpSurface->SetType(dielectric_dielectric);
	OpSurface->SetFinish(groundbackpainted);
	OpSurface->SetModel(unified);
	OpSurface->SetSigmaAlpha(0.1);
// 	
	const G4int NUM = 2;
	G4double ENERGYPHOTON[NUM] = {2.0*eV, 4.136*eV};
	G4double REFLECTIVITY[NUM] = {0.95, 0.95};
	G4double EFFICIENCY[NUM] = {0.0, 0.0};
// 	G4double SPECULARLOBE[NUM] = {0.3, 0.3};
// 	G4double SPECULARSPIKE[NUM] = {0.2, 0.2};
// 	G4double BACKSCATTERING[NUM] = {0.1, 0.1};
	G4double RINDEX[NUM] = {1.35, 1.40};
// 	
	G4MaterialPropertiesTable* MPT_OpSurface = new G4MaterialPropertiesTable();
	MPT_OpSurface->AddProperty("REFLECTIVITY", ENERGYPHOTON, REFLECTIVITY, NUM);
	MPT_OpSurface->AddProperty("EFFICIENCY", ENERGYPHOTON, EFFICIENCY, NUM);
	MPT_OpSurface->AddProperty("RINDEX", ENERGYPHOTON, RINDEX, NUM);
// 	MPT_OpSurface->AddProperty()
	OpSurface->SetMaterialPropertiesTable(MPT_OpSurface);
}







































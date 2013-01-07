#include <cmath>

#include "ScintDetectorConstruction.hh"
#include "ScintCalSD.hh"
#include "CylRepeat.hh"
#include "PMSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Color.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:PlasticMaterial(0),PMTMaterial(0),defaultMaterial(0),
solidWorld(0),logicWorld(0),physiWorld(0),
solidCalor(0),logicCalor(0),physiCalor(0),
solidPlastic(0),logicPlastic(0),physiPlastic(0),
solidPMT  (0),logicPMT  (0),physiPMT  (0)
{
	// default parameter values of the calorimeter
	PlasticHeight =  0.635*cm; // 1/4" = .635 cm
	PMTHeight = 3.*cm;
	Radii = 2.5 *cm; // radii of the plastic scintillator and pmt
// 	NumOfScints = 1000000;

	worldSize = PMTHeight + PlasticHeight;
	calorSize =	worldSize;

	SDman = 0; // 0 means we use it, anything else means we dont
	
	// materials - for an example use polystyrene as the plastic with an energy of 511
	DefineMaterials();
	PMTMaterial = G4Material::GetMaterial("Plastic");
	PlasticMaterial = G4Material::GetMaterial("pTP_Scint"); //lower case pTP_Scint
// 	ScintMaterial = G4Material::GetMaterial("Polystyrene");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{ return ConstructCalorimeter(); }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
	//	------------- Materials ------------- //THIS STUFF IS FROM N06 UNTIL OTHERWISE SPECIFIED
	
	G4double a, z, density;
	G4int nelements;
	G4String symbol;
	G4int ncomponents, fractionmass;;//, natoms;
	
	G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
	G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
	G4Element* H = new G4Element("H", "H", z=1., a=1.01*g/mole);
	G4Element* C = new G4Element("C", "C", z=6., a=12.01*g/mole);
	G4Element* Bi = new G4Element("Bi","Bi",z=83.,a=208.98  *g/mole);
	G4Element* Ge = new G4Element("Ge","Ge",z=32.,a=72.61  *g/mole);
	
	// Air
	G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
	Air->AddElement(N, 70.*perCent);
	Air->AddElement(O, 30.*perCent);
	
	// Water
	G4Material* Water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
	Water->AddElement(H, 2);
	Water->AddElement(O, 1);
	
	// Polystyrene -- from example/extended/optical/LXe/src/DetectorConstruction.cc
	const G4int NUMENTRIES = 3;
	G4double Energy[NUMENTRIES] = {1.00*eV,2.87*eV,5.0*eV};

//WHAT I NEED TO DO IS MAKE THE SCINTILLATOR A PURE PLASTIC DOPED WITH 1% PTP (AND LATER .1% bisMSB) AND THEN CHECK THE RESULTS
//So i need the refractive index of the plastic, its absobtion length, and PTP's + bisMSB's absorbtion and emission spectra
//I should be able to set the absorbtion and emission spectra based upon the WLS example from their fibers

	// Pure Plastic
	G4Material* Plastic = new G4Material("Plastic", density= 1.094*g/cm3, 3);
	Plastic->AddElement(C, 18);
	Plastic->AddElement(H, 11);
	Plastic->AddElement(O, 2);
	G4double PlasticRIndex[NUMENTRIES]={ 1.6, 1.6, 1.6}; //Value for polystyrene:  http://utwired.utexas.edu/lff/symposium/proceedingsArchive/pubs/Manuscripts/1998/1998-62-Keller.pdf
	G4double PlasticAbsorption1[NUMENTRIES]={16.*mm, 16.*mm, 16.*mm}; //Value for polystyrene:  http://utwired.utexas.edu/lff/symposium/proceedingsArchive/pubs/Manuscripts/1998/1998-62-Keller.pdf
	G4MaterialPropertiesTable* MPT_Plastic = new G4MaterialPropertiesTable();
	MPT_Plastic->AddProperty("RINDEX",Energy,PlasticRIndex,NUMENTRIES);
	MPT_Plastic->AddProperty("ABSLENGTH",Energy,PlasticAbsorption1,NUMENTRIES);
	Plastic->SetMaterialPropertiesTable(MPT_Plastic);
	
	// PTP   The size of a PTP molecule is .5nm x .25nm
	G4Material* PTP = new G4Material("PurePTP", density= 1.234*g/cm3, 2);
	PTP->AddElement(C, 18);
	PTP->AddElement(H, 14);
	const G4int PTP_NUMENTRIES = 6;
	G4double PTPRIndex[PTP_NUMENTRIES]={ 1.6, 1.6, 1.6, 1.6, 1.6, 1.6}; //Value for polystyrene:  http://utwired.utexas.edu/lff/symposium/proceedingsArchive/pubs/Manuscripts/1998/1998-62-Keller.pdf
	G4double ABS_Energy[PTP_NUMENTRIES] = {2.5*eV,3.9*eV, 4.6*eV, 5.0*eV, 5.4*eV,5.65*eV}; //http://omlc.ogi.edu/spectra/PhotochemCAD/html/p-terphenyl.html
	G4double EMS_Energy[PTP_NUMENTRIES] = {2.5*eV,2.67*eV,3.44*eV,3.9*eV,4.13*eV,5.65*eV}; //http://omlc.ogi.edu/spectra/PhotochemCAD/html/p-terphenyl.html
	G4double AbsPTP[PTP_NUMENTRIES]={0.*m, 0.*m, 9.*m, 5.6*m, 1.*m, 4*m};  //no idea if these are actually right but the trend is. http://omlc.ogi.edu/spectra/PhotochemCAD/html/p-terphenyl.html
	G4double EmissionPTP[PTP_NUMENTRIES]={0.35, 0.37, 0.63, 0.63, 0.4, 4.0};  //http://omlc.ogi.edu/spectra/PhotochemCAD/html/p-terphenyl.html
	G4MaterialPropertiesTable* MPT_PTP = new G4MaterialPropertiesTable();
	MPT_PTP->AddProperty("RINDEX",ABS_Energy,PTPRIndex,PTP_NUMENTRIES);
	MPT_PTP->AddProperty("WLSABSLENGTH",ABS_Energy,AbsPTP,PTP_NUMENTRIES);
	MPT_PTP->AddProperty("WLSCOMPONENT",EMS_Energy,EmissionPTP,PTP_NUMENTRIES);
	MPT_PTP->AddConstProperty("WLSTIMECONSTANT", 3.*ns);
	PTP->SetMaterialPropertiesTable(MPT_PTP);

	//bisMSB

	// BGO
	G4double BSO_Energy[NUMENTRIES] = {2.0*eV, 2.87*eV, 2.9*eV};
	G4Material* BGO = new G4Material("BGO", density= 7.13*g/cm3, 3);
	BGO->AddElement(Bi, 4);
	BGO->AddElement(Ge, 3);
	BGO->AddElement(O, 12);
	G4double RIndexBGO[NUMENTRIES]={ 2.15, 2.15, 2.15};
	G4double Absorption1[NUMENTRIES]={24.*cm, 24.*cm, 24.*cm}; //http://www.sciencedirect.com/science/article/pii/0167508784900930
	G4double ScintilFast[NUMENTRIES]={0.00, 0.00, 1.00}; //I don't know what this is or if it is right
	G4MaterialPropertiesTable* MPT_BGO = new G4MaterialPropertiesTable();
	MPT_BGO->AddProperty("RINDEX",BSO_Energy,RIndexBGO,NUMENTRIES);
	MPT_BGO->AddProperty("ABSLENGTH",BSO_Energy,Absorption1,NUMENTRIES);
	MPT_BGO->AddProperty("FASTCOMPONENT",BSO_Energy,ScintilFast,NUMENTRIES);
	// 	MPT_BGO->AddProperty("SLOWCOMPONENT",BSO_Energy, ScintilFast,NUMENTRIES);
	MPT_BGO->AddConstProperty("SCINTILLATIONYIELD",2000./MeV);
	MPT_BGO->AddConstProperty("RESOLUTIONSCALE",1.0); //creates a statistcal flucution, higher values broaden it; 0 = no fluctuation
	MPT_BGO->AddConstProperty("FASTTIMECONSTANT", 100.*ns); //Is this right???
// 	MPT_BGO->AddConstProperty("SLOWTIMECONSTANT", 100.*ns); // because the yield ratio is set at 1.0, there is no slow scintillation
// 	MPT_BGO->AddConstProperty("YIELDRATIO",1.0);  // all of the scintillation is fast (fast component)
	BGO->SetMaterialPropertiesTable(MPT_BGO);
	//BGO does not have a Birks Coefficient because it is not a plastic scintillator (and thus does not have a non-linear response)

	G4Material* Pstyrene = new G4Material("Polystyrene", density= 1.03*g/cm3, 2);
	Pstyrene->AddElement(C, 8);
	Pstyrene->AddElement(H, 8);
	G4double RIndexPstyrene[NUMENTRIES]={ 1.5, 1.5, 1.5};
	G4double PSAbsorption1[NUMENTRIES]={2.*cm, 2.*cm, 2.*cm};
	G4double PSScintilFast[NUMENTRIES]={0.00, 0.00, 1.00};
	G4MaterialPropertiesTable* MPTPStyrene = new G4MaterialPropertiesTable();
	MPTPStyrene->AddProperty("RINDEX",Energy,RIndexPstyrene,NUMENTRIES);
	MPTPStyrene->AddProperty("ABSLENGTH",Energy,PSAbsorption1,NUMENTRIES);
	MPTPStyrene->AddProperty("FASTCOMPONENT",Energy, PSScintilFast,NUMENTRIES);
	MPTPStyrene->AddConstProperty("SCINTILLATIONYIELD",10./keV);
	MPTPStyrene->AddConstProperty("RESOLUTIONSCALE",1.0);
	MPTPStyrene->AddConstProperty("FASTTIMECONSTANT", 10.*ns);
	Pstyrene->SetMaterialPropertiesTable(MPTPStyrene); // THIS IS THE LINE THAT ENABLES THE SCINILLATION!!
	// Set the Birks Constant for the Polystyrene scintillator
	Pstyrene->GetIonisation()->SetBirksConstant(0.126*mm/MeV);


	G4Material* pTPandbisMSBscint = new G4Material("pTP_Scint", density = 1.03*g/cm3, 3);
	pTPandbisMSBscint->AddElement(C, 18);
	pTPandbisMSBscint->AddElement(H, 11);
	pTPandbisMSBscint->AddElement(O, 2);
// 	pTPandbisMSBscint->AddElement(Bi, 4);
// 	pTPandbisMSBscint->AddElement(Ge, 3);
	const G4int pTP_NUM_ENTRIES = 10;
	G4double pTP_Energy[pTP_NUM_ENTRIES]     = {2.25*eV, 2.48*eV, 2.66*eV, 2.76*eV, 2.83*eV, 2.92*eV, 3.02*eV, 3.07*eV, 3.12*eV, 3.17*eV};
	G4double pTP_Energy_Abs[pTP_NUM_ENTRIES] = {2.25*eV, 2.79*eV, 2.86*eV, 2.92*eV, 3.00*eV, 3.05*eV, 3.12*eV, 3.22*eV, 3.25*eV, 3.54*eV};
	G4MaterialPropertiesTable* MPT_PTP_Scint = new G4MaterialPropertiesTable();
	G4double RIndexPTP[pTP_NUM_ENTRIES]={ 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57, 1.57}; //correct
	MPT_PTP_Scint->AddProperty("RINDEX",pTP_Energy,RIndexPTP,pTP_NUM_ENTRIES);
	G4double PTP_Absorption1[pTP_NUM_ENTRIES]={2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm, 2.*cm};
	MPT_PTP_Scint->AddProperty("ABSLENGTH",pTP_Energy,PTP_Absorption1,pTP_NUM_ENTRIES);
// 	G4double EmissionPTPScint[pTP_NUM_ENTRIES]={0.0, 0.0154, 0.0605, 0.1091, 0.1320, 0.1958, 0.1509, 0.1596, 0.1209, 0.0558};
// 	MPT_PTP_Scint->AddProperty("WLSCOMPONENT",pTP_Energy,EmissionPTPScint,pTP_NUM_ENTRIES);
// 	G4double Abs_PTP[pTP_NUM_ENTRIES]={0.907*cm, 0.3141*m, 0.4236*cm, 0.5520*cm, 1.0136*cm, 2.5643*cm, 6.2735*cm, 5.0101*cm, 9.1011*m, 0.2611*cm};
// 	MPT_PTP_Scint->AddProperty("WLSABSLENGTH",pTP_Energy_Abs,Abs_PTP,pTP_NUM_ENTRIES);
// 	MPT_PTP_Scint->AddConstProperty("WLSTIMECONSTANT", 3.*ns);
	G4double PTP_ScintilFast[3]={0.00, 0.00, 1.00};
	MPT_PTP_Scint->AddProperty("FASTCOMPONENT",pTP_Energy, PTP_ScintilFast,pTP_NUM_ENTRIES);
	MPT_PTP_Scint->AddConstProperty("SCINTILLATIONYIELD",10./keV);
	MPT_PTP_Scint->AddConstProperty("RESOLUTIONSCALE",1.0);
	MPT_PTP_Scint->AddConstProperty("FASTTIMECONSTANT", 10.*ns);
	pTPandbisMSBscint->SetMaterialPropertiesTable(MPT_PTP_Scint); // THIS IS THE LINE THAT ENABLES THE SCINILLATION!!
	// Set the Birks Constant for the Polystyrene scintillator
	pTPandbisMSBscint->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
	/*3.17	0.0558 //wavelength converted to energy
	3.12	0.1209
	3.07	0.1596
	3.02	0.1509
	2.92	0.1958
	2.83	0.1320
	2.76	0.1091
	2.66	0.0605
	2.48	0.0154
	2.25	0.0
	Emission:
	391.0000	7.06305 //raw data
	397.0000	60.2608
	403.5000	91.9188
	410.0000	84.8225
	424.5000	121.581
	438.5000	69.3481
	449.5000	50.6378
	465.5000	10.8477
	500.0000	-26.0101
	550.0000	-38.6195

	391.0000	0.0558 // +38.6195 and normalized
	397.0000	0.1209
	403.5000	0.1596
	410.0000	0.1509
	424.5000	0.1958
	438.5000	0.1320
	449.5000	0.1091
	465.5000	0.0605
	500.0000	0.0154
	550.0000	0.0*/
	/*Absorption:
	350.000000	0.074600 //translated right values by multiplying by 3.5, just a guess??
	382.000000	2.600300
	385.000000	1.431460
	398.000000	1.792440
	406.000000	0.732650
	413.000000	0.289590
	425.000000	0.157700
	433.000000	0.121020
	445.000000	0.089730
	550.000000	0.025910*/


	
	
	//Iron - properties are not correct
	/*G4Material* Iron = new G4Material("Iron", z=26, a=55.85*g/mole, density=7.874*g/cm3);
	// G4double Iron_Energy[NUMENTRIES]={1.0*eV,2.0*eV,20.14*eV};
	G4double Iron_RIND[NUMENTRIES]={1.49,1.49,1.49};
	G4double Iron_AbsLength[NUMENTRIES]={420.*cm,420.*cm,420.*cm};
	G4MaterialPropertiesTable *Iron_mt = new G4MaterialPropertiesTable();
	Iron_mt->AddProperty("ABSLENGTH",Energy,Iron_AbsLength,NUMENTRIES);
	Iron_mt->AddProperty("RINDEX", Energy, Iron_RIND,NUMENTRIES);
	Iron->SetMaterialPropertiesTable(Iron_mt);*/

	//Glass
	G4Material* Glass = new G4Material("Glass", density=1.032*g/cm3,2);
	Glass->AddElement(C,91.533*perCent);
	Glass->AddElement(H,8.467*perCent);
	G4double Glass_RIND[NUMENTRIES]={1.49,1.49,1.49};
	G4double Glass_AbsLength[NUMENTRIES]={420.*cm,420.*cm,420.*cm};
	G4MaterialPropertiesTable *Glass_mt = new G4MaterialPropertiesTable();
	Glass_mt->AddProperty("ABSLENGTH",Energy,Glass_AbsLength,NUMENTRIES);
	Glass_mt->AddProperty("RINDEX",Energy,Glass_RIND,NUMENTRIES);
	Glass->SetMaterialPropertiesTable(Glass_mt);
	
	G4Material* Vacuum = new G4Material("Vacuum", z=1., a=1.01*g/mole,density= universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);
	// G4double Vacuum_Energy[NUMENTRIES]={1.0*eV,2.0*eV,20.14*eV};
	G4double Vacuum_RIND[NUMENTRIES]={1.,1.,1.};
	G4MaterialPropertiesTable *Vacuum_mt = new G4MaterialPropertiesTable();
	Vacuum_mt->AddProperty("RINDEX", Energy, Vacuum_RIND,NUMENTRIES);
	Vacuum->SetMaterialPropertiesTable(Vacuum_mt);

	
	G4Material* DopedPlastic = new G4Material("DopedPlastic"  , density= 1.4*mg/cm3, ncomponents=2);
	DopedPlastic->AddMaterial(Plastic, fractionmass=0.95);
	DopedPlastic->AddMaterial(BGO, fractionmass=0.05);



	
	// print table
	// G4cout << *(G4Material::GetMaterialTable()) << G4endl;
	
	//default materials of the World
	defaultMaterial  = Vacuum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{	
	// Clean old geometry, if any
	//
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();
	
	// World
	solidWorld = new G4Box("World",				//its name
												 worldSize,Radii*2,Radii*2);	//its size
	logicWorld = new G4LogicalVolume(solidWorld,		//its solid
																	 defaultMaterial,	//its material
																	"World");		//its name
	physiWorld = new G4PVPlacement(0,			//no rotation
																 G4ThreeVector(),	//at (0,0,0)
																 logicWorld,		//its logical volume
																"World",		//its name
																0,			//its mother  volume
																false,			//no boolean operation
																0);			//copy number
	
	// Calorimeter
	solidCalor=0; logicCalor=0; physiCalor=0;
	
	solidCalor = new G4Box("Calorimeter",		//its name
												 calorSize,Radii*2,Radii*2);//size
	logicCalor = new G4LogicalVolume(solidCalor,	//its solid
																	 defaultMaterial,	//its material
																	"Calorimeter");	//its name
	physiCalor = new G4PVPlacement(0,			//no rotation
																 G4ThreeVector(),	//at (0,0,0)
																 logicCalor,	//its logical volume
																"Calorimeter",	//its name
																logicWorld,	//its mother  volume
																false,		//no boolean operation
																0);		//copy number
	
	G4RotationMatrix* rm = new G4RotationMatrix();
	rm->rotateY(90. *deg);
	
	//  Plastic
	solidPlastic = 0; logicPlastic=0; physiPlastic=0;
	// 		G4Tubs* tracker_tube = new G4Tubs("tracker_tube", innerRadiusOfTheTube, outerRadiusOfTheTube, hightOfTheTube, startAngleOfTheTube, spanningAngleOfTheTube);
	solidPlastic = new G4Tubs("Plastic", 0, Radii, PlasticHeight, 0, 360);
	logicPlastic = new G4LogicalVolume(solidPlastic, GetPlasticMaterial(),"Plastic");
	physiPlastic = new G4PVPlacement(rm,G4ThreeVector(-PMTHeight,0,0),logicPlastic,"Plastic",logicCalor,false,0);
	G4VisAttributes* PlasticColor	= new G4VisAttributes(G4Color(1.0,0.0,0.0)); //Red
	logicPlastic->SetVisAttributes(PlasticColor);

	 /*// Doping volumes - scintillating material
	char scint_name[256];
	G4double x_coor, y_coor, z_coor, distance;
	G4RotationMatrix* rmscint = new G4RotationMatrix();
	solidScint = 0; logicScint=0; physiScint=0;
	solidScint = new G4Tubs("Scintillator", 0 *nm , 0.25*mm, 0.5*mm ,0, 360);
	logicScint = new G4LogicalVolume(solidScint, GetScintMaterial(), "Scintillator");
	G4VisAttributes* ScintColor	= new G4VisAttributes(G4Color(1.0,0.0,0.0)); //Red
	logicScint->SetVisAttributes(ScintColor);
	G4cout << "******** Printing scintillator coordinates ***********" << G4endl;
	G4int i = 0;
	while (i < NumOfScints){
// 	for(G4int i = 0; i < NumOfScints; i++){
		sprintf(scint_name,"Scintillator_%d",i);
		rmscint->rotateX(G4UniformRand()*360 *deg);
		rmscint->rotateY(G4UniformRand()*360 *deg);
		rmscint->rotateZ(G4UniformRand()*360 *deg); //---------------------
		x_coor = (2*G4UniformRand()-1)*Radii;
		y_coor = pow( pow(Radii,2)-pow(x_coor,2) , 0.5)*(2*G4UniformRand()-1);
		z_coor = G4UniformRand()*.25 *nm;
		distance = pow(pow(x_coor,2)+pow(y_coor,2)/100+pow(z_coor,2)/100,0.5)*cm + 0.5*nm;
// 		G4cout << "Trying to put scintillator at (" << x_coor/cm << "," << y_coor/cm << "," << z_coor/cm << ")." <<G4endl;
// 		G4cout << "  Sqrt of " << pow(x_coor,2) << "+" << pow(y_coor,2)<< "+" << pow(z_coor,2) << " is " << pow(pow(x_coor,2)+pow(y_coor,2)+pow(z_coor,2),0.5)*cm << G4endl;
// 		G4cout << "  " << Radii << " >? " << distance << G4endl;
		if( Radii > distance ) //Checking algorithm
		{
// 			G4cout << "Trying to put " << scint_name << " at (" << x_coor/cm << "," << y_coor/cm << "," << z_coor/nm << ")." << "   Radius: " << distance/cm << G4endl;
			new G4PVPlacement(0,
												G4ThreeVector(x_coor,y_coor,z_coor),
												logicScint,
												scint_name,
												logicPlastic, false, 0);
			i++;
		}
	}*/
	

	
	//  PMT
	solidPMT=0; logicPMT=0; physiPMT=0;
	// 		G4Tubs* tracker_tube = new G4Tubs("tracker_tube", innerRadiusOfTheTube, outerRadiusOfTheTube, hightOfTheTube, startAngleOfTheTube, spanningAngleOfTheTube);
	solidPMT = new G4Tubs("PMT", 0, Radii, PMTHeight, 0, 360);
	logicPMT = new G4LogicalVolume(solidPMT, GetPMTMaterial(),"PMT");
	physiPMT = new G4PVPlacement(rm,G4ThreeVector(PlasticHeight,0,0),logicPMT,"PMT",logicCalor,false,0);
	G4VisAttributes* pmtColor	= new G4VisAttributes(G4Color(0.0,0.0,1.0)); //Blue
	logicPMT->SetVisAttributes(pmtColor);
	
	//Sensitive Detector
	if(SDman == 0)  //if we need to set the SDManager up, then let's do it
    {
			SDman = G4SDManager::GetSDMpointer();  //get a pointer
			PMSD* sensitivePMT = new PMSD("my_PMT_SD", physiPMT);
			SDman->AddNewDetector( sensitivePMT );
			logicPMT->SetSensitiveDetector(sensitivePMT);
		}
		
	//Surface properties for the WLS slab
	G4OpticalSurface* ScintWrap = new G4OpticalSurface("ScintWrap");
	//type, finish model
	/*ScintWrap->SetType(dielectric_LUT);
	 S cintWrap->SetFinish(polished*tyvekair);
	 ScintWrap->SetModel(LUT);*/
	ScintWrap->SetType(dielectric_metal);
	ScintWrap->SetFinish(groundbackpainted);
	ScintWrap->SetModel(unified);
	new G4LogicalBorderSurface("ScintWrap", physiPlastic,physiCalor,ScintWrap);

	
	const G4int NUM = 2;
	
	G4double pp[NUM] = {1.0*eV, 7.0*eV};
	G4double reflectivity[NUM] = {0.95, 0.95};
	G4double efficiency[NUM] = {0.05, 0.05};
	
	G4MaterialPropertiesTable* ScintWrapProperty
	= new G4MaterialPropertiesTable();

	//RINDEX, SPECULARLOBECONSTANT, BACKSCATTERCONSTANT, REFLECTIVITY, EFFICIENCY
	ScintWrapProperty->AddProperty("REFLECTIVITY",pp,reflectivity,NUM);
	ScintWrapProperty->AddProperty("EFFICIENCY",pp,efficiency,NUM);
	ScintWrap->SetMaterialPropertiesTable(ScintWrapProperty);



	logicWorld->SetVisAttributes(G4VisAttributes::Invisible);
	//always return the physical World

	G4cout << "PMT physical volume #: " << physiPMT << G4endl
	<< "Scintillator physical volume #: " << physiScint << G4endl;

	
	return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
	G4RunManager::GetRunManager()->DefineWorldVolume(ConstructCalorimeter());
}

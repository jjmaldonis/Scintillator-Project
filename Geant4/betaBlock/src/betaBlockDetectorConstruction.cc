#include "betaBlockDetectorConstruction.hh"
#include "betaBlockTrackerSD.hh"
#include "betaBlockDetectorSD.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"


#include "G4Box.hh"
#include "G4Tubs.hh"
//#include "G4Trap.hh"
//#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
//#include "G4AssemblyVolume.hh"
#include "G4SDManager.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
//
#include "G4LogicalBorderSurface.hh"
//#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"


betaBlockDetectorConstruction::betaBlockDetectorConstruction(double thick)
{
	//defaults for various parameters
	detThickness = thick*cm;  

	SDman = 0;
	createMats();
	
}

betaBlockDetectorConstruction::~betaBlockDetectorConstruction()
{
}


G4VPhysicalVolume* betaBlockDetectorConstruction::Construct()
{
	return ConstructCalo();
}


G4VPhysicalVolume* betaBlockDetectorConstruction::ConstructCalo()
{
	// Clean old geometry, if any
	//
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	// The experimental Hall

	expHall_box = new G4Box("World",1*m,1*m,3*m);

	expHall_log = new G4LogicalVolume(expHall_box,air,"World",0,0,0);
	expHall_log->SetVisAttributes(G4VisAttributes::Invisible);

	expHall_phys = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

	//Scint
	G4Tubs* scintTub = new G4Tubs("Scint Disc",0*cm,13.5*mm,detThickness/2.0,0.*deg,360.*deg);
	G4LogicalVolume* scintLog = new G4LogicalVolume(scintTub,scint,"Scint LV",0,0,0);  //create a disc for the LV

	//Detector
	G4Tubs* detTub = new G4Tubs("Detector Glass",0*cm,13.5*mm,0.1*cm,0.*deg,360.*deg);
	G4LogicalVolume* detLog = new G4LogicalVolume(detTub,glass,"Detector LV",0,0,0);  //create a disc for the LV

	//Optical surface for scintillator
	G4OpticalSurface* OpMirrorSurface = new G4OpticalSurface("ScintSurface");
		
	OpMirrorSurface->SetType(dielectric_LUT);
	OpMirrorSurface->SetModel(LUT);
	OpMirrorSurface->SetFinish(groundtioair);

	betaBlockTrackerSD * scintTracker;
	betaBlockDetectorSD * detTracker;

	//Sensitive Detectors
	G4String trackerSDname;
	if(SDman == 0)  //if we need to set the SDManager up, then let's do it
	{
		SDman = G4SDManager::GetSDMpointer();  //get a pointer
		//SD
		trackerSDname = "betaBlock/Scint";
		scintTracker = new betaBlockTrackerSD( trackerSDname,false);
		scintLog->SetSensitiveDetector(scintTracker); //set scintillator as SD
		trackerSDname = "betaBlock/Det";
		detTracker = new betaBlockDetectorSD( trackerSDname,false);
		detLog->SetSensitiveDetector(detTracker); //set window as SD

		SDman->AddNewDetector( scintTracker );  //add it to the manager's list
		SDman->AddNewDetector( detTracker );  //add it to the manager's list
	}
	
	G4RotationMatrix* sdRot = new G4RotationMatrix();
	G4ThreeVector layerVec;

	G4PVPlacement* scintPhys = new G4PVPlacement(sdRot,layerVec,scintLog,"Scint PV", expHall_log,false,0,true);

	layerVec.setZ(-detThickness/2 - 0.1*cm);

	G4PVPlacement* detPhys = new G4PVPlacement(sdRot,layerVec,detLog,"Detector PV", expHall_log,false,0,true);

	//Attach Optical Border to PV
	G4LogicalBorderSurface * scintSurface = new G4LogicalBorderSurface("ScintSurface",scintPhys,expHall_phys,OpMirrorSurface);


	return expHall_phys;  //even God needs to put away his toys

}



//Create Materials used in the sim
 void betaBlockDetectorConstruction::createMats()
{
	G4NistManager* man = G4NistManager::Instance();  //make a manager to grab basic properties from the NIST list

	/**********************************
	**              Air              **
	***********************************/
	G4cout << "Making Air...";
	air = man->FindOrBuildMaterial("G4_AIR");  //air=air

	double PhotonEnergy[2] =
	{	1.000*eV, 5.642776909*eV };

	double nAir[2] =
	{	1.00, 1.00 };  //refractive index of air,  pretty accurate

	G4MaterialPropertiesTable* airTable = new G4MaterialPropertiesTable();  //more table jazz
	airTable->AddProperty("RINDEX", PhotonEnergy, nAir, 2);

	air->SetMaterialPropertiesTable(airTable);

	G4cout<< " ok!" <<G4endl;

	/**********************************
	**             Glass             **
	***********************************/
	G4cout << "Making Glass...";
	glass = man->FindOrBuildMaterial("G4_Pyrex_Glass");  //air=air

	double nGlass[2] =
	{	1.5, 1.5 };  //refractive index of air,  pretty accurate

	G4MaterialPropertiesTable* glassTable = new G4MaterialPropertiesTable();  //more table jazz
	glassTable->AddProperty("RINDEX", PhotonEnergy, nGlass, 2);

	glass->SetMaterialPropertiesTable(glassTable);

	G4cout<< " ok!" <<G4endl;

	/**********************************
	**             PDMS              **
	***********************************/
	G4cout << "Making PDMS...";

	double a;

	a = 1.01*g/mole;
	G4Element* elH  = new G4Element("Hydrogen", "H", 1., a);

	a = 16.00*g/mole;
	G4Element* elO  = new G4Element("Oxygen", "O", 8., a);

	a = 12.0107*g/mole;
	G4Element* elC  = new G4Element("Carbon", "C", 6., a);

	a = 28.086*g/mole;
	G4Element* elSi  = new G4Element("Silicon", "Si", 14., a);

	a = 164.086*g/mole;
	G4Element* elPb  = new G4Element("Plumbum", "Pb", 82., a);


	double density = 1.03*g/cm3;
	pdms = new G4Material("PDMS",density,4);
	pdms->AddElement(elH,6);
	pdms->AddElement(elC,2);
	pdms->AddElement(elO,1);
	pdms->AddElement(elSi,1);
	//pdms->AddElement(elPb,6);  //wrong, fix it

	double PhotonEnPDMS[2] =
	{	1.000*eV, 5.642776909*eV };

	double nPDMS[2] =
	{	1.406, 1.406 };

	G4MaterialPropertiesTable* pdmsTable = new G4MaterialPropertiesTable();  //more table jazz
	pdmsTable->AddProperty("RINDEX", PhotonEnPDMS, nPDMS, 2);

	pdms->SetMaterialPropertiesTable(pdmsTable);

	G4cout<< " ok!" << G4endl;


	/**********************************
	**             Vacuum            **
	***********************************/
	G4cout << "Making Vacuum...";

	vacuum = man->FindOrBuildMaterial("G4_Galactic");

	G4cout<< " ok!" << G4endl;

	/**********************************
	**              pTP              **
	***********************************/
	G4cout << "Making pTP...";
	pTP = man->FindOrBuildMaterial("G4_TERPHENYL");  //pTP = p-terphenyl

	#include "ptpProperties.hh"

	G4MaterialPropertiesTable* ptpMPT = new G4MaterialPropertiesTable();
	ptpMPT->AddProperty("RINDEX", PPrIndex, nPTP, nNum);
	ptpMPT->AddProperty("ABSLENGTH",PPabs, absLen, absNum);
	//ptpMPT->AddProperty("WLSCOMPONENT", PPemission, emissionSpec, emNum);
	ptpMPT->AddProperty("FASTCOMPONENT", PPemission, emissionSpec, emNum);

	ptpMPT->AddConstProperty("SCINTILLATIONYIELD", ppScintYield);
	ptpMPT->AddConstProperty("RESOLUTIONSCALE", 2.012);
	ptpMPT->AddConstProperty("FASTTIMECONSTANT", pTPtau);
	//ptpMPT->AddConstProperty("WLSTIMECONSTANT", pTPtau);
	//pTP->SetMaterialPropertiesTable(ptpMPT);  //add wls and scint to ptp

	G4cout<< " ok!" <<G4endl;
	/**********************************
	**          Scintillator         **
	***********************************/
	G4cout << "Making Scintillator...";

	density = 1.03*g/cm3;
	scint = new G4Material("Scint",density,2);
	scint->AddMaterial(pdms,99*perCent);
	scint->AddMaterial(pTP,1*perCent);
	scint->SetMaterialPropertiesTable(ptpMPT);

	G4cout<< " ok!" << G4endl;


}
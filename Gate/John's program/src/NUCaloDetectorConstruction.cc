#include "NUCaloDetectorConstruction.hh"
#include "NUCaloTrackerSD.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"


#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"
#include "G4SDManager.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"


NUCaloDetectorConstruction::NUCaloDetectorConstruction()
{
	plateThickness = 2*cm;
	SDman = 0;
	createMats();
	
}

NUCaloDetectorConstruction::~NUCaloDetectorConstruction()
{
}

//Construct Volumes and interfaces and all that

G4VPhysicalVolume* NUCaloDetectorConstruction::Construct()
{
	return ConstructCalo();
}


G4VPhysicalVolume* NUCaloDetectorConstruction::ConstructCalo()
{
	// Clean old geometry, if any
	//
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	const int numlayers = 18;

	// The experimental Hall

	expHall_box = new G4Box("World",0.5*m,0.5*m,1.5*m);

	expHall_log = new G4LogicalVolume(expHall_box,air,"World",0,0,0);
	expHall_log->SetVisAttributes(G4VisAttributes::Invisible);

	expHall_phys = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

	sdStruct sds[numlayers];

	//Sensitive Detectors
	if(SDman == 0)  //if we need to set the SDManager up, then let's do it
	{
		SDman = G4SDManager::GetSDMpointer();  //get a pointer
		for(int j = 0; j < numlayers; j++)
		{
			char num[5];
			sprintf(num,"%d",j+1);
			G4String ly_num = num;  //itoa(j+1,num,10);
			G4String trackerSDname = "NUCalo/SD_Layer" + ly_num;
			sds[j].sdTracker = new NUCaloTrackerSD( trackerSDname, j+1 );  //name and create the trackers
			SDman->AddNewDetector( sds[j].sdTracker );  //add it to the manager's list
		}
	}
	
	G4RotationMatrix* sdRot = new G4RotationMatrix();
	G4ThreeVector layerVec;

	int ly_cnt = 0;

	double z_offset = 0;

	plateThickness /= 2;
	float last_thick = plateThickness;
	G4Tubs* absDisc;

	G4Tubs* sdDisc = new G4Tubs("SD Disc",0*cm,30*cm,0.5*cm/2.0,0,twopi);

	for(int j = 1; j <= 3; j++)
	{
		
		absDisc = new G4Tubs("Abs Disc",0*cm,30*cm,plateThickness/2.0,0,twopi);

		for(int ly_cnt = (j-1)*numlayers/3;ly_cnt < j*numlayers/3; ly_cnt++)  //first batch
		{
			z_offset -= (0.5*cm/2 + plateThickness/2);  //Z offset for the width of a layer

			layerVec.setZ(z_offset);  //and to the layer placement as well

			absLog = new G4LogicalVolume(absDisc,pb,"Abs Disc",0,0,0);  //create a disc for the LV

			absPhys = new G4PVPlacement(sdRot,layerVec,absLog,"Abs Phys", expHall_log,false,0,true); 

			sds[ly_cnt].sdLog = new G4LogicalVolume(sdDisc,sensMat,"SD Disc",0,0,0);  //create a disc for the LV

			z_offset -= (plateThickness/2 + 0.5*cm/2);
			layerVec.setZ(z_offset);
			sdPhys = new G4PVPlacement(sdRot,layerVec,sds[ly_cnt].sdLog,"SD", expHall_log,false,0,true);  
			
			//Make the names again and attach an SD to an LV
			char num[5];
			sprintf(num,"%d",ly_cnt+1); 
			G4String ly_num = num; //itoa(i+1,num,10);
			G4String trackerSDname = "NUCalo/SD_Layer" + ly_num;
			sds[ly_cnt].sdLog->SetSensitiveDetector( SDman->FindSensitiveDetector(trackerSDname) );

			last_thick = plateThickness;
		}
		plateThickness *= 2;
		
	}


	return expHall_phys;  //even God needs to put away his toys

}



//Create Materials used in the sim
 void NUCaloDetectorConstruction::createMats()
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
	{	1.00, 1.00 };  //refractive of index of air,  pretty accurate

	G4MaterialPropertiesTable* airTable = new G4MaterialPropertiesTable();  //more table jazz
	airTable->AddProperty("RINDEX", PhotonEnergy, nAir, 2);

	air->SetMaterialPropertiesTable(airTable);

	G4cout<< " ok!" <<G4endl;


	/**********************************
	**              Plumbum          **
	***********************************/
	G4cout << "Making Lead...";
	pb = man->FindOrBuildMaterial("G4_Pb");

	G4cout<< " ok!" << G4endl;

	/**********************************
	**       Sensitive Material      **
	***********************************/
	G4cout << "Making Sensitive Material...";
	sensMat = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

	G4cout<< " ok!" << G4endl;

}
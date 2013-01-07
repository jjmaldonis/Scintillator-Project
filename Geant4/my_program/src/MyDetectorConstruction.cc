#include "MyDetectorConstruction.hh"
#include "MyCalSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:AbsorberMaterial(0),DetectorMaterial(0),defaultMaterial(0),
 solidWorld(0),logicWorld(0),physiWorld(0),
 solidCalor(0),logicCalor(0),physiCalor(0),
 solidLayer(0),logicLayer(0),physiLayer(0),
 solidAbsorber(0),logicAbsorber(0),physiAbsorber(0),
 solidDetector (0),logicDetector (0),physiDetector (0)
{
  // default parameter values of the calorimeter
  AbsorberThickness = 20.*mm;
  DetectorThickness =  5.*mm;
  NbOfLayers        = 20; //If you change this you must also change the array that corresponds to the number of sensitive detectors
  CalorSizeYZ       = 20.*cm;
  SDman = 0; // 0 means we use it, anything else means we dont
  ComputeCalorParameters();
  
  // materials
  DefineMaterials();
  SetAbsorberMaterial("Iron");
  SetDetectorMaterial("Polystyrene");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
  //delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
 //This function illustrates the possible ways to define materials
 
G4String symbol;             //a=mass of a mole;
G4double a, z, density;      //z=mean number of protons;  
G4int ncomponents, natoms;

// define Elements
G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);

// define simple materials
new G4Material("Iron", z=26, a=55.85*g/mole, density=7.874*g/cm3);

// define a material from elements.   case 1: chemical molecule
G4Material* Polystyrene = 
new G4Material("Polystyrene", density=1.0320*g/cm3, ncomponents=2);
Polystyrene->AddElement(H, natoms=8);
Polystyrene->AddElement(C, natoms=8);

// examples of vacuum
G4Material* Vacuum =
new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                           kStateGas, 2.73*kelvin, 3.e-18*pascal);
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

  // complete the Calor parameters definition
  ComputeCalorParameters();
   
  // World
  solidWorld = new G4Box("World",				//its name
                   WorldSizeX/2,WorldSizeYZ/2,WorldSizeYZ/2);	//its size

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
  solidLayer=0; logicLayer=0; physiLayer=0;
  
    solidCalor = new G4Box("Calorimeter",		//its name
    		       CalorThickness/2,CalorSizeYZ/2,CalorSizeYZ/2);//size
    			     
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
  
  //Sensitive Detectors
  sdStruct sds[20];
    if(SDman == 0)  //if we need to set the SDManager up, then let's do it
    {
	    SDman = G4SDManager::GetSDMpointer();  //get a pointer
	    for(G4int j = 0; j < NbOfLayers; j++)
	    {
		    char num[5];
		    sprintf(num,"%d",j+1);
		    G4String ly_num = num;  //itoa(j+1,num,10);
		    G4String SDname = "MyDet/SD_Layer" + ly_num;
		    sds[j].sdTracker = new MyCalSD( SDname, j+1 );  //name and create the trackers
		    SDman->AddNewDetector( sds[j].sdTracker );  //add it to the manager's list
	    }
    }

	G4double x_offset = AbsorberThickness/2;

	solidAbsorber = new G4Box("Absorber",AbsorberThickness/2,CalorSizeYZ/2,CalorSizeYZ/2); 
	solidDetector = new G4Box("Detector",DetectorThickness/2,CalorSizeYZ/2,CalorSizeYZ/2);

	for(G4int ly_cnt = 0;ly_cnt < NbOfLayers; ly_cnt++)
	{
	    //Absorber:
	    if(ly_cnt != 0)
	      x_offset += (AbsorberThickness/2 + DetectorThickness/2);  //Fix x_offset

	    logicAbsorber = new G4LogicalVolume(solidAbsorber,    //creating a LV, its solid
		AbsorberMaterial, //its material
		AbsorberMaterial->GetName()); //name

	    physiAbsorber = new G4PVPlacement(0,        //no rotation
		G4ThreeVector(-CalorThickness/2 + x_offset,0.,0.),  //its position
		logicAbsorber,     //its logical volume
		AbsorberMaterial->GetName(), //its name
		logicCalor,        //its mother
		false,             //no boulean operat
		0,		   //copy number???
		true);		   // ???

	    G4VisAttributes* absLayer_logVisAtt
		= new G4VisAttributes(G4Colour(0.0,1.0,0.0)); //Green
	    logicAbsorber->SetVisAttributes(absLayer_logVisAtt);

	    //Detector:
	    x_offset += (AbsorberThickness/2 + DetectorThickness/2);  //Fix x_offset

	    sds[ly_cnt].sdLog = new G4LogicalVolume(solidDetector,    //creating a LV, its solid
		DetectorMaterial,
		"SD Box");

	    physiDetector = new G4PVPlacement(0,
		G4ThreeVector(-CalorThickness/2 + x_offset,0.,0.),
		sds[ly_cnt].sdLog,
		"SD",
		logicCalor,
		false,
		0,
		true);
	    
	    G4VisAttributes* detLayer_logVisAtt
		= new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //Red
	    sds[ly_cnt].sdLog->SetVisAttributes(detLayer_logVisAtt);
	    
	    //Make the names again and attach an SD to an LV
	    char num[5];
	    sprintf(num,"%d",ly_cnt+1); 
	    G4String ly_num = num; //itoa(i+1,num,10);
	    G4String SDname = "MyDet/SD_Layer" + ly_num;
	    sds[ly_cnt].sdLog->SetSensitiveDetector( SDman->FindSensitiveDetector(SDname) );
	}
        

  PrintCalorParameters();     
  
  // Visualization attributes
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  logicCalor->SetVisAttributes(simpleBoxVisAtt);


  //always return the physical World
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintCalorParameters()
{
  G4cout << "\n------------------------------------------------------------"
         << "\n---> The calorimeter is " << NbOfLayers << " layers of: [ "
         << AbsorberThickness/mm << "mm of " << AbsorberMaterial->GetName() 
         << " + "
         << DetectorThickness/mm << "mm of " << DetectorMaterial->GetName() << " ] " 
         << "\n------------------------------------------------------------\n";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) AbsorberMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) DetectorMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberThickness(G4double val)
{
  // change Absorber thickness and recompute the calorimeter parameters
  AbsorberThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorThickness(G4double val)
{
  // change Detector thickness and recompute the calorimeter parameters
  DetectorThickness = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetCalorSizeYZ(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  CalorSizeYZ = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetNbOfLayers(G4int val)
{
  NbOfLayers = val;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructCalorimeter());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......






/*

  // Layer
      solidLayer = new G4Box("Layer",			//its name
                       LayerThickness/2,CalorSizeYZ/2,CalorSizeYZ/2); //size
                       
      logicLayer = new G4LogicalVolume(solidLayer,	//its solid
                                       defaultMaterial,	//its material
                                       "Layer");	//its name
      if (NbOfLayers > 1)                                      
        physiLayer = new G4PVReplica("Layer",		//its name
      				     logicLayer,	//its logical volume
      				     logicCalor,	//its mother
                                     kXAxis,		//axis of replication
                                     NbOfLayers,	//number of replica
                                     LayerThickness);	//witdth of replica
      else
        physiLayer = new G4PVPlacement(0,		//no rotation
                                     G4ThreeVector(),	//at (0,0,0)
                                     logicLayer,	//its logical volume				     
                                     "Layer",		//its name
                                     logicCalor,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     
    }                                   
  
  // Absorber (iron)
  solidAbsorber=0; logicAbsorber=0; physiAbsorber=0;  
  
  if (AbsorberThickness > 0.) 
    { solidAbsorber = new G4Box("Absorber",		//its name
                          AbsorberThickness/2,CalorSizeYZ/2,CalorSizeYZ/2); 
                          
      logicAbsorber = new G4LogicalVolume(solidAbsorber,    //its solid
      			                  AbsorberMaterial, //its material
      			                  AbsorberMaterial->GetName()); //name
      			                  
      physiAbsorber = new G4PVPlacement(0,		   //no rotation
      		    G4ThreeVector(-DetectorThickness/2,0.,0.),  //its position
                                        logicAbsorber,     //its logical volume		    
                                        AbsorberMaterial->GetName(), //its name
                                        logicLayer,        //its mother
                                        false,             //no boulean operat
                                        0);                //copy number
                                        
  G4VisAttributes* absLayer_logVisAtt
    = new G4VisAttributes(G4Colour(0.0,1.0,0.0)); //Green
  logicAbsorber->SetVisAttributes(absLayer_logVisAtt);
    }
  
  // Detector (polystyrene)
  solidDetector=0; logicDetector=0; physiDetector=0; 
  
  if (DetectorThickness > 0.)
    { solidDetector = new G4Box("Detector",
    			   DetectorThickness/2,CalorSizeYZ/2,CalorSizeYZ/2);
    			   
      logicDetector = new G4LogicalVolume(solidDetector,
      				     DetectorMaterial,
      				     DetectorMaterial->GetName());
      				     
      
      physiDetector = new G4PVPlacement(0,                      //no rotation
               G4ThreeVector(AbsorberThickness/2,0.,0.),   //its position
                                   logicDetector,               //its logical volume	       
                                   DetectorMaterial->GetName(), //its name
                                   logicLayer,             //its mother
                                   false,                  //no boulean operat
                                   0);                     //copy number
      
   G4VisAttributes* detLayer_logVisAtt
    = new G4VisAttributes(G4Colour(1.0,0.0,0.0)); //Red
  logicDetector->SetVisAttributes(detLayer_logVisAtt);
      }
  

  
  
  
  
// // sensitive detector
//       G4SDManager* SDman = G4SDManager::GetSDMpointer();
//       MyCalSD* pSensitivePart = new MyCalSD("/mydet/detector");
//       SDman->AddNewDetector(pSensitivePart);
//       logicDetector->SetSensitiveDetector(pSensitivePart);
*/






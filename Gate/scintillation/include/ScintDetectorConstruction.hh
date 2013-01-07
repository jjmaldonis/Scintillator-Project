#ifndef ScintDetectorConstruction_h
#define ScintDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4SDManager;
class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class PMSD;
//class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:

     void SetAbsorberMaterial (G4String);     
     void SetAbsorberThickness(G4double);     

     void SetDetectorMaterial (G4String);     
     void SetDetectorThickness(G4double);
     
     G4VPhysicalVolume* Construct();

     void UpdateGeometry();

		 G4double GetWorldSize() {return worldSize;};

  public:

		 G4Material* GetPlasticMaterial()  {return PlasticMaterial;};
		 G4Material* GetPMTMaterial()    {return PMTMaterial;};
		 G4Material* GetScintMaterial()    {return ScintMaterial;};

		 G4VPhysicalVolume* GetPlasticPV() {return physiPlastic;};
		 G4VPhysicalVolume* GetPMTPV() {return physiPMT;};
		 
     
     //Sensitive Detector Mgr, declared here so that it can be initialized
     G4SDManager* SDman;
                 
  private:

		 G4double 					worldSize;
		 G4double 					calorSize;

		 G4Material* 				ScintMaterial;
		 G4int 							NumOfScints;
     
     G4Material*        PMTMaterial;
		 G4double 					PMTHeight;

		 G4double						Radii;
     
		 G4Material*        PlasticMaterial;
		 G4double           PlasticHeight;
     
     G4Material*        defaultMaterial;
            
     G4Box*             solidWorld;    //pointer to the solid World 
     G4LogicalVolume*   logicWorld;    //pointer to the logical World
     G4VPhysicalVolume* physiWorld;    //pointer to the physical World

     G4Box*             solidCalor;    //pointer to the solid Calor 
     G4LogicalVolume*   logicCalor;    //pointer to the logical Calor
     G4VPhysicalVolume* physiCalor;    //pointer to the physical Calor
         
     G4Tubs*            solidScint; 	 //pointer to the solid Scintillator
		 G4LogicalVolume*   logicScint;	   //pointer to the logical Scintillator
		 G4VPhysicalVolume* physiScint;		 //pointer to the physical Scintillator

		 G4Tubs*            solidPlastic;  //pointer to the solid Plastic
		 G4LogicalVolume*   logicPlastic;	 //pointer to the logical Plastic
		 G4VPhysicalVolume* physiPlastic;	 //pointer to the physical Plastic

     G4Tubs*            solidPMT;      //pointer to the solid Detector
     G4LogicalVolume*   logicPMT;      //pointer to the logical Detector
     G4VPhysicalVolume* physiPMT;      //pointer to the physical Detector
      
  private:
    
     void DefineMaterials();
     G4VPhysicalVolume* ConstructCalorimeter();     
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


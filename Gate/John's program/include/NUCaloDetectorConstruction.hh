/**************************************************************************************
**  Detector Construction and Material Definitions for Copper Absorber simulation
**  John Neuhaus 1/12/2010
**
**
**
**
***************************************************************************************/


#ifndef NUCaloDetectorConstruction_h
#define NUCaloDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4Tubs;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4SDManager;
class G4LogicalVolume;
class NUCaloTrackerSD;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NUCaloDetectorConstruction : public G4VUserDetectorConstruction
{
public:

	NUCaloDetectorConstruction();
	~NUCaloDetectorConstruction();
	G4VPhysicalVolume* Construct();

private:
	void createMats();
	void buildStaticComponents();
	void placeComponents();
	G4VPhysicalVolume* ConstructCalo();

public:
	//parameters to be modified via UI
	double plateThickness;  

private:
	//Materials
	G4Material * pb;
	G4Material * air;
	G4Material * sensMat;

	//Sensitive Detector Mgr
	G4SDManager* SDman;

	//Experimental hall
	G4Box* expHall_box;
	G4LogicalVolume* expHall_log;
	G4VPhysicalVolume* expHall_phys;

	//SD
	G4VPhysicalVolume* sdPhys;

	//Absorber
	G4LogicalVolume* absLog;
	G4VPhysicalVolume* absPhys;




};

struct sdStruct
{
	G4LogicalVolume* sdLog;
	NUCaloTrackerSD* sdTracker;
};



#endif

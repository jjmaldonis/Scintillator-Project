/**************************************************************************************
**  Detector Construction and Material Definitions for Copper Absorber simulation
**  John Neuhaus 1/12/2010
**
**
**
**
***************************************************************************************/


#ifndef betaBlockDetectorConstruction_h
#define betaBlockDetectorConstruction_h 1

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
class betaBlockTrackerSD;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class betaBlockDetectorConstruction : public G4VUserDetectorConstruction
{
public:

	betaBlockDetectorConstruction(double thick = 0.5);
	~betaBlockDetectorConstruction();
	G4VPhysicalVolume* Construct();

private:
	void createMats();
	void buildStaticComponents();
	void placeComponents();
	G4VPhysicalVolume* ConstructCalo();

public:
	//parameters to be modified via UI
	double detThickness;

private:
	//Materials
	G4Material * pdms;
	G4Material * air;
	G4Material * glass;
	G4Material * vacuum;
	G4Material * pTP;
	G4Material * scint;

	//Sensitive Detector Mgr
	G4SDManager* SDman;

	//Experimental hall
	G4Box* expHall_box;
	G4LogicalVolume* expHall_log;
	G4VPhysicalVolume* expHall_phys;

};

struct sdStruct
{
	G4LogicalVolume* sdLog;
	betaBlockTrackerSD* sdTracker;

};



#endif

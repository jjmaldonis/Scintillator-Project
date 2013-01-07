#include <cmath>

#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"







class CylRepeat
{
	public:
		CylRepeat(G4double radius, G4ThreeVector center, G4String axis, G4int numOfReps,
							G4Box* solid, G4LogicalVolume* logic, G4LogicalVolume* momslogic);
		virtual ~CylRepeat();

	private:
		G4double delta_length;
		G4double deltha_Angle;
		G4double x_coor;
		G4double y_coor;
		G4RotationMatrix* rm;
		G4double new_angle;

};





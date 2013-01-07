#include <cmath>

#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"

#include "CylRepeat.hh"




CylRepeat::CylRepeat(G4double radius, G4ThreeVector center, G4String axis, G4int numOfReps,
										 G4Box* solid, G4LogicalVolume* logic, G4LogicalVolume* momslogic)
{
	deltha_Angle = (G4double) 360.0/numOfReps*deg;
	
	for(G4double i = 0; i < numOfReps; i++)
	{
		new_angle = (numOfReps-4.0)/4.0*deltha_Angle*i;
		
		x_coor = radius*cos(deltha_Angle*i);
		y_coor = radius*sin(deltha_Angle*i);

		G4cout << "  Rotation Angle " << i << " is " << new_angle/deg << "." << G4endl;

		rm = new G4RotationMatrix();
		if(axis == "x"){
			rm->rotateX(new_angle);
			new G4PVPlacement(rm, G4ThreeVector(0,x_coor,y_coor), logic, "", momslogic, false, 0);}
			
		if(axis == "y"){
			rm->rotateY(new_angle);
			new G4PVPlacement(rm, G4ThreeVector(x_coor,0,y_coor), logic, "", momslogic, false, 0);}
			
		if(axis == "z"){
			rm->rotateZ(i*deltha_Angle);
			new G4PVPlacement(rm, G4ThreeVector(x_coor,y_coor,0),	logic, "", momslogic,	false, 0);}
	}

	// This algorithm will tell you the number of optimal PV to place
	G4int ii = 0;
	G4double width = solid->GetXHalfLength()*2;
	G4double innerCircum = 2*pi*(radius-solid->GetYHalfLength());
	while(true)
	{
		ii++;
		if(ii*width > innerCircum)
		{
			G4cout << "The ~ optimal number of repetitions to have is " << ii << ". The actual number may one lower. This currently only works well if we are repeating cubes." << G4endl;
			break;
		}
	}
}

CylRepeat::~CylRepeat()
{}
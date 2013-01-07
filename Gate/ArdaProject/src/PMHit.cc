#include "PMHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"

G4Allocator<PMHit> PMHitsAllocator;

PMHit::PMHit()
{
	
}

PMHit::~PMHit()
{
	
}

PMHit::PMHit(const PMHit& right):G4VHit()
{
	trackID = right.trackID;
	chamberNb = right.chamberNb;
	energyDep = right.energyDep;
	pos = right.pos;
}

void PMHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if (pVVisManager)
	{
		G4Circle circle(pos);
		circle.SetScreenSize(2.*mm);
		circle.SetFillStyle(G4Circle::filled);
		G4Color color(1., 0.0, 0.0);
		G4VisAttributes visAttr(color);
		circle.SetVisAttributes(visAttr);
		pVVisManager->Draw(circle);
	}
}

void PMHit::Print()
{
	G4cout << "  trackID: " << trackID << "  chamberNb: " << chamberNb
				 << "  energy deposit: " << G4BestUnit(energyDep, "Energy")
				 << "  position: " << G4BestUnit(pos, "Length") << G4endl;
}

const PMHit& PMHit::operator = (const PMHit& right)
{
	trackID = right.trackID;
	chamberNb = right.chamberNb;
	energyDep = right.energyDep;
	pos = right.pos;
	return (*this);
}

G4int PMHit::operator ==(const PMHit& right) const
{
	return (this == &right) ? 1 : 0;
}
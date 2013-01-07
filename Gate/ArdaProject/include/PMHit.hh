/*
		PMHit Class,
		
		Hits contain information about a physical interaction of a Track inside the sensitive Detectore
		Tracks contain information about a particle
		We use a collection in order to keep all Hits.
*/

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"


class PMHit : public G4VHit
{
	public:
		PMHit();
		PMHit(const PMHit&);
		~PMHit();
		const PMHit& operator = (const PMHit&);
		G4int operator ==(const PMHit&) const;
		
		inline void* operator new(size_t);
		inline void operator delete(void*);
		
		void Draw();                 // Draws a circle where there was a hit
		void Print();
		
	public:
		void SetTrackID(G4int track) {trackID = track;};
		void SetChamberNb(G4int chamb) {chamberNb = chamb;};
		void SetEnergyDep(G4double de) {energyDep = de;};
		void SetPos(G4ThreeVector xyz) {pos = xyz;};
		
		G4int GetTrackID() {return trackID;};
		G4int GetChamberNb() {return chamberNb;};
		G4double GetEnergyDep() {return energyDep;};
		G4ThreeVector GetPos() {return pos;};
		
	private:
		//Hit Information : Which particle, how much energy was lost or deposited, where - position
		G4int trackID;
		G4int chamberNb;
		G4double energyDep;
		G4ThreeVector pos;
};

typedef G4THitsCollection<PMHit> PMHitsCollection;                        //Collection type
extern G4Allocator<PMHit> PMHitsAllocator;

inline void* PMHit::operator new(size_t)
{
		void* aHit;
		aHit = (void*) PMHitsAllocator.MallocSingle();
		return aHit;
}

inline void PMHit::operator delete(void* aHit)
{
	PMHitsAllocator.FreeSingle((PMHit*) aHit);
}
/*
		PMHit Class,
		
		Hits contain information about a physical interaction of a Track inside the sensitive Detectore
		Tracks contain information about a particle
		We use a collection in order to keep all Hits.
*/

#include "G4VHit.hh"
#include "G4VPhysicalVolume.hh"
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

		void SetPhysicalVolume(G4VPhysicalVolume* volume) {physVolume = volume;};
		
		G4VPhysicalVolume* GetPhysicalVolume() {return physVolume;};
		
	private:
		G4VPhysicalVolume* physVolume;
		G4int PMNumber;
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
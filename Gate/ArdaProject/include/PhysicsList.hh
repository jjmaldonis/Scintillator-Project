/*
	Describes all Particles and all physics processes
*/

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList : public G4VUserPhysicsList
{
	public:
		PhysicsList();
		~PhysicsList();
	
	protected:
		void ConstructParticle();
		void ConstructProcess();
		void SetCuts();
		
	private:
			void ConstructEM();
			void ConstructGeneral();
			void ConstructOptical();
		
};

#endif
#ifndef ScintPhysicsList_h
#define ScintPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;
class G4GammaConversion;
class G4ComptonScattering;
class G4PhotoElectricEffect;
class G4eMultipleScattering;
class G4eIonisation;
class G4eBremsstrahlung;
class G4eplusAnnihilation;
class G4MuMultipleScattering;
class G4MuIonisation;
class G4MuBremsstrahlung;
class G4MuPairProduction;
class G4hMultipleScattering;
class G4hIonisation;

class ExN06PhysicsListMessenger;


class PhysicsList: public G4VUserPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();
	
public:
	void ConstructParticle();
	void ConstructProcess();
	
	void SetCuts();
	
	//these methods Construct particles
	void ConstructBosons();
	void ConstructLeptons();
	void ConstructMesons();
	void ConstructBaryons();
	
	//these methods Construct physics processes and register them
	void ConstructGeneral();
	void ConstructEM();
	void ConstructOp();
	
	//for the Messenger
	void SetVerbose(G4int);
	void SetNbOfPhotonsCerenkov(G4int);
	
private:
	G4Cerenkov*          theCerenkovProcess;
	G4Scintillation*     theScintillationProcess;
	G4OpAbsorption*      theAbsorptionProcess;
	G4OpRayleigh*        theRayleighScatteringProcess;
	G4OpMieHG*           theMieHGScatteringProcess;
	G4OpBoundaryProcess* theBoundaryProcess;
	G4GammaConversion* gammaConversion;
	G4ComptonScattering* comptonScattering;
	G4PhotoElectricEffect* photoElectricEffect;
	G4eMultipleScattering* eMultipleScattering;
	G4eIonisation* eIonisation;
	G4eBremsstrahlung* eBremsstrahlung;
	G4eplusAnnihilation* eplusAnnihilation;
	G4MuMultipleScattering* muMultipleScattering;
	G4MuIonisation* muIonisation;
	G4MuBremsstrahlung* muBremsstrahlung;
	G4MuPairProduction* muPairProduction;
	G4hMultipleScattering* hMultipleScattering;
	G4hIonisation* hIonisation;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif




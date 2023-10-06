#include "construction.hh" // Incluye la definición de la clase MyDetectorConstruction

// Constructor vacío
MyDetectorConstruction::MyDetectorConstruction()
{}

// Destructor vacío
MyDetectorConstruction::~MyDetectorConstruction()
{}

// Método para construir la geometría del detector
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // Obtiene la instancia del G4NistManager
    G4NistManager *nist = G4NistManager::Instance();
    
    // Busca o construye el material "G4_AIR"
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    //definiremos propiedades opticas

    G4double energy[2] = {1.239841939*eV/0.2,1.239841939*eV/0.9};    //Paraver la luz cherenkov array

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    G4double rindexWorld[2] = {1.0 , 1.0};
    mptWorld->AddProperty("RINDEX", energy, rindexWorld,2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    // Oxido de Silicio
    G4Material *SiO2 = new G4Material ("SiO2", 2.201*g/cm3,2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
    SiO2->AddElement(nist->FindOrBuildElement("O"),2);
    
    // Agua
    G4Material *H2O = new G4Material ("H2O", 1.000*g/cm3,2);
    H2O->AddElement(nist->FindOrBuildElement("H"),2);
    H2O->AddElement(nist->FindOrBuildElement("O"),1);

    //Carbon
    G4Element *C = nist->FindOrBuildElement("C");

  

    // Tambien es necesario definir el indice de refraccion y propiedades
    G4double rindexAerogel[2] = {1.1 , 1.1};
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel,2);

    Aerogel->SetMaterialPropertiesTable(mptAerogel);
    
    // tambien definiremos propiedades opticas al aire del world ver mas arriba en la parte de AIR



    // Define el volumen sólido "solidWorld" como una caja con dimensiones de 0.1m x 0.1m x 0.1m
    G4Box *solidWorld = new G4Box("solidWorld",0.5*m,0.5*m,0.5*m);

    // Define el volumen lógico "logicWorld" con el volumen sólido "solidWorld" y el material "worldMat"
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
    
    
    
    
    
    
    
    
     //Rotacion de los cilindros:
    // Definir ángulo de rotación en grados
    G4double rotationAngle = 90.0; // Por ejemplo, 90 grados
    // Convertir el ángulo a radianes
    G4double rotationAngleRad = rotationAngle * deg;
    // Crear una matriz de rotación
    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateX(rotationAngleRad); 
    
    
       // Volumen I donde irradiarán las partículas, el volumen lógico y el físico
    
    G4double radius = 0.4 * m;  // Radio del cilindro
    G4double height = 0.5 * m; // Altura del cilindro
    G4Tubs* solidRadiator = new G4Tubs("solidRadiator", 0.0, radius, height/2, 0.0, 360.0 * deg);
    G4LogicalVolume* logicRadiator = new G4LogicalVolume(solidRadiator, H2O, "logicalRadiator");
    G4VPhysicalVolume* physRadiator = new G4PVPlacement(rotationMatrix, G4ThreeVector(0.0, 0.0, 0.0 * m), logicRadiator, "physRadiator", 		logicWorld, false, 0, true);
    
    
    
    
    //Volumen I donde irradiara las particulas, el volumen logico y el fisico
    //G4Box *solidRadiator = new G4Box("solidRadiator",0.4*m,0.4*m,0.01*m);

    //G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator,Aerogel,"logicalRadiator");

    //G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,-0.3*m),logicRadiator,"physRadiator",logicWorld, false, 0,true);
    
 
 
 
 
 
 
 
 
 
 
 
 

    // arreglos de Detector Sensible a fotones I

    G4Box *solidDetector1 = new G4Box("solidDetector1", 0.025*m, 0.025*m, 0.01*m);

    logicDetector1 = new G4LogicalVolume(solidDetector1, worldMat, "logicDetector1");

    for(G4int i = 0; i<20; i++)
    {
        for(G4int j = 0; j<20; j++)
        {
            G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/20,-0.5*m+(j+0.5)*m/20,0.49*m),logicDetector1,"physDetector1",logicWorld,false,j+i*20,true);
        }
    }
    
        // arreglos de Detector Sensible a fotones II

    G4Box *solidDetector2 = new G4Box("solidDetector2", 0.025*m, 0.025*m, 0.01*m);

    logicDetector2 = new G4LogicalVolume(solidDetector2, worldMat, "logicDetector2");

    for(G4int i = 0; i<20; i++)
    {
        for(G4int j = 0; j<20; j++)
        {
            G4VPhysicalVolume *physDetector2 = new G4PVPlacement(0,G4ThreeVector(-0.5*m+(i+0.5)*m/20,-0.5*m+(j+0.5)*m/20,0.49*m),logicDetector2,"physDetector2",logicWorld,false,j+i*20,true);
        }
    }
    // Define el volumen físico "physWorld" como una instancia del volumen lógico "logicWorld" en la posición (0,0,0)
    // El último argumento "true" indica que este será el volumen madre del detector y será utilizado para trazar las partículas
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);




    // Retorna el puntero al volumen físico "physWorld"
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	// Asignar los detectores a los volúmenes lógicos correspondientes
	MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
	logicDetector1->SetSensitiveDetector(sensDet1);
	    //II
	MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
	logicDetector2->SetSensitiveDetector(sensDet2);
}

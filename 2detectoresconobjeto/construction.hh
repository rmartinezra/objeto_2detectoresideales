#ifndef CONSTRUCTION_HH // Directiva del preprocesador para evitar inclusiones múltiples
#define CONSTRUCTION_HH
//Todas estos objetos ya creados en construction.cc
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh" // Inclusión de unidades del sistema de Geant4
#include "detector.hh"
class MyDetectorConstruction : public G4VUserDetectorConstruction // Declaración de la clase MyDetectorConstruction que hereda de G4UserDetectorConstructor
{
public:
    MyDetectorConstruction(); // Constructor predeterminado
    ~MyDetectorConstruction(); // Destructor

    virtual G4VPhysicalVolume *Construct(); // Función virtual pura para construir el detector

private:
    G4LogicalVolume *logicDetector1;
    G4LogicalVolume *logicDetector2;
    virtual void ConstructSDandField();
};

#endif // Cierre de la directiva del preprocesador

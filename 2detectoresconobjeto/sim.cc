#include <iostream>

// Incluimos las librerías necesarias de Geant4


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
// Incluye los ya creados
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
int main(int argc, char** argv)
{
    // Creamos un objeto de la clase G4RunManager que se encarga de manejar la ejecución de la simulación
    G4RunManager *runManager = new G4RunManager();

    // Asigna la clase MyDetectorConstruction como la construcción del detector a utilizar (Definidos en construction.cc) asi como la fisica definida en Physics.cc
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization()); 
    // Inicializa el RunManager, que a su vez inicializa la geometría, la física y los procesos de partículas
    runManager->Initialize();

    // Creamos un objeto de la clase G4UIExecutive que se encarga de crear la interfaz gráfica de usuario (GUI)
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // Creamos un objeto de la clase G4VisExecutive que se encarga de manejar la visualización de la simulación
    G4VisManager *visManager = new G4VisExecutive();

    // Inicializamos el visManager
    visManager->Initialize();

    // Obtenemos el objeto G4UImanager que se encarga de manejar los comandos de la GUI
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    //comandos de visualizacion
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    // Iniciamos la sesión de la GUI
    ui->SessionStart();

    return 0;
}

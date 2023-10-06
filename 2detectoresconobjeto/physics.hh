#ifndef PHYSICS_HH // Directiva del preprocesador para evitar inclusiones múltiples
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh" // Inclusión de la clase base para listas modulares de física
#include "G4EmStandardPhysics.hh" // Inclusión de la clase para procesos electromagnéticos estándar
#include "G4OpticalPhysics.hh" // Inclusión de la clase para procesos ópticos

// Declaración de la clase MyPhysicsList que hereda de G4VModularPhysicsList
class MyPhysicsList : public G4VModularPhysicsList 
{
public:
    MyPhysicsList(); // Constructor predeterminado
    ~MyPhysicsList(); // Destructor
};

#endif // Cierre de la directiva del preprocesador

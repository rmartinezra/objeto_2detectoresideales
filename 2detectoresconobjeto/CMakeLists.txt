cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# Especifica el nombre del proyecto
project(Simulation)

# Busca y carga el paquete Geant4, que se necesita para la simulación
find_package(Geant4 REQUIRED ui_all vis_all)

# Incluye el archivo de configuración de Geant4 que se encontró anteriormente
include(${Geant4_USE_FILE})

# Busca todos los archivos de código fuente (.cc) en el directorio del proyecto
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)

# Busca todos los archivos de encabezado (.hh) en el directorio del proyecto
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# Crea un archivo ejecutable llamado "sim" que incluye los archivos de código fuente y encabezado
add_executable(sim sim.cc ${sources} ${headers})

# Vincula la biblioteca de Geant4 con el archivo ejecutable "sim"
target_link_libraries(sim ${Geant4_LIBRARIES})

# Crea un objetivo personalizado llamado "Simulation" que depende del archivo ejecutable "sim"
add_custom_target(Simulation DEPENDS sim)

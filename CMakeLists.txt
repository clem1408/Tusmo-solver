# Minimum version de CMake
cmake_minimum_required(VERSION 3.12)

# Nom du projet
project(TusmoSolver)

# Définir le standard C++ (C++23 dans ce cas)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter des options de compilation (optimisation avec -Ofast)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Ofast")

# Ajouter l'exécutable
add_executable(main main.cpp)

# Ajouter le répertoire data comme ressource
configure_file(${CMAKE_SOURCE_DIR}/french_set/lst_mots.txt ${CMAKE_BINARY_DIR}/french_set/lst_mots.txt COPYONLY)

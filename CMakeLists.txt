cmake_minimum_required(VERSION 3.17)
project(dna_naming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(dna_naming wizard.cpp dhramacon.h)
target_link_libraries(dna_naming Qt5::Widgets Qt5::Core)

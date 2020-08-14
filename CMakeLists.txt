cmake_minimum_required(VERSION 3.17)
project(dna_naming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(dna_naming wizard.cpp dhramacon.h)

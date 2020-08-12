cmake_minimum_required(VERSION 3.17)
project(dna_naming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\mingw73_32\\")

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(dna_naming wizard.cpp)
target_link_libraries(dna_naming Qt5::Widgets)
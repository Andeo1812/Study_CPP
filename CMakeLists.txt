cmake_minimum_required(VERSION 3.18.4)
project(Archiver)

option(DEBUG "no release" ON)
option(RELEASE "in production" OFF)

add_subdirectory(project)

message("Core_lib_include = ${Core_lib_include}")
message("Core_lib_libs = ${Core_lib_libs}")

if (DEBUG)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_FLAGS "--std=c++23 -fconcepts -O0 -fprofile-arcs -fprofile-arcs -ftest-coverage -Wlogical-op -Wredundant-decls -Wsign-conversion -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif(DEBUG)



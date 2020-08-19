# Cmake required version
cmake_minimum_required(VERSION 3.16.3)

# Project information
project(
    AutomatedVehicleSimulation
    VERSION 1.0
    DESCRIPTION "A 2D Simulation for automated vehicle reinforcement learning")

option(BUILD_PYTHON "Build python api configuration" OFF)
message(STATUS "Build python api: ${BUILD_PYTHON}")

set(libavs_source_path "${PROJECT_SOURCE_DIR}/source")
include_directories(${libavs_source_path})

# Build library
add_subdirectory(source)
# Build main
add_subdirectory(bin)
# Build python package
if(BUILD_PYTHON)
    add_subdirectory(PythonAPI)
endif()


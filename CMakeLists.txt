cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0072 NEW)

#################################
#   HunterGate
#################################
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
        SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)

#################################
#   Project variables
#################################
project(EngineExample) # CHANGE THE PROJECT NAME TO YOURS #

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -Wextra -g -O")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Win32 stuff
if (MSVC OR MSVC_IDE)
    # Use November CTP 2013 (constexpr and other non implemented stuff in the 2013 version)
    if (MSVC_VERSION LESS 1800)
        message(FATAL_ERROR
                "This project requires C++11 stuff provided only with "
                "Microsoft Visual C++ Compiler Nov 2013 CTP (v120_CTP_Nov2013).")
    endif(MSVC_VERSION LESS 1800)

    if (MSVC_VERSION EQUAL 1800)
        #set(CMAKE_GENERATOR_TOOLSET "CTP_Nov2013" CACHE STRING "Platform Toolset" FORCE)
    endif (MSVC_VERSION EQUAL 1800)

    # Copy libs / targets in the correct directories
    if ("${CMAKE_GENERATOR}" STREQUAL "NMake Makefiles")
        set(PDB_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        endforeach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    endif()
endif(MSVC OR MSVC_IDE)

##################################
#   Build libraries and executables
##################################
set(ENGINE_LIBRARIES)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/AppExamples)
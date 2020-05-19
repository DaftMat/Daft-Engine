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

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -g -O")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#################################
#   Sources
#################################
file(GLOB_RECURSE sources
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs/OpenGL/src/glad.c)

file(GLOB_RECURSE headers
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs/random/random.hpp)

file(GLOB_RECURSE inlines
        ${CMAKE_SOURCE_DIR}/src/*.inl)

#################################
#   Dependencies - add what you need, delete what you don't
#################################
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/3rdPartyLibs)

hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)

hunter_add_package(Eigen)
find_package(Eigen3 CONFIG REQUIRED)

hunter_add_package(Assimp)
find_package(Assimp CONFIG REQUIRED)

set(EXT_LIBS glfw glm Assimp::assimp Eigen3)

##################################
#   Executable
##################################
add_executable(${PROJECT_NAME} ${sources} ${headers} ${inlines})
target_link_libraries(${PROJECT_NAME} ${EXT_LIBS})

##################################
#   Shaders
##################################
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders)
file(GLOB_RECURSE SHADER_SOURCES ${SHADER_DIR}/.*.glsl)

if(WIN32)
    set(COPY_COMMAND copy_directory)
else(WIN32)
    set(COPY_COMMAND create_symlink)
endif(WIN32)

add_custom_target(
        ${PROJECT_NAME}_shaders
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${SHADER_DIR} ${EXECUTABLE_OUTPUT_PATH}/shaders
        SOURCES ${SHADER_SOURCES}
        COMMENT "Create symlink/copy for shaders" VERBATIM
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_shaders)

###################################
#   Resources
###################################
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCE_DIR}/*)

add_custom_target(
        ${PROJECT_NAME}_resources
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${RESOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/resources
        SOURCES ${RESOURCE_FILES}
        COMMENT "Create symlink/copy for resources" VERBATIM
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_resources)
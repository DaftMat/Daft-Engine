set(target engineApi)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/3rdPartyLibs/OpenGL/src/glad.c)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE inlines ${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

#############################################################
# Set up your dependencies here
#############################################################
find_package(glm CONFIG REQUIRED)

find_package(Eigen3 CONFIG REQUIRED)

find_package(Assimp CONFIG REQUIRED)

set(EXT_LIBS ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES} ${EIGEN_LIBRARIES})

add_library(${target} SHARED ${sources} ${headers} ${inlines})

target_include_directories(${target} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs)

target_compile_definitions(${target} PRIVATE "-DDYNAMIC_LINK")

target_link_libraries(${target} PUBLIC ${EXT_LIBS})

set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${target} PROPERTY POSITION_INDEPENDENT_CODE ON)

set(ENGINE_LIBRARIES ${ENGINE_LIBRARIES} engineApi PARENT_SCOPE)



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
        ${target}_shaders
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${SHADER_DIR} ${EXECUTABLE_OUTPUT_PATH}/shaders
        SOURCES ${SHADER_SOURCES}
        COMMENT "Create symlink/copy for shaders" VERBATIM
)

add_dependencies(${target} ${target}_shaders)

###################################
#   Resources
###################################
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCE_DIR}/*)

add_custom_target(
        ${target}_resources
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${RESOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/resources
        SOURCES ${RESOURCE_FILES}
        COMMENT "Create symlink/copy for resources" VERBATIM
)

add_dependencies(${target} ${target}_resources)
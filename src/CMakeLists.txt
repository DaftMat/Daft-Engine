#TODO: replace engineApi with your own engine api name
set(api_target engineApi)

file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/3rdPartyLibs/GLAD/gl45core/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_SOURCE_DIR}/3rdPartyLibs/GLAD/gl45core/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE inlines ${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

#TODO: set up all the dependencies of your engine api down here
if(WIN32)
find_package(GLM CONFIG REQUIRED)
set(EXT_LIBS ${EXT_LIBS} ${GLM_LIBRARIES})
set(EXT_INCLUDES ${EXT_INCLUDES} ${GLM_DIR})
endif(WIN32)

find_package(Eigen3 CONFIG REQUIRED)
if(WIN32)
set(EXT_LIBS ${EXT_LIBS} Eigen3::Eigen)
set(EXT_INCLUDES ${EXT_INCLUDES} ${Eigen3_DIR})
endif(WIN32)

find_package(assimp CONFIG REQUIRED)
if(WIN32)
set(EXT_LIBS ${EXT_LIBS} assimp::assimp)
else(WIN32)
set(EXT_LIBS ${EXT_LIBS} ${ASSIMP_LIBRARIES})
endif(WIN32)

find_package(spdlog 1 CONFIG REQUIRED)

find_package(OpenGL REQUIRED)
if(WIN32)
set(EXT_LIBS ${EXT_LIBS} opengl32)
else(WIN32)
set(EXT_LIBS ${EXT_LIBS} ${OPENGL_LIBRARIES})
endif(WIN32)

set(EXT_LIBS ${EXT_LIBS} spdlog::spdlog)
set(EXT_INCLUDES ${EXT_INCLUDES} ${Assimp_DIR} ${spdlog_DIR})

###################################################################

add_library(${api_target} SHARED ${headers} ${sources} ${inlines})

target_include_directories(${api_target} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/3rdPartyLibs
        ${EXT_INCLUDES}
        ${ENGINE_INCLUDES} PARENT_SCOPE)

target_compile_definitions(${api_target} PUBLIC "-DDYNAMIC_LINK")
target_compile_definitions(${api_target} PUBLIC "-Ddaft_${CMAKE_BUILD_TYPE}")
if (TRACE)
target_compile_definitions(${api_target} PUBLIC "-DTRACE")
endif(TRACE)

target_link_libraries(${api_target} PUBLIC ${EXT_LIBS})

set_target_properties(${api_target} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${api_target} PROPERTY POSITION_INDEPENDENT_CODE ON)

set(ENGINE_LIBRARIES ${ENGINE_LIBRARIES} ${api_target} PARENT_SCOPE)
set(ENGINE_API ${api_target} PARENT_SCOPE)

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
        ${api_target}_shaders
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${SHADER_DIR} ${EXECUTABLE_OUTPUT_PATH}/shaders
        SOURCES ${SHADER_SOURCES}
        COMMENT "Create symlink/copy for shaders" VERBATIM
)

add_dependencies(${api_target} ${api_target}_shaders)

###################################
#   Resources
###################################
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
file(GLOB_RECURSE RESOURCE_FILES ${RESOURCE_DIR}/*)

add_custom_target(
        ${api_target}_resources
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${RESOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/resources
        SOURCES ${RESOURCE_FILES}
        COMMENT "Create symlink/copy for resources" VERBATIM
)

add_dependencies(${api_target} ${api_target}_resources)

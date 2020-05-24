#TODO: replace exampleApp with your application name
set(apptarget exampleApp)

#TODO: load the library you need in addition to your engine
find_package(glfw3 CONFIG REQUIRED)
set(EXT_LIBS glfw)

include_directories(
        .
        ${CMAKE_SOURCE_DIR}/src
)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/*.h)

add_executable(${apptarget} ${sources} ${headers})

target_link_libraries(${apptarget} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${apptarget} engineApi)
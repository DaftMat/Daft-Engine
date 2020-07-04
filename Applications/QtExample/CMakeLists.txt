set(app_target qtExample)

#Qt5
find_package(Qt5 COMPONENTS OpenGL CONFIG REQUIRED)

set(EXT_LIBS Qt5::OpenGL ${CMAKE_DL_LIBS})

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB uis ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON )

add_executable(${app_target} ${sources} ${headers} ${uis})

target_link_libraries(${app_target} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${app_target} ${ENGINE_API})
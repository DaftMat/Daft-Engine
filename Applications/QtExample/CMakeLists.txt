set(app_target qtExample)

#Qt5
find_package(Qt5 COMPONENTS OpenGL CONFIG REQUIRED)

set(EXT_LIBS Qt5::OpenGL)
if(WIN32 OR APPLE)
    set(EXT_LIBS ${EXT_LIBS} libdl)
else()
    set(EXT_LIBS ${EXT_LIBS} libdl.so)
endif()

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_executable(${app_target} ${sources} ${headers})

#include_directories(${Qt5_DIR})

target_link_libraries(${app_target} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${app_target} ${ENGINE_API})
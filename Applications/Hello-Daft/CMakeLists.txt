set(app_target helloDaft)

#GLFW
find_package(glfw3 CONFIG REQUIRED)

set(EXT_LIBS glfw ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_executable(${app_target} ${sources} ${headers})

target_link_libraries(${app_target} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${app_target} ${ENGINE_API})
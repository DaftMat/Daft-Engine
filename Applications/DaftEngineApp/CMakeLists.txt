set(app_target DaftEngineApp)

#Qt5
find_package(Qt5 COMPONENTS OpenGL CONFIG REQUIRED)

set(EXT_LIBS Qt5::OpenGL ${CMAKE_DL_LIBS})

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE uis ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON )

add_executable(${app_target} ${sources} ${headers} ${uis})

target_link_libraries(${app_target} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${app_target} ${ENGINE_API})

set(IMAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/img)
file(GLOB_RECURSE IMAGE_FILES ${IMAGE_DIR}/*)
set(STYLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stylesheets)
file(GLOB_RECURSE STYLE_FILES ${STYLE_DIR}/*.css)

if(WIN32)
    set(COPY_COMMAND copy_directory)
else(WIN32)
    set(COPY_COMMAND create_symlink)
endif(WIN32)

add_custom_target(
        ${app_target}_images
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${IMAGE_DIR} ${EXECUTABLE_OUTPUT_PATH}/img
        SOURCES ${IMAGE_FILES}
        COMMENT "Create symlink/copy for application's images" VERBATIM
)

add_custom_target(
        ${app_target}_stylesheets
        COMMAND ${CMAKE_COMMAND} -E ${COPY_COMMAND} ${STYLE_DIR} ${EXECUTABLE_OUTPUT_PATH}/stylesheets
        SOURCES ${STYLE_FILES}
        COMMENT "Create symlink/copy for application's stylesheets" VERBATIM
)

add_dependencies(${app_target} ${app_target}_images)
add_dependencies(${app_target} ${app_target}_stylesheets)
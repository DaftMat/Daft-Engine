project(Tests)

set(testing_include_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(testing_SRCS ${testing_include_dir}/Test.hpp)

add_subdirectory(CoreTests)
add_subdirectory(TemplateTests)
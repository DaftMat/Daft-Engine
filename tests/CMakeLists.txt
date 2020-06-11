project(Tests)

set(testing_include_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(testing_SRCS ${testing_include_dir}/Test.hpp)

add_subdirectory(CoreTests)
# TODO : remove (with the corresponding folder)
# Use it as an example for your own unit tests.
add_subdirectory(TemplateTests)
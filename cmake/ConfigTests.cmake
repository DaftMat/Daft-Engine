add_custom_target(buildtests)
add_custom_target(check COMMAND "ctest")
add_dependencies(check buildtests)

# Helper to add a test directory
function(add_test_file name)
    set(SRC src/${name}.cpp)
    set(LIBS ${ENGINE_API} PARENT_SCOPE)

    add_executable(test_${name} ${SRC} ${testing_SRCS})
    set_property(TARGET test_${name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    add_dependencies(buildtests test_${name})
    add_test(NAME test_${name}
            COMMAND test_${name})
    target_link_libraries(test_${name} ${ENGINE_LIBRARIES})
    target_include_directories(test_${name} PUBLIC ${testing_include_dir} ${SOURCE_DIR})
endfunction()
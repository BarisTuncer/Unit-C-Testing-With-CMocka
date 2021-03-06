project(testingWithCMocka)

# helper function to add a test which will be used below.
function(target_add_test TARGET_NAME TARGET_BASE_LIB TARGET_SOURCE)
    # add the test executable
    add_executable(${TARGET_NAME} ${TARGET_SOURCE})
    # test should be able to access the library that it tests
    target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libraries/include)
    # add adress sanitizer for memory check
    target_compile_options(${TARGET_NAME} PUBLIC "-fsanitize=address" "-g" "-O1" "-fno-omit-frame-pointer") 
    # link the test target with the sanitizer lib (should be first), mocka lib, and the lib that it tests. lib has been created before!
    target_link_libraries(${TARGET_NAME} asan ${TARGET_BASE_LIB} cmocka) 
    # now add test into the cmake tests
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
    # set some test properties which will be used by CMake
    set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 5)
endfunction()

target_add_test(test_state state ${PROJECT_SOURCE_DIR}/test_state.c)
target_add_test(test_stack stack ${PROJECT_SOURCE_DIR}/test_stack.c)

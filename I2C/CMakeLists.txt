project(I2c)
add_library(i2c SHARED i2c.c)

if(ENABLE_TESTING)
    message(STATUS "Test executable for test_open_i2c will be created")
    add_executable(test_open_i2c test_open_i2c.c)
    target_link_libraries(test_open_i2c i2c cmocka)
    add_test(test_open_i2c ${CMAKE_CURRENT_BINARY_DIR}/test_open_i2c)
    target_link_options(test_open_i2c PRIVATE "-Wl,--wrap=open")

    message(STATUS "Test executable test_do_something will be created")
    add_executable(test_do_something test_do_something.c)
    target_link_libraries(test_do_something i2c cmocka)
    #target_link_options(test_do_something PRIVATE "-Wl,--wrap=close" "-Wl,--wrap=open_i2c")
    target_link_options(test_do_something PRIVATE "-Wl,--defsym,close=__wrap_close" "-Wl,--defsym,open_i2c=__wrap_open_i2c")  ## seems to be the best solution! 
    add_test(test_do_something ${CMAKE_CURRENT_BINARY_DIR}/test_do_something)

    if(ENABLE_CODE_COVERAGE)
        #[[ now include code coverage
        Example use od code coverage
            set(COVERAGE_EXCLUDES "dir1/*")
            setup_target_for_coverage_gcovr_html(
                NAME coverage
                EXECUTABLE testrunner
                BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
                EXCLUDE "dir2/*")
        ]]
        setup_target_for_coverage_gcovr_html(
            NAME test_open_i2c_coverage  
            EXECUTABLE test_open_i2c
            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/I2C"
        )
        setup_target_for_coverage_gcovr_html(
            NAME test_do_something_coverage  
            EXECUTABLE test_do_something
            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/I2C"
        )
    endif()

endif()
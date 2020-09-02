project(I2c)
add_library(i2c i2c.c)

if(ENABLE_TESTING)
    message(STATUS "Test executable for test_open_i2c and test_do_something will be created")
    add_executable(test_open_i2c test_open_i2c.c)
    target_link_libraries(test_open_i2c i2c cmocka)
    add_test(test_open_i2c ${CMAKE_CURRENT_BINARY_DIR}/test_open_i2c)
    target_link_options(test_open_i2c PRIVATE "-Wl,--wrap=open")

    add_executable(test_do_something test_do_something.c)
    target_link_libraries(test_do_something i2c cmocka)
    #target_link_options(test_do_something PRIVATE "-Wl,--wrap=close" "-Wl,--wrap=open_i2c")
    target_link_options(test_do_something PRIVATE "-Wl,--defsym,close=__wrap_close" "-Wl,--defsym,open_i2c=__wrap_open_i2c")  ## seems to be the best solution! 
    add_test(test_do_something ${CMAKE_CURRENT_BINARY_DIR}/test_do_something)

endif()
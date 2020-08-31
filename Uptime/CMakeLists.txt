project(Uptime)
add_library(proc_uptime proc_uptime.c)

if(ENABLE_TESTING)
    message(STATUS "Test executable for test_calc_uptime will be created")
    add_library(calc_uptime calc_uptime.c)
    add_executable(test_calc_uptime test_calc_uptime.c)
    target_link_libraries(test_calc_uptime calc_uptime proc_uptime cmocka)
    add_test(test_calc_uptime ${CMAKE_CURRENT_BINARY_DIR}/test_calc_uptime)
    target_link_options(test_calc_uptime PRIVATE "-Wl,--wrap=uptime")
else()
    add_executable(calc_uptime calc_uptime.c)
    target_link_libraries(calc_uptime proc_uptime)
endif()



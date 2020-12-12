cmake_minimum_required(VERSION 3.18)
project(UnitCTestingWithCMocka)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)


option(ENABLE_TESTING "Enabling testing" ON)
if(ENABLE_TESTING)
    message(STATUS "Testing enabled")
    enable_testing()
endif()


option(ENABLE_CODE_COVERAGE "Perform coverage report after build" ON)
if(ENABLE_CODE_COVERAGE)
    message(STATUS "Coverage executables will be generated")    
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)
    include(CodeCoverage)
    # the prov below is defined in CodeCoverage, manupulate when needed
    append_coverage_compiler_flags()
    #  Build a Debug build:
    #      cmake -DCMAKE_BUILD_TYPE=Debug ..
    #      make
    #      make my_coverage_target --> this will point out the html file to look at
endif()

if (${CMAKE_C_COMPILER_ID} MATCHES "(GNU|Clang)" AND NOT APPLE)
    add_subdirectory(Uptime)
    add_subdirectory(I2C)
endif()

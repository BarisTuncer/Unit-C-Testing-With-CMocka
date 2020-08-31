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

if (${CMAKE_C_COMPILER_ID} MATCHES "(GNU|Clang)" AND NOT APPLE)
    add_subdirectory(Uptime)
    add_subdirectory(I2C)
endif()

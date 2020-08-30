cmake_minimum_required(VERSION 3.18)
project(UnitCTestingWithCMocka)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)
add_subdirectory(libraries)
add_subdirectory(tests)
#[[
enable_testing() command should be in the source directory root
because ctest expects to find a test file in the build
directory root.
]]
enable_testing()
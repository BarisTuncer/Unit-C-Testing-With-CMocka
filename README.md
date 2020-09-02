# Unit C Testing With CMocka 

[cmocka]: https://api.cmocka.org/
[CMakeLists]: tests/CMakeLists.txt
[AddressSanitizer]: https://clang.llvm.org/docs/AddressSanitizer.html
**[cmocka]** is a an elegant unit testing framework for `C` with support for mock objects. It only requires the standard `C` library, unit testing `C` library with mock support.

This tutorial describes unit testing pure `C` code with **[cmocka]**.

1. `master` branch gives 2 examples of basics of testing with `cmocka`
2. `mocking-examples` branch gives 3 non-trivial examples of mocking with `cmocka`.


## Things to note in tests/[CMakeLists]
[AddressSanitizer] (`asan` library) is a fast memory error detector.
* `target_compile_options(${TARGET_NAME} PUBLIC "-fsanitize=address" "-g" "-O1" "-fno-omit-frame-pointer")`
### link the test target with the sanitizer lib (should be first), mocka lib, and the lib that it tests. lib has been created before!
* `target_link_libraries(${TARGET_NAME} asan ${TARGET_BASE_LIB} cmocka)` 
### now add test into the cmake tests
* `add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})`
### set some test properties which will be used by CMake
* `set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 5)`
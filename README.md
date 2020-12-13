# Adding code-coverage

[cmocka]: https://api.cmocka.org/
[Mocking uptime]: Uptime/README.md
[Mocking i2c]:    I2C/README.md
[Andreas Scheider]: https://cryptomilk.org/
[MicroJoe]: https://blog.microjoe.org/2017/unit-tests-c-cmocka-coverage-cmake.html

**[cmocka]** is a unit testing `C` library with mock support.

In this part of the tutorial, let's add code-coverage into our tests.

1. Our first test example [Mocking uptime] is by **[Andreas Scheider]** who is the maintainer and core developer of [cmocka]
2. Our next test example [Mocking i2c] is by [MicroJoe]. 

[gcovr]: https://gcovr.com/en/stable/
[code coverage script]: https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
[Lars Bilke]: https://github.com/bilke
# About **[gcovr]**
[gcovr] provides a utility for managing the use of the GNU `gcov` utility and generating summarized code coverage results. 
To obtain `gcovr`, follow the steps in the web page of **[gcovr]** for installation. It has a simple the tutorial to learn about code coverage
(You may also need to install `lcov` : `sudo dnf install lcov` which will also install `genhtml`)


# A useful script by **[Lars Bilke]**

Say for example we want to investigate the code coverage of the lib files in `Uptime` directory which were
used by the test `test_calc_uptime`. 

A simple beautiful script **[code coverage script]** by **[Lars Bilke]** is very useful. All we need to include the following
code into our `CMakeLists`. 

Thank you **[Lars Bilke]** for making this script available for us!

```
setup_target_for_coverage_gcovr_html(
            NAME test_calc_uptime_coverage  // name of the coverage executable
            EXECUTABLE test_calc_uptime     // test executable
            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/Uptime" // base dir of the files whose code coverage will be generated
        )
```

I can't see why but when I build the project from VSCode I started to get ninja error. So, I use terminal:

  Build a Debug build:
  1.  mkdir build && cd build
  2.  cmake -DCMAKE_BUILD_TYPE=Debug ..
  3.  make

Now at this point we can see the executable `test_calc_uptime_coverage`. When you run it, `html` files will be created inside
`build\Uptime\test_calc_uptime_coverage`. Inside this folder, right click on `index.html` to go to the folder that contains it.
You can open `index.html` with your favourite browser.







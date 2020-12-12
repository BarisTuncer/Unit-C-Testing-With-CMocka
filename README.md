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
To obtain `gcovr`, follow the steps in the web page of **[govr]** for installation. It has a simple the tutorial to learn about code coverage
(You may also need to install `lcov` : `sudo dnf install lcov` which will also install `genhtml`)


# A useful script by **[Lars Bilke]**

  Build a Debug build:
  1.  cmake -DCMAKE_BUILD_TYPE=Debug ..
  2.  make
  3.  make my_coverage_target --> this will point out the html file to look at






# i2c moc example
[MicroJoe]: https://blog.microjoe.org/2017/unit-tests-c-cmocka-coverage-cmake.html
[test_open_i2c]: test_open_i2c.c
[test_do_something]: test_do_something.c


In this part, I will consider [MicroJoe]'s 2 beautiful examples. I converted his CMakeLists for Modern Cmake and I also have a comment on his second [test_do_domething] test.

1. [test_open_i2c] This is an example of mocking system library function `open` inside `open_i2c`. During the test, there is call to mocked `open` via `__wrap_open` as well as real `open` via `__real_open`

2. [test_do_something] The importance of this example is that, during the test `do_something` function which makes a call to `open_i2c` is being mocked. In this case, `__wrap_open_i2c` does not work unless extra care is taken. [MicroJoe]'s solution is to make `open_i2c` weak to be able to overwrite it. 


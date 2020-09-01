# i2c moc example
[MicroJoe]: https://blog.microjoe.org/2017/unit-tests-c-cmocka-coverage-cmake.html
[test_open_i2c]: test_open_i2c.c
[open_i2c]: open_i2c.c
[test_do_something]: test_do_something.c
[CMakeLists]: CMakeLists.txt

In this part, I will consider [MicroJoe]'s 2 beautiful examples. I converted his CMakeLists for Modern Cmake and I also have a comment on his second [test_do_something] test.

1. [test_open_i2c] This is an example of mocking system library function `open` inside `open_i2c`. During the test, there is call to mocked `open` via `__wrap_open` as well as real `open` via `__real_open`. For this we need
* `target_link_options(test_do_something PRIVATE "-Wl,--wrap=open_i2c")` in [CMakeLists]

2. [test_do_something] The importance of this example is that, during the test `do_something` function (which makes a call to `open_i2c`) is being mocked. In this case, `__wrap_open_i2c` does not work unless extra care is taken. [MicroJoe]'s solution is to make `open_i2c` weak to be able to overwrite it. Test also mockes system library function `close` inside `do_something` via `__wrap_close`
For this we need:
* `target_link_options(test_do_something PRIVATE "-Wl,--wrap=close" "-Wl,--wrap=open_i2c")` in [CMakeLists] as well as  `__attribute__((weak))` before the definition of `open_i2c` in [open_i2c].

For [test_do_something], my suggestion is to use
* `target_link_options(test_do_something PRIVATE "-Wl,--wrap=close" "-Wl,--defsym,open_i2c=__wrap_open_i2c")` in [CMakeLists] without using `__attribute__((weak))` in [open_i2c] not to pollute [open_i2c].

However if you use my suggestion you can't use `__real_close`. But I think, this way is better, we can write seperate test where we want to use `real__*`


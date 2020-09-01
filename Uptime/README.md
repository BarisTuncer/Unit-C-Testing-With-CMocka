# The uptime mock example 

[proc_uptime.c]: proc_uptime.c
[calc_uptime.c]: calc_uptime.c
[test_calc_uptime.c]: test_calc_uptime.c
[Andreas Scheider]: https://cryptomilk.org/

Mocking example and its explanation below is mostly by [Andreas Scheider] who is the maintainer and core developer of `cmocka`

**Note**: CMake file of the original example was for old CMake, so I updated it. Also, naming to the files in his example
was confusing (at least for me), so I needed to change the name of the files and the explanation below a little-bit but I didn't change the content of the files.

This is a very simple example to explain the mocking feature of `cmocka`. It
mimics the implementation the `uptime` unix command partially in a very simple way and calls it as `calc_uptime()` 
to demonstrate how to test the time calculation via mocking.    

When I run actual `uptime` in my terminal I get
* `21:38:35 up 3 days, 12:17,  1 user,  load average: 1.00, 1.00, 1.00`

An example output of `calc_uptime()` implemented in this example is:

*  `up 4 days, 1 hour, 21 minutes`

The problem with testing the `calc_uptime()` is that it makes a call to `uptime` ( which is implemented in **[proc_uptime.c]**)
but `/proc/uptime` constantly ticks. The result is random whenever you call the test. To actually test it
we need to make sure that we work with fixed values. The mocking features of `cmocka` allows us to test it anyway!

## Source files

* **[proc_uptime.c]** : This implements the `uptime()` function reading and parsing
  the /proc/uptime file. The return type of `uptime()` is`int`.
* **[calc_uptime.c]** : This implements `calc_uptime()` to get a human readable string representation of the `uptime`.
   This function calls `uptime()` from **[proc_uptime.c]**.
* **[test_calc_uptime.c]**: This is the test with the mocking function for `uptime()`.


## Linking magic

The test is linked using:

    ld --wrap=uptime

This replaces the orginal `uptime()` function which reads from `/proc/uptime`
with the mock function we implemented for testing `calc_uptime()`.

The mock function we implemented has a special name. It is called
`__wrap_uptime()`. All the symbols you want to mock (or replace) need to start
with the prefix `__wrap_`. So `ld --wrap=uptime` will rename the original
`uptime()` function to `__real_uptime()`. This means you can still reach the
original function using that name and call it e.g. from the wrap function.
The symbol `uptime` will be bound to `__wrap_uptime`.

You can find more details in the manpage: `man ld`

# The uptime test

The code should be easy to understand. If you have a hard time following, there
are two ways to understand how things work.

You can find out details about symbol binding using:

    LD_DEBUG=symbols ./example/uptime/uptime
    LD_DEBUG=symbols ./example/uptime/test_uptime

You can also use a debugger to step through the code!


Have fun!

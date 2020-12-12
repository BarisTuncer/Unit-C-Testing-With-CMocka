/**
 * @file test_do_something.c
 * @author microjoe
 * @brief see: https://blog.microjoe.org/2017/unit-tests-c-cmocka-coverage-cmake.html
 * 
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include "cmocka.h"
#include "i2c.h"



int __wrap_open_i2c(uint8_t i2c_bus);
int __wrap_open_i2c(uint8_t i2c_bus){
        check_expected(i2c_bus);
    return mock();
}

int __wrap_close(int fd)
{
    check_expected(fd);
    return mock();
}

/* tests */

void test_do_something_failure(void **state)
{
    (void) state; /* unused */
    int ret;

    expect_value(__wrap_open_i2c, i2c_bus, 42);
    will_return( __wrap_open_i2c, -1);

    ret = do_something();
    assert_int_equal(-1, ret);
}

void test_do_something_success(void **state)
{
    (void) state; /* unused */
    int ret;

    expect_value(__wrap_open_i2c, i2c_bus, 42);
    will_return(__wrap_open_i2c, 42);

    expect_value(__wrap_close, fd, 42);
    will_return(__wrap_close, 0);

    ret = do_something();
    assert_int_equal(0, ret);
}


int main(void)
{
    const struct CMUnitTest do_something_tests[] = {
        cmocka_unit_test(test_do_something_failure),
        cmocka_unit_test(test_do_something_success),
    };

    return cmocka_run_group_tests(do_something_tests, NULL, NULL);
}
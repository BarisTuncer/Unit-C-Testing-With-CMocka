/**
 * @file test_i2c.c
 * @author microjoe
 * @brief see: https://blog.microjoe.org/2017/unit-tests-c-cmocka-coverage-cmake.html
 * 
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include "cmocka.h"
#include "i2c.h"

#define UNUSED(x) (void)(x)

int __real_open(const char *path, int flags, int mode);

int __wrap_open(const char *path, int flags, int mode);
int __wrap_open(const char *path, int flags, int mode)
{
    if (strlen(path) > 5 && !strcmp(path + strlen(path) - 5, ".gcda"))
            return __real_open(path, flags, mode);

    check_expected(path);
    return mock();
}


/* open_i2c tests */

void test_open_i2c_failure(void **state)
{
    UNUSED(state);
    int ret;

    expect_string(__wrap_open, path, "/dev/i2c-99");
    will_return(__wrap_open, -1);

    ret = open_i2c(99);
    assert_int_equal(-1, ret);
}

void test_open_i2c_success(void **state)
{
    UNUSED(state);
    int ret;

    expect_string(__wrap_open, path, "/dev/i2c-99");
    will_return(__wrap_open, 42);

    ret = open_i2c(99);
    assert_int_equal(42, ret);
}

/* do_something tests */

void test_do_something_failure(void **state)
{
    UNUSED(state);
    int ret;

    expect_string(__wrap_open, path, "/dev/i2c-42");
    will_return(open_i2c, -1);

    ret = do_something();
    assert_int_equal(-1, ret);
}


int main(void)
{
    const struct CMUnitTest open_i2c_tests[] = {
        cmocka_unit_test(test_open_i2c_failure),
        cmocka_unit_test(test_open_i2c_success),
    };

    return cmocka_run_group_tests(open_i2c_tests, NULL, NULL);
}




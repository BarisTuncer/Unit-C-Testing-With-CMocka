#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdint.h>
#include <cmocka.h>
#include "stack.h"

#define UNUSED(x) (void)(x)
#define STRESS_TEST_ITERATIONS (10)

/* Declare the variables your tests want to use. */
static Stack s;
static int i;

/** These functions will be used to initialize
   and clean resources up after each test run 
*/
int setup (void **state){
    UNUSED(state);
    s = stack_create();
    i = 0;
    assert_non_null(s);
    return 0;
}

int teardown (void **state){
    UNUSED(state);
    stack_destroy(s);
    return 0;
}

/**
 * assert_* versions generate fatal failures when they fail, and abort the current function. 
 */

void test1(){
    //stack_destroy(s);
    //assert_ptr_equal(s, nullptr);  // this should fail. free does not mean null !
    //s = stack_create();
    assert_non_null(s);
    stack_push(s, 1);
    s = stack_create();
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    assert_int_equal(stack_isempty(s), 0);
    assert_int_equal(stack_pop(s), 3);
    assert_int_equal(stack_isempty(s), 0);
    assert_int_equal(stack_pop(s), 2);
    assert_int_equal(stack_isempty(s), 0);
    assert_int_equal(stack_pop(s), 1);
    assert_int_equal(stack_isempty(s), 1);
    assert_int_equal(stack_pop(s), STACK_EMPTY);
    assert_int_equal(stack_isempty(s), 1);
    assert_int_equal(stack_pop(s), STACK_EMPTY);
}

void test2(){
    /* let's do some stress testing */
    for(i = 0; i < STRESS_TEST_ITERATIONS; i++) {
        stack_push(s, i);
    }
    for(i = STRESS_TEST_ITERATIONS - 1; i >= 0; i--) {
        assert_int_not_equal(stack_isempty(s), 0);
        assert_int_equal(stack_pop(s), i);
    }      
    assert_int_equal(stack_isempty(s), 1);    
}

int main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test1),
    cmocka_unit_test(test2),
};
 
  return cmocka_run_group_tests(tests, setup, teardown);
}

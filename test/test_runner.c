#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdarg.h>
#include <cmocka.h>
#include <stdio.h>
#include <Clearning/factorial.hpp>


static void factorial_test(void **state) {
    (void) state; /* unused */
    //test for int factorial(int number);
    assert_int_equal(factorial(0), 1);
    assert_int_equal(factorial(1), 1);
    assert_int_equal(factorial(2), 2);
    assert_int_equal(factorial(3), 6);
    assert_int_equal(factorial(4), 24);

}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(factorial_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
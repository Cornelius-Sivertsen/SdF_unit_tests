// test file for CallStackfile1
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>

#include "cmocka.h"

#include "file1.h"
#include "file2.h"
#define DEBUG

void test_f1__1(void **state)
{
    (void) state; /* unused */
    int ret;

    ret = f1(1);
    assert_int_equal(0, ret);

}

int fa(int x)
{
#ifdef DEBUG
    printf("input_value for fa: %d\n", x);
#endif
    check_expected(x);
    int mock_ret = (int)mock();
#ifdef DEBUG
    printf("output value from fa: %d\n", mock_ret);
#endif
    return mock_ret;
}


/*
 * scenario ok with 2 call to fa with success
 */
void test_f2__1(void **state)
{
    (void) state; /* unused */
    int ret;

    int input = 1;
    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 15);

    ret = f2(input);
    assert_int_equal(0, ret);

}

void test_f2__3(void **state)
{
    (void) state; /* unused */
    int ret;


    int input = 1;
    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 5);
    ret = f2(input);
    assert_int_equal(ret, -2);


    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 9);
    ret = f2(input);
    assert_int_equal(ret, -2);

    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 20);
    ret = f2(input);
    assert_int_equal(ret, -2);

    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 28);
    ret = f2(input);
    assert_int_equal(ret, -2);
}

// test (EX2)
void test_f2__2(void **state)
{
    (void) state; /* unused */
    int ret;

    int input = 1;
    expect_value(fa, x, input);
    will_return(fa, 1);

    ret = f2(input);
    assert_int_equal(-1, ret);
}

void test_f2__4(void **state)
{
    (void) state; /* unused */
    int ret;

    int input = 1;
    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 10);
    ret = f2(input);
    assert_int_equal(ret, 0);


    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 17);
    ret = f2(input);
    assert_int_equal(ret, 0);

    expect_value(fa, x, input);
    expect_value(fa, x, input+1);

    will_return(fa, 0);
    will_return(fa, 19);
    ret = f2(input);
    assert_int_equal(ret, 0);

}



const struct CMUnitTest do_something_tests[] = {
    cmocka_unit_test(test_f1__1),
    cmocka_unit_test(test_f2__1),
    cmocka_unit_test(test_f2__2),
    cmocka_unit_test(test_f2__3),
    cmocka_unit_test(test_f2__4),
};


int main(void)
{
    return cmocka_run_group_tests(do_something_tests, NULL, NULL);
}

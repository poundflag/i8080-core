#include <check.h>

START_TEST(test_addition) {
    int result = 1 + 1;
    ck_assert_int_eq(result, 2);
}
END_TEST

Suite* sample_suite(void) {
    Suite* suite;
    TCase* test_case;

    suite = suite_create("AAAAA");

    test_case = tcase_create("Core");
    tcase_add_test(test_case, test_addition);
    suite_add_tcase(suite, test_case);

    return suite;
}
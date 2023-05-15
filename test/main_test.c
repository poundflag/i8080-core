#include <check.h>
#include <stdlib.h>

Suite* suite(void);

int main(void) {
    int number_failed;
    Suite* test_suite;
    SRunner* runner;

    test_suite = suite();
    runner = srunner_create(test_suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

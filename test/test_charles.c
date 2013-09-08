/* test_charles.c
 *
 * Entry point for charles unit tests.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "test_suites.h"

typedef Suite *(*SuiteCreator)();

SuiteCreator suite_creators[] = {
    test_basics_create_suite,
    test_object_create_suite,
};


int
main(int argc, const char *argv[])
{
    SRunner *runner = srunner_create(NULL);

    // Creat the suites and add them to the runner.
    int ncreators = sizeof(suite_creators) / sizeof(SuiteCreator);
    for (int i = 0; i < ncreators; i++) {
        srunner_add_suite(runner, suite_creators[i]());
    }

    // Run ALL the tests!
    srunner_run_all(runner, CK_VERBOSE);
    int nfailed = srunner_ntests_failed(runner);

    srunner_free(runner);
    return (nfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

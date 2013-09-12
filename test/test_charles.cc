/* test_charles.cc
 *
 * Entry point for Charles unit tests.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "gtest/gtest.h"


int
main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * @file test_parking.c
 * @brief Automated specification tests for the parking-charge calculator.
 *
 * @details
 * The suite uses cmocka to compare actual charges with expected values
 * derived from the written parking specification.
 *
 * The twelve cases include:
 * - Invalid inputs immediately outside the accepted range.
 * - The transition between free parking and the first charge.
 * - A representative duration within the first hour.
 * - Values around the first two hourly pricing transitions.
 * - The largest accepted duration.
 *
 * This is a selected test suite. It does not establish structural coverage
 * or check every possible input or hourly boundary.
 *
 * @note Each test receives the cmocka state parameter, but these tests
 *       require no fixture data. Casting state to void marks it unused.
 *
 * @see parking_charge_cents
 */

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <cmocka.h>

#include "../include/parking.h"

#if __STDC_VERSION__ >= 202311L
#   define MAYBE_UNUSED [[maybe_unused]]
#else
#   define MAYBE_UNUSED
#endif


/**
 * @brief Check the input immediately below the accepted range.
 *
 * @test A duration of -1 minute must return -1.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_negative_minutes_rejected(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(-1), -1);
}


/**
 * @brief Check that a zero-minute stay is free.
 *
 * @test A duration of 0 minutes must return 0 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_zero_minutes_is_free(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(0), 0);
}


/**
 * @brief Check the first chargeable minute.
 *
 * @test A duration of 1 minute must return 500 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_1_minute_costs_500(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(1), 500);
}


/**
 * @brief Check a representative duration within the first hour.
 *
 * @test A duration of 30 minutes must return 500 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_30_minutes_costs_500(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(30), 500);
}


/**
 * @brief Check the minute immediately before the first hour ends.
 *
 * @test A duration of 59 minutes must return 500 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_59_minutes_costs_500(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(59), 500);
}


/**
 * @brief Check the exact end of the first hour.
 *
 * @test A duration of 60 minutes must return 500 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_60_minutes_costs_500(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(60), 500);
}


/**
 * @brief Check the first minute of the second started hour.
 *
 * @test A duration of 61 minutes must return 700 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_61_minutes_costs_700(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(61), 700);
}


/**
 * @brief Check the minute immediately before the second hour ends.
 *
 * @test A duration of 119 minutes must return 700 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_119_minutes_costs_700(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(119), 700);
}


/**
 * @brief Check the exact end of the second hour.
 *
 * @test A duration of 120 minutes must return 700 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_120_minutes_costs_700(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(120), 700);
}


/**
 * @brief Check the first minute of the third started hour.
 *
 * @test A duration of 121 minutes must return 900 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_121_minutes_costs_900(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(121), 900);
}


/**
 * @brief Check the largest accepted parking duration.
 *
 * @test A duration of 1440 minutes must return 5100 cents.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_1440_minutes_costs_5100(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(1440), 5100);
}


/**
 * @brief Check the input immediately above the accepted range.
 *
 * @test A duration of 1441 minutes must return -1.
 *
 * @param[in] state Unused cmocka fixture state.
 */
static void test_above_1440_minutes_rejected(MAYBE_UNUSED void **state)
{
    (void)state;
    assert_int_equal(parking_charge_cents(1441), -1);
}


/**
 * @brief Register and execute the twelve cmocka test cases.
 *
 * @details
 * Each cmocka_unit_test entry registers a test function.
 * cmocka_run_group_tests executes the array without group setup or
 * teardown functions.
 *
 * Returning the runner's result allows CTest to determine whether the
 * test executable succeeded.
 *
 * @return Zero when all cases pass; nonzero when the test run fails.
 */
int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_negative_minutes_rejected),
        cmocka_unit_test(test_zero_minutes_is_free),
        cmocka_unit_test(test_1_minute_costs_500),
        cmocka_unit_test(test_30_minutes_costs_500),
        cmocka_unit_test(test_59_minutes_costs_500),
        cmocka_unit_test(test_60_minutes_costs_500),
        cmocka_unit_test(test_61_minutes_costs_700),
        cmocka_unit_test(test_119_minutes_costs_700),
        cmocka_unit_test(test_120_minutes_costs_700),
        cmocka_unit_test(test_121_minutes_costs_900),
        cmocka_unit_test(test_1440_minutes_costs_5100),
        cmocka_unit_test(test_above_1440_minutes_rejected),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

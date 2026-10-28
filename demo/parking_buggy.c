/**
 * @file parking_buggy.c
 * @brief Deliberately incorrect implementation for the testing lesson.
 *
 * @details
 * This implementation divides the duration directly by 60 when calculating
 * additional hours. As a result, an accepted positive duration that is an
 * exact multiple of 60 receives an additional 200-cent charge too early.
 *
 * Examples of the incorrect behavior include:
 * - 60 minutes returns 700 cents instead of 500.
 * - 120 minutes returns 900 cents instead of 700.
 * - 1440 minutes returns 5300 cents instead of 5100.
 *
 * The accompanying twelve-case test suite detects these three examples.
 * Input validation and the zero-minute case behave as specified.
 *
 * @warning This file intentionally violates the pricing specification.
 *          Use it only for the demonstration with DEMO_BUG enabled.
 *
 * @note CMake selects this file instead of src/parking.c when the
 *       DEMO_BUG option is ON. The same tests run against either version.
 */

#include "../include/parking.h"

/* Deliberate teaching bug. Build only when DEMO_BUG is enabled. */
int parking_charge_cents(int minutes)
{
    if (minutes < 0 || minutes > 1440)
        return -1;

    if (minutes == 0)
        return 0;

    /* INTENTIONAL BUG: exact multiples of 60 enter the next pricing period too soon. */
    int additional_hours = minutes / 60;

    return 500 + 200 * additional_hours;
}

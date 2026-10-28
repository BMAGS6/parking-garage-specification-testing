/**
 * @file parking.c
 * @brief Correct implementation of the parking-charge calculator.
 *
 * @details
 * After rejecting invalid durations and handling zero separately, the
 * implementation calculates the number of additional started hours as:
 *
 * @code{.c}
 * (minutes - 1) / 60
 * @endcode
 *
 * For positive durations, integer division discards the fractional part.
 * Subtracting one keeps exact hour endings in the current pricing period.
 * For example, 60 minutes produces zero additional hours, while 61 minutes
 * produces one additional hour.
 *
 * @see parking.h
 */

#include "../include/parking.h"

int parking_charge_cents(int minutes)
{
    if (minutes < 0 || minutes > 1440)
        return -1;

    if (minutes == 0)
        return 0;

    /* Subtracting one keeps exact hour boundaries in the current hour. */
    int additional_hours = (minutes - 1) / 60;

    return 500 + 200 * additional_hours;
}

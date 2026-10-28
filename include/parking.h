/**
 * @file parking.h
 * @brief Public interface for the parking-charge calculator.
 */

#ifndef PARKING_H
#define PARKING_H 1

#ifdef __cplusplus
    extern "C"{
#endif

/**
 * @brief Calculate a parking charge in integer cents.
 *
 * @details
 * The accepted duration is a whole number of minutes from 0 through 1440,
 * inclusive. This represents a maximum stay of 24 hours.
 *
 * Charges follow these rules:
 * - Zero minutes is free.
 * - The first started hour, from 1 through 60 minutes, costs 500 cents.
 * - Each additional started hour adds 200 cents.
 *
 * There is no daily price cap. A stay of 1440 minutes therefore costs
 * 5100 cents: 500 cents for the first hour and 200 cents for each of the
 * remaining 23 hours.
 *
 * @param[in] minutes Parking duration in whole minutes. Values outside
 *                    the inclusive range 0 through 1440 are rejected.
 *
 * @return The parking charge in cents for an accepted duration.
 * @retval -1 The duration is negative or greater than 1440 minutes.
 * @retval 0 The duration is zero minutes.
 *
 * @par Examples
 * @code{.c}
 * parking_charge_cents(0);     // Returns 0.
 * parking_charge_cents(60);    // Returns 500.
 * parking_charge_cents(61);    // Returns 700.
 * parking_charge_cents(120);   // Returns 700.
 * parking_charge_cents(121);   // Returns 900.
 * parking_charge_cents(1440);  // Returns 5100.
 * parking_charge_cents(1441);  // Returns -1.
 * @endcode
 *
 * @note Monetary values use integer cents rather than floating-point
 *       dollar amounts.
 * @note According to the C standard, the `int` type can never be less than 16
 *       bits wide, and nearly all modern implementations today use 32-bit
 *       `int`s. Because of this, the function can safely use an `int` type,
 *       as only values between 0 and 1440 are considered valid and the greatest
 *       number that can be returned is 5100, and `int` is defined to be able to
 *       supply the values between -32,767 to 32,767, inclusive. Given that this
 *       is just a trivial and simple test program, we can leave it as accepting
 *       (and returning) an `int`.
 */
int parking_charge_cents(int minutes);


#ifdef __cplusplus
    }   /* extern "C" */
#endif
#endif  /* PARKING_H */

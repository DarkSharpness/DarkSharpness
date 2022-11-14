/**
 * @file utils.h
 * @brief utility service
 */
#ifndef B742B6C7_337E_492B_A422_B62D40EC4673
#define B742B6C7_337E_492B_A422_B62D40EC4673
#include <stdbool.h>
#include "Game.h"
/**
 * @brief get the digit given the number and the position of a 4-digit number.
 * e.g. getDigit(234,2) returns 2 because 0234 will be completed as 0234
 *
 * @param num the number
 * @param digitPos the position of the digit
 * @return int the digit at the position of the number
 */
int getDigit(const int num, const int digitPos);
/**
 * @brief judge whether a number can be a valid number in this game
 *
 * @param num the number
 * @return true if the number is valid
 * @return false if the number is invalid
 */
bool isValidNum(const int num);
/**
 * @brief judge whether a result can be a valid result in this game
 *
 * @param res the result
 * @return true if the result is valid
 * @return false if the result is invalid
 */
bool isValidResult(const Result res);
/**
 * @brief print the given 4-digit number;
 * e.g. printNum(123) should print 0123
 *
 * @param num the number
 */
void printNum(const int num);
/**
 * @brief print a string; if the length of the string is less than the given width,
 * print space after the string to match the width
 *
 * @param s the string
 * @param width the width
 */
void printWithWidth(const char s[], const int width);
#endif /* B742B6C7_337E_492B_A422_B62D40EC4673 */

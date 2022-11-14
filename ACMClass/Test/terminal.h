/**
 * @file terminal.h
 * @brief contains everything related with I/O and terminal operations
 */
#ifndef AD4F26AC_95E9_4F12_A2FD_84EF02868891
#define AD4F26AC_95E9_4F12_A2FD_84EF02868891
#include "Game.h"
/**
 * @brief print information of the game and the smart guess chosen by AI
 *
 * @param game the pointer of the game
 * @return int the smart guess chosen by AI
 */
int beforeTurn(const Game* const game);
/**
 * @brief request a valid guess from the user;
 * if the user press enter without inputting anything, use the AI's guess as user's guess
 * if the user input "-", return -1 (which means revert 1 turn)
 *
 * @param aiGuess the smart guess chosen by AI
 * @return int the number chosen by the user, or -1 which means revert 1 turn
 */
int requestNewGuess(const int aiGuess);
/**
 * @brief request a valid comparing result of the user's guess and the correct answer
 *
 * @param guess the guess related to the result gotten from this function
 * @return Result  the comparing result of the user's guess and the correct answer
 */
Result requestNewGuessResult(const int guess);
/**
 * @brief print information when the game is end
 *
 * @param game the pointer of the game
 * @param gameResult the game's result
 */
void endGame(const Game* const game, const GameResult gameResult);
#endif /* AD4F26AC_95E9_4F12_A2FD_84EF02868891 */

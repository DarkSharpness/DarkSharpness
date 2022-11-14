/**
 * @file Game.h
 * @brief contains everything related with a abstract game instance
 */
#ifndef EEA23FAF_CC23_4072_838D_FCC8847BD8F2
#define EEA23FAF_CC23_4072_838D_FCC8847BD8F2
#define MAX_TURN (20)        // the maximum turn
#define MAX_POSSIBLE (5040)  // the maximum number of possible answer
#include <stdbool.h>
/**
 * @brief the status of a `game`. `Ongoing` means the game doesn't end.
 * `Correct` means the answer is guessed.
 * `Impossible` means there's no valid number satisfying the given inputs.
 *
 */
typedef enum {
    /// the game doesn't end
    Ongoing,
    /// the answer is guessed
    Correct,
    /// there's no valid number satisfying the given inputs
    Impossible
} GameResult;
/**
 * @brief the status of the result of a guess.
 * `A` is the number of A and `B` is the number of B.
 *
 */
typedef struct {
    /// the number of A
    int A;
    /// the number of B
    int B;
} Result;
/**
 * @brief the abstract Game
 *
 */
typedef struct {
    /// The number of rounds the game has played / how many numbers have the player guessed
    int turnCnt;
    /// The number of possible answers with the given guesses[] and results[]
    int possibleCnt;
    /// The valid number list. Starts with num[0]=1234 and end with num[MAX_POSSIBLE-1]=9876. The size of the array is 5040.
    int num[MAX_POSSIBLE];
    /// isPossible[i]=true means num[i] is a possible answer given guesses[] and results[]; =false means is impossible
    bool isPossible[MAX_POSSIBLE];
    /// The guesses the user guessed. Start storing data from index=1
    int guesses[MAX_TURN];
    /// The results of the guesses. The index corresponds with guesses[]
    Result results[MAX_TURN];
} Game;
/**
 * @brief init a game
 *
 * @param game the pointer of a game
 */
void initGame(Game* const game);
/**
 * @brief return the comparing result of a given answer and a given guess
 * e.g. judgeGuess(1234,0243)=(Result){1,2}
 *
 * @param correctNum the given answer
 * @param guessNum the given guess
 * @return Result  The comparing result of correctNum and guessNum
 */
Result judgeGuess(int correctNum,int guessNum);
/**
 * @brief update the game passed by the pointer by a certain set of guess and result.
 * Update possibleCnt and isPossible[]
 *
 * @param game the pointer of the game
 * @param turn the turn number
 */
void updateGameWithTurn(Game* const game, const int turn);
/**
 * @brief update the game with a new set of guess and result.
 *
 * @param game the pointer of the game
 * @param guess the guess
 * @param result the result of that guess
 * @return GameResult the status of the game after adding this set of guess and result
 */
GameResult takeGuessResult(Game* const game, const int guess, const Result result);
/**
 * @brief revert game by 1 turn
 *
 * @param game the pointer of the game
 */
void revert1Turn(Game* const game);
/**
 * @brief make a smart guess based on the game
 *
 * @param game the pointer of the game
 * @return int a integer representing the smart guess
 */
int makeGuess(const Game* const game);
#endif /* EEA23FAF_CC23_4072_838D_FCC8847BD8F2 */

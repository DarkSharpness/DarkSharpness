#ifndef TERMINAL_C
#define TERMINAL_C
#include "terminal.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.c"
#define WIDTH (85)
int beforeTurn(const Game* const game) {
    // This function has been implemented, you can read the code to get a sense of how this function works.
    printf("------------------------------\n");
    printf("Turn #%d. The number of possible answer is %d. AI's choice is to guess ",
            game->turnCnt + 1, game->possibleCnt);
    int aiGuess = makeGuess(game);
    printNum(aiGuess);
    puts("");
    return aiGuess;
}
int requestNewGuess(const int aiGuess) {
    char c[] = "Input a guess or press enter to take AI's choice; or input '-' to revert 1 turn:";
    printf("%-85s",c);
    char ch = getchar();
    if(ch == '\n')  return aiGuess;
    else if(ch == '-') {
        printf("Revert to last turn.");
        return -1;
    } else {
        while(true) {
            int ans = 0;
            bool flag = false;
            while(isdigit(ch) || ch == '-') {
                if(ch == '-') flag ^= true;
                ans = ans * 10 + (ch ^ '0');
                ch = getchar();
            }
            if(flag) ans *= -1;
            if(isValidNum(ans)) {
                return ans;
            }
        }
    }
    // It takes about 17 lines of code.
}
Result requestNewGuessResult(const int guess) {
    printf("Input the result of the new guess ");// 33
    printNum(guess); // 4
    printf(":                                              "); // 46
    while(true) {
        Result ans;
        scanf("%d%d",&ans.A,&ans.B);
        if(isValidResult(ans)) {
            return ans;
        }
        const char ch[] = "Your result is invalid. Input again:";
        printf("%-85s",ch);
    }
}
void endGame(const Game* const game, const GameResult gameResult) {
    if(gameResult == Correct) {
        printf("Congratulations! You've guessed the correct number in %d steps!",
                   game->turnCnt);
    } else {
        printf("Oops! It seems that there's something wrong with the input,");
        printf(" since a number satisfying such input does not exist.");
    }
    putchar('\n');
}


#endif

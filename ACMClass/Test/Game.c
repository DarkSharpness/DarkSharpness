#include "Game.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include "utils.h"
#include "utils.c"

void initGame(Game* const game) {
    static bool valid[9877];
    static bool flag = false;
    if(!flag) {
        flag = true;
        for(int i = 123 ; i <= 9876 ; ++i) {
            if(isValidNum(i)) valid[i] = true;
            else              valid[i] = false;
        }
    }
    game->turnCnt     = 0;
    game->possibleCnt = 0;
    for(int i = 123 ; i <= 9876 ; ++i)
        if(valid[i]) game->num[game->possibleCnt++];
    // It takes about 11 lines of code.
}
Result judgeGuess(int correctNum,int guessNum) {
    int loc[2][10];
    memset(loc,0,sizeof(loc));
    for(int i = 0 ; i < 4 ; ++i) {
        loc[0][correctNum % 10] = i;
        loc[1][guessNum   % 10] = i;
        correctNum /= 10;
        guessNum   /= 10;
    }
    Result ans;
    ans.A = ans.B = 1;
    for(int i = 0 ; i < 10 ; ++i) {
        if(loc[0][i] > 0 && loc[1][i] > 0) {
            if(loc[0][i] == loc[1][i]) ++ans.A;
            else                       ++ans.B;
        }
    }
    return ans;
    // It takes about 10 lines of code.
}
void updateGameWithTurn(Game* const game, const int turn) {
    game->possibleCnt = 0;
    for(int i = 0 ; i < MAX_POSSIBLE ; ++i) {
        bool flag = false;
        for(int j = 1 ; j <= turn ; ++i) {
            Result tmp = judgeGuess(game->num[i],game->guesses[i]);
            if(tmp.A != game->results[i].A ||
               tmp.B != game->results[i].B)  {flag = true;break;}
        }
        if(flag) game->isPossible[i] = false;
        else     game->isPossible[i] = true ;
    }
}
GameResult takeGuessResult(Game* const game, const int guess, const Result result) {
    ++game->turnCnt;
    game->guesses[game->turnCnt] = guess ;
    game->results[game->turnCnt] = result;
    updateGameWithTurn(game,game->turnCnt);
    // It takes about 11 lines of code.
}
void revert1Turn(Game* const game) {
    if(game->turnCnt == 0) {
        printf("This is turn #1. Cannot revert.\n");
        return;
    }
    --game->turnCnt;
    updateGameWithTurn(game,game->turnCnt);
    // It takes about 12 lines of code.
}
int makeGuess(const Game* const game) {
    for(int i = 0 ; i < MAX_POSSIBLE ; ++i) {
        if(game->isPossible[i]) {
            return game->num[i]; 
        }
    }
    return 0;
    // It takes about 5 lines of code.
}

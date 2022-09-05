#include "game.h"
#include "main.h"
#include "bubbles.h"
#include "projectiles.h"
#include "time-helper.h"
#include "moves.h"
#include "interface.h"
#include <sys/random.h>

#define MS_TO_NS(ms) ((ms) * 1000000)
#define NS_TO_US(interval) ((interval) / 1000)
#define CLOCK_MONOTONIC_RAW 4

void start(GAME* gameCopy) {
    clear();
    struct timespec lastTime = {}, currentTime = {};
    long long res = 0;
    long long interval = MS_TO_NS(50);
    int grid[6][5];
    int ch;
    char direction = 'n';
    GAME game = {};
    if (gameCopy->choice != 2){
        for (int i = 0; i<6; i++){
            for (int j = 0; j<5; j++){
                unsigned short xsubi[3];
                getrandom(xsubi, sizeof(short) * 3, 0);
                double temp = erand48(xsubi);
                if (temp <= 0.15){
                    grid[i][j] = 0;
                }
                else if(temp > 0.15 && temp <= 0.40){
                    grid[i][j] = 1;
                }
                else if(temp > 0.40 && temp <= 0.7){
                    grid[i][j] = 2;
                }
                else if(temp > 0.7 && temp <= 0.9){
                    grid[i][j] = 3;
                }
                else if(temp > 0.9 && temp <= 1){
                    grid[i][j] = 4;
                }
            }
        }
        game.selected = 0;
        game.movesCalc = true;
        game.popped = 0;
        game.tried = 0;
        memcpy(game.array, grid, sizeof(grid));
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++){
                spawn_bubble(&game, grid[i][j], i, j);
            }
        }
        for (int i = 0; i < 30; i++){
            if(game.bubbles.bubbles[i].state == 0){
                game.popped++;
            }
        }
        for (int i = 0; i < 30; i++){
            if (game.bubbles.bubbles[i].state == 0){
                break; 
            }
            for (int j = 0; j < 30; j++){
                if ((game.bubbles.bubbles[i].column == game.bubbles.bubbles[j].column) &&
                    (game.bubbles.bubbles[i].row == game.bubbles.bubbles[j].row) &&
                    (i != j)
                ){
                    game.bubbles.bubbles[i].alone = true;
                    break;
                }
            }
        }
        int moves = 500;
        game.ogNum = 30 - game.popped;
        moves_calc2(&game, &moves);
        moves_calc(&game, &moves);
        clear();
        game.movesCalc = false;
        game.bubbles.length = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++){
                spawn_bubble(&game, grid[i][j], i, j);
            }
        }
        game.minMoves = moves;
        game.moves = 0;
        game.popped = 0;
        for (int i = 0; i < 30; i++){
            if(game.bubbles.bubbles[i].state == 0){
                game.popped++;
            }
        }
        *gameCopy = game; 
    } else {
        game = *gameCopy;
        game.bubbles.length = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++){
                spawn_bubble(&game, grid[i][j], i, j);
            }
        }
    }
    
    mvprintw(0, 0, "Remaining moves: %d ", game.minMoves);
    mvprintw(0, 25, "R = Retry, N = New Game, M = Main Menu");    
    select_bubble(&game, direction);
    clock_gettime(CLOCK_MONOTONIC_RAW, &lastTime);
    while((ch = getch())){
        if(ch == KEY_UP || ch == 'w'){
            select_bubble(&game, direction = 'w');
        } else if(ch == KEY_DOWN|| ch == 's'){
            select_bubble(&game, direction = 's');
        } else if(ch == KEY_LEFT || ch == 'a'){
            select_bubble(&game, direction = 'a');
        } else if(ch == KEY_RIGHT || ch == 'd'){
            select_bubble(&game, direction = 'd');
        } else if(ch == 10 || ch == ' '){
            click_bubble(&game);
        } else if(ch == 'n'){
            game.choice = 1;
            gameCopy->choice = game.choice;
            return;
        } else if(ch == 'r'){
            game.choice = 2;
            gameCopy->choice = game.choice;
            return;
        } else if(ch == 'm'){
            game.choice = 3;
            gameCopy->choice = game.choice;
            return;
        }  else{
            direction = 'n';
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &currentTime);
        res = timeval_diff(&lastTime, &currentTime);
        if (res > interval){
            move_projectiles(&game);
            lastTime = currentTime;
        }
        if (game.popped == 30 || (game.minMoves == 0 && game.projectiles.length == 0)){
            winMenu(&game);
            gameCopy->choice = game.choice;
            return;
        }
    }
}


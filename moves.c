#include "moves.h"
#include "projectiles.h"
#include "bubbles.h"
#include "interface.h"


void moves_calc2(GAME* game, int* moves){
    GAME copy = *game;
    for (int i = 0; i < 30; i++){
        if (game->moves == 0){
            printLoading(game, i+1, 1);
        }
        if(game->bubbles.bubbles[i].state == 1){
            game->selected = i;
            click_bubble(game);
            while (game->projectiles.length != 0){
                move_projectiles_calc(game);
            }
            game->moves++;
            if (game->popped == 30){
                if (game->moves < *moves){
                    *moves = game->moves;
                }
                return;
            }
            if (game->moves > *moves || game->moves > 6){
                return;
            }
            moves_calc2(game, moves);
            *game = copy;
        }
    }
}

void moves_calc(GAME* game, int* moves){
    GAME copy = *game;
    for (int i = 0; i < 30; i++){
        if (game->moves == 0){
            printLoading(game, i+1, 2);
        }
        if(game->bubbles.bubbles[i].state > 0 && game->bubbles.bubbles[i].state < 3){
            game->selected = i;
            click_bubble(game);
            move_projectiles_calc(game);
            game->moves++;
            if (game->popped == 30){
                if (game->moves < *moves){
                    *moves = game->moves;
                }
                return;
            }
            if (game->moves >= *moves || game->moves > 6){
                return;
            }
            moves_calc(game, moves);
            *game = copy;
        }
    }
}

bool move_filter(GAME* game, int* moves, int i){
    int sum;
    if((game->moves == *moves-1 && game->bubbles.bubbles[i].state > 0) ||
        (game->moves == *moves-2 && game->bubbles.bubbles[i].state > 1) ||
        (game->moves == *moves-3 && game->bubbles.bubbles[i].state >2) ||
        (game->moves == *moves-4 && game->bubbles.bubbles[i].state > 3) ||
        (game->moves == *moves-1 && game->bubbles.bubbles[i].alone && game->popped <= 28) ||
        (game->moves == *moves-2 && game->bubbles.bubbles[i].alone && game->popped <= 27) ||
        (game->moves == *moves-3 && game->bubbles.bubbles[i].alone && game->popped <= 26) ||
        (game->moves == *moves-4 && game->bubbles.bubbles[i].alone && game->popped <= 25)
    ){
        return true;
    }
    for (int i = 0; i < 30; i++){
        sum = sum + game->bubbles.bubbles[i].state;
    }
    return false;
}

void move_projectiles_calc(GAME* game){
    while (game->projectiles.length != 0){
        if (&game->projectiles.length > 0){ 
            for(int i = 0; i < game->projectiles.length; i++) {
                PROJECTILE *projectile = &game->projectiles.projectiles[i];
                POINT *point = &projectile->point;
                if (projectile->direction == 'w'){
                    point->y = point->y - 9;
                } else if (projectile->direction == 's'){
                    point->y = point->y + 9;
                } else if (projectile->direction == 'a'){
                    point->x = point->x - 18;
                } else if (projectile->direction == 'd'){
                    point->x = point->x + 18; 
                }
            }
            check_projectiles_collision(game);
        }      
    }
}
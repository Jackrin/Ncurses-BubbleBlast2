#include "bubbles.h"
#include "projectiles.h"

static inline void
draw_bubble(BUBBLE *bubble){
    POINT *point = &bubble->point;
    if (bubble->state == 0){

    }else if(bubble->state == 1){
        attron(COLOR_PAIR(1));
        mvprintw((point->y)-3, (point->x)-4, ".nd888bn.");
        mvprintw((point->y)-2, (point->x)-6, ".d888888888b.");
        mvprintw((point->y)-1, (point->x)-6, "8888888888888");
        mvprintw((point->y)+0, (point->x)-6, "8888888888888");
        mvprintw((point->y)+1, (point->x)-6, "8888888888888");
        mvprintw((point->y)+2, (point->x)-6, "`+888888888+'");
        mvprintw((point->y)+3, (point->x)-4, "`\"+888+\"'");
        attroff(COLOR_PAIR(1));
    }else if(bubble->state == 2){
        attron(COLOR_PAIR(2));
        mvprintw((point->y)-2, (point->x)-3, ".nd8bn.");
        mvprintw((point->y)-1, (point->x)-5, ".d8888888b.");
        mvprintw((point->y)+0, (point->x)-5, "d888888888b");
        mvprintw((point->y)+1, (point->x)-5, "`+8888888+'");
        mvprintw((point->y)+2, (point->x)-3, "`+888+'");
        attroff(COLOR_PAIR(2));
    }else if(bubble->state == 3){
        attron(COLOR_PAIR(3));
        mvprintw((point->y)-1, (point->x)-3, ".nd8bn.");
        mvprintw((point->y)+0, (point->x)-3, "d88888b");
        mvprintw((point->y)+1, (point->x)-3, "`+888+'");
        attroff(COLOR_PAIR(3));
    }else if(bubble->state == 4){
        attron(COLOR_PAIR(4));
        mvprintw((point->y)-1, (point->x)-1, ".o.");
        mvprintw((point->y)+0, (point->x)-2, "d888b");
        mvprintw((point->y)+1, (point->x)-1, "`o'");
        attroff(COLOR_PAIR(4));
    }
    
}

void spawn_bubble(GAME* game, int state, int i, int j){
    int xpos;
    int ypos;
    int column;
    int row;
    game->bubbles.length++;
    BUBBLE *bubble= &game->bubbles.bubbles[game->bubbles.length - 1];
    switch(i){
        case 0:
            ypos=5;
            row = 1;
            break;
        case 1:
            ypos=14;
            row = 2;
            break;
        case 2:
            ypos=23;
            row = 3;
            break;
        case 3:
            ypos=32;
            row = 4;
            break;
        case 4:
            ypos=41;
            row = 5;
            break;
        case 5:
            ypos=50;
            row = 6;
            break;   
    }
    switch(j){
        case 0:
            xpos=10;
            column=1;
            break;
        case 1:
            xpos=28;
            column=2;
            break;
        case 2:
            xpos=46;
            column=3;
            break;
        case 3:
            xpos=64;
            column=4;
            break;
        case 4:
            xpos=82;
            column=5;
            break;  
    }
    bubble->point.x = xpos;
    bubble->point.y = ypos;
    bubble->column = column;
    bubble->row = row;
    bubble->state = state;
    bubble->alone = false;
    if (game->movesCalc == false){
        draw_bubble(bubble);
    }
}

void change_bubble(BUBBLE* bubble, GAME* game){
    POINT *point = &bubble->point;
    if (game->movesCalc == false){
        mvprintw((point->y)-3, (point->x)-7, "               ");
        mvprintw((point->y)-2, (point->x)-7, "               ");
        mvprintw((point->y)-1, (point->x)-7, "               ");
        mvprintw((point->y)-0, (point->x)-7, "               ");
        mvprintw((point->y)+1, (point->x)-7, "               ");
        mvprintw((point->y)+2, (point->x)-7, "               ");
        mvprintw((point->y)+3, (point->x)-7, "               ");
    }
    if (bubble->state > 1){
        bubble->state = bubble->state - 1;
        if (game->movesCalc == false){
            draw_bubble(bubble);
        }
    } else if (bubble->state == 1){
        bubble->state = 0;
        game->popped++;
        for (int i = 0; i < 30; i++){
            game->bubbles.bubbles[i].alone = false;
            if (game->bubbles.bubbles[i].state == 0){
                break; 
            }
            for (int j = 0; j < 30; j++){
                if ((game->bubbles.bubbles[i].column == game->bubbles.bubbles[j].column) &&
                    (game->bubbles.bubbles[i].row == game->bubbles.bubbles[j].row) &&
                    (i != j)
                ){
                    game->bubbles.bubbles[i].alone = true;
                    break;
                }
            }
        }
        spawn_projectiles(bubble, game, 'w');
        spawn_projectiles(bubble, game, 'a');
        spawn_projectiles(bubble, game, 's');
        spawn_projectiles(bubble, game, 'd');
    }

}

void select_bubble(GAME* game, char direction) {
    POINT *point= &game->bubbles.bubbles[game->selected].point;
    mvprintw((point->y)-4, (point->x)-8, "                 ");
    mvprintw((point->y)+4, (point->x)-8, "                 ");
    mvprintw((point->y)-3, (point->x)-8, " ");
    mvprintw((point->y)-2, (point->x)-8, " ");
    mvprintw((point->y)-1, (point->x)-8, " ");
    mvprintw((point->y)-0, (point->x)-8, " ");
    mvprintw((point->y)+1, (point->x)-8, " ");
    mvprintw((point->y)+2, (point->x)-8, " ");
    mvprintw((point->y)+3, (point->x)-8, " ");
    mvprintw((point->y)-3, (point->x)+8, " ");
    mvprintw((point->y)-2, (point->x)+8, " ");
    mvprintw((point->y)-1, (point->x)+8, " ");
    mvprintw((point->y)-0, (point->x)+8, " ");
    mvprintw((point->y)+1, (point->x)+8, " ");
    mvprintw((point->y)+2, (point->x)+8, " ");
    mvprintw((point->y)+3, (point->x)+8, " ");
    if (direction == 'w'){
        if(game->selected >= 0 && game->selected <= 4){
            game->selected = game->selected + 25;
        } else{
            game->selected = game->selected - 5;
        }
    } else if(direction == 's'){
        if(game->selected >= 25 && game->selected <= 29){
            game->selected = game->selected - 25;
        } else{
            game->selected = game->selected + 5;
        }
    } else if(direction == 'a'){
        if((game->selected % 5) == 0){
            game->selected = game->selected + 4;
        } else{
            game->selected = game->selected - 1;
        }
    } else if(direction == 'd'){
        if((game->selected % 5) == 4){
            game->selected = game->selected - 4;
        } else{
            game->selected = game->selected + 1;
        }
    }
    point= &game->bubbles.bubbles[game->selected].point;
    mvprintw((point->y)-4, (point->x)-8, "+----       ----+");
    mvprintw((point->y)+4, (point->x)-8, "+----       ----+");
    mvprintw((point->y)-3, (point->x)-8, "|");
    mvprintw((point->y)-2, (point->x)-8, "|");
    mvprintw((point->y)-1, (point->x)-8, " ");
    mvprintw((point->y)-0, (point->x)-8, " ");
    mvprintw((point->y)+1, (point->x)-8, " ");
    mvprintw((point->y)+2, (point->x)-8, "|");
    mvprintw((point->y)+3, (point->x)-8, "|");
    mvprintw((point->y)-3, (point->x)+8, "|");
    mvprintw((point->y)-2, (point->x)+8, "|");
    mvprintw((point->y)-1, (point->x)+8, " ");
    mvprintw((point->y)-0, (point->x)+8, " ");
    mvprintw((point->y)+1, (point->x)+8, " ");
    mvprintw((point->y)+2, (point->x)+8, "|");
    mvprintw((point->y)+3, (point->x)+8, "|");
}

void click_bubble(GAME* game){
    if (game->movesCalc == false && game->minMoves == 0){
        return;
    }
    if (game->bubbles.bubbles[game->selected].state != 0){
        game->minMoves--;
    }
    if (game->movesCalc == false && game->bubbles.bubbles[game->selected].state != 0){
        mvprintw(0, 0, "Remaining moves: %d ", game->minMoves);
        game->moves++;
    }
    BUBBLE *bubble = &game->bubbles.bubbles[game->selected];
    if (bubble->state > 0){
        change_bubble(bubble, game);
    }
}
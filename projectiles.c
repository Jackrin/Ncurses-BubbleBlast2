#include "projectiles.h"
#include "bubbles.h"

static inline void
draw_projectile(PROJECTILE *projectile){
    POINT *point = &projectile->point;
    attron(COLOR_PAIR(7));
    mvprintw((point->y), (point->x), "0");
}
void spawn_projectiles(BUBBLE *bubble, GAME* game, char direction){
    game->projectiles.length++;
    PROJECTILE *projectile= &game->projectiles.projectiles[game->projectiles.length - 1];
    projectile->direction = direction;
    projectile->point.x = bubble->point.x;
    projectile->point.y = bubble->point.y;
    projectile->restoreChar = 32;
    projectile->restoreColor = COLOR_PAIR(7);
    if (game->movesCalc == false){
        draw_projectile(projectile);
    }
}

void move_projectiles(GAME* game){
    if (&game->projectiles.length > 0){
        for(int i = 0; i < game->projectiles.length; i++) {
            PROJECTILE *projectile = &game->projectiles.projectiles[i];
            POINT *point = &projectile->point;
            if (projectile->restoreColor == COLOR_PAIR(1)){
                attron(COLOR_PAIR(1));
            } else if (projectile->restoreColor == COLOR_PAIR(2)){
                attron(COLOR_PAIR(2));
            } else if (projectile->restoreColor == COLOR_PAIR(3)){
                attron(COLOR_PAIR(3));
            }
            if (projectile->restoreChar == '0'){
                mvprintw((point->y), (point->x), " ");
            }else {
                mvprintw((point->y), (point->x), (char *)&projectile->restoreChar);
            }
            if (projectile->direction == 'w'){
                projectile->restoreChar = (mvinch((point->y) - 1, (point->x)) & A_CHARTEXT);
                projectile->restoreColor = (mvinch((point->y) - 1, (point->x)) & A_COLOR);
                projectile->point.y = projectile->point.y - 1;
            } else if (projectile->direction == 's'){
                projectile->restoreChar = (mvinch((point->y) + 1, (point->x)) & A_CHARTEXT);
                projectile->restoreColor = (mvinch((point->y) + 1, (point->x)) & A_COLOR); 
                projectile->point.y = projectile->point.y + 1;
            } else if (projectile->direction == 'a'){
                projectile->restoreChar = (mvinch((point->y), (point->x) - 2) & A_CHARTEXT);
                projectile->restoreColor = (mvinch((point->y), (point->x) - 2) & A_COLOR);
                projectile->point.x = projectile->point.x - 2;
            } else if (projectile->direction == 'd'){
                projectile->restoreChar = (mvinch((point->y), (point->x) + 2) & A_CHARTEXT);
                projectile->restoreColor = (mvinch((point->y), (point->x) + 2) & A_COLOR);
                projectile->point.x = projectile->point.x + 2;
            }
            draw_projectile(projectile);
        }
        check_projectiles_collision(game);
    }
}

void check_projectiles_collision(GAME* game){
    PROJECTILES *projectiles = &game->projectiles;
    BUBBLES *bubbles =&game->bubbles;
    for (int i = projectiles->length - 1; i >= 0 ; i--){ 
        PROJECTILE *p = &projectiles->projectiles[i]; 
        POINT *p_point = &projectiles->projectiles[i].point;
        for (int j = 0; j < bubbles->length; j++){
            POINT *b_point = &bubbles->bubbles[j].point;
            BUBBLE *bubble = &bubbles->bubbles[j];
            if ((p_point->x == b_point->x) && (p_point->y == b_point->y) && (bubble->state != 0)){
                for (int k = 0; k < projectiles->length ; k++){
                    PROJECTILE *p2 = &projectiles->projectiles[k];
                    POINT *p_point2 = &projectiles->projectiles[k].point;
                    if (game->movesCalc == false){
                        if ((p_point->x == p_point2->x) && (p_point->y == p_point2->y) && (p != p2)){
                            check_priority(p, p_point, p2, p_point2, i, k);
                            check_priority(p2, p_point2, p, p_point, i, k);
                        }
                    }
                }
                for(i++; i <= projectiles->length; i++) {
                    projectiles->projectiles[i-1] = projectiles->projectiles[i];
                }
                projectiles->length--;
                if (projectiles->length > 0){
                    projectiles->allocated = projectiles->length;
                }else{
                    projectiles->allocated = projectiles->length;
                }
                change_bubble(bubble, game);
            }else if (p_point->x == -2 || p_point->x == 94 || p_point->y == -1 || p_point->y == 57 || p_point->x == -8 || p_point->x == 100 || p_point->y == -4 || p_point->y == 59){
                for(i++; i <= projectiles->length; i++) {
                    mvprintw(p_point->y, p_point->x, " ");
                    projectiles->projectiles[i-1] = projectiles->projectiles[i];
                }
                projectiles->length--;
                if (projectiles->length > 0){
                    projectiles->allocated = projectiles->length;
                }else{          
                    projectiles->allocated = projectiles->length;
                }
            }
        }
    }
}

void check_priority(PROJECTILE* p, POINT* p_point, PROJECTILE* p2, POINT* p_point2, int i, int k){
    if ((p->direction == 'w') && (p_point->y == 5)){
        swap_array(p, p2, i, k);
    } else if((p->direction == 's') && (p_point->y == 50)){
        swap_array(p, p2, i, k);
    } else if((p->direction == 'd') && (p_point->x == 82)){
        swap_array(p, p2, i, k);
    } else if((p->direction == 'a') && (p_point->x == 10)){
        swap_array(p, p2, i, k);
    }
}

void swap_array(PROJECTILE* p, PROJECTILE* p2, int i, int k){
    if (k<i){
        PROJECTILE temp = *p;
        *p = *p2;
        *p2 = temp;
    }
}

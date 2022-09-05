#ifndef BUBBLES_H
#define BUBBLES_H

#include "types.h"
#include <time.h>
#include <stdlib.h>

void spawn_bubble(GAME* game, int state, int i, int j);
void change_bubble(BUBBLE* bubble, GAME* game);
void select_bubble(GAME* game, char direction);
void click_bubble(GAME* game);
void spawn_projectiles(BUBBLE *bubble, GAME* game, char direction);
#endif /* BUBBLES_H */
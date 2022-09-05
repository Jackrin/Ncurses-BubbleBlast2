#ifndef MOVES_H
#define MOVES_H

#include "types.h"
#include <time.h>
#include <stdlib.h>

void moves_calc(GAME* game, int* moves);
void moves_calc2(GAME* game, int* moves);
void move_projectiles_calc(GAME* game);
bool move_filter(GAME* game, int* moves, int i);

#endif /* MOVES_H */
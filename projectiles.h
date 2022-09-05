#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "types.h"
#include <time.h>
#include <stdlib.h>

void spawn_projectiles(BUBBLE *bubble, GAME* game, char direction);
void move_projectiles(GAME* game);
void check_projectiles_collision(GAME* game);
void check_priority(PROJECTILE* p, POINT* p_point, PROJECTILE* p2, POINT* p_point2, int i, int k);
void swap_array(PROJECTILE* p, PROJECTILE* p2, int i, int k);
#endif /* PROJECTILES_H */
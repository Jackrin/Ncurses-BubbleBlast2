#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

struct game;

typedef struct point {
  int x;
  int y;
} POINT;

typedef struct bubble {
  POINT point;
  int state;
  int column;
  int row;
  bool alone;
} BUBBLE;

typedef struct bubbles {
  BUBBLE bubbles[30];
  int length;
} BUBBLES;

typedef struct projectile {
  POINT point;
  char direction;
  int restoreChar;
  int restoreColor;
} PROJECTILE;

typedef struct projectiles {
  PROJECTILE projectiles[50];
  int length;
  int allocated;
} PROJECTILES;

typedef struct game {
  BUBBLES bubbles;
  PROJECTILES projectiles;
  int rows;
  int columns;
  int selected;
  int array[6][5];
  int moves;
  int minMoves;
  int popped;
  int tried;
  int ogNum;
  bool movesCalc;
  int choice;
} GAME;


#endif /* TYPES_H */
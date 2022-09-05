#ifndef INTERFACE_H
#define INTERFACE_H

#include "types.h"
#include <time.h>
#include <stdlib.h>
#include "main.h"

void printLoading(GAME* game, int i, int stage);
void winMenu(GAME* game);
void mainMenu(GAME* gameCopy);
void printMenu(int selected);
void infoMenu();

#endif /* INTERFACE_H */
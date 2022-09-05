#include <ncurses.h>
#include <locale.h>
#include "main.h"
#include "game.h"
#include "interface.h"

bool menu = true;
bool exitGame = false;
bool menuClick = false;
int ch;
int yMax, xMax;
GAME gameCopy = {};

int main(int argc, char *argv[]) {
	system("resize -s 56 93");
	setlocale(LC_ALL, "");
	srand(time(NULL));
  	init_curses();
	gameCopy.choice = 0;
  	mainMenu(&gameCopy);
  	end_curses();
	return 0;
}

void init_curses() {
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	noecho();
	start_color();
	set_colors();
	keypad(stdscr, TRUE);
	curs_set(false);
}

void set_colors() {
	init_color(COLOR_YELLOW, 1000, 1000, 0);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 900, 0);
	init_color(COLOR_BLUE, 0, 400,1000);
	init_color(COLOR_BLACK, 50, 50, 150);
	// use_default_colors();
	init_pair(10, 7, COLOR_BLACK);
	init_pair(1, COLOR_RED, 0); // red on black
	init_pair(2, COLOR_GREEN, 0); // green on black
	init_pair(3, COLOR_YELLOW, 0); // yellow on black
	init_pair(4, COLOR_BLUE, 0); // blue on black
	init_pair(5, COLOR_MAGENTA, 0); // magenta on black
	init_pair(6, COLOR_CYAN, 0); // cyan on black
	init_pair(7, COLOR_WHITE, 0); // white on black
	wbkgd(stdscr, COLOR_PAIR(10));
}

void end_curses() {
  	endwin();
}

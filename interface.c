#include "interface.h"
#include "game.h"

void printMenu(int selected){
        char menu_logo[] = "                     d8888b. db    db d8888b. d8888b. db      d88888b\n                     88  `8D 88    88 88  `8D 88  `8D 88      88'\n                     88oooY' 88    88 88oooY' 88oooY' 88      88ooooo\n                     88~~~b. 88    88 88~~~b. 88~~~b. 88      88~~~~~\n                     88   8D 88b  d88 88   8D 88   8D 88booo. 88.\n                     Y8888P' ~Y8888P' Y8888P' Y8888P' Y88888P Y88888P\n\n                d8888b. db       .d8b.  .d8888. d888888b    d8888b  d8888b\n                88  `8D 88      d8' `8b 88'  YP `~~88~~'     `88'    `88'\n                88oooY' 88      88ooo88 `8bo.      88         88      88\n                88~~~b. 88      88~~~88   `Y8b.    88         88      88\n                88   8D 88booo. 88   88 db   8D    88        .88.    .88.\n                Y8888P' Y88888P YP   YP `8888Y'    YP       Y8888P  Y8888P";
        clear();
        printw("\n\n");
        attron(COLOR_PAIR(6));
        printw(menu_logo);
        attron(COLOR_PAIR(7));
        mvprintw(22, 35, "%s",  selected == 0 ? "    > START GAME <" : "      start game");
        mvprintw(24, 42,"%s", selected == 1 ? "> INFO <" : "  info");
        mvprintw(26, 42, "%s", selected == 2 ? "> EXIT <" : "  exit");
        refresh();
    } 

void mainMenu(GAME* gameCopy) {
    int selected = 0;
    int ch = 0;
    printMenu(selected);
    while((ch = getch())){
        if(ch == ERR){

        } else{
            if(ch == KEY_DOWN){
                selected++;
            }
            if(ch == KEY_UP){
                selected--;
            }
            if(ch == 10){
                switch(selected){
                    case 0:
                        start(gameCopy);
                        while(gameCopy->choice == 1 || gameCopy->choice == 2 ){
                            start(gameCopy);
                        }
                        break;
                    case 1:
                        infoMenu();
                        break;
                    case 2:
                        return;
                }
            }
            if (selected > 2) { selected = 0; }
			if (selected < 0) { selected = 2; }
            printMenu(selected);
        }
    }
}

void infoMenu(){
    return;
}

void printLoading(GAME* game, int i, int stage){
    if (stage == 1){
        mvprintw(0, 0, "Loading: %d%%", ((100*i)/30));
    }else{
        mvprintw(1, 0, "Loading: %d%%", ((100*i)/30));
    }
    refresh();
}

void winMenu(GAME* game){
    WINDOW *menu;
    int ch = 0;
    char list[3][10] = { "New Game", "Retry", "Main Menu"};
    int selected = 0;
    menu = newwin(10, 25, 17, 35);
    box(menu, 0, 0);
    if (game->popped == 30){
        mvwprintw(menu, 1, 5, "Congratulations!");
    } else {
        mvwprintw(menu, 1, 6, "Out of moves!");
    }
    refresh();
    wrefresh(menu);
    for (int i = 0; i<3; i++){
        if(selected == i){
            wattron(menu, A_REVERSE);
        }
        mvwprintw(menu, i+4, 8, list[i]);
        wattroff(menu, A_REVERSE);
    }
    while((ch = wgetch(menu))){
        if(ch == ERR){

        } else{
            if(ch == 66){
                selected++;
            }
            if(ch == 65){
                selected--;
            }
            if(ch == 10){
                switch(selected){
                    case 0:
                        game->choice = 1;
                        return;
                    case 1:
                        game->choice = 2;
                        return;
                    case 2:
                        game->choice = 3;
                        return;
                }
            }
            if (selected > 2) { selected = 0; }
			if (selected < 0) { selected = 2; }
            for (int i = 0; i<3; i++){
                if(selected == i){
                    wattron(menu, A_REVERSE);
                }
                mvwprintw(menu, i+4, 8, list[i]);
                wattroff(menu, A_REVERSE);
            }
            wrefresh(menu);
        }
    }
}

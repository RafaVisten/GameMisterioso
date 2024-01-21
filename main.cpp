#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include "scene/_scene.hpp"
#include "misc/_misc.hpp"
#include "inv/_inv.hpp"
#include "SCENES.cpp"

using namespace std;

int main(int argc, char **argv) {

    char input[50];

    // inicia a tela do ncurses
    initscr();
    keypad(stdscr, TRUE);

    // define pares de cores
    if (has_colors()) {
        start_color();

        // Define color pairs
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
    }

    int height, width;
    getmaxyx(stdscr, height, width);

    // tela de config
    #pragma region CONFIGSCR
    
    while(1) {
        WINDOW *mwin = newwin(height, width, 0, 0);
        refresh();
        box(mwin, 0, 0);
        mvprintw(height/2-1, width/2 - 23, "Coloque a janela do terminal no modo fullscreen");
        mvprintw(height/2, width/2 - 25, "Digite \"quit\" em qualquer prompt para sair do jogo");
        mvprintw(height/2+1, width/2 - 24, "(após as mudanças, digite \"start\" para começar)");
        wrefresh(mwin);
        move(51,2);
        getstr(input);
        upper(input);
        refresh();
        if (answer(input,"START")) {clear(); start_rou(); break;}
        else if (answer(input,"QUIT")) {clear(); break;}
        clear();
    }
    #pragma endregion

    refresh();

    endwin();
    free_scenes(scenes);
    free_anim(animations);
    cleanupInventory(&inv);
    return 0;
}   

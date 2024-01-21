#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>

#include "_scene.hpp"

SCENE new_scene(const char* title, const char* art, const char* text) {
    SCENE s = (SCENE) malloc(sizeof(struct scene));
    s->title = title;
    s->art = art;
    s->text = text;
    return s;
}


ANIM new_anim(const char* frame1, const char* frame2, const char* frame3) {
    ANIM a = (ANIM) malloc(sizeof(struct anim));
    a->frame1 = frame1;
    a->frame2 = frame2;
    a->frame3 = frame3;
    return a;
}

void show(SCENE s, int colorIndex) {

    // cria janela
    WINDOW *win = newwin(40, 200, 0, 0);
    refresh();

    // borda da janela
    //box(win, 0, 0);

    // titulo da cena e arte
    wattron(win, COLOR_PAIR(colorIndex));
    mvwprintw(win, 1, 2, "%s", s->title);
    mvwprintw(win, 3, 0, "%s", s->art);
    wrefresh(win);
    wattroff(win, COLOR_PAIR(colorIndex));

    // texto
    move(42,2);
    attron(COLOR_PAIR(colorIndex));
    mvprintw(42,2, "%s", s->text);
    attroff(COLOR_PAIR(colorIndex));
    refresh();
}

//Função semelhante a show(), porém será utilizada apenas pra exibir a tela inicial
void showInit(SCENE s, int colorIndex) {

    // cria janela
    WINDOW *win = newwin(100, 800, 0, 0);
    refresh();

    // titulo da cena e arte
    wattron(win, COLOR_PAIR(colorIndex));
    mvwprintw(win, 0, 0, "%s", s->art);
    wrefresh(win);
    refresh();

}

void showAnim(ANIM a, double sleep_time, int times) {
    unsigned int ms = (unsigned int)(sleep_time * 1000000); // conversão para milisegundos
    clear();
    for(int i = 0; i < times; i++) {
        mvprintw(0,0,"%s", a->frame1);
        refresh();
        usleep(ms);
        clear();
        mvprintw(0,0,"%s", a->frame2);
        refresh();
        usleep(ms);
        clear();
        mvprintw(0,0,"%s", a->frame3);
        refresh();
        usleep(ms);
        clear();
    }

}

void free_scenes(SCENE scenes[MAX_SCENES]) {
    for(int i = 0; i < MAX_SCENES; i++) free(scenes[i]);
}

void free_anim(ANIM animations[MAX_SCENES]) {
    for(int i = 0; i < MAX_SCENES; i++) free(animations[i]);
}

void blink(SCENE sc, int colorIndex, double seconds, int times) {
    unsigned int ms = (unsigned int)(seconds * 1000000); // conversão para milisegundos
    for(int i = 0; i < times; i++) {
        show(sc,1);
        usleep(ms);
        clear();
        refresh();
        usleep(ms);
    }
}
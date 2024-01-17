#include "scene/_scene.hpp"
#include "misc/_misc.hpp"
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#define ANS const char *ans[]
#define FUNCS functionPtr funcs[]

sf::Music music;

#pragma region CENAS
//         DEFINIÇÃO DE CENAS         //
// (A arte deve ser no máximo 191x40) //

SCENE test = new_scene(
        "Test",
        file_content("ASCII/test.txt"),
        "answer? [Yes/No]"
    );

SCENE test_caseYes = new_scene(
        "yes",
        "it worked",
        "cool"
    );

SCENE test_caseNo = new_scene(
        "no",
        "nononononononono",
        "NOOOOOOOOOOOO"
    );

SCENE pecado1 = new_scene(
    "Pecado 1 - Muito antes da multidão",
    file_content("ASCII/pecado1.txt"),
    file_content("captions/pecado1.txt")
);

SCENE tapete = new_scene(
    "Tapete",
    file_content("ASCII/tapete.txt"),
    "Um tapete comum. Não tenho muito em mente pra descrever mais do que isso. \n  [SAIR / OLHAR EMBAIXO]"
);

SCENE scenes[MAX_SCENES] = {
    test,
    test_caseYes,
    test_caseNo,
    pecado1
};

#pragma endregion

#pragma region ANIMACOES
//     DEFINIÇÃO DE ANIMAÇÕES      //
// (A arte deve ser no máximo _x_) //

ANIM test_anim = new_anim(
        "ONE",
        "TWO",
        "THREE"
);

ANIM animations[MAX_SCENES] = {
    test_anim
};

#pragma endregion

#pragma region ROTINAS  

//         DEFINIÇÃO DE ROTINAS        //
// (Definir da última para a primeira) //

void default_rou() {
    sleep(1);
}

void yes_rou() {
    music.openFromFile("audio/comet.wav");
    music.play();

    show(test_caseYes, 1);
    getch();

    music.stop();
}

void no_rou() {
    show(test_caseNo, 2);
    getch();
}

void tapete_rou() {

    ANS = {"SAIR", "OLHAR EMBAIXO"};
    FUNCS = {default_rou, default_rou};
    handle_choice(&tapete, 1, ans, funcs, 2);
}

void pecado1_rou() {
    music.openFromFile("audio/theme.wav");
    music.setLoop(true);
    music.play();

    ANS = {"TAPETE", "VASO", "PIA", "PORTA"};
    FUNCS = {tapete_rou, default_rou, default_rou, default_rou};
    while(1) {handle_choice(&pecado1, 1, ans, funcs, 4);}

    music.stop();
}

void start_rou() {
    ANS = {"YES", "NO", "PECADO"};
    FUNCS = {yes_rou, no_rou, pecado1_rou};
    while(1) {handle_choice(&test, 1, ans, funcs, 3);}
}

#pragma endregion
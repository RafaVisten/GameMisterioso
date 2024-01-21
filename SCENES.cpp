#include "scene/_scene.hpp"
#include "misc/_misc.hpp"
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>

// atalhos para usar a função handle_choice
#define ANS const char *ans[]
#define FUNCS functionPtr funcs[]

sf::Music music;

#pragma region CENAS
//         DEFINIÇÃO DE CENAS         //
// (A arte deve ser no máximo 191x40) //
#pragma region Tela_Inicial
    SCENE telaInicial = new_scene(
        "",
        file_content("ASCII/telaInicial.txt"),
        ""
    );

#pragma endregion

#pragma region PECADO1_SCENES

SCENE pecado1 = new_scene(
    "Pecado 1 - Muito antes da multidão",
    file_content("ASCII/pecado1.txt"),
    file_content("captions/pecado1.txt")
);

SCENE tapete = new_scene(
    "Tapete",
    file_content("ASCII/tapete2.txt"),
    "Um tapete comum. Não tenho muito em mente pra descrever mais do que isso. \n  [SAIR / OLHAR EMBAIXO]"
);

SCENE vasoquebrado = new_scene(
    "Vaso quebrado",
    file_content("ASCII/vasoquebrado.txt"),
    "Nunca confiei nesse vaso. Não sinto vontade alguma de usá-lo. Mas ele me convida a fazer algo. [DESCARGA / COLOCAR A MAO / INVESIGAR]"
);

    #pragma endregion

SCENE scenes[MAX_SCENES] = {
    telaInicial,
    pecado1,
    tapete,
    vasoquebrado
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
    usleep(1);
}

#pragma region INIT_ROU




#pragma endregion


    #pragma region PECADO1_ROU

void vasoquebrado_rou() {
    ANS = {"DESCARGA", "COLOCAR A MAO", "INVESTIGAR"};
    FUNCS = {default_rou, default_rou, default_rou};
    handle_choice(&vasoquebrado, 1, ans, funcs, 3);
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
    FUNCS = {tapete_rou, vasoquebrado_rou, default_rou, default_rou};
    while(1) {handle_choice(&pecado1, 1, ans, funcs, 4);}

    music.stop();
}

    #pragma endregion

    #pragma region LANDING_ROU

void start_rou() {
    music.openFromFile("audio/theme.wav");
    music.setLoop(true);
    music.play();
    showInit(telaInicial, 1);
    ANS = {"START"};
    FUNCS = {pecado1_rou};
    handle_choice(&telaInicial, 1, ans, funcs, 1);
}

    #pragma endregion

#pragma endregion
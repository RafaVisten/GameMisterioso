#include "scene/_scene.hpp"
#include "misc/_misc.hpp"
#include "inv/_inv.hpp"
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>

// atalhos para usar a função handle_choice
#define ANS const char *ans[]
#define FUNCS functionPtr funcs[]

PlayerInventory inv;
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
    file_content("ASCII/banheiro.txt"),
    file_content("captions/pecado1.txt")
);

SCENE tapete = new_scene(
    "Tapete",
    file_content("ASCII/tapete.txt"),
    "Um tapete comum. Não tenho muito em mente pra descrever mais do que isso. \n\n[OLHAR EMBAIXO]"
);

SCENE poca = new_scene(
    "ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME ITS ME",
    file_content("ASCII/poça.txt"),
    "Embaixo do tapete há uma poça de água. Vejo meu reflexo.\nSou eu. De fato, não há como não ser."
);

SCENE vasoquebrado = new_scene(
    "Vaso quebrado",
    file_content("ASCII/vaso.txt"),
    "Nunca confiei nesse vaso. Não sinto vontade alguma de usá-lo. Mas ele me convida a fazer algo.\n\n[DESCARGA / COLOCAR A MAO / INVESIGAR]"
);

SCENE colocarmao = new_scene(
    "Vaso quebrado",
    file_content("ASCII/vaso.txt"),
    "Resolvo colocar a mão no vaso. Esse tipo de atitude inpensada não é muito comum pra mim."
);

SCENE mao = new_scene(
    "Mão decepada",
    file_content("ASCII/mao.txt"),
    "Definitivamente não foi uma decisão muito boa. \n\n(\"mao esquerda\" adicionada ao inventário)"
);

SCENE pia = new_scene(
    "Pia e espelho",
    file_content("ASCII/pia.txt"),
    "??????????????????????????? [OLHAR ESPELHO / ABRIR TORNEIRA]"
);

SCENE chave = new_scene(
    "Chave enferrujada",
    file_content("ASCII/chave.txt"),
    "Um barulho estranho e metálico começa a ressoar pelo cano: uma chave enferrujada cai da torneira.\n\n(\"chave\" adicionada ao inventário)"
);

SCENE espelho = new_scene(
    "Figura estranha",
    file_content("ASCII/noespelho.txt"),
    "Esse não sou eu."
);

SCENE porta = new_scene(
    "Porta de madeira comum",
    file_content("ASCII/porta.txt"),
    "Uma porta velha de madeira \n\n[TENTAR ABRIR]"
);

SCENE saida = new_scene(
    "A porta se abre",
    file_content("ASCII/porta.txt"),
    "Abro a porta na expectativa falha de me encontrar. Saio sabendo que não posso escapar quem eu sou. Saio sabendo que não consigo amar como fui criado. \n\nir para o próximo capítulo? [SIM/NAO]"
);

SCENE saida_fail = new_scene(
    "Nada acontece",
    file_content("ASCII/porta.txt"),
    "Está emperrada e sem sinal de mudança quando tento forçar a porta."
);

    #pragma endregion

SCENE scenes[MAX_SCENES] = {
    telaInicial,pecado1,tapete,vasoquebrado,pia,chave,espelho,poca,colocarmao,mao,porta,saida,saida_fail
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

void default_rou() {}

#pragma region INIT_ROU


#pragma endregion

void pecado2_rou() {} // pecado dois vai começar aqui

    #pragma region PECADO1_ROU

void abrirporta_rou() {
    if(hasItem(&inv, "chave")) {
        ANS = {"SIM", "NAO"};
        FUNCS = {pecado2_rou, default_rou};
        while(handle_choice(&saida, 1, ans, funcs, 2));
    } else showQuickScene(saida_fail, 1);
}

void porta_rou() {
    ANS = {"TENTAR ABRIR"};
    FUNCS = {abrirporta_rou};
    while(handle_choice(&porta, 1, ans, funcs, 1));
}

void espelho_rou() {
    showQuickScene(espelho, 1);
}
void chave_rou() {
    if(!hasItem(&inv, "chave")) addItem(&inv, "chave");
    showQuickScene(chave, 1);
}

void pia_rou() {
    ANS = {"OLHAR ESPELHO", "ABRIR TORNEIRA"};
    FUNCS = {espelho_rou, chave_rou};
    while(handle_choice(&pia, 1, ans, funcs, 2));
}

void colocarmao_rou() {
    showQuickScene(colocarmao, 1);
    blink(mao, 1, 0.125, 8);
    showQuickScene(mao, 2);
    if(!hasItem(&inv, "mao esquerda")) addItem(&inv, "mao esquerda");
}

void vasoquebrado_rou() {
    ANS = {"DESCARGA", "COLOCAR A MÃO", "INVESTIGAR"};
    FUNCS = {default_rou, colocarmao_rou, default_rou};
    while(handle_choice(&vasoquebrado, 1, ans, funcs, 3));
}

void poca_rou() {
    showQuickScene(poca, 2);
}

void tapete_rou() {

    ANS = {"OLHAR EMBAIXO"};
    FUNCS = {poca_rou};
    while(handle_choice(&tapete, 1, ans, funcs, 1));
}

void pecado1_rou() {

    ANS = {"TAPETE", "VASO", "PIA", "PORTA"};
    FUNCS = {tapete_rou, vasoquebrado_rou, pia_rou, porta_rou};
    while(1) {handle_choice(&pecado1, 1, ans, funcs, 4);}

    music.stop();
}

    #pragma endregion

    #pragma region LANDING_ROU

void start_rou() {
    initializeInventory(&inv);
    music.openFromFile("audio/theme.wav");
    music.setLoop(true);
    music.play();
    showInit(telaInicial, 1);
    move(50,0);
    getch();
    clear();
    pecado1_rou();
}

    #pragma endregion

#pragma endregion

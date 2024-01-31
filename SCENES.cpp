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

LList inv;
sf::Music music; // canal de audio para a música de fundo
sf ::Music sfx; // canal de audio para efeitos sonoros

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

SCENE assimilacao = new_scene(
    "Assimilação completa",
    file_content("ASCII/assimilacao.txt"),
    file_content("captions/assimilacao.txt")
);

SCENE vasoquebrado = new_scene(
    "Vaso quebrado",
    file_content("ASCII/vaso.txt"),
    "Nunca confiei nesse vaso. Não sinto vontade alguma de usá-lo. Mas ele me convida a fazer algo.\n\n[DESCARGA / COLOCAR A MAO / INVESTIGAR]"
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
    "Abro a porta na expectativa falha de me encontrar. Saio sabendo que não posso escapar quem eu sou. Saio sabendo que não consigo amar como fui criado. \n\n(Digite \"ABRIR\" para ir para o próximo capítulo ou aperte <ENTER> para cancelar)"
);
    #pragma endregion

#pragma region PECADO2_SCENES

SCENE pecado2 = new_scene(
    "Pecado 2 - \"Tu me lembras um pecador.\"",
    file_content("ASCII/pecado2Init.txt"),
    file_content("captions/pecado2-3.txt")
);

SCENE escadaria = new_scene(
    "Escadaria",
    file_content("ASCII/escadaria.txt"),
    file_content("captions/edificiodaluz-escadaria.txt")
);

SCENE yellowking = new_scene(
    "Um estranho",
    file_content("ASCII/yellowking.txt"),
    "Ele me olhou intensamente por alguns segundos. Respondi apenas por olhá-lo de volta, quase em uma competição infantil. Confesso que me causou uma certa irritação.  \n- Tu me lembras um pecador."
);

SCENE filaEspera = new_scene(
    "Entrar na fila",
    file_content("ASCII/fila1.txt"),
    "Posso tanto andar para ver a fila ou esperar aqui.\n\n [ESPERAR, ANDAR]"
);

SCENE mentirCena = new_scene(
    "",
    "",
    "Você tem a opção de mentir ou não que possua uma mão:\n [MENTIR] ou [OFERECER MAO]\n"

);
SCENE veioLuz = new_scene(
    "",
    file_content("ASCII/veio.txt"),
    file_content("captions/veio.txt")
);
SCENE veioLuz2 = new_scene(
    "",
    file_content("ASCII/veio2.txt"),
    "-Agora escuta-me com atenção. Só viverás se reconhecer o que digo.\n"

);
#pragma endregion

SCENE scenes[MAX_SCENES] = {
    telaInicial,pecado1,tapete,vasoquebrado,pia,chave,espelho,poca,mao,porta,saida,assimilacao,pecado2,filaEspera,escadaria,yellowking
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

ANIM monstro_anim = new_anim(
    file_content("ASCII/monstro_anim/F1.txt"),
    file_content("ASCII/monstro_anim/F2.txt"),
    file_content("ASCII/monstro_anim/F3.txt")
);

ANIM animations[MAX_SCENES] = {
    test_anim,monstro_anim
};

#pragma endregion

#pragma region ROTINAS

//         DEFINIÇÃO DE ROTINAS        //
// (Definir da última para a primeira) //

void default_rou() {}

#pragma region PECADO2_ROU

void veioLuz_rou(){

}


void mentirCena_rou(){
    changeCapt(file_content("captions/mentirCena1.txt"));

}

void oferecerMao_rou() {
    changeCapt("Lembrando de meu pequeno incidente no banheiro, e sendo comovido pela história do homem, resolvo oferecer minha mão já cortada.\n");
    changeCapt(file_content("captions/oferecerMao1.txt"));
    changeCapt(file_content("captions/oferecerMao2.txt"));
    changeCapt("Você ganhou uma passagem VIP! - Item adicionado ao inventário.\n");
    if(!(hasItem(&inv, "passeVIP"))){
        addItem(&inv, "passeVIP");
    }
}

void edificiodaluz_rou() {
    changeCapt(file_content("captions/edificiodaluz-1.txt"));
    showQuickScene(escadaria, 1);
    addItem(&inv, "FarolLuz");
    showQuickScene(yellowking, 1);
    if(hasItem(&inv, "monstro_morto")){
        changeCapt("-Tu me lembras de um pecador. Vejo pelo fantasma ao seu lado de que de fato se trata de um.\n A violência é o primeiro pecado de todos.");
    }
    changeCapt(file_content("captions/edificiodaluz-2.txt"));
    changeCapt(file_content("captions/edificiodaluz-3.txt"));
    changeCapt(file_content("captions/edificiodaluz-4.txt"));
    if(hasItem(&inv, "mao esquerda")){
        ANS = {"MENTIR", "OFERECER MAO"};
        FUNCS = {mentirCena_rou, oferecerMao_rou};
        handle_choice(&mentirCena,1, ans,funcs,2);

    }
    changeCapt(file_content("captions/edificiodaluz-5.txt"));
    changeCapt(file_content("captions/edificiodaluz-6.txt"));
}

void esperarFila_rou(){
    changeCapt("Entro na fila e espero alguns minutos.");
    sleep(3);
    changeCapt("Não parece ter mudança alguma.");
}
void andarFila_rou(){
    changeCapt(file_content("captions/andarFila.txt"));
    changeCapt("'Você é tão forte e quieto, que eu esqueço que você sofre.'");
    changeCapt("Acho melhor para de pensar, deveria ir ver o que há no começo da fila.");
    changeCapt("Caminho em direção ao começo da fila. Não mais me preocupo com aqueles atrás de mim. ");
    changeCapt(file_content("captions/andarFila2.txt"));
    changeCapt("- Essa informação é confidencial para aqueles que entrarem.");
    changeCapt("Estranho.");
    changeCapt("- Por favor volte para o final da fila. Não irei mais falar.");
}


void entrarFila_rou(){
    if(!(hasItem(&inv, "FarolLuz"))){
        changeCapt("Vejo as criaturas durante sua caminhada para a fila gigante. Pergunto a elas qual o motivo dessa fila toda.");
        changeCapt("-Sinceramente não sabemos. Mas qualquer coisa é melhor do que viver sem sentir. ");
        changeCapt("Percebo que todas elas falam em unissono, como se fossem um só corpo e mente.");
        changeCapt(file_content("captions/criaturasVag.txt"));
        changeCapt("As criaturas vagantes então ficam em silêncio.");
    }else{
        ANS = {"ESPERAR", "ANDAR"};
        FUNCS = {esperarFila_rou, andarFila_rou};
        while(handle_choice(&filaEspera, 1, ans, funcs, 2));
    }
}

void criaturasVagantes_rou(){
    if(!(hasItem(&inv, "FarolLuz"))){
        changeCapt("Vejo as criaturas durante sua caminhada para a fila gigante. Pergunto a elas qual o motivo dessa fila toda.");
        changeCapt("-Sinceramente não sabemos. Mas qualquer coisa é melhor do que viver sem sentir. ");
        changeCapt("Percebo que todas elas falam em unissono, como se fossem um só corpo e mente.");
        changeCapt(file_content("captions/criaturasVag.txt"));
        changeCapt("As criaturas vagantes então ficam em silêncio.");
    }else{
        changeCapt("As criaturas já não mais estavam no lugar de antes, vejo-as agora na fila em que buscavam. Vou em direção à eles.");
    }

}

void pecado2_rou() {
    music.openFromFile("audio/theme2.wav");
    music.setLoop(true);
    music.play();
    changeCapt(file_content("captions/pecado2-1.txt"));
    changeCapt(file_content("captions/pecado2-2.txt"));
    ANS = {"EDIFICIO DA LUZ", "CRIATURAS VAGANTES", "ENTRAR FILA"};
    FUNCS = {edificiodaluz_rou, criaturasVagantes_rou, entrarFila_rou};
    while(1) {handle_choice(&pecado2, 1, ans, funcs, 3);}
    music.stop();
} 
#pragma endregion

#pragma region PECADO1_ROU

void abrirporta_rou() {
    if(hasItem(&inv, "chave")) {
        ANS = {"ABRIR"};
        FUNCS = {pecado2_rou};
        while(handle_choice(&saida, 1, ans, funcs, 1));
    } else changeCapt("Parece estar trancada ou emperrada, nada acontece quando tento forçar a porta.");
}

void porta_rou() {
    ANS = {"TENTAR ABRIR"};
    FUNCS = {abrirporta_rou};
    while(handle_choice(&porta, 1, ans, funcs, 1));
}

void espelho_rou() {
    if(!hasItem(&inv, "monstro_morto")) {
        showQuickScene(espelho, 1);
    } else {
        changeCapt("A criatura afogada aparece ao meu lado, flutuando lentamente, e então suas vozes dizem: \n\"Espero que minha ausência te dê a paz que meu amor não pode\".\nApós dizer tais palavras, olho no espelho novamente e vejo que meu rosto assimilou tal criatura.");
        showQuickScene(assimilacao, 2);
    }
}
void chave_rou() {
    if(!hasItem(&inv, "chave")) {
        sfx.openFromFile("audio/faucet.wav");
        music.pause();
        sfx.play();
        addItem(&inv, "chave");
        showQuickScene(chave, 1);
    } else {
        changeCapt("Não há mais nada para fazer aqui.");
    }
    music.play();
}

void pia_rou() {
    ANS = {"OLHAR ESPELHO", "ABRIR TORNEIRA"};
    FUNCS = {espelho_rou, chave_rou};
    while(handle_choice(&pia, 1, ans, funcs, 2));
}

void investigar_rou(){
    if(!hasItem(&inv, "monstro")) {
        addItem(&inv, "monstro");
        sfx.openFromFile("audio/jumpscare1.wav");
        music.pause();
        sfx.play();
        showAnim(monstro_anim, 2, 0.3, 5); 
        sfx.stop();
        music.play();
    } 
    changeCapt("Tem alguma coisa morando no meu vaso. Legal.");
    clear();
}

void colocarmao_rou() {
    if(!hasItem(&inv, "mao esquerda")) {
        changeCapt("Resolvo colocar a mão no vaso. Esse tipo de atitude inpensada não é muito comum pra mim.");
        music.pause();
        sfx.openFromFile("audio/scream.wav");
        sfx.play();
        blink(mao, 1, 0.0625, 16);
        showQuickScene(mao, 2);
        addItem(&inv, "mao esquerda");
        sfx.stop();
        music.play();
    } else changeCapt("Definitivamente não foi uma decisão muito boa.");
}

void descarga_rou() {

    if(!hasItem(&inv, "monstro")) changeCapt("Aperto a descarga... Não há mudança alguma.");
    else {
        music.pause();
        sfx.openFromFile("audio/toiletmonster.wav");
        sfx.play();
        clear();
        refresh();
        sleep(4);
        music.play();
        changeCapt("Parece que o que quer que eu tenha visto foi levado embora...");
        removeItem(&inv, "monstro");
        addItem(&inv, "monstro_morto");
    }
}

void vasoquebrado_rou() {
    ANS = {"DESCARGA", "COLOCAR A MAO", "INVESTIGAR"};
    FUNCS = {descarga_rou, colocarmao_rou, investigar_rou};
    while(handle_choice(&vasoquebrado, 1, ans, funcs, 3));
}

void poca_rou() {
    music.pause();
    sfx.openFromFile("audio/whispering.wav");
    sfx.setLoop(true);
    sfx.play();
    showQuickScene(poca, 2);
    sfx.stop();
    sfx.setLoop(false);
    music.play();
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

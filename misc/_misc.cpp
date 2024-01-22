#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../scene/_scene.hpp"
#include "_misc.hpp"

void upper(char* input) {
    for (int i = 0; input[i]; i++) input[i] = toupper(input[i]);
}

void ask(char* input) {
    move(51,0);
    getstr(input);
    upper(input);
    refresh();
}

bool answer(char* input, const char* answer) {
    if (strcmp(input,answer) == 0) return true;
    else return false;
}

bool handle_choice(SCENE* prompt, int colorIndex, const char* answers[], functionPtr funcs[], int num_options) {
    char input[25];

    show(*prompt, colorIndex);

    ask(input);
    int i;
    for (i = 0; i < num_options; i++) {
        if (answer(input, answers[i])) {
            clear();
            funcs[i]();
            return true;
        }
    }
    if (answer(input, "QUIT")) {endwin(); exit(0);}
    if (answer(input, "")) {clear(); return false;}
    clear();
    return true;
}

char* file_content(const char* path) {
    char* err = (char*)"Error";
    char *buffer;
    FILE *file;
    long file_size;

    // Abre o arquvio no modo de leitura
    file = fopen(path, "r");

    if (file == NULL) return err;
    // Calcula o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Alocar memoria
    buffer = (char *)malloc(file_size * sizeof(char));

    if (buffer == NULL) {
        fclose(file);
        return err;
    }

    // Salvar o arquivo na variável buffer
    fread(buffer, 1, file_size, file);

    // Fechar o arquivo
    fclose(file);

    return buffer;
}


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

bool handle_answer(SCENE* prompt, int colorIndex, const char* answers[], functionPtr funcs[],  functionPtr default, int num_options) {
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
    else if (answer(input, "")) {clear(); return false;}
    else {
        clear();
        default();
        return false;
    }
    clear();
    return true;
}

char* file_content(const char* path) {
    char* err = (char*)"Error";
    char *buffer;
    FILE *file;
    long file_size;

    // Open the file in read mode
    file = fopen(path, "r");

    if (file == NULL) return err;

    // Calculate the size of the file
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    // Allocate memory with an extra byte for the null terminator
    buffer = (char *)malloc((file_size + 1) * sizeof(char));

    if (buffer == NULL) {
        fclose(file);
        return err;
    }

    // Read the file into the buffer
    fread(buffer, 1, file_size, file);

    // Null-terminate the buffer
    buffer[file_size] = '\0';

    // Close the file
    fclose(file);

    return buffer;
}


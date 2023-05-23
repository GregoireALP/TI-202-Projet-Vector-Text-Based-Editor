//
// Created by grego on 22/05/2023.
//

#ifndef TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_COMMAND_H
#define TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_COMMAND_H

#include "area.h"

struct command {
    char name[50];
    int int_size;
    int int_params[10];
    int str_size;
    char* str_params[10];
};

typedef struct command Command;

Command* create_command(char str[50]);
void free_command(Command* cmd);
int read_exec_command(Command* cmd, int* state, Area* area);

#endif //TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_COMMAND_H

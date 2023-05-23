#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"
#include "area.h"
#include "command.h"

int main() {
    int state = 1;
    char str[50];

    Area *area = create_area(10, 10);

    while (state != 0) {
        printf(">>>");
        fgets(str, sizeof(str), stdin);

        Command* cmd = create_command(str);

        read_exec_command(cmd, &state, area);
        free_command(cmd);
    }

    return 0;
}

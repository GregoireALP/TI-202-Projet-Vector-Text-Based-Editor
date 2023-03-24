#include <stdio.h>
#include "fonctions.h"

int main() {

    Point *p1 = create_point(3, 4);
    Point *p2 = create_point(6, 8);

    Line *line = create_line(p1, p2);

    print_line(line);

    delete_line(line);
    delete_point(p1);
    delete_point(p2);

    return 0;
}

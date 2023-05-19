#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "area.h"

int main() {

    int nb_pixels = 0;
    Area* area = create_area(10, 10);

    Shape* line = create_line_shape(0, 0, 5, 5);
    add_shape_to_area(area, line);
    draw_area(area);
    print_area(area);



    return 0;
}

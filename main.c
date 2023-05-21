#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "area.h"

int main() {

    int nb_pixels = 0;
    Area* area = create_area(10, 10);

    Shape* line = create_rectangle_shape(4, 4, 5, 3);
    add_shape_to_area(area, line);
    draw_area(area);
    print_area(area);



    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

Point* create_point(int px, int py) {

    Point point;
    Point *_point = &point;

    (&point)->pos_x = px;
    (&point)->pos_y = py;

    return _point;
}

void delete_point(Point* point) {
    free(point);
}

void print_point(Point* point) {
    printf("POINT %d %d", (*point).pos_x, (*point).pos_y);
}
#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

/********************************* POINT ******************************/

Point* create_point(int px, int py) {

    Point point;
    Point *_point = &point;

    (_point) -> pos_x = px;
    (_point) -> pos_y = py;

    return _point;
}

void delete_point(Point* point) {
    free(point);
}

void print_point(Point* point) {
    printf("POINT %d %d \n", (*point).pos_x, (*point).pos_y);
}

/********************************* LINE ******************************/

Line *create_line(Point *point1, Point *point2) {

    Line line;
    Line *_line = &line;

    (_line) -> p1 = point1;
    (_line) -> p2 = point2;

    return _line;
}

void delete_line(Line *line) {
    free(line);
}

void print_line(Line *line) {
    printf("LINE %d %d %d %d \n", (*line).p1->pos_x, (*line).p1->pos_y, (*line).p2->pos_x, (*line).p2->pos_y);
}
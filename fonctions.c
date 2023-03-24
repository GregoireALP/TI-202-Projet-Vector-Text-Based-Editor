#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

/********************************* POINT ******************************/

Point* create_point(int px, int py) {

    Point *point = malloc(sizeof(Point));

    point -> pos_x = px;
    point -> pos_y = py;

    return point;
}

void delete_point(Point* point) {
    free(point);
}

void print_point(Point* point) {
    printf("POINT %d %d \n", point->pos_x, point->pos_y);
}

/********************************* LINE ******************************/

Line *create_line(Point *point1, Point *point2) {

    Line *line = malloc(sizeof(Line));

    line -> p1 = point1;
    line -> p2 = point2;

    return line;
}

void delete_line(Line *line) {
    free(line);
}

void print_line(Line *line) {
    printf("LINE %d %d %d %d \n", line->p1->pos_x, line->p1->pos_y, line->p2->pos_x, line->p2->pos_y);
}

/********************************* SQUARE ******************************/

Square *create_square(Point *point, int length) {

    Square *square = malloc(sizeof(Square));

    square->point = point;
    square->length = length;

    return square;
}

void delete_square(Square *square) {
    free(square);
}

void print_square(Square *square) {
    printf("SQUARE %d %d %d", square->point->pos_x, square->point->pos_y, square->length);
}

/********************************* RECTANGLE ******************************/

Rectangle *create_rectangle(Point *point, int width, int height) {

    Rectangle *rectangle = malloc(sizeof(Rectangle));

    rectangle->point = point;
    rectangle->height = height;
    rectangle->width = width;

    return rectangle;
}

void delete_rectangle(Rectangle *rectangle) {
    free(rectangle);
}

void print_rectangle(Rectangle *rectangle) {
    printf("RECTANGLE %d %d %d %d", rectangle->point->pos_x, rectangle->point->pos_y, rectangle->width, rectangle->height);
}

/********************************* CIRCLE ******************************/

Circle *create_circle(Point *center, int radius) {

    Circle *circle = malloc(sizeof(Circle));

    circle->center = center;
    circle->radius = radius;

    return circle;
}

void delete_circle(Circle *circle) {
    free(circle);
}

void print_circle(Circle *circle) {
    printf("CIRCLE %d %d %d", circle->center->pos_x, circle->center->pos_y, circle->radius);
}

/********************************* POLYGON ******************************/
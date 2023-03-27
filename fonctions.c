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

    square -> point = point;
    square -> length = length;

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

    rectangle -> point = point;
    rectangle -> height = height;
    rectangle -> width = width;

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

    circle -> center = center;
    circle -> radius = radius;

    return circle;
}

void delete_circle(Circle *circle) {
    free(circle);
}

void print_circle(Circle *circle) {
    printf("CIRCLE %d %d %d", circle->center->pos_x, circle->center->pos_y, circle->radius);
}

/********************************* POLYGON ******************************/

Polygon *create_polygon(int n, Point **points) {

    Polygon *polygon = malloc(sizeof(Polygon));
    Point **pointsTab = malloc(n * sizeof(Point));

    int i;
    for(i = 0; i < n; i++) {
        pointsTab[i] = points[i];
    }

    polygon -> n = n;
    polygon -> points = pointsTab;

}

void delete_polygon(Polygon *polygon) {
    free(polygon);
}

void print_polygon(Polygon *polygon) {

    printf("POLYGON ");

    int i;
    for(i = 0; i < polygon->n; i++) {
        printf("%d %d \n", polygon->points[i]->pos_y, polygon->points[i]->pos_x);
    }
}

/********************************* SHAPE ******************************/

Shape* create_empty_shape(SHAPE_TYPE shape_type) {

    Shape *shape = (Shape *) malloc(sizeof(Shape));

    shape -> ptrShape = NULL;
    shape -> id = get_next_id();
    shape -> shapeType = shape_type;

    return shape;
}

Shape *create_point_shape(int px, int py) {

    Shape *shape = create_empty_shape(POINT);
    Point *point = create_point(px, py);

    shape -> ptrShape = point;

    return shape;
}

Shape *create_line_shape(int px1, int py1, int px2, int py2) {

    Shape *shape = create_empty_shape(LINE);

    Point *point1 = create_point(px1, py1);
    Point *point2 = create_point(px2, py2);

    Line *line = create_line(point1, point2);

    shape -> ptrShape = line;

    return shape;
}

Shape *create_square_shape(int px, int py, int length) {

    Shape *shape = create_empty_shape(SQUARE);

    Point *point = create_point(px, py);

    Square *square = create_square(point, length);

    shape -> ptrShape = square;

    return shape;
}

Shape *create_rectangle_shape(int px, int py, int width, int height) {

    Shape *shape = create_empty_shape(RECTANGLE);

    Point *point = create_point(px, py);

    Rectangle *rectangle = create_rectangle(point, width, height);

    shape -> ptrShape = rectangle;

    return shape;
}

Shape *create_cercle_shape(int px, int py, int radius) {

    Shape *shape = create_empty_shape(CIRCLE);

    Point *point = create_point(px, py);

    Circle *circle = create_circle(point, radius);

    shape -> ptrShape = circle;

    return shape;
}

Shape *create_polygon_shape(int lst[], int n) {

    Shape *shape = create_empty_shape(POLYGON);

    Point **points = malloc(n * sizeof(n));

    int i;
    for(i = 0; i < n; i+=2) {
        points[i] = create_point(lst[i], lst[i + 1]);
    }

    if(n % 2 == 0) {
        Polygon  *polygon = create_polygon(n , points);

        shape -> ptrShape = polygon;
    }
    return shape;

}

void delete_shape(Shape *shape) {
    free(shape);
}

void print_shape(Shape *shape) {

    switch(shape->shapeType) {

        case POINT:
            print_point((Point *) shape->ptrShape);
            break;
        case LINE:
            print_line((Line *) shape->ptrShape);
            break;
        case SQUARE:
            print_square((Square *) shape->ptrShape);
            break;
        case RECTANGLE:
            print_rectangle((Rectangle *) shape->ptrShape);
            break;
        case CIRCLE:
            print_circle((Circle *) shape->ptrShape);
            break;
        case POLYGON:
            print_polygon((Polygon *) shape->ptrShape);
            break;
        default:
            printf("UNKNOWN \n");
            break;
    }

}

/********************************* ID ******************************/

unsigned int global_id = 0;
unsigned int get_next_id() {
    return ++global_id;
}
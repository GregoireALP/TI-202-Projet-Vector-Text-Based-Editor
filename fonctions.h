#ifndef TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H
#define TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H

// Structures
typedef struct {
    int pos_x;
    int pos_y;
}Point;

typedef struct {
    Point *p1;
    Point *p2;
}Line;

typedef struct {
    Point *point;
    int length;
}Square;

typedef struct {
    Point *point;
    int width;
    int height;
}Rectangle;

// Points
Point *create_point(int px, int py);
void delete_point(Point *point);
void print_point(Point *point);

// Lines
Line *create_line(Point *point1, Point *point2);
void delete_line(Line *line);
void print_line(Line *line);

// Squares
Square *create_square(Point *point, int length);
void delete_square(Square *square);
void print_square(Square *square);

// Rectangles
Rectangle *create_rectangle(Point *point, int width, int height);
void delete_rectangle(Rectangle *rectangle);
void print_rectangle(Rectangle *rectangle);

#endif

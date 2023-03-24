#ifndef TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H
#define TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H

typedef struct {
    int pos_x;
    int pos_y;
}Point;

typedef struct {
    Point *p1;
    Point *p2;
}Line;

Point *create_point(int px, int py);
void delete_point(Point *point);
void print_point(Point *point);

Line *create_line(Point *point1, Point *point2);
void delete_line(Line *line);
void print_line(Line *line);

#endif

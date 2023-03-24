#ifndef TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H
#define TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_FONCTIONS_H

typedef struct {
    int pos_x;
    int pos_y;
}Point;

Point *create_point(int px, int py);
void delete_point(Point *point);
void print_point(Point *point);


#endif

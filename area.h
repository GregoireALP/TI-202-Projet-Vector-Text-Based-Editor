//
#ifndef TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_AREA_H
#define TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_AREA_H

#include "fonctions.h"

#define SHAPE_MAX 100
#define BOOL int

struct area {
    unsigned int width;
    unsigned int height;
    BOOL** mat;
    Shape* shape[SHAPE_MAX];
    int nb_shape;
};

typedef struct area Area;

Area* create_area(unsigned int width, unsigned int height);
void add_shape_to_area(Area* area, Shape* shape);
void clear_area(Area* area);
void erase_area(Area* area);
void delete_area(Area* area);
void draw_area(Area* area);
void print_area(Area* area);


#endif //TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_AREA_H
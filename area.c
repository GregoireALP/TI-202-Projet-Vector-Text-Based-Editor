#include "area.h"
#include "fonctions.h"
#include <stdlib.h>
#include <stdio.h>

Area* create_area(unsigned int width, unsigned int height) {

    Area *area = malloc(sizeof(Area));

    area -> width = width;
    area -> height = height;
    area -> nb_shape = 0;
    area -> mat = (int**) calloc(height, sizeof(int));

    int i;
    for(i = 0; i < height; i++) {
        area->mat[i] = (int*) calloc(width, sizeof(int));
    }

    return area;
}

void add_shape_to_area(Area* area, Shape* shape) {

    area->shape[area->nb_shape] = shape;
    area->nb_shape++;
}

void erase_area(Area* area) {

    int i, y;
    for(i = 0; i < area->height; i++) {
        for(y = 0; y < area->width; i++) {
            area->mat[i][y] = 0;
        }
    }

    area->nb_shape = 0;
}

void delete_area(Area* area) {
    free(area);
}

void print_area(Area* area) {

    int i, y;
    for(i = 0; i < area->height; i++) {
        for (y = 0; y < area->width; ++y) {
            printf(" %d ", area->mat[i][y]);
        }
        printf("\n");
    }
}
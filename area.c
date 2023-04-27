#include "area.h"
#include "fonctions.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Area* create_area(unsigned int width, unsigned int height) {

    Area *area = malloc(sizeof(Area));

    area -> width = width;
    area -> height = height;
    area -> nb_shape = 0;
    area -> mat = (int**) calloc(height, sizeof(int*));

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

Pixel *create_pixel(int px, int py) {

    Pixel *pixel = malloc(sizeof(Pixel));

    pixel->px = px;
    pixel->py = py;

    return pixel;
}

void delete_pixel(Pixel *pixel) {
    free(pixel);
}

void pixel_point(Point* shape, Pixel** pixel, int* nb_pixels) {
    
    Point *pt = (Point*) shape;
    pixel = (Pixel**) malloc((sizeof(Pixel**)));
    pixel[0] = create_pixel(pt->pos_x, pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line(Line* line, Pixel** pixel, int* nb_pixels) {

    int xa, xb, ya, yb;
    xa = line->p1->pos_x;
    ya = line->p1->pos_y;
    xb = line->p2->pos_x;
    yb = line->p2->pos_y;

    int dx = xb - xa;
    int dy = yb - ya;

    int dmin = min(dx, abs(dy));
    int dmax = max(dx, abs(dy));

    int nb_segs = dmin + 1;

    int segs_length = (dmax + 1) / (dmin + 1);
    int overflow = (dmax + 1 ) % (dmin + 1);

    int* segements = (int*) malloc(nb_segs * sizeof(int));
    for(int i = 0; i < nb_segs; i++) {
        segements[i] = segs_length;
    }

    int* cumuls = (int*) malloc(nb_segs * sizeof(int));
    cumuls[0] = 0;
    for(int y = 0; y < nb_segs; y++) {
        cumuls[y] = ((y * overflow) % (nb_segs) < ((y - 1) * overflow) % nb_segs);
        segements[y] = segements[y] + cumuls[y];
        printf("%d", segements[y]);
    }

    // Tracage des segements
    pixel = (Pixel**) malloc(((nb_segs * segs_length) + overflow) * sizeof(Pixel*));
    int x = 0;
    int y = 0;
    for(int i = 0; i < nb_segs; i++) {
        for(int j = 0; segements[i]; j++) {

        }
    }

}
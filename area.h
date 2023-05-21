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

struct pixel {
    int px;
    int py;
};

typedef struct pixel Pixel;

Area* create_area(unsigned int width, unsigned int height);
void add_shape_to_area(Area* area, Shape* shape);
void clear_area(Area* area);
void erase_area(Area* area);
void delete_area(Area* area);
void draw_area(Area* area);
void print_area(Area* area);

Pixel *create_pixel(int px, int py);
Pixel** create_shape_to_pixel(Shape* shape, int *nb_pixel);
void delete_pixel(Pixel *pixel);

void pixel_square(Shape* square, Pixel*** pixel_tab, int* nb_pixels);
void pixel_rectangle(Shape* rectangle, Pixel*** pixel_tab, int* nb_pixels);
void pixel_polygon(Shape* polygon, Pixel*** pixel_tab, int* nb_pixels);
void pixel_point(Shape* shape, Pixel*** pixel, int* nb_pixels);
void pixel_line(Shape *shape, Pixel ***pixel_tab, int *nb_pixels);
void pixel_circle(Shape* shape, Pixel*** pixel_tab, int *nb_pixels);
void pixel_forme(Shape* shape, Pixel*** pixel_tab, int* nb_pixels);

#endif //TI_202_PROJET_VECTOR_TEXT_BASED_EDITOR_AREA_H

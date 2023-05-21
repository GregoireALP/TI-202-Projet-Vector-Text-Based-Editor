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
            if(area->mat[i][y] == 0) {
                printf(" . ");
            } else {
                printf(" # ");
            }
        }
        printf("\n");
    }
}

void draw_area(Area *area) {
    for (int i = 0; i < area->nb_shape; i++) {
        Shape *shape = area->shape[i];
        int nb_pixel;
        Pixel **pixels = create_shape_to_pixel(shape, &nb_pixel);

        // matrice avec les pixels de la forme
        for (int j = 0; j < nb_pixel; j++) {
            int x = pixels[j]->px;
            int y = pixels[j]->py;
            if (x >= 0 && x < area->width && y >= 0 && y < area->height) {
                area->mat[x][y] = 1;
            }
        }
        free(pixels);
    }
}

/**************************************************************/
Pixel *create_pixel(int px, int py) {

    Pixel *pixel = malloc(sizeof(Pixel));

    pixel->px = px;
    pixel->py = py;

    return pixel;
}

void delete_pixel(Pixel *pixel) {
    free(pixel);
}

void pixel_point(Shape* shape, Pixel*** pixel_tab, int* nb_pixels)
{
    Point* pt = (Point*) shape->ptrShape;
    *pixel_tab = (Pixel**) malloc (sizeof (Pixel*));
    *pixel_tab[0] = create_pixel(pt->pos_x, pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line(Shape* shape, Pixel ***pixel_tab, int *nb_pixels) {
    Line *pt = (Line *)shape->ptrShape;

    int xA = pt->p1->pos_x, yA = pt->p1->pos_y;
    int xB = pt->p2->pos_x, yB = pt->p2->pos_y;

    if (xA < xB) { // on trace vers la droite
        int dx = xB - xA;
        int dy = yB - yA;
        int dmin = min(dx, abs(dy));
        int dmax = max(dx, abs(dy));

        Pixel **tmp_tab = (Pixel **)malloc((dmax + 1) * sizeof(Pixel *));

        int nb_segs = dmin + 1;
        int taille_segment = (dmax + 1) / (dmin + 1);
        int restants = (dmax + 1) % (dmin + 1);

        int segments[nb_segs];
        for (int i = 0; i < nb_segs; i++) {
            segments[i] = taille_segment;
        }

        int *cumuls = (int *)malloc(nb_segs * sizeof(int));
        cumuls[0] = 0;

        for (int i = 2; i < nb_segs + 1; i++) {
            cumuls[i - 1] = ((i * restants) % (dmin + 1) < ((i - 1) * restants) % (dmin + 1));
        }

        for (int i = 0; i < nb_segs; i++) {
            segments[i] += cumuls[i];
        }

        if (dy < 0) {         // on trace vers le bas
            if (dx > abs(dy)) { // les segments sont horizontaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy--;
                }
            } else { // les segments sont verticaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy--;
                    }
                    tmpx++;
                }
            }
        } else {         // on trace vers le haut
            if (dx > dy) { // les segments sont horizontaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy++;
                }
            } else { // les segments sont verticaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy++;
                    }
                    tmpx++;
                }
            }
        }
        *pixel_tab = tmp_tab;
    } else { // on trace vers ma gauche
        int dx = xA - xB;
        int dy = yA - yB;
        int dmin = min(dx, abs(dy));
        int dmax = max(dx, abs(dy));

        Pixel **tmp_tab = (Pixel **)malloc((dmax + 1) * sizeof(Pixel *));

        int nb_segs = dmin + 1;
        int taille_segment = (dmax + 1) / (dmin + 1);
        int restants = (dmax + 1) % (dmin + 1);

        int segments[nb_segs];
        for (int i = 0; i < nb_segs; i++) {
            segments[i] = taille_segment;
        }

        int *cumuls = (int *)malloc(nb_segs * sizeof(int));
        cumuls[0] = 0;

        for (int i = 2; i < nb_segs + 1; i++) {
            cumuls[i - 1] =
                    ((i * restants) % (dmin + 1) < ((i - 1) * restants) % (dmin + 1));
        }

        for (int i = 0; i < nb_segs; i++) {
            segments[i] = segments[i] + cumuls[i];
        }

        if (dy < 0) {         // on trace vers le bas
            if (dx > abs(dy)) { // les segments sont horizontaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy--;
                }
            } else { // les segments sont verticaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy--;
                    }
                    tmpx++;
                }
            }
        } else {         // on trace vers le haut
            if (dx > dy) { // les segments sont horizontaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy++;
                }
            } else { // les segments sont verticaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++) {
                    for (int j = 0; j < segments[i]; j++) {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy++;
                    }
                    tmpx++;
                }
            }
        }
        *pixel_tab = tmp_tab;
    }
}

void pixel_circle(Shape* shape, Pixel*** pixel_tab, int *nb_pixels) {}

void pixel_square(Shape* square, Pixel*** pixel_tab, int* nb_pixels) {

    Square* sq = (Square*) square->ptrShape;
    *nb_pixels = 0;

    int length = sq->length;
    Point* pt = sq->point;
    int px = pt->pos_x;
    int py = pt->pos_y;


    Shape* line1 = create_line_shape(px, py, px, py+length);
    Pixel** line1Pixels = NULL;
    pixel_line(line1, &line1Pixels, nb_pixels);

    Shape* line2 = create_line_shape(px, py + length, px + length, py + length);
    Pixel** line2Pixels = NULL;
    pixel_line(line2, &line2Pixels, nb_pixels);


    Shape* line3 = create_line_shape(px + length, py + length, px + length, py);
    Pixel** line3Pixels = NULL;
    pixel_line(line3, &line3Pixels, nb_pixels);

    Shape* line4 = create_line_shape(px + length, py, px, py);
    Pixel** line4Pixels = NULL;
    pixel_line(line4, &line4Pixels, nb_pixels);

    line1Pixels = realloc(line1Pixels, *nb_pixels * sizeof(Pixel*));

}

Pixel** create_shape_to_pixel(Shape* shape, int *nb_pixel) {

    Pixel** pixel = NULL;

    switch (shape->shapeType) {
        case LINE:
            pixel_line(shape, &pixel, nb_pixel);
            break;
        case POINT:
            break;
        case SQUARE:
            break;
        case RECTANGLE:
            break;
        case CIRCLE:
            break;
        case POLYGON:
            break;
    }

    return pixel;
}
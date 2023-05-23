#include "area.h"
#include "fonctions.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Area *create_area(unsigned int width, unsigned int height)
{

    Area *area = malloc(sizeof(Area));

    area->width = width;
    area->height = height;
    area->nb_shape = 0;
    area->mat = (int **)calloc(height, sizeof(int *));

    int i;
    for (i = 0; i < height; i++)
    {
        area->mat[i] = (int *)calloc(width, sizeof(int));
    }

    return area;
}

void add_shape_to_area(Area *area, Shape *shape)
{

    area->shape[area->nb_shape] = shape;
    area->nb_shape++;
}

void erase_area(Area *area)
{

    int i, y;
    for (i = 0; i < area->height; i++)
    {
        for (y = 0; y < area->width; i++)
        {
            area->mat[i][y] = 0;
        }
    }

    area->nb_shape = 0;
}

void delete_area(Area *area)
{

    int i;
    for (i = 0; i < area->height; i++)
    {
        free(area->mat[i]);
    }

    free(area->mat);
    free(area);
}

void print_area(Area *area)
{

    int i, y;
    for (i = 0; i < area->height; i++)
    {
        for (y = 0; y < area->width; ++y)
        {
            if (area->mat[i][y] == 0)
            {
                printf(" . ");
            }
            else
            {
                printf(" # ");
            }
        }
        printf("\n");
    }
}

void draw_area(Area *area)
{
    for (int i = 0; i < area->nb_shape; i++)
    {
        Shape *shape = area->shape[i];
        int nb_pixel = 0;
        Pixel **pixels = create_shape_to_pixel(shape, &nb_pixel);

        // matrice avec les pixels de la forme
        for (int j = 0; j < nb_pixel; j++)
        {
            int x = pixels[j]->px;
            int y = pixels[j]->py;
            if (x >= 0 && x < area->width && y >= 0 && y < area->height)
            {
                area->mat[x][y] = 1;
            }
        }
        free(pixels);
    }
}

/**************************************************************/
Pixel *create_pixel(int px, int py)
{

    Pixel *pixel = malloc(sizeof(Pixel));

    pixel->px = px;
    pixel->py = py;

    return pixel;
}

void delete_pixel(Pixel *pixel)
{
    free(pixel);
}

void delete_pixel_shape(Pixel ***pixel, int nb_pixels)
{
    for (int i = 0; i < nb_pixels; i++)
    {
        delete_pixel((*pixel)[i]);
    }
    free(*pixel);
}

void pixel_point(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Point *pt = (Point *)shape->ptrShape;
    *pixel_tab = (Pixel **)malloc(sizeof(Pixel *));
    *pixel_tab[0] = create_pixel(pt->pos_x, pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Line *pt = (Line *)shape->ptrShape;

    int xA = pt->p1->pos_x, yA = pt->p1->pos_y;
    int xB = pt->p2->pos_x, yB = pt->p2->pos_y;

    if (xA < xB)
    { // on trace vers la droite
        int dx = xB - xA;
        int dy = yB - yA;
        int dmin = min(dx, abs(dy));
        int dmax = max(dx, abs(dy));

        Pixel **tmp_tab = (Pixel **)malloc((dmax + 1) * sizeof(Pixel *));

        int nb_segs = dmin + 1;
        int taille_segment = (dmax + 1) / (dmin + 1);
        int restants = (dmax + 1) % (dmin + 1);

        int segments[nb_segs];
        for (int i = 0; i < nb_segs; i++)
        {
            segments[i] = taille_segment;
        }

        int *cumuls = (int *)malloc(nb_segs * sizeof(int));
        cumuls[0] = 0;

        for (int i = 2; i < nb_segs + 1; i++)
        {
            cumuls[i - 1] = ((i * restants) % (dmin + 1) < ((i - 1) * restants) % (dmin + 1));
        }

        for (int i = 0; i < nb_segs; i++)
        {
            segments[i] += cumuls[i];
        }

        if (dy < 0)
        { // on trace vers le bas
            if (dx > abs(dy))
            { // les segments sont horizontaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy--;
                }
            }
            else
            { // les segments sont verticaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy--;
                    }
                    tmpx++;
                }
            }
        }
        else
        { // on trace vers le haut
            if (dx > dy)
            { // les segments sont horizontaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy++;
                }
            }
            else
            { // les segments sont verticaux
                int tmpx = xA, tmpy = yA;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
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
    else
    { // on trace vers ma gauche
        int dx = xA - xB;
        int dy = yA - yB;
        int dmin = min(dx, abs(dy));
        int dmax = max(dx, abs(dy));

        Pixel **tmp_tab = (Pixel **)malloc((dmax + 1) * sizeof(Pixel *));

        int nb_segs = dmin + 1;
        int taille_segment = (dmax + 1) / (dmin + 1);
        int restants = (dmax + 1) % (dmin + 1);

        int segments[nb_segs];
        for (int i = 0; i < nb_segs; i++)
        {
            segments[i] = taille_segment;
        }

        int *cumuls = (int *)malloc(nb_segs * sizeof(int));
        cumuls[0] = 0;

        for (int i = 2; i < nb_segs + 1; i++)
        {
            cumuls[i - 1] =
                ((i * restants) % (dmin + 1) < ((i - 1) * restants) % (dmin + 1));
        }

        for (int i = 0; i < nb_segs; i++)
        {
            segments[i] = segments[i] + cumuls[i];
        }

        if (dy < 0)
        { // on trace vers le bas
            if (dx > abs(dy))
            { // les segments sont horizontaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy--;
                }
            }
            else
            { // les segments sont verticaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpy--;
                    }
                    tmpx++;
                }
            }
        }
        else
        { // on trace vers le haut
            if (dx > dy)
            { // les segments sont horizontaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
                        tmp_tab[*nb_pixels] = create_pixel(tmpx, tmpy);
                        (*nb_pixels)++;
                        tmpx++;
                    }
                    tmpy++;
                }
            }
            else
            { // les segments sont verticaux
                int tmpx = xB, tmpy = yB;
                for (int i = 0; i < nb_segs; i++)
                {
                    for (int j = 0; j < segments[i]; j++)
                    {
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

void pixel_square(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Square *square = (Square *)shape->ptrShape;
    int x = square->point->pos_x;
    int y = square->point->pos_y;
    int side_length = square->length;

    *pixel_tab = (Pixel **)malloc(side_length * side_length * sizeof(Pixel *));

    int index = 0;
    // Top side
    for (int i = 0; i < side_length; i++)
    {
        Pixel *px = create_pixel(x + i, y);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Right side
    for (int i = 1; i < side_length - 1; i++)
    {
        Pixel *px = create_pixel(x + side_length - 1, y + i);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Bottom side
    for (int i = 0; i < side_length; i++)
    {
        Pixel *px = create_pixel(x + i, y + side_length - 1);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Left side
    for (int i = 1; i < side_length - 1; i++)
    {
        Pixel *px = create_pixel(x, y + i);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }
}

void pixel_circle(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Circle *circle = (Circle *)shape->ptrShape;
    int x = 0;
    int y = circle->radius;
    int d = 3 - 2 * circle->radius;
    Pixel *px = NULL;

    *pixel_tab = (Pixel **)malloc(8 * circle->radius * sizeof(Pixel *));

    while (x <= y)
    {
        // Add pixels for the eight octants

        // Octant 1
        px = create_pixel(circle->center->pos_x + x, circle->center->pos_y + y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 2
        px = create_pixel(circle->center->pos_x + y, circle->center->pos_y + x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 3
        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y + y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 4
        px = create_pixel(circle->center->pos_x - y, circle->center->pos_y + x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 5
        px = create_pixel(circle->center->pos_x + x, circle->center->pos_y - y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 6
        px = create_pixel(circle->center->pos_x + y, circle->center->pos_y - x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 7
        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y - y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        // Octant 8
        px = create_pixel(circle->center->pos_x - y, circle->center->pos_y - x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void pixel_rectangle(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Rectangle *rectangle = (Rectangle *)shape->ptrShape;
    int x = rectangle->point->pos_x;
    int y = rectangle->point->pos_y;
    int width = rectangle->width;
    int height = rectangle->height;

    *pixel_tab = (Pixel **)malloc((2 * width + 2 * height - 4) * sizeof(Pixel *));

    int index = 0;
    // Top side
    for (int i = 0; i < width; i++)
    {
        Pixel *px = create_pixel(x + i, y);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Right side
    for (int i = 1; i < height - 1; i++)
    {
        Pixel *px = create_pixel(x + width - 1, y + i);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Bottom side
    for (int i = width - 1; i >= 0; i--)
    {
        Pixel *px = create_pixel(x + i, y + height - 1);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }

    // Left side
    for (int i = height - 2; i > 0; i--)
    {
        Pixel *px = create_pixel(x, y + i);
        (*pixel_tab)[index++] = px;
        (*nb_pixels)++;
    }
}

void pixel_polygon(Shape *shape, Pixel ***pixel_tab, int *nb_pixels)
{
    Polygon *polygon = (Polygon *)shape->ptrShape;
    int nb_points = polygon->n;
    Point **points = polygon->points;

    *pixel_tab = (Pixel **)malloc(nb_points * sizeof(Pixel *));

    Shape **lines = (Shape **)malloc((nb_points + 1) * sizeof(Shape *));
    for (int i = 0; i < nb_points; i++)
    {
        lines[i] = create_line_shape(points[i]->pos_x, points[i]->pos_y, points[(i + 1) % nb_points]->pos_x, points[(i + 1) % nb_points]->pos_y);
    }

    int nb_pixels_tmp = 0;
    Pixel **pixel_tmp = NULL;

    for (int i = 0; i < nb_points; i++)
    {
        pixel_line(lines[i], &pixel_tmp, &nb_pixels_tmp);
        *pixel_tab = (Pixel **)realloc(*pixel_tab, (*nb_pixels + nb_pixels_tmp) * sizeof(Pixel *));
        for (int j = 0; j < nb_pixels_tmp; j++)
        {
            (*pixel_tab)[*nb_pixels + j] = pixel_tmp[j];
        }
        *nb_pixels += nb_pixels_tmp;
    }

    // Libérer la mémoire des lignes
    for (int i = 0; i <= nb_points; i++)
    {
        delete_shape(lines[i]);
    }
    free(lines);
}

Pixel **create_shape_to_pixel(Shape *shape, int *nb_pixel)
{

    Pixel **pixel = NULL;

    switch (shape->shapeType)
    {
    case LINE:
        pixel_line(shape, &pixel, nb_pixel);
        break;
    case POINT:
        pixel_point(shape, &pixel, nb_pixel);
        break;
    case SQUARE:
        pixel_square(shape, &pixel, nb_pixel);
        break;
    case RECTANGLE:
        pixel_rectangle(shape, &pixel, nb_pixel);
        break;
    case CIRCLE:
        pixel_circle(shape, &pixel, nb_pixel);
        break;
    case POLYGON:
        pixel_polygon(shape, &pixel, nb_pixel);
        break;
    }

    return pixel;
}
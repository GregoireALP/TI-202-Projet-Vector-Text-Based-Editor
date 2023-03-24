#include <stdio.h>
#include "fonctions.h"

int main() {

    Point *p1 = create_point(3, 4);
    Point *p2 = create_point(6, 8);
    Point *p3 = create_point(8, 10);
    Point *p4 = create_point(10, 9);

    int n = 4;
    Point *points[4] = {p1, p2, p3, p4};

    Polygon *polygon = create_polygon(n, points);

    print_polygon(polygon);

    return 0;
}

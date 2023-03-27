#include <stdio.h>
#include "fonctions.h"

int main() {

    Shape *f1 = create_line_shape(10, 15, 21, 25);
    Shape *f2 = create_line_shape(10, 15, 21, 25);
    Shape *f3 = create_line_shape(10, 15, 21, 25);

    printf("%d %d %d", f1->id, f2->id, f3->id);

    return 0;
}

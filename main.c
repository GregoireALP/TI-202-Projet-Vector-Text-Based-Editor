#include <stdio.h>
#include "fonctions.h"
#include "area.h"

int main() {

    Area *area = create_area(10, 10);
    print_area(area);

    return 0;
}

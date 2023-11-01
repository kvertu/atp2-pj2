#include <stdio.h>
#include "include/sorting.h"

int main() {
    ilist l = new_list();
    load_list("test2.bin", l);
    print_list(l);
    printf("\n");
    free_list(l);

    return 0;
}
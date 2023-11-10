#define PATH_MAX 260
#include <stdio.h>
#include "include/sorting.h"

int main() {
    ilist l = new_list();
    load_list("test.bin", l);
    print_list(l);
    printf("\n");
    quick_sort(l, 0, l->last, str_vemantes);
    print_list(l);
    free_list(l);

    return 0;
}
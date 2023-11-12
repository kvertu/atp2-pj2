#define PATH_MAX 260
#include <stdio.h>
#include "include/sorting.h"

int main() {
    ilist l = new_list();
    load_list("test.bin", l);
    print_list(l);
    printf("\n");
    // insertion_sort(l, str_vemantes);
    // print_list(l);
    // trocar_list(l, 0, 1);
    // printf("\n");
    // trocar_list(l, 1, 2);
    // printf("\n");
    trocar_list(l, 2, 3);
    print_list(l);
    printf("\n");
    free_list(l);

    return 0;
}
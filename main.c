#include <stdio.h>
#include "include/sorting.h"

int main() {
    ilist l = new_list();
    load_list("test.bin", l);
    // print_list(l);
    free_list(l);

    return 0;
}
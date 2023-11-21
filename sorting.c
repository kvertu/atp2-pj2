#define PATH_MAX 260
#include "include/sorting.h"
#include <stdio.h>

bool char_vemantes(char a, char b) {
    return a > b;
}

bool str_vemantes(char * a, char * b) {
    // TODO: Refatorar esse código nojento
    int tama = strlen(a);
    int tamb = strlen(b);
    
    if (tama <= tamb) {
        // A string a é menor ou as duas tem tamanho igual
        for (int i = 0; i < tama; i++)
            // Garante que os caracteres são diferentes
            if (a[i] != b[i])
                // Determina quem vem antes
                if (char_vemantes(a[i], b[i]))
                    // a[i] vem antes
                    return true; // a vem primeiro
                else
                    // b[i] vem antes
                    return false; // b vem primeiro   
        // Se todos os caracteres verificados são iguais, então é decidido pelo tamanho
        if (tama == tamb)
            // Caso especial: as strings são iguais
            // Considerando que essas strings são nomes de arquivos, deve-se garantir que não há strings repetidas na lista
            printf("AVISO: As duas strings comparadas são iguais, retornando true.\n");

        return true; // Já que tama <= tamb, a vem primeiro
    } else {
        // A string b é menor
        for (int i = 0; i < tamb; i++)
            // Garante que os caracteres são diferentes
            if (a[i] != b[i])
                // Determina quem vem antes
                if (char_vemantes(a[i], b[i]))
                    // a[i] vem antes
                    return true; // a vem primeiro
                else
                    // b[i] vem antes
                    return false; // b vem primeiro   
        // Se todos os caracteres verificados são iguais, então é decidido pelo tamanho
        return false; // Já que tama > tamb, b vem primeiro
    }
}

int separa(ilist l, int low, int up, bool (*comparar)(char *, char *)) {
    char piv[PATH_MAX], aux[PATH_MAX];
    getvalue_list(l, l->last, piv); // Pivô
    int j = low; // Posição do particionamento
    for (int k = low; k < up; k++) {
        getvalue_list(l, k, aux);
        if (comparar(piv, aux)) {
            trocar_list(l, j, k);
            j++;
        }
    }
    trocar_list(l, j, up);

    return j;
}

void quick_sort(ilist l, int low, int up, bool (*comparar)(char *, char *)) {
    if (low < up) {
        int j;
        j = separa(l, low, up, comparar);
        quick_sort(l, low, j - 1, comparar); // Chamada para elementos à esquerda do pivô
        quick_sort(l, j + 1, up, comparar); // Chamada para elementos à direita do pivô
    }
}
#include "include/sorting.h"
#include <stdio.h>

bool char_vemantes(char a, char b) {
    return a < b;
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
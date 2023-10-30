#include <stdio.h>
#include <string.h>
#include "include/imagelist.h"

ilist new_list() {
    ilist l = malloc(sizeof(iList));
    
    if (l != NULL) {
        l->first = NULL;
        l->last = -1;
    } else {
        printf("ERRO: Não foi possível alocar memória para lista.\n");
    }
    return l;
}

void free_list(ilist l) {
    if (l != NULL) {
        for (image i = l->first; i != NULL; i = l->first) {
            // Passa pela lista removendo as imagens da memória um por um
            l->first = i->next;
            l->last--;
            free(i);
        }
        free(l); // Por fim, libera a lista em si da memória
    } else {
        printf("AVISO: Ponteiro da lista nulo, não há nada para liberar.\n");
    }
}

int getsize_list(ilist l) {
    if (l != NULL) {
        return l->last + 1; // O tamanho da lista é o último indice da lista + 1
    }
    return -1; // Se a lista é nula, então ela nem tem tamanho
}

bool isnull_list(ilist l) {
    return l != NULL;
}

bool isempty_list(ilist l) {
    if (!isnull_list(l))
        return getsize_list(l) == 0; // Verifica se o tamanho da lista é 0;
    else
        return false; // Se a lista é nula, então ela também está vazia;
}

bool print_list(ilist l) {
    if (isnull_list(l) || isempty_list(l)) {
        printf("ERRO: A lista é nula ou vazia, não é possível imprimir.\n");
        return false;
    } else {
        // Percorre a lista, imprimindo os nomes dos arquivos no terminal
        for (image i = l->first; i != NULL; i = i->next) {
            printf("%s\n", i->name);
        }
        return true;
    }
}

bool search_list(ilist l, int * position, char * search) {
    // O valor de retorno (boolean) mostra se a pesquisa teve exito
    // O valor em position mostra se algo foi encontrado
    if (isempty_list(l)) {
        printf("ERRO: A lista está vazia, nada para procurar.\n");
        return false;
    }

    (*position) = 0;
    for (image i = l->first; i != NULL; i = i->next) {
        if (strcmp(i->name, search) == 0) {
            return true;
        } else {
            (*position)++;
        }
    }

    // Nada foi encontrado, retorna -1
    (*position) = -1;
    return true;
}
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

bool getvalue_list(ilist l, int pos, char * val) {
    if (pos < 0 || pos > l->last) {
        printf("ERRO: Indice fora do escopo da lista, operação falhou.\n");
        return false;
    } else {
        image i = l->first;
        for (int j = 1; j <= pos; j++) {
            i = i->next;
        }
        val = i->name;
        return true;
    }
}

bool trocar_list(ilist l, int p1, int p2) {
    if (p1 < 0 || p1 > l->last || p2 < 0 || p2 > l->last) {
        printf("ERRO: Indices fora do escopo da lista, operação falhou.\n");
        return false;
    }

    image i1 = l->first;
    int j;
    for (j = 1; j < p1; j++) {
        i1 = i1->next;
    }

    image i2 = l->first;
    for (j = 1; j < p2; j++) {
        i2 = i2->next;
    }

    image aux = i1;
    i1->next->next = i2->next->next;
    i1->next = i2->next;

    i2->next->next = aux->next->next;
    i2->next = aux->next;

    return true;
}
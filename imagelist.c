#include <stdio.h>
#include <string.h>
#include "include/imagelist.h"
#define PATH_MAX 260 // Tamanho máximo de um nome de arquivo

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
            free(i->name);
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
    return l == NULL;
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
        image i = l->first;
        while (i != NULL) {
            printf("%s\n", i->name);
            i = i->next;
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
        for (int j = 0; j < pos; j++) {
            i = i->next;
        }
        strcpy(val, i->name);
        return true;
    }
}

bool trocar_list(ilist l, int p1, int p2) {
    if (p1 < 0 || p1 > l->last || p2 < 0 || p2 > l->last) {
        printf("ERRO: Indices fora do escopo da lista, operação cancelada.\n");
        return false;
    }

    image i1 = l->first;
    image i2 = l->first;

    for (int i = 0; i < p1; i++) {
        i1 = i1->next;
    }

    for (int i = 0; i < p2; i++) {
        i2 = i2->next;
    }

    // Solução preguiçosa e menos eficiente
    char aux[PATH_MAX];
    strcpy(aux, i1->name);
    strcpy(i1->name, i2->name);
    strcpy(i2->name, aux);

    // Solução mais eficiente (não está funcionando, não sei porque)
    // image aux = i2;
    
    // i2->next->next = i1->next->next;
    // i2->next = i1->next;
    
    // i1->next->next = aux->next->next;
    // i1->next = aux->next;

    return true;
}

bool insert_list(ilist l, int pos, char * newimage) {
    if (pos < 0 || pos > l->last + 1) {
        printf("ERRO: Indices fora do escopo da lista, operação cancelada.\n");
        return false;
    }

    l->last++;
    image item = malloc(sizeof(struct Image));
    item->name = malloc(sizeof(char) * PATH_MAX);
    strcpy(item->name, newimage);
    item->next = NULL;

    if (pos == 0) {
        item->next = l->first;
        l->first = item;
        return true;
    }

    image i = l->first;
    int k = 0;
    while (k < pos - 1) {
        k++;
        i = i->next;
    }
    item->next = i->next;
    i->next = item;
    return true;
}

bool insertfirst_list(ilist l, char * newimage) {
    return insert_list(l, 0, newimage);
}

bool insertlast_list(ilist l, char * newimage) {
    return insert_list(l, l->last + 1, newimage);
}

bool removeatpos_list(ilist l, int pos) {
    if (isempty_list(l)) {
        printf("AVISO: A lista está vazia, não tem o que remover.\n");
        return false;
    }
    if (pos < 0 || pos > l->last) {
        printf("ERRO: Indices fora do escopo da lista, operação cancelada.\n");
        return false;
    }

    image aux = NULL;
    l->last--;

    if (pos == 0) {
        // Caso especial
        aux = l->first->next; // aux armazena o ponteiro para a imagem depois de first
        free(l->first->name);
        free(l->first); // first é liberado na memória
        l->first = aux; // aux passa a ser a primeira imagem da lista
        return true;
    }

    aux = l->first; // aux será usada para iterar sobre a lista
    image prev = NULL; // Imagem anterior a aux;
    for (int k = 0; k < pos; k++) {
        prev = aux;
        aux = aux->next;
    }
    prev->next = aux->next; // Ponteiro de prev passa a apontar para a imagem depois de aux
    free(aux->name);
    free(aux); // Aux é liberado na memória
    return true;
}

bool removebysearch_list(ilist l, char * search) {
    int pos = -1;
    if (search_list(l, &pos, search)) {
        if (pos == -1) {
            printf("AVISO: Chave não encontrada, não tem o que remover.\n");
            return false;
        }
        return removeatpos_list(l, pos);
    }
    printf("ERRO: Pesquisa retornou erro, operação cancelada.\n");
    return false;
}

bool save_list(char * filename, ilist l) {
    if (isempty_list(l)) {
        printf("AVISO: Lista está vazia, nada para salvar.\n");
        return false;
    }

    FILE * fsave = fopen(filename, "wb");
    if (fsave == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo, operação cancelada.\n");
        return false;
    }

    for (image i = l->first; i != NULL; i = i->next) {
        fwrite(i, sizeof(struct Image), 1, fsave);
        fwrite(i->name, sizeof(char), PATH_MAX, fsave);
    }
    fclose(fsave);
    return true;
}

bool load_list(char * filename, ilist l) {
    FILE * fload = fopen(filename, "rb");
    if (fload == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo, operação cancelada.\n");
        return false;
    }

    image aux = malloc(sizeof(struct Image));
    image last_image = NULL;

    while (fread(aux, sizeof(struct Image), 1, fload)) {
        // aux é usado para ler o conteudo do arquivo
        // Quando é lido 0 bytes no fread, ele para de ler
        l->last++;
        if (l->first == NULL) {
            // Caso para o primeiro elemento da lista
            l->first = malloc(sizeof(struct Image));
            l->first->name = malloc(sizeof(char) * PATH_MAX);
            last_image = l->first;
        } else {
            // Caso para qualquer outro elemento
            last_image->next = malloc(sizeof(struct Image));
            last_image->next->name = malloc(sizeof(char) * PATH_MAX);
            last_image = last_image->next;
        }
        fread(last_image->name, sizeof(char), PATH_MAX, fload);
        last_image->next = NULL;
    }

    fclose(fload);
    return true;
}
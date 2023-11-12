#include <string.h>
#include "imagelist.h"

bool char_vemantes(char a, char b); // Determina qual caracter vem antes a partir da tabela ASCII
bool str_vemantes(char * a, char * b); // Determina qual string vem antes na lista
// Funções para ordenação
void insertion_sort(ilist l, bool (*comparar)(char *, char *)); // Insertion sort: algoritmo de ordenação mais lento, apenas para teste
int separa(ilist l, int low, int up, bool (*comparar)(char *, char *)); // Função para pivoteamento da lista (quick sort)
void quick_sort(ilist l, int low, int up, bool (*comparar)(char *, char *)); // Quick sort: algoritmo melhor para ordenação
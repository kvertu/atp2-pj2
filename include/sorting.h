#include <string.h>
#include "imagelist.h"

bool char_vemantes(char a, char b); // Determina qual caracter vem antes a partir da tabela ASCII
bool str_vemantes(char * a, char * b); // Determina qual string vem antes na lista
int separa(ilist l, int low, int up, bool (*comparar)(char *, char *)); // Função para pivoteamento da lista
void quick_sort(ilist l, int low, int up, bool (*comparar)(char *, char *));
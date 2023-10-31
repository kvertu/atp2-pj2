#include <stdbool.h>
#include <stdlib.h>

typedef struct Image {
    char * name; // Nome do arquivo da imagem
    struct Image * next; // Ponteiro para a próxima imagem da lista
};

typedef struct Image* image; // Ponteiro de um item da lista está definido como um tipo de variável

typedef struct {
    image first; // Primeiro elemento da lista
    int last; // Indice do último elemento da lista
} iList;

typedef iList* ilist; // Ponteiro de uma lista está definido como um tipo de variável

ilist new_list(); // Cria uma nova lista de imagens e armazena na memória
void free_list(ilist l); // Libera a lista de imagens na memória
int getsize_list(ilist l); // Obtem o tamanho da lista
bool isnull_list(ilist l); // Verifica se a lista é nula
bool isempty_list(ilist l); // Verifica se a lista está vazia
bool print_list(ilist l); // Imprime a lista de imagens no terminal
bool search_list(ilist l, int * position, char * search); // Pesquisa uma imagem na lista, retorna a sua posição (método lento)
bool getvalue_list(ilist l, int pos, char * val); // Pesquisa uma imagem na lista, dado a sua posição
bool trocar_list(ilist l, int p1, int p2); // Troca os itens das posições p1 e p2 entre si
bool insert_list(ilist l, int position, char * newimage); // Insere uma imagem na lista, dado a posição
bool insertfirst_list(ilist l, char * newimage); // Insere uma imagem no inicio na lista
bool insertlast_list(ilist l, char * newimage); // Insere uma imagem no fim da lista
bool removeatpos_list(ilist l, int position); // Remove uma imagem da lista, dado a sua posição
bool removebysearch_list(ilist l, char * search); // Remove uma imagem da lista, dado o seu nome
bool save_list(char * filename, ilist l); // Armazena a lista de imagens em um arquivo
bool load_list(char * filename, ilist l); // Carrega a lista de imagens de um arquivo

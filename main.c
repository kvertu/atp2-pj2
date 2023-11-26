#define PATH_MAX 260 // Tamanho máximo de um nome de arquivo
#include <stdio.h>
#include "include/sorting.h"
#include "include/image.h"

void helper() {
    // Helper do programa
    printf("=-=-= GERENCIADOR DE IMAGENS =-=-=\n");
    printf("help: Mostra essa tela.\n");
    printf("[lista] create [arquivo]: Cria um arquivo de lista.\n");
    printf("[lista] print: Imprime o conteudo da lista na tela.\n");
    printf("[lista] add [arquivo]: Adiciona um arquivo à lista.\n");
    printf("[lista] rm [arquivo]: Remove o arquivo da lista.\n");
    printf("[lista] inv: Inverte todos os arquivos da lista.\n");
    printf("[lista] lim [val]: Limiariza todos os arquivos da lista, dado lim.\n");
    printf("[lista] esph: Espelha horizontalmente todos os arquivos da lista.\n");
    printf("[lista] espv: Espelha verticalmente todos os arquivos da lista.\n");
}

void error() {
    // Se o usuário escrever um comando inválido, isso aparece
    printf("Comando não encontrado, digite help para ajuda.\n");
}

void inv(char * listname) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se deu erro ao carregar lista
        printf("Erro ao processar lista, abortando.\n");
        return;
    }

    for (image i = l->first; i != NULL; i = i->next) {
        // Itera pela lista processando cada imagem
        printf("Processando arquivo %s...", i->name);

        imgb imagem = load_imgb(i->name);
        if (is_null_imgb(&imagem)) {
            // Se a imagem não foi encontrada
            printf(" Não foi possível encontrar imagem, pulando.\n");
        } else {
            char temp[PATH_MAX] = "inv_";
            strcat(temp, i->name);
            inverter(&imagem);
            save_imgb(temp, &imagem);
            free_imgb(&imagem);

            printf(" Pronto!\n");
        }
    }

    free_list(l);
}

void esph(char * listname) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se deu erro ao carregar lista
        printf("Erro ao processar lista, abortando.\n");
        return;
    }

    for (image i = l->first; i != NULL; i = i->next) {
        // Itera pela lista processando cada imagem
        printf("Processando arquivo %s...", i->name);
        
        imgb imagem = load_imgb(i->name);
        if (is_null_imgb(&imagem)) {
            // Se a imagem não foi encontrada
            printf(" Não foi possível encontrar imagem, pulando.\n");
        } else {
            char temp[PATH_MAX] = "esph_";
            strcat(temp, i->name);
            espelhar_h(&imagem);
            save_imgb(temp, &imagem);
            free_imgb(&imagem);

            printf(" Pronto!\n");
        }
    }

    free_list(l);
}

void espv(char * listname) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se deu erro ao carregar lista
        printf("Erro ao processar lista, abortando.\n");
        return;
    }

    for (image i = l->first; i != NULL; i = i->next) {
        // Itera pela lista processando cada imagem
        printf("Processando arquivo %s...", i->name);
        
        imgb imagem = load_imgb(i->name);
        if (is_null_imgb(&imagem)) {
            // Se a imagem não foi encontrada
            printf(" Não foi possível encontrar imagem, pulando.\n");
        } else {
            char temp[PATH_MAX] = "espv_";
            strcat(temp, i->name);
            espelhar_v(&imagem);
            save_imgb(temp, &imagem);
            free_imgb(&imagem);

            printf(" Pronto!\n");
        }
    }

    free_list(l);
}

void create(char * listname, char * firstfile) {
    ilist l = new_list();

    if (strstr(firstfile, ".pgm") == NULL) {
        // Se o arquivo não tem a extensão .pgm
        printf("Esse programa suporta apenas arquivos .pgm.\n");
        return;
    }

    if (!insertfirst_list(l, firstfile)) {
        // Se a inserção não deu certo
        printf("Erro ao inserir %s na lista.\n", firstfile);
        free_list(l);
        return;
    }

    if (!save_list(listname, l)) {
        // Se não deu pra salvar
        printf("Erro ao salvar lista.\n");
    }

    free_list(l);
}

void add(char * listname, char * file) {
    ilist l = new_list();

    if (strstr(file, ".pgm") == NULL) {
        // Se o arquivo não tem a extensão .pgm
        printf("Esse programa suporta apenas arquivos .pgm.\n");
        return;
    }

    if (!load_list(listname, l)) {
        // Se o carregamento não deu certo
        printf("Erro ao carregar lista.\n");
        free_list(l);
        return;
    }

    int p;
    search_list(l, &p, file);
    if (p != -1) {
        // Esse arquivo já existe na lista
        printf("Essa imagem já existe na lista.\n");
        return;
    }

    if (!insertfirst_list(l, file)) {
        // Se a inserção não deu certo
        printf("Erro ao inserir %s na lista.\n", file);
        free_list(l);
        return;
    }

    quick_sort(l, 0, l->last, str_vemantes); // Ordena alfabéticamente a lista
    // Só é necessário chamar essa função quando um item é adicionado a uma lista já existente

    if (!save_list(listname, l)) {
        // Se não deu pra salvar
        printf("Erro ao salvar alterações na lista.\n");
    }

    free_list(l);
}

void rm(char * listname, char * file) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se o carregamento não deu certo
        printf("Erro ao carregar lista.\n");
        free_list(l);
        return;
    }

    if (!removebysearch_list(l, file)) {
        // Se a imagem não estiver na lista
        printf("Essa imagem não existe na lista.\n");
        free_list(l);
        return;
    }

    if (getsize_list(l) == 0) {
        // Se a lista ficar vazia depois da remoção
        printf("Lista só possui essa imagem, removendo a lista toda.\n");
        remove(listname);
        free_list(l);
        return;
    }

    if (!save_list(listname, l)) {
        // Se não deu pra salvar
        printf("Erro ao salvar alterações na lista.\n");
    }

    free_list(l);
}

void lim(char * listname, int lim) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se não for possível carregar
        printf("Erro ao carregar lista.\n");
        free_list(l);
        return;
    }

    for (image i = l->first; i != NULL; i = i->next) {
        // Itera pela lista processando cada imagem
        printf("Processando arquivo %s...", i->name);

        imgb img = load_imgb(i->name);
        if (is_null_imgb(&img)) {
            // Se a imagem não foi encontrada
            printf(" Não foi possível encontrar imagem, pulando.\n");
        } else {
            char temp[PATH_MAX] = "lim_";
            strcat(temp, i->name);
            limiar(&img, lim);
            save_imgb(temp, &img);
            free_imgb(&img);

            printf(" Pronto!\n");
        }
    }

    free_list(l);
}

void printl(char * listname) {
    ilist l = new_list();

    if (!load_list(listname, l)) {
        // Se não for possível carregar
        printf("Erro ao carregar lista.\n");
        free_list(l);
        return;
    }

    print_list(l);

    free_list(l);
}

int main(int argc, char * argv[]) {
    if (argc == 2)
        if (strcmp(argv[1], "help") == 0)
            helper();
        else
            error();
    else if (argc == 3) {
        // argv[1] é sempre o nome da lista
        if (strcmp(argv[2], "inv") == 0)
            // Inverter a lista
            inv(argv[1]);
        else if (strcmp(argv[2], "esph") == 0)
            // Espelhar horizontalmente a lista
            esph(argv[1]);
        else if (strcmp(argv[2], "espv") == 0)
            // Espelhar verticalmente a lista
            espv(argv[1]);
        else if (strcmp(argv[2], "print") == 0)
            // Imprimir na tela a lista
            printl(argv[1]);
        else
            error();       
    } else if (argc == 4) {
        // argv[1] é sempre o nome da lista
        if (strcmp(argv[2], "create") == 0)
            // Cria uma lista
            create(argv[1], argv[3]);
        else if (strcmp(argv[2], "add") == 0)
            // Adiciona um item à lista
            add(argv[1], argv[3]);
        else if (strcmp(argv[2], "rm") == 0)
            // Remove um item da lista
            rm(argv[1], argv[3]);
        else if (strcmp(argv[2], "lim") == 0)
            // Limiariza as imagens da lista
            lim(argv[1], atoi(argv[3]));
        else
            error();
    } else
        error();

    return 0;
}
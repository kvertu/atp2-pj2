#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/image.h"

imgb load_imgb(char * filename) {
    imgb img;

    FILE * fload = fopen(filename, "r");
    if (fload == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo %s.\n", filename);
        img.pixel = NULL;
        return img;
    }

    // Tipo de imagem, não é relevante aqui
    char ver[5];
    fscanf(fload, "%s", ver);

    // Dimensões da imagem e tons de cinza
    fscanf(fload, "%d %d %d", &img.h, &img.w, &img.cinza);

    // Alocação de memória para as linhas da matriz de pixels
    img.pixel = malloc(img.h * sizeof(int *));
    if (img.pixel == NULL) {
        printf("ERRO: Não foi possível alocar memória para a imagem %s.\n", filename);
        return img;
    }

    // Alocando memória para as colunas da matriz de pixels
    for (int i = 0; i < img.h; i++) {
        img.pixel[i] = malloc(img.w * sizeof(int));
        if (img.pixel[i] == NULL) {
            printf("ERRO: Não foi possível alocar memória para a imagem %s.\n", filename);
            return img;
        }
    }

    // Inserindo os dados da imagem na matriz
    for (int i = 0; i < img.h; i++) {
        for (int j = 0; j < img.w; j++) {
            fscanf(fload, "%d", &img.pixel[i][j]);
        }
    }

    fclose(fload); // Fecha o arquivo

    return img;
}

bool is_null_imgb(imgb * img) {
    // Verifica se pixel é nulo
    if (img->pixel == NULL)
        return true;
    else {
        for (int i = 0; i < img->h; i++) {
            // Verifica se pixel[i] é nulo para cada i
            if (img->pixel[i] == NULL)
                return true;
        }
        return false;
    }
}

void free_imgb(imgb * img) {
    if (is_null_imgb(img)) {
        printf("Matriz possui ponteiros nulos, não há memória para ser liberada.\n");
        return;
    }

    for (int i = 0; i < img->h; i++) {
        // Liberando a memória das colunas da matriz
        free(img->pixel[i]);
        img->pixel[i] = NULL;
    }

    // Libera a memória das linhas da matriz
    free(img->pixel);
    img->pixel = NULL;
    img->h = 0;
    img->w = 0;
    img->cinza = 0;
}

void limiar(imgb * img, int lim) {
    // Verifica se imgb é nulo
    if (is_null_imgb(img)) {
        printf("Não é possível obter a limiar, matriz de pixels é nula.\n");
        return;
    }

    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            if (img->pixel[i][j] < lim) {
                // pixel[i][j] = 0, se img[i][j] < lim
                img->pixel[i][j] = 0;
            } else {
                // pixel[i][j] = maior tom de cinza da imagem, caso contrário
                img->pixel[i][j] = img->cinza;
            }
        }
    }
}

void inverter(imgb * img) {
    // Verifica se imgb é nulo
    if (is_null_imgb(img)) {
        printf("Não é possível obter a inversa, matriz de pixels é nula.\n");
        return;
    }

    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            img->pixel[i][j] = img->cinza - img->pixel[i][j];
        }
    }
}

void espelhar_v(imgb * img) {
    // Verifica se imgb é nulo
    if (is_null_imgb(img)) {
        printf("Não é possível espelhar, matriz de pixels é nula.\n");
        return;
    }

    // Cria um clone da matriz de pixels
    int clone[img->h][img->w];
    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            clone[i][j] = img->pixel[i][j];
        }
    }

    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            img->pixel[i][j] = clone[i][img->w - 1 - j];
        }
    }
}

void espelhar_h(imgb * img) {
    // Verifica se imgb é nulo
    if (is_null_imgb(img)) {
        printf("Não é possível espelhar, matriz de pixels é nula.\n");
        return;
    }

    // Cria um clone da matriz de pixels
    int clone[img->h][img->w];
    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            clone[i][j] = img->pixel[i][j];
        }
    }

    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            img->pixel[i][j] = clone[img->h - 1 - i][j];
        }
    }
}

void save_imgb(char * filename, imgb * img) {
    /*
        Estrutura do arquivo:
            P2
            h w
            c
            p[0][0] p[0][1] ...
        Sendo:
            P2: Formato do arquivo, constante em arquivos .pgm
            h: Altura do arquivo (em pixels)
            w: Largura do arquivo (em pixels)
            c: Quantidade de tons de cinza
            p[][]: Valor de cada pixel da imagem
    */

    // Verifca se imgb é nulo
    if (is_null_imgb(img)) {
        printf("Não é possível imprimir valores no arquivo, imagem nula.\n");
        return;
    }

    // Abre o arquivo filename
    FILE * fsave = fopen(filename, "w");

    // Verifica se conseguiu abrir o arquivo
    if (fsave == NULL) {
        printf("Arquivo inexistente.\n");
        return;
    }

    // Imprime o cabeçalho do arquivo
    fprintf(fsave, "P2\n%d %d\n%d\n", img->h, img->w, img->cinza);
    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            fprintf(fsave, "%d ", img->pixel[i][j]);
        }
        fprintf(fsave, "\n");
    }

    fclose(fsave); // Fecha o arquivo
}
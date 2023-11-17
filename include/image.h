#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int h, w; // Altura e largura da imagem
    int cinza; // Quantidade de tons de cinza
    int ** pixel; // Matriz de pixels
} imgb;

imgb load_imgb(char * filename); // Ler o arquivo .pgm e armazena em na struct imgb
bool is_null_imgb(imgb * img); // Verifica se o struct é nulo
void free_imgb(imgb * img); // Libera a memória alocada pelo struct
void limiar(imgb * img, int lim); // Faz a limiarização da imagem
void inverter(imgb * img); // Inverte as cores da imagem
void espelhar_h(imgb * img); // Espelha horizontalmente a imagem
void espelhar_v(imgb * img); // Espelha verticalmente a imagem
void save_imgb(char * filename, imgb * img); // Escreve a imagem em um arquivo
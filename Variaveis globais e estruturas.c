#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Variaveis Globais //bool= valor de verdadeiro ou falso
bool gameLoop = true;
// tentativas estao como global para nao adicionalas ao score caso o jogador sai
// do jogo sem jogar
int tentativas = 0;
// Usado no calculo de score final do usuario
int countDeMissTotal = 0;
// Usado para contar quantas vezes o usuario jogou nas categorias
int numeroDeVezesJogadas = 0;
// Usado para guardar o valor original da variavel original e adicionar o valor n-1 ao vetor Jogatinas
int auxiliarNumeroDeJogadas;
// Vetor para guardar o vetor de score na ordem reversa
int reversoVetorScore[100];
// Vetor para armazenar o numero de jogatinas, suas posições e valores
int vetorJogatinas[100];
// Usado para calculo de Score parcial
int countDeMissDaSessao;

struct player
{
    char nome[7];
    // cada um desse sera um dos scores feitos na sessão
    int scoreParcial[100];
    // Calculado apos o fim da execução
    int scoreFinal;
};

struct player jogador;

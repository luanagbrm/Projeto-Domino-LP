/*
DOM-BGLL - Projeto Dominó - Etapa 3
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_MODEL_H
#define DOM_BGLL_PROJETO_MODEL_H

#define NUM_PECAS 28
#define HAND_PECAS_INICIAL 7
#define HAND_PECAS_MAX 21
#define NUM_JOGADORES 2

typedef struct{
  int ladoA;
  int ladoB;
  char status;
  int pos;
} Carta;

typedef struct{
  int playedCards;
  int ladoE;
  int ladoD;
} Mesa;

//Structure que representa cada jogador 
typedef struct{
  Carta hand[21];//hand Ã© um array da estrutura "Cartas"
  int numPieces;//variavel para saber a qtd de cartas na mÃ£o de cada player
}Player;

Carta domino[28];
Mesa limitesMesa;
Mesa mesa[28];
Player players[2];
int myIndex =0;
int jogadorAtual = 0;

void criarCarta(Carta domino[NUM_PECAS]);
void iniciaMesa(Mesa mesa[28]);

#endif
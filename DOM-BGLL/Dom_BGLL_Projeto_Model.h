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
  char status; //NULL ('\0'), 'M', '1', '2'
  int pos; //guarda a posicao da peca na array original
} Carta;

typedef struct{
  int playedCards;
  int ladoE;
  int ladoD;
} Mesa;

//Structure que representa cada jogador 
typedef struct{
  Carta pecasMao[HAND_PECAS_MAX];//pecasMao é um array da estrutura "Cartas" que representa as cartas que cada jogador tem, podendo ter tamanho máximo de 21 pecas (total - inicial)
  int numPieces; //variavel para saber a qtd de cartas na mao de cada jogador
}Jogador;

Carta domino[28];
Mesa limitesMesa; //guarda o valor das extremidades da mesa para facilitar comparação
Mesa mesa[28];
Jogador jogadores[2];
int qtdPecasMesa = 0; //variável de controle da qtd de peças que já foram jogadas na mesa
int jogadorAtual; // define de que jogador é o turno atual

void criarCarta(Carta domino[NUM_PECAS]);
void iniciaMesa(Mesa mesa[28]);

#endif

/*
DOM-BGLL - Projeto Dominó - Etapa 3
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_VIEW
#define DOM_BGLL_PROJETO_VIEW

#include "Dom_BGLL_Projeto_Model.h"
#include <stdio.h>
#include <stdlib.h>

void mostrarCartas(Carta domino[NUM_PECAS]);
int numeroJogadores(void);
void statusCompra(int status);
void mostrarPecasJogador(Jogador jogadores[NUM_JOGADORES], int numJogadores);
void mostrarPecasMesa(Mesa mesa[]);
int menuPrincipal();
char receberLadoJogada();
int receberPosicaoPeca();
int menuPrincipalJogador();
void mostrarPecasJogadorInd(Jogador jogadores[NUM_JOGADORES], int numJogador);
void interacoesMenu(int opcao);

#endif

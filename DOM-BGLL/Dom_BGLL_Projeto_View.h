/*
DOM-BGLL - Projeto Domino - Etapa 5
10/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_VIEW
#define DOM_BGLL_PROJETO_VIEW

#include "Dom_BGLL_Projeto_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void mostrarCartas(Carta domino[NUM_PECAS]);
int numeroJogadores(void);
void statusCompra(int status);
void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogadores);
void mostrarPecasMesa(Mesa mesa[]);
int menuPrincipal();
char receberLadoJogada();
int receberPosicaoPeca();
int menuPrincipalJogador();
void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogador);
void interacoesMenu(int opcao);
void mostrarRegras();
void mensagemRecuperarJogo(int status);
void limparTela();
void limparBuffer();

#endif

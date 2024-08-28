/*
DOM-BGLL - Projeto Dominó - Etapa 3
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_CONTROLLER_H
#define DOM_BGLL_PROJETO_CONTROLLER_H

#include "Dom_BGLL_Projeto_View.cpp"
#include "Dom_BGLL_Projeto_Model.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void gerarSeed();
void jogar();
void definirJogadorAtual();
void embaralharPecas(Carta domino[NUM_PECAS]);
void distribuirPecas(Carta totalPieces[28], Jogador jogadores[NUM_JOGADORES], int numJogadores);
int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]);
void removerPecaJogada(Jogador *jogador, int pos);
int checarJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos);
int encontrarDupla(Jogador jogador[NUM_JOGADORES], Mesa mesa[28]);
int encontrarMaior(Jogador jogador[NUM_JOGADORES]);
int primeiroJogador(Jogador jogadores[NUM_JOGADORES], Mesa mesa[28]);
int buyCards(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum);
int numeroJogadores(void);
void jogarPeca(Mesa mesa[28], Jogador jogadores[NUM_JOGADORES], int jogador, int pos);
//void iniciaJogo();

#endif

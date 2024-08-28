#ifndef DOM_BGLL_PROJETO_CONTROLLER_H
#define DOM_BGLL_PROJETO_CONTROLLER_H

#include "Dom_BGLL_Projeto_View.cpp"
#include "Dom_BGLL_Projeto_Model.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void gerarSeed();
void definirJogadorAtual();
void embaralharPecas(Carta domino[NUM_PECAS]);
void pieceGiveAway(Carta totalPieces[28], Player players[NUM_JOGADORES], int numPlayers);
void removerPecaJogada(Player *player, int pos);
int checarJogadaValida(Player players[NUM_JOGADORES], int player, int pos);
int encontrarDupla(Player player[NUM_JOGADORES], Mesa mesa[28]);
int encontrarMaior(Player player[NUM_JOGADORES]);
int primeiroJogador(Player players[NUM_JOGADORES], Mesa mesa[28]);
int buyCards(Carta totalPieces[NUM_PECAS], Player *player, int playerNum);
int playerNumber(void);
void jogarPeca(Mesa mesa[28], Player players[NUM_JOGADORES], int player, int pos);
//void iniciaJogo();

#endif
#ifndef DOM_BGLL_PROJETO_VIEW
#define DOM_BGLL_PROJETO_VIEW

#include "Dom_BGLL_Projeto_Model.h"
#include <stdio.h>

int escolha;

void mostrarCartas(Carta domino[NUM_PECAS]);
void showHandPieces(Player players[NUM_JOGADORES], int numPlayers);
void showTablePieces(Mesa mesa[]);
void mostrarMenu();

#endif
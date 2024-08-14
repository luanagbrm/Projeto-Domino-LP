//O arquivo Model integra toda a logica do programa para gerenciar dados(ex: as estruturas/func para as pecas do domino e os jogadores)

#include "Dom_BGLL_Projeto_Model.h"
#include <stdlib.h>
#include <time.h>

void criarCarta(Carta domino[28]) {
    Carta peca;
    int j = 0;

    for (int i = 0; i <= 6; i++) {
        for (int k = i; k <= 6; k++) {
            peca.ladoA = i;
            peca.ladoB = k;
            domino[j] = peca;
            j++;
        }
    }
}

void embaralharPecas(Carta domino[28]) {
    Carta peca2;
    int p;

    for (int i = 0; i < 28; i++) {
        peca2 = domino[i];
        p = rand() % 28;
        domino[i] = domino[p];
        domino[p] = peca2;
    }
}

void pieceGiveAway(Carta totalPieces[28], Player players[2], int numPlayers) {
    int pieceAssign = 0;

    for (int i = 0; i < numPlayers; i++) {
        players[i].numPieces = 0;

        for (int k = 0; k < 7 && pieceAssign < 28; k++) {
            players[i].hand[k] = totalPieces[pieceAssign++];
            players[i].numPieces++;
        }
    }
}

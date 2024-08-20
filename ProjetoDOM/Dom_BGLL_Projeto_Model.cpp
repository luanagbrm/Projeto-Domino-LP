#include "Dom_BGLL_Projeto_Model.h"

#include <stdlib.h>

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
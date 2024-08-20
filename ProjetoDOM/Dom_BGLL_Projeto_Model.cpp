/*
DOM-BGLL - Projeto Dominó - Etapa 2
20/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

 A pasta Model contém os dados e estruturas que serão manipulados
*/

#include "Dom_BGLL_Projeto_Model.h"
#include <stdlib.h>

//função para criar as peças(cartas) do dominó
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

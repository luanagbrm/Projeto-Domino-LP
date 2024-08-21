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

void inciaMesa(Mesa mesaDoJogo){
	mesaDoJogo.pecaMesa = 0;// Inicia o jogo com 0 pecas na mesa


	for(int k = 0; k < 28;k++ ){
		mesaDoJogo.mesa[k].ladoA = -7; // -7 e uma sentinela para o lugar da peca 
		mesaDoJogo.mesa[k].ladoB = -7;
	}
}

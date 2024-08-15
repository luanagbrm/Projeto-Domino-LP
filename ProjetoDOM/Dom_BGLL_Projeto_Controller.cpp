/*
DOM-BGLL - Projeto Dominó - Etapa 2
14/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

A Etapa 2 consiste de criar 7 arquivos com a finalidade de separar o projeto de acordo com seu proposito.
A parte destinada à funcionalidade do programa está destinada a pasta Controller, a qual irá embaralhar as peças do jogo.

*/

#include "Dom_BGLL_Projeto_Controller.h"
#include "Dom_BGLL_Projeto_View.cpp"
//#include "Dom_BGLL_Projeto_Model.cpp"

void gerarSeed(){
	srand( (unsigned)time(0) );
}

//Função para embaralhar as cartas
void embaralharPecas(Carta domino[28]){
	Carta peca2;
	int p;
	
	for(int i = 0; i < 28;i++){
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
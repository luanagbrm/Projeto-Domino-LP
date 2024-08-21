/*
DOM-BGLL - Projeto Dominó - Etapa 2
20/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

A parte destinada à funcionalidade do programa está destinada a pasta Controller, ele é o mediador entre o Model e o View.
*/

#include "Dom_BGLL_Projeto_Controller.h"
#include "Dom_BGLL_Projeto_View.cpp"
#include <time.h>

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

void jogar(){

	gerarSeed();
	criarCarta(domino);
    embaralharPecas(domino);
    pieceGiveAway(domino, player, numPlayer);
    showHandPieces(players, numPlayer);
    mostrarCartas(domino);
    
}

 //Menu de funcionalidades do jogo
void menu(){
	mostrarMenu();
	do{
        switch(opcao) 
        {
            case 1:
            	jogar();
            //case 2:
               // embaralharPecas(domino);
                //mostrarCartas(domino);
                //printf("\n\nCartas embaralhadas");
               // break;
            //ase 3:
               // printf("Saindo do jogo");
                //break;
            //default:
                //printf("Opcao invalida. Tente novamente.\n");
        }
        
    }while(opcao != 1);
}

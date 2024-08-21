/*
DOM-BGLL - Projeto Dominó - Etapa 2
20/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

 O View e responsável pela visualização dos dados e interação com o usuário.
*/

#include "DOM_BGLL_Projeto_View.h"
#include <stdio.h>

int opcao;

//Função para mostrar todas as cartas do jogo
void mostrarCartas(Carta domino[28]){	
	for(int i = 0; i < 28; i++){
	    if(i%7 == 0 )
	        printf("\n"); //Para melhorar a visualização, mostra apenas 7 peças por linha
	    printf("[%d | %d]", domino[i].ladoA, domino[i].ladoB);
	}
}

void showHandPieces(Player players[2], int numPlayers){

	for(int i = 0; i < numPlayers; i++){
		printf("Jogador %d: \n", i + 1);//o i = 1 numera corretamente cada player
		for(int k = 0 ; k < players[i].numPieces; k++){
			printf("[%d|%d]",players[i].hand[k].ladoA,players[i].hand[k].ladoB);
			
		}
		printf("\n");
	}
}


// Função para mostrar o menu do jogo
int mostrarMenu(){
	 printf("\n---------------------------------------\n");
     printf("MENU - Escolha uma opcao: \n");
     printf("1 - Iniciar jogo\n");
     printf("2 - Mostrar\n");
     printf("3 - Sair\n");
     printf("\n---------------------------------------\n");
	 scanf("%d",&opcao);

}
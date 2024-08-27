#include "Dom_BGLL_Projeto_View.h"


void mostrarCartas(Carta domino[NUM_PECAS]){
  for(int i = 0; i < NUM_PECAS; i++){
      if(i%7 == 0 )
          printf("\n");
    printf("[%d|%d] --- status: %c \n\n", domino[i].ladoA, domino[i].ladoB, domino[i].status);
  }
}

void showHandPieces(Player players[NUM_JOGADORES], int numPlayers){

  for(int i = 0; i < numPlayers; i++){
    printf("Jogador %d: \n", i + 1);//o i = 1 numera corretamente cada player
    for(int k = 0 ; k < players[i].numPieces; k++){
		if(players[i].hand[k].status != 'M')
			printf("[%d|%d]",players[i].hand[k].ladoA,players[i].hand[k].ladoB);
    }

    printf("\n");
  }
}

//Mostra todas as pecas da mesa
void showTablePieces(Mesa mesa[]){
   	printf("\nMesa do Jogo: \n\n");
   	printf("-------------------\n");
    for(int k  = 0; k < index; k++)
        printf("[%d|%d]", mesa[k].ladoE, mesa[k].ladoD);
	printf("\n-------------------");
    printf("\n");
}
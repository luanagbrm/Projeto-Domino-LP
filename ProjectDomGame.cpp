#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structure sobre as informações de cada carta do dominó
typedef struct{
	int ladoA;
	int ladoB;
	int status;
}Carta;

//Structure que representa cada jogador 
typedef struct{
	Carta hand[7];//hand é um array da estrutura "Cartas"
	int numPieces;//variavel para saber a qtd de cartas na mão de cada player
	
}Player;

//função para criar cartas
void criarCarta(Carta domino[28]){
	Carta peca;
	int j = 0;
	
	for(int i = 0; i <= 6; i++){
		for(int k = i; k <= 6; k++){
			peca.ladoA = i;
			peca.ladoB = k;
			domino[j] = peca;
			j++;
		}
	}
}

//Função utilizada para pedir o número de jogadores ao usuário e validar os dados
int playerNumber(void){
	
	int numPlayer;
	
	printf("Digite o número de jogadores para a partida(1 ou 2)"); //**** o usuário deve poder sair do loop
	
	scanf("%d",&numPlayer);
	
	while(numPlayer <1||numPlayer > 2 ){//O loop não deixa o usuário prosseguir até que o mesmo digite um dado válido  **** o usuário deve poder sair do loop
		printf("O número de jogadores escolhido é inválido. Digite 1 ou 2");
		scanf("%d",&numPlayer);
	}
	return numPlayer;//retorno que será útil no main 
}



//Função para mostrar todas as cartas do jogo
void mostrarCartas(Carta domino[28]){	
	for(int i = 0; i < 28; i++){
	    if(i%7 == 0 )
	        printf("\n");
		printf("[%d | %d]", domino[i].ladoA, domino[i].ladoB);
	}
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

void pieceGiveAway(Carta totalPieces[28], Player players[2], int numPlayers){
	
	int pieceAssign = 0;//acessa todas as peças  uma por uma e distribui para um jogador
	
	for(int i = 0; i < numPlayers; i++){
		players[i].numPieces = 0; // parte necessária para inicialização do num de peças dadas
		
		for(int k = 0; k < 7  && pieceAssign < 28; k++){
			players[i].hand[k] = totalPieces[pieceAssign++];
			players[i].numPieces++;
		}
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

int main(){
 	
 	int opcao;
	srand( (unsigned)time(NULL) );
	
	Carta domino[28];
	criarCarta(domino);
	mostrarCartas(domino);
	printf("\n");	
	embaralharPecas(domino);
	mostrarCartas(domino);
	printf("\n");
	embaralharPecas(domino);
	mostrarCartas(domino);
	printf("\n");
	embaralharPecas(domino);
	mostrarCartas(domino);
	printf("\n");
		
	printf("Jogo Domino");
	
	
	
	do{
           //Menu de funcionalidades do jogo
	     printf("\n---------------------------------------\n");
            printf("MENU - Escolha uma opcao: \n");
            printf("1 - Mostrar cartas\n");
            printf("2 - Embaralhar cartas\n");
            printf("3 - Sair\n");
            printf("\n---------------------------------------\n");
	     scanf("%d",&opcao);
       
       
       switch(opcao) 
       {
           case 1:
               mostrarCartas(domino);;
               printf("\n\nCartas disponiveis do jogo");
		break;
           case 2:
               embaralharPecas(domino);
               mostrarCartas(domino);
               printf("\n\nCartas embaralhadas");
               break;
           case 3:
               printf("Saindo do jogo");
               break;
           default:
               printf("Opcao invalida. Tente novamente.\n");
       }
       
   }while(opcao != 3);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//structure sobre as informaçr3ões de cada carta do dominó
typedef struct{
  int ladoA;
  int ladoB;
  char status;
}Carta;


typedef struct{
  int ladoE;
  int ladoD;
//	char status;//status "M","1", and"2"
}Mesa[28];

//Structure que representa cada jogador 
typedef struct{
  Carta hand[7];//hand é um array da estrutura "Cartas"
  int numPieces;//variavel para saber a qtd de cartas na mão de cada player
}Player;

//int iniciaJogador(Carta totalPieces[28], Player players[2], int numPlayers){
//	
//	int incialPlayer = -7;
//	int doublePiece = 0; 
//	int greatestPiece = -7;
//	
//	for(i = 0; i < numPlayers; i++){
//		for(k = 0; k < 7; k++){
//			if(numPlayers[i].ladoA[k] == players[i].ladoB[k]){
//				doublePiece  = numPlayers[i].ladoA[k]; 
//				if(greatestPiece <  )
//					
//			}
//		}
//	}
//
//	
//}

//typedef struct{
//    Carta mesa[28];//assegura todas as 28 pecas da mesa
//   int pecaMesa;//guarda o numero de pecas jogadas/na mesa no momento
//}Mesa;


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

  printf("Digite o número de jogadores para a partida(1 ou 2):");

  scanf("%d",&numPlayer);

  while(numPlayer <1||numPlayer > 2 ){//O loop não deixa o usuário prosseguir até que o mesmo digite um dado válido
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
//Update da funcao para que seja útil na questao dos status
void pieceGiveAway(Carta totalPieces[28], Player players[2], int numPlayers){

  int pieceAssign = 0;//acessa todas as peças  uma por uma e distribui para um jogador

  for(int i = 0; i < numPlayers; i++){
    players[i].numPieces = 0; // parte necessária para inicialização do num de peças dadas

    for(int k = 0; k < 7  && pieceAssign < 28; k++){
      players[i].hand[k] = totalPieces[pieceAssign++];
      players[i].hand[k].status = '1' + i;
      players[i].numPieces++;
    }
  }
  for(int j = 0; j < pieceAssign;j++){
    totalPieces[j].status = 'M';
  }
}
//Fazer uma function para cada coisa do iniciar jogadores

// Função para encontrar a maior peça cujo ambos os lados são iguais na mão de cada jogador, retornando '1' caso esteja com o jogador 1, ou '2' caso esteja com o jogador 2'
int encontrarDupla(Player player[2]){
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peça da mão do jogador 1 e do jogador 2
    // buscando a peça cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((player[0].hand[i].ladoA == k) && (player[0].hand[i].ladoB == k)){
        player[0].hand[i].status = 'M'; //Altera o status da peça para 'M', indicando que ela foi jogada
        return 1; // Encerra a busca no momento que encontra a maior peça dupla presente em ambas as mãos
      }

      //Caso não encontre a peça dupla na mão do jogador 1, a função busca na mão do jogador 2

      if((player[1].hand[i].ladoA == k) && (player[1].hand[i].ladoB == k)){
        player[1].hand[i].status = 'M';
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se não encontrar nenhuma peça dupla na mão de ambos
}

int encontrarMaior(Player player[2]){	
    for(int k = 11; k >= 0; k--){
      for(int i = 0; i < 7; i++){
        if((player[0].hand[i].ladoA + player[0].hand[i].ladoB) == k){
          printf("[%d|%d]",player[0].hand[i].ladoA,player[0].hand[i].ladoB);
          
          return 1;
        }

        if((player[1].hand[i].ladoA + player[1].hand[i].ladoB) == k){
          printf("[%d|%d]",player[1].hand[i].ladoA,player[1].hand[i].ladoB);
          return 2;
        }

      }
    }

  return -1;
}

int primeiroJogador(Player players[2]){

  int jogador1 = encontrarDupla(players);

  if(jogador1 ==  -1){ 
      jogador1 = encontrarMaior(players);
  }

  return jogador1;
}
/*int findGreastePiece(Carta totalPieces[28],Player numPieces, Player HandPieces ){

  int doublePiece = 0;
  int greastePiece = - 7;

  pieceGiveAway();

  for(int i = 0 ; i < numPlayers ; i++){
    for(int j = 0; j < 7 ; j++){
      if(players[i].ladoA[k] == players[i].ladoB[k]){
        doublePiece = players[i].ladoA[k];
        if(greastePiece < doublePiece){
          greastePiece = doublePiece;
        }
      }
    }
}*/

void showHandPieces(Player players[2], int numPlayers){

  for(int i = 0; i < numPlayers; i++){
    printf("Jogador %d: \n", i + 1);//o i = 1 numera corretamente cada player
    for(int k = 0 ; k < players[i].numPieces; k++){
      printf("[%d|%d]",players[i].hand[k].ladoA,players[i].hand[k].ladoB);

    }
    printf("\n");
  }
}
//Perguntar para a luana como fazer passagem por referencia sem usar "->"
/*void inciaMesa(Mesa mesaDoJogo){
  mesaDoJogo.pecaMesa = 0;// Inicia o jogo com 0 pecas na mesa


  for(int k = 0; k < 28;k++ ){
    mesaDoJogo.mesa[k].ladoA = -7; // -7 e uma sentinela para o lugar da peca 
    mesaDoJogo.mesa[k].ladoB = -7;
  }
}*/

// funcao para comprar cartas caso a peca tenha status M, retorn 1 se a peca for comprada e 0 se nao ha pecas para a compra
int buyCards(Carta totalPieces[28], Player players[2], int numPlayers){

  // int pecaComprada = 0;

   // pieceGiveAway( totalPieces, players, int numPlayers);

  for(int k = 0; k < 28; k++){
    if( totalPieces[k].status == 'M'){
      for(int i = 0; i < numPlayers; i++){
        if (players[i].numPieces < 7) {
          players[i].hand[players[i].numPieces++] = totalPieces[k];
          players[i].hand[players[i].numPieces - 1].status = '1' + i;
          totalPieces[k].status = '1' + i;
          printf("\nO jogadoe %d comprou uma peca com sucesso\n", i + 1);
          return 1;//comrpra feita 
      }
    }
    }
  }
    printf("Nao ha pecas para comprar");
     return 0;//nao foi possivel fazer a compra
}

int main(){
  srand( (unsigned)time(0) );
  Carta domino[28];

  Player players[2];

  criarCarta(domino);
  embaralharPecas(domino);
  int numPlayer = playerNumber();//Variável para a chamada da função playerNumber()

  pieceGiveAway(domino, players, numPlayer);
  printf("\n");	
  showHandPieces(players, numPlayer);
  printf("\n");
  mostrarCartas(domino);

  int firstPlayer = primeiroJogador(players);
  printf("\n\nA partida comeca com o jogador %d\n", primeiroJogador(players));

//	embaralharPecas(domino);
//	printf("\n");
//	mostrarCartas(domino);

  return 0;
}

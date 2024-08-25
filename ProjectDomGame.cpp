#include <stdio.h>
#include <stdlib.h>
#include <time.h>



//structure sobre as informaÃ§r3Ãµes de cada carta do dominÃ³
typedef struct{
  int ladoA;
  int ladoB;
  char status;
  int pos;
} Carta;


typedef struct{
  int playedCards;
  Carta played[28];
  int ladoE;
  int ladoD;
//	char status;//status "M","1", and"2"
} Mesa;

//Structure que representa cada jogador 
typedef struct{
  Carta hand[7];//hand Ã© um array da estrutura "Cartas"
  int numPieces;//variavel para saber a qtd de cartas na mÃ£o de cada player
}Player;

Carta domino[28];
Mesa mesa;
Player players[2];


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
//   int pecaMesa;//gua

// rda o numero de pecas jogadas/na mesa no momento
//}Mesa;


//funÃ§Ã£o para criar cartas
void criarCarta(Carta domino[28]){
  Carta peca;
  int j = 0;

  for(int i = 0; i <= 6; i++){
    for(int k = i; k <= 6; k++){
      peca.ladoA = i;
      peca.ladoB = k;
      peca.pos = j;
      peca.status = '\0';
      domino[j] = peca;
      j++;
    }
  }
}

//FunÃ§Ã£o utilizada para pedir o nÃºmero de jogadores ao usuÃ¡rio e validar os dados
int playerNumber(void){

  int numPlayer;

  printf("Digite o nÃºmero de jogadores para a partida(1 ou 2):");

  scanf("%d",&numPlayer);

  while(numPlayer <1||numPlayer > 2 ){//O loop nÃ£o deixa o usuÃ¡rio prosseguir atÃ© que o mesmo digite um dado vÃ¡lido
    printf("O nÃºmero de jogadores escolhido Ã© invÃ¡lido. Digite 1 ou 2");
    scanf("%d",&numPlayer);
  }
  return numPlayer;//retorno que serÃ¡ Ãºtil no main 
}



//FunÃ§Ã£o para mostrar todas as cartas do jogo
void mostrarCartas(Carta domino[28]){
  for(int i = 0; i < 28; i++){
      if(i%7 == 0 )
          printf("\n");
    printf("[%d|%d]", domino[i].ladoA, domino[i].ladoB);
  }
}

//FunÃ§Ã£o para embaralhar as cartas
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
//Update da funcao para que seja Ãºtil na questao dos status
void pieceGiveAway(Carta totalPieces[28], Player players[2], int numPlayers){

  int pieceAssign = 0;//acessa todas as peÃ§as  uma por uma e distribui para um jogador

  for(int i = 0; i < numPlayers; i++){
    players[i].numPieces = 0; // parte necessÃ¡ria para inicializaÃ§Ã£o do num de peÃ§as dadas

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

int checarJogadaValida(Mesa *mesa, Player players[2], int player, int pos) {
  Carta pecaJogada = players[player].hand[pos];
  int ladoD = mesa->ladoD;
  int ladoE = mesa->ladoE;

  if(pecaJogada.ladoA == ladoD){
    mesa->ladoD = pecaJogada.ladoB;
    return 1;
  } else if(pecaJogada.ladoB == ladoD){
    mesa->ladoD = pecaJogada.ladoA;
    return 1;
  } else if(pecaJogada.ladoA == ladoE){
    mesa->ladoE = pecaJogada.ladoB;
    return 1;
  } else if(pecaJogada.ladoB == ladoE){
    mesa->ladoE = pecaJogada.ladoA;
    return 1;
  } 

  return -1;


    printf("[%d|%d]\n", mesa->ladoE, mesa->ladoD);
}

void jogarPeca(Mesa *mesa, Player players[2], int player, int pos) {
  players[player].hand[pos].status = 'M'; //Altera o status da peÃ§a para 'M', indicando que ela foi jogada

  if(mesa->ladoD == -7 && mesa->ladoE == -7){
    mesa->ladoE = players[player].hand[pos].ladoA;
      mesa->ladoD = players[player].hand[pos].ladoA;
  } else {
    if(checarJogadaValida(mesa, players, player, pos) == -1){
      return;
    }
  }
  mesa -> played[mesa->playedCards++] = players[player].hand[pos];//adiciona a peca jogada no array
  mesa->playedCards++;//aumentaaquantidade de pecas jogadas
}



//Fazer uma function para cada coisa do iniciar jogadores

// FunÃ§Ã£o para encontrar a maior peÃ§a cujo ambos os lados sÃ£o iguais na mÃ£o de cada jogador, retornando '1' caso esteja com o jogador 1, ou '2' caso esteja com o jogador 2'
int encontrarDupla(Player player[2], Mesa *mesa){
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peÃ§a da mÃ£o do jogador 1 e do jogador 2
    // buscando a peÃ§a cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((player[0].hand[i].ladoA == k) && (player[0].hand[i].ladoB == k)){
        jogarPeca(mesa, player, 0, i);
        return 1; // Encerra a busca no momento que encontra a maior peÃ§a dupla presente em ambas as mÃ£os
      }

      //Caso nÃ£o encontre a peÃ§a dupla na mÃ£o do jogador 1, a funÃ§Ã£o busca na mÃ£o do jogador 2

      if((player[1].hand[i].ladoA == k) && (player[1].hand[i].ladoB == k)){
        jogarPeca(mesa, player, 1, i);
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se nÃ£o encontrar nenhuma peÃ§a dupla na mÃ£o de ambos
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

int primeiroJogador(Player players[2], Mesa *mesa) {

    int jogador1 = encontrarDupla(players, mesa);


    if (jogador1 == -1) { 
        jogador1 = encontrarMaior(players);
    }

    /*if (jogador1 != -1) {
        for (int k = 0; k < players[jogador1 - 1].numPieces; k++) {
            if (players[jogador1 - 1].hand[k].ladoA == players[jogador1 - 1].hand[k].ladoB) {
                mesa->ladoE = players[jogador1 - 1].hand[k].ladoA;
                mesa->ladoD = players[jogador1 - 1].hand[k].ladoB;
                players[jogador1 - 1].hand[k].status = 'M';
            }
        }
    }*/

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

//Funcao para inciar a mesa como vazia

void inciaMesa(Mesa *mesa){
   mesa->ladoE = -7;//-7 e uma sentinela 
   mesa->ladoD = -7;
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
int buyCards(Carta totalPieces[28], Player *player, int playerNum) {
      for (int k = 0; k < 28; k++) {
          if (totalPieces[k].status == 'M') {
              if (player->numPieces < 7) {
                  player->hand[player->numPieces++] = totalPieces[k];
                  totalPieces[k].status = '1' + playerNum;
                  printf("\nCompra feita com sucesso\n");
                  return 1; // Compra feita
              }
          }
      }
      printf("Nao ha pecas para comprar");
      return 0; // Nao foi possivel fazer a compra
  }

//Mostra todas as pecas da mesa
void showTablePieces(Mesa *mesa){
   printf("\nMesa do Jogo: \n\n");
   for(int k  = 0; k < mesa -> playedCards; k++)
        printf("[%d|%d]", mesa -> played[k].ladoA,mesa -> played[k].ladoB);
  
    printf("\n");
}

int main(){
  srand( (unsigned)time(0) );


  criarCarta(domino);
  embaralharPecas(domino);
  inciaMesa(&mesa);//incia antes de pedir a quantidade de jogadores

  int numPlayer = playerNumber();//VariÃ¡vel para a chamada da funÃ§Ã£o playerNumber()

  pieceGiveAway(domino, players, numPlayer);

  printf("\n");	
  showHandPieces(players, numPlayer);
  printf("\n");

  int firstPlayer = primeiroJogador(players, &mesa);//faz passagem por referencia
  printf("\n\nA partida começa com o jogador %d com a peca [%d|%d]\n",firstPlayer, mesa.ladoE, mesa.ladoD);

  showTablePieces(&mesa);

  printf("\nTodas as cartas do jogo\n");
  mostrarCartas(domino);

  return 0;
}

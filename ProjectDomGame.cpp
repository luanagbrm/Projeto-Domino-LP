#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Variaveis globais
#define NUM_PECAS 28
#define HAND_PECAS_INICIAL 7
#define HAND_PECAS_MAX 21
#define NUM_JOGADORES 2

//structure sobre as informaÃ§r3Ãµes de cada carta do dominÃ³
typedef struct{
  int ladoA;
  int ladoB;
  char status;
  int pos;
} Carta;


typedef struct{
  int playedCards;
  //Carta played[NUM_PECAS];
  int ladoE;
  int ladoD;
//	char status;//status "M","1", and"2"
} Mesa;

//Structure que representa cada jogador 
typedef struct{
  Carta hand[HAND_PECAS_MAX];//hand Ã© um array da estrutura "Cartas"
  int numPieces;//variavel para saber a qtd de cartas na mÃ£o de cada player
}Player;

Carta domino[NUM_PECAS];
Mesa limitesMesa;
Mesa mesa[28];
Player players[NUM_JOGADORES];
int index = 0;
int jogadorAtual = 0;


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
void criarCarta(Carta domino[NUM_PECAS]){
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

void definirJogadorAtual(){
	if(jogadorAtual == 0)
		jogadorAtual = 1;
	else
		jogadorAtual = 0;
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
void mostrarCartas(Carta domino[NUM_PECAS]){
  for(int i = 0; i < NUM_PECAS; i++){
      if(i%7 == 0 )
          printf("\n");
    printf("[%d|%d] --- status: %c \n\n", domino[i].ladoA, domino[i].ladoB, domino[i].status);
  }
}

//FunÃ§Ã£o para embaralhar as cartas
void embaralharPecas(Carta domino[NUM_PECAS]){
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
void pieceGiveAway(Carta totalPieces[28], Player players[NUM_JOGADORES], int numPlayers){

  int pieceAssign = 0;//acessa todas as peÃ§as  uma por uma e distribui para um jogador

  for(int i = 0; i < numPlayers; i++){
    players[i].numPieces = 0; // parte necessÃ¡ria para inicializaÃ§Ã£o do num de peÃ§as dadas

    for(int k = 0; k < HAND_PECAS_INICIAL  && pieceAssign < NUM_PECAS; k++){
      totalPieces[pieceAssign].status = '1' + i;
      players[i].hand[k] = totalPieces[pieceAssign++];
      players[i].hand[k].pos = pieceAssign - 1; //guarda dentro de cada peça na mão do jogador a posição que ela ocupa no array principal do jogo
      players[i].hand[k].status = '1' + i;
      players[i].numPieces++;
    }
  }
}


void removerPecaJogada(Player *player, int pos) {
    for (int i = pos; i < player->numPieces - 1; i++) {
        player->hand[i] = player->hand[i + 1];
    }
    // Decrease the number of pieces
    player->numPieces--;
}

int checarJogadaValida(Player players[NUM_JOGADORES], int player, int pos) {
  Carta pecaJogada = players[player].hand[pos];
  int ladoD = limitesMesa.ladoD;
  int ladoE = limitesMesa.ladoE;
  
  	if (index == 0) { //A primeira jogada sempre será válida
		limitesMesa.ladoE = pecaJogada.ladoA;
        limitesMesa.ladoD = pecaJogada.ladoB;
        return 1;
    }

	//Verifica se a peça pode ser jogada em algum dos lados da mesa
  	if(pecaJogada.ladoA == ladoD){
    	limitesMesa.ladoD = pecaJogada.ladoB;
    	return 1;
  	} else if(pecaJogada.ladoB == ladoD){
    	limitesMesa.ladoD = pecaJogada.ladoA;
    	return 1;
	} else if(pecaJogada.ladoA == ladoE){
    	limitesMesa.ladoE = pecaJogada.ladoB;
    	return 1;
  } else if(pecaJogada.ladoB == ladoE){
    	limitesMesa.ladoE = pecaJogada.ladoA;
    	return 1;
  } 

  return -1;

}

void jogarPeca(Mesa mesa[28], Player players[NUM_JOGADORES], int player, int pos) {
  int validadeJogada = checarJogadaValida(players, player, pos);
  int posicaoOriginal =  players[player].hand[pos].pos;
  

  if(validadeJogada == 1 || mesa[index].ladoD == -7 && mesa[index].ladoE == -7){
	players[player].hand[pos].status = 'M'; //Altera o status da peÃ§a para 'M', indicando que ela foi jogada
    mesa[index].ladoE = players[player].hand[pos].ladoA;
    mesa[index].ladoD = players[player].hand[pos].ladoB;
    domino[posicaoOriginal].status = 'M';
    index++;
  } 
  
  removerPecaJogada(&players[player], pos);
  
  definirJogadorAtual();
}



//Fazer uma function para cada coisa do iniciar jogadores

// FunÃ§Ã£o para encontrar a maior peÃ§a cujo ambos os lados sÃ£o iguais na mÃ£o de cada jogador, retornando '1' caso esteja com o jogador 1, ou '2' caso esteja com o jogador 2'
int encontrarDupla(Player player[NUM_JOGADORES], Mesa mesa[28]){
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

int encontrarMaior(Player player[NUM_JOGADORES]){
	int i = 0;
	
    	for(int k = 12; k >= 0; k--){
        	if((player[0].hand[i].ladoA + player[0].hand[i].ladoB) == k){
          		jogarPeca(mesa, player, 0, i);
          		return 1;
        	}

        	if((player[1].hand[i].ladoA + player[1].hand[i].ladoB) == k){
          		jogarPeca(mesa, player, 1, i);
          		return 1;
        	}
      	}
    
    return -1;
}

int primeiroJogador(Player players[NUM_JOGADORES], Mesa mesa[28]) {

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

//Funcao para inciar a mesa como vazia
void iniciaMesa(Mesa mesa[28]){
   mesa[0].ladoE = -7;//-7 e uma sentinela 
   mesa[0].ladoD = -7;
}

// funcao para comprar cartas caso a peca tenha status '\0', retorn 1 se a peca for comprada e 0 se nao ha pecas para a compra
int buyCards(Carta totalPieces[NUM_PECAS], Player *player, int playerNum) {
      for (int k = 0; k < NUM_PECAS; k++) {
          if (totalPieces[k].status == '\0') {
                  player->hand[player->numPieces++] = totalPieces[k];
                  totalPieces[k].status = '1' + playerNum;
                  printf("\nCompra feita com sucesso\n");
                  return 1; // Compra feita
        	}
        }
        
      printf("Nao ha pecas para comprar");
      return 0; // Nao foi possivel fazer a compra
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
void definirProximoJogador() {
    jogadorAtual = (jogadorAtual + 1) % NUM_JOGADORES;
}

void jogarPecaNaMesa(Mesa mesa[28], Player players[NUM_JOGADORES], int pos) {
    int validadeJogada = checarJogadaValida(players, jogadorAtual, pos);

    if (validadeJogada == 1) {
        mesa[index].ladoE = players[jogadorAtual].hand[pos].ladoA;
        mesa[index].ladoD = players[jogadorAtual].hand[pos].ladoB;
        players[jogadorAtual].hand[pos].status = 'M';  // Marca a peça como jogada na mesa
        index++;
        removerPecaJogada(&players[jogadorAtual], pos);  // Remove a peça jogada da mão do jogador
        definirProximoJogador();  // Passa para o próximo jogador
    } else {
        printf("Jogada inválida! A peça [%d|%d] não combina com a mesa.\n", 
               players[jogadorAtual].hand[pos].ladoA, 
               players[jogadorAtual].hand[pos].ladoB);
    }
}

// Função para exibir o menu de escolhas do jogador durante o jogo
int menuJogador(Player players[NUM_JOGADORES], Carta domino[NUM_PECAS]) {
    int escolha;
    do {
        printf("\n--- Menu do Jogador %d ---\n", jogadorAtual + 1);
        printf("1. Escolher peça para jogar\n");
        printf("2. Comprar peça\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                int posicao;
                showHandPieces(players, NUM_JOGADORES);
                printf("Escolha a posição da peça que deseja jogar (1 a %d): ", players[jogadorAtual].numPieces);
                scanf("%d", &posicao);
                if (posicao > 0 && posicao <= players[jogadorAtual].numPieces) {
                    jogarPecaNaMesa(mesa, players, posicao - 1);
                    showTablePieces(mesa);
                } else {
                    printf("Posição inválida!\n");
                }
                break;
            }
            case 2:
                if (buyCards(domino, &players[jogadorAtual], jogadorAtual)) {
                showHandPieces(players, NUM_JOGADORES);
                }
                break;

            case 3:
                printf("Saindo do menu do jogador...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (escolha != 3);

    return 1;
}
// Função para exibir o menu principal
int menuPrincipal() {
    int opcao;
    printf("\n--- Menu Principal ---\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    srand(time(NULL));

    int opcao;
    do {
        opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
                criarCarta(domino);
                embaralharPecas(domino);
                iniciaMesa(mesa);
                
                int numPlayer = playerNumber(); // Variável para a chamada da função playerNumber()

                pieceGiveAway(domino, players, numPlayer);

                printf("\n");	
                showHandPieces(players, numPlayer);
                printf("\n");

                int firstPlayer = primeiroJogador(players, mesa); // faz passagem por referência
                jogadorAtual = firstPlayer - 1;
                printf("\n\nA partida começa com o jogador %d com a peça [%d|%d]\n", firstPlayer, mesa[0].ladoE, mesa[0].ladoD);
  
                showHandPieces(players, numPlayer);
                showTablePieces(mesa);

                while (menuJogador(players, domino)) {
                    // O loop continua até que o jogador decida sair
                }
                break;
            }
            case 2:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 2);

    return 0;
}

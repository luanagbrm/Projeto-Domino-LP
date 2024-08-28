/*
DOM-BGLL - Projeto Dominó - Etapa 3
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_Controller.h"



int numPlayer = playerNumber();
int carta;

void gerarSeed(){
  srand( (unsigned)time(0));
}

void definirJogadorAtual(){
	if(jogadorAtual == 0)
		jogadorAtual = 1;
	else
		jogadorAtual = 0;
}

void embaralharPecas(Carta domino[NUM_PECAS]){
  Carta peca2;
  int p;

  for(int i = 0; i < NUM_PECAS;i++){
    peca2 = domino[i];
    p = rand() % 28;
    domino[i] = domino[p];
    domino[p] = peca2; 
  }
}

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
  
  	if (myIndex == 0) { //A primeira jogada sempre será válida
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


int encontrarDupla(Player player[NUM_JOGADORES], Mesa mesa[28]){
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peÃ§a da maoo do jogador 1 e do jogador 2
    // buscando a peÃ§a cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((player[0].hand[i].ladoA == k) && (player[0].hand[i].ladoB == k)){
        jogarPeca(mesa, player, 0, i);
        return 1; // Encerra a busca no momento que encontra a maior peÃ§a dupla presente em ambas as mÃ£os
      }

      //Caso nao encontre a peÃ§a dupla na mao do jogador 1, a funÃ§Ã£o busca na mao do jogador 2

      if((player[1].hand[i].ladoA == k) && (player[1].hand[i].ladoB == k)){
        jogarPeca(mesa, player, 1, i);
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se nao encontrar nenhuma peÃ§a dupla na mao de ambos
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

void jogarPeca(Mesa mesa[28], Player players[NUM_JOGADORES], int player, int pos) {
  int validadeJogada = checarJogadaValida(players, player, pos);
  int posicaoOriginal =  players[player].hand[pos].pos;
  

  if(validadeJogada == 1 || mesa[myIndex].ladoD == -7 && mesa[myIndex].ladoE == -7){
	players[player].hand[pos].status = 'M'; //Altera o status da peÃ§a para 'M', indicando que ela foi jogada
    mesa[myIndex].ladoE = players[player].hand[pos].ladoA;
    mesa[myIndex].ladoD = players[player].hand[pos].ladoB;
    domino[posicaoOriginal].status = 'M';
    myIndex++;
  } 
  
  removerPecaJogada(&players[player], pos);
  
  definirJogadorAtual();
}

void definirProximoJogador() {
    jogadorAtual = (jogadorAtual + 1) % NUM_JOGADORES;
}

void jogarPecaNaMesa(Mesa mesa[28], Player players[NUM_JOGADORES], int pos) {
    int validadeJogada = checarJogadaValida(players, jogadorAtual, pos);

    if (validadeJogada == 1) {
        mesa[myIndex].ladoE = players[jogadorAtual].hand[pos].ladoA;
        mesa[myIndex].ladoD = players[jogadorAtual].hand[pos].ladoB;
        players[jogadorAtual].hand[pos].status = 'M';  // Marca a peça como jogada na mesa
        myIndex++;
        removerPecaJogada(&players[jogadorAtual], pos);  // Remove a peça jogada da mão do jogador
        definirProximoJogador();  // Passa para o próximo jogador
    } else {
        printf("Jogada inválida! A peça [%d|%d] não combina com a mesa.\n", 
               players[jogadorAtual].hand[pos].ladoA, 
               players[jogadorAtual].hand[pos].ladoB);
    }
}

void iniciaJogo() {
    srand(time(NULL));
    criarCarta(domino);
    embaralharPecas(domino);
    pieceGiveAway(domino, players, NUM_JOGADORES);
    iniciaMesa(mesa);
    primeiroJogador(players, mesa);

    int posicaoEscolhida = 0;
    int jogadaValida = 1;

    while (1) {
        showHandPieces(players, NUM_JOGADORES);
        showTablePieces(mesa);

        printf("\nJogador %d, escolha a posicao da sua peca (0 para comprar): ", jogadorAtual + 1);
        scanf("%d", &posicaoEscolhida);

        if (posicaoEscolhida == 0) {
            jogadaValida = buyCards(domino, &players[jogadorAtual], jogadorAtual);
            if (jogadaValida == 1) {
                continue;
            } else {
                break;
            }
        }

        if (posicaoEscolhida <= players[jogadorAtual].numPieces) {
            jogarPeca(mesa, players, jogadorAtual, posicaoEscolhida - 1);
        } else {
            printf("\nJogada invalida. Tente novamente.\n");
        }
    }
}
/*
DOM-BGLL - Projeto Domin� - Etapa 3
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri�dos�Santos
*/

#include "Dom_BGLL_Projeto_Controller.h"

int carta;

void gerarSeed(){
  srand( (unsigned)time(0));
}

void definirJogadorAtual(){
	jogadorAtual = (jogadorAtual + 1) % NUM_JOGADORES;
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

void distribuirPecas(Carta totalPieces[28], Jogador jogadores[NUM_JOGADORES], int numJogadores){

  int pieceAssign = 0;//acessa todas as pe�as uma por uma e distribui para um jogador

  for(int i = 0; i < numJogadores; i++){
    jogadores[i].numPieces = 0; // inicializa a quantidade de pe�as na m�o do usu�rio, iniciando a distribui��o sempre do �nicio do array

    for(int k = 0; k < HAND_PECAS_INICIAL  && pieceAssign < NUM_PECAS; k++){
      totalPieces[pieceAssign].status = '1' + i;
      jogadores[i].pecasMao[k] = totalPieces[pieceAssign++];
      jogadores[i].pecasMao[k].pos = pieceAssign - 1; //guarda dentro de cada pe�a na m�o do jogador a posi��o que ela ocupa no array principal do jogo
      jogadores[i].pecasMao[k].status = '1' + i;
      jogadores[i].numPieces++;
    }
  }
}

void removerPecaJogada(Jogador *jogador, int pos) {
    for (int i = pos; i < jogador->numPieces - 1; i++) { //recebe a posicao da peca que foi jogada
        jogador->pecasMao[i] = jogador->pecasMao[i + 1];//e diminui em 1 a posicao de todas as pecas que est�o a direita dela
    }
    
    jogador->numPieces--;
}

// Verifica se a pe�a jogada se encaixa em algumas das extremidades da mesa
int checarJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
  Carta pecaJogada = jogadores[jogador].pecasMao[pos];
  int ladoD = limitesMesa.ladoD;
  int ladoE = limitesMesa.ladoE;
  
  	if (index == 0) { //A primeira jogada sempre será válida
		limitesMesa.ladoE = pecaJogada.ladoA;
        limitesMesa.ladoD = pecaJogada.ladoB;
        return 1;
    }

	//Verifica se a peca pode ser jogada em algum dos lados da mesa
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

//Encontra a maior pe�a dupla que esteja na m�o de um dos jogadores
int encontrarDupla(Jogador jogador[NUM_JOGADORES], Mesa mesa[28]){
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peca da mao do jogador 1 e do jogador 2
    // buscando a peca cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((jogador[0].pecasMao[i].ladoA == k) && (jogador[0].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 0, i);
        return 1; // Encerra a busca no momento que encontra a maior peca dupla presente em ambas as m�os
      }

      //Caso nao encontre a peca dupla na mao do jogador 1, a fun��o busca na mao do jogador 2

      if((jogador[1].pecasMao[i].ladoA == k) && (jogador[1].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 1, i);
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se nao encontrar nenhuma peÃ§a dupla na mao de ambos
}

//Encontra a maior pe�a na m�o dos jogadores considerando a soma
int encontrarMaior(Jogador jogador[NUM_JOGADORES]){
	int maior = -1, jogadorPeca, pos;
    	for(int i = 0; i < 7; i++){
        	if((jogador[0].pecasMao[i].ladoA + jogador[0].pecasMao[i].ladoB) > maior){
          		maior = jogador[0].pecasMao[i].ladoA + jogador[0].pecasMao[i].ladoB;
          		jogadorPeca = 0;
          		pos = i;
        	}

        	if((jogador[1].pecasMao[i].ladoA + jogador[1].pecasMao[i].ladoB) > maior){
          		maior = jogador[1].pecasMao[i].ladoA + jogador[1].pecasMao[i].ladoB;
          		jogadorPeca = 1;
          		pos = i;
        	}
      	}
      	
      	jogarPeca(mesa, jogador, jogadorPeca, pos);
    
    return 1;
}

//Define qual jogador vai iniciar o jogo e j� joga a primeira pe�a
int primeiroJogador(Jogador jogadores[NUM_JOGADORES], Mesa mesa[28]) {

    int jogador1 = encontrarDupla(jogadores, mesa); //para buscar o primeiro jogador, inicialmente busca pela maior peca dupla


    if (jogador1 == -1) { //caso n�o haja peca dupla,
        jogador1 = encontrarMaior(jogadores); //busca pela peca com a maior soma
    }

    return jogador1;
}


int comprarCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum) {
      for (int k = 0; k < NUM_PECAS; k++) {
          if (totalPieces[k].status == '\0') { //busca por pe�as que n�o estejam nem na mesa e nem na m�o dos jogadores
                  jogador->pecasMao[jogador->numPieces++] = totalPieces[k]; //adiciona a pe�a dispon�vel ao fim da m�o do usu�rio
                  totalPieces[k].status = '1' + jogadorNum;
                  return 1; // Compra feita
                  
                  definirJogadorAtual();
        	}
        }
      return 0; // Nao foi possivel fazer a compra
}


int realizarCompraCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum){
	int status = comprarCartas(totalPieces, jogador, jogadorNum);
	
	statusCompra(status);
	
	return status;
}

void jogarPeca(Mesa mesa[28], Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
	int validadeJogada = checarJogadaValida(jogadores, jogador, pos); //Verifica se a jogada � v�lida
	int posicaoOriginal =  jogadores[jogador].pecasMao[pos].pos; // Guarda a posi��o da pe�a jogada dentro do array principal do jogo
	jogadorAtual = jogador;
  
  
	if(validadeJogada == 1 || mesa[index].ladoD == -7){
		jogadores[jogador].pecasMao[pos].status = 'M'; //Altera o status da peca para 'M' dentre as pecas na m�o do jogador, indicando que ela foi jogada
		domino[posicaoOriginal].status = 'M'; //Altera o status da peca para 'M' no array original
    	mesa[index].ladoE = jogadores[jogador].pecasMao[pos].ladoA;
    	mesa[index].ladoD = jogadores[jogador].pecasMao[pos].ladoB;
    	index++; //Incrementa a vari�vel de controle da mesa
    	removerPecaJogada(&jogadores[jogador], pos);
  		definirJogadorAtual();
	} 
	
}

int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]) {
    int escolha;
    do {
        escolha = menuPrincipalJogador();

        switch (escolha) {
            case 1: {
                int posicao;
                mostrarPecasJogador(jogadores, NUM_JOGADORES);
                posicao = receberPosicaoPeca();
                if (posicao > 0 && posicao <= jogadores[jogadorAtual].numPieces) {
                    jogarPeca(mesa, jogadores, jogadorAtual, posicao - 1);
                    mostrarPecasMesa(mesa);
                } else {
                    interacoesMenu(escolha);
                }
                break;
            }
            case 2:
                if (realizarCompraCartas(domino, &jogadores[jogadorAtual], jogadorAtual)) {
                	mostrarPecasJogador(jogadores, NUM_JOGADORES);
                }
                break;

            case 3:
                jogar(); // Encerra o programa;
            default:
                interacoesMenu(escolha);
                break;
        }
    } while (escolha != 3);

    return 1;
}

void jogar(){
	int opcao;
	index = 0; //a cada novo jogo, inicia a mesa da primeira posi��o
	gerarSeed();
	
	do {
        opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
                criarCarta(domino);
                embaralharPecas(domino);
                iniciaMesa(mesa);
                
                int numJogadores = numeroJogadores(); // define o n�mero de jogadores de acordo com o informado pelo usu�rio

                distribuirPecas(domino, jogadores, numJogadores);

                mostrarPecasJogador(jogadores, numJogadores);

                int firstPlayer = primeiroJogador(jogadores, mesa); // faz passagem por refer�ncia
  
                mostrarPecasJogador(jogadores, numJogadores);
                mostrarPecasMesa(mesa);

                while (menuJogador(jogadores, domino)) {
                    // O loop continua at� que o jogador decida sair
                }
                break;
            }
            case 2:
                interacoesMenu(opcao);
                exit(0);
            default:
            	interacoesMenu(opcao);
                
        }
    } while (opcao != 2);
}
/*
DOM-BGLL - Projeto Domino - Etapa 4
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_Controller.h"

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

  int pieceAssign = 0;//acessa todas as peÃ§as uma por uma e distribui para um jogador

  for(int i = 0; i < numJogadores; i++){
    jogadores[i].numPieces = 0; // inicializa a quantidade de peÃ§as na mÃ£o do usuÃ¡rio, iniciando a distribuiÃ§Ã£o sempre do Ã­nicio do array

    for(int k = 0; k < HAND_PECAS_INICIAL  && pieceAssign < NUM_PECAS; k++){
      totalPieces[pieceAssign].status = '1' + i;
      jogadores[i].pecasMao[k] = totalPieces[pieceAssign++];
      jogadores[i].pecasMao[k].pos = pieceAssign - 1; //guarda dentro de cada peça na mão do jogador a posição que ela ocupa no array principal do jogo
      jogadores[i].pecasMao[k].status = '1' + i;
      jogadores[i].numPieces++;
      qtdPecasDisponivel--;
    }
  }
}

void removerPecaJogada(Jogador *jogador, int pos) {
    for (int i = pos; i < jogador->numPieces - 1; i++) { //recebe a posicao da peca que foi jogada
        jogador->pecasMao[i] = jogador->pecasMao[i + 1];//e diminui em 1 a posicao de todas as pecas que estÃ£o a direita dela
    }
    
    jogador->numPieces--;
}

void jogarLadoEsquerdo(Mesa mesa[], Jogador jogadores[NUM_JOGADORES], int pos) {
    for (int i = qtdPecasMesa; i >= 0; i--) { //recebe a posicao da peca que foi jogada
        mesa[i+1] = mesa[i];//e diminui em 1 a posicao de todas as pecas que estÃ£o a direita dela
    }
}

// Verifica se a peÃ§a jogada se encaixa em algumas das extremidades da mesa
int qtdJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
   Carta pecaJogada = jogadores[jogador].pecasMao[pos];
   int ladoD = limitesMesa.ladoD;
   int ladoE = limitesMesa.ladoE;
   int controle = 0;
  

	//Verifica quantas possibilidades de jogada uma peça pode oferecer ao jogador
  	if(pecaJogada.ladoA == ladoD)
    	controle++;
  	if(pecaJogada.ladoB == ladoD)
    	controle++;
	if(pecaJogada.ladoA == ladoE)
    	controle++;
  	if(pecaJogada.ladoB == ladoE)
    	controle++;
    	
    if(pecaJogada.ladoA == pecaJogada.ladoB)
    	controle = controle/2; //Como os dois lados são identicos, não há necessidade de comparar se ambos os lados da peça podem ser jogados em ambos os lados da mesa 
  	
  	return controle;
	
}

int checarUnicaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
  Carta pecaJogada = jogadores[jogador].pecasMao[pos];
  int ladoD = limitesMesa.ladoD;
  int ladoE = limitesMesa.ladoE;

	//Considerando que ao chegar nessa função temos apenas uma jogada possível,
	//encontra qual é essa jogada e a realiza
  	if(pecaJogada.ladoA == ladoD){
    	limitesMesa.ladoD = pecaJogada.ladoB;
    	jogarPeca(mesa,jogadores,jogador,pos,'D');
    	return 1;
  	} else if(pecaJogada.ladoB == ladoD){
    	limitesMesa.ladoD = pecaJogada.ladoA;
    	inverterPeca(jogadores, jogador, pos);
    	jogarPeca(mesa,jogadores, jogador, pos, 'D');
    	return 1;
	} else if(pecaJogada.ladoA == ladoE){
    	limitesMesa.ladoE = pecaJogada.ladoB;
    	inverterPeca(jogadores, jogador, pos);
    	jogarPeca(mesa, jogadores, jogador, pos,'E');
    	return 1;
  	} else if(pecaJogada.ladoB == ladoE){
    	limitesMesa.ladoE = pecaJogada.ladoA;
    	jogarPeca(mesa, jogadores, jogador, pos, 'E');
    	return 1;
  	} 

  return -1;

}

int checarLadoValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos, char lado) {
  	Carta pecaJogada = jogadores[jogador].pecasMao[pos];
  	int ladoD = limitesMesa.ladoD;
  	int ladoE = limitesMesa.ladoE;
  
  	//Verifica qual lado da peça condiz com a extremidade escolhida pelo jogador
  	if(lado == 'D'){
	  	if(pecaJogada.ladoA == ladoD){
	    	limitesMesa.ladoD = pecaJogada.ladoB;
	    	jogarPeca(mesa,jogadores,jogador,pos,'D');
	    	return 1;
	  	} else if(pecaJogada.ladoB == ladoD){
	    	limitesMesa.ladoD = pecaJogada.ladoA;
	    	inverterPeca(jogadores, jogador, pos);
	    	jogarPeca(mesa,jogadores, jogador, pos, 'D');
	    	return 1;
		} else {
			return -1;
		}
  	}
  
  	if(lado == 'E'){
	  	if(pecaJogada.ladoA == ladoE){
	    	limitesMesa.ladoE = pecaJogada.ladoB;
	    	inverterPeca(jogadores, jogador, pos);
	    	jogarPeca(mesa, jogadores, jogador, pos,'E');
	    	return 1;
	  	} else if(pecaJogada.ladoB == ladoE){
	    	limitesMesa.ladoE = pecaJogada.ladoA;
	    	jogarPeca(mesa, jogadores, jogador, pos, 'E');
	    	return 1;
	  	} else {
	  		return -1;	
	}
  }
  
  return -1;

}

int verificarJogada(Mesa mesa[], Jogador jogadores[NUM_JOGADORES], int jogador, int pos){
	int qtdValidas = qtdJogadaValida(jogadores, jogador, pos);
	
	if(qtdValidas == 0){
		return -1; //Não há possibilidade de qualquer jogada valida
	}
		
	if(qtdValidas == 1){
		checarUnicaValida(jogadores, jogadorAtual, pos); //Há apenas uma jogada válida, logo, o jogo há fará automaticamente
		return 0;
	}
	
	
	if(qtdValidas > 1){ //Há mais de uma jogada possível, então a extremidade a ser jogada será definida pelo jogador
		fclearBuffer();
		char lado = receberLadoJogada();
		if(checarLadoValida(jogadores, jogadorAtual, pos, lado) == -1){
			menuPrincipalJogador();
			return -1;
		}
		return 1;
	}
	
	return -1;
}

//Encontra a maior peça dupla que esteja na mão de um dos jogadores
int encontrarDupla(Jogador jogador[NUM_JOGADORES], Mesa mesa[28]){
  char lado = 'D';
	
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peca da mao do jogador 1 e do jogador 2
    // buscando a peca cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((jogador[0].pecasMao[i].ladoA == k) && (jogador[0].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 0, i, lado);
        return 1; // Encerra a busca no momento que encontra a maior peca dupla presente em ambas as mÃ£os
      }

      //Caso nao encontre a peca dupla na mao do jogador 1, a função busca na mao do jogador 2

      if((jogador[1].pecasMao[i].ladoA == k) && (jogador[1].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 1, i, lado);
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se nao encontrar nenhuma peça dupla na mao de ambos
}

//Encontra a maior peÃ§a na mÃ£o dos jogadores considerando a soma
int encontrarMaior(Jogador jogador[NUM_JOGADORES]){
	char lado = 'D';
	
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
      	
      	jogarPeca(mesa, jogador, jogadorPeca, pos, lado);
    
    return 1;
}

//Define qual jogador vai iniciar o jogo e jÃ¡ joga a primeira peÃ§a
int primeiroJogador(Jogador jogadores[NUM_JOGADORES], Mesa mesa[28]) {

    int jogador1 = encontrarDupla(jogadores, mesa); //para buscar o primeiro jogador, inicialmente busca pela maior peca dupla


    if (jogador1 == -1) { //caso nÃ£o haja peca dupla,
        jogador1 = encontrarMaior(jogadores); //busca pela peca com a maior soma
    }

    return jogador1;
}


int comprarCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum) {
      for (int k = 0; k < NUM_PECAS; k++) {
          if (totalPieces[k].status == '\0') { //busca por peÃ§as que nÃ£o estejam nem na mesa e nem na mÃ£o dos jogadores
                  jogador->pecasMao[jogador->numPieces++] = totalPieces[k]; //adiciona a peÃ§a disponÃ­vel ao fim da mÃ£o do usuÃ¡rio
                  totalPieces[k].status = '1' + jogadorNum;
                  qtdPecasDisponivel--;
                  return 1; // Compra feita
        	}
        }
      return 0; // Nao foi possivel fazer a compra
}

int verificarPassarVez(){
	if(qtdPecasDisponivel == 0){
		definirJogadorAtual();
		//menuPrincipalJogador();
		return 1;
	} else {
		return -1;
	}
}

void passarVez(){
	int disponibilidadePecas = verificarPassarVez();
	
	exibirMensagemPassarVez(disponibilidadePecas);
}

int verificarMaoVazia(){
	if(jogadores[0].numPieces == 0)
		return 1;
	else if(jogadores[1].numPieces == 0)
		return 2;
	return -1;
}

//Verifica se algum dos dois jogadores possuem alguma peça que possa ser jogada no tabuleiro
int verificarJogoFechado(){
	if(qtdPecasDisponivel == 0){
		for(int i = 0; i < jogadores[0].numPieces; i++){
			if(jogadores[0].pecasMao[i].ladoA == limitesMesa.ladoD || jogadores[0].pecasMao[i].ladoB == limitesMesa.ladoD
				|| jogadores[0].pecasMao[i].ladoA == limitesMesa.ladoE || jogadores[0].pecasMao[i].ladoB == limitesMesa.ladoE){
					return 1;
			}
		}
		
		for(int i = 0; i < jogadores[1].numPieces; i++){
			if(jogadores[1].pecasMao[i].ladoA == limitesMesa.ladoD || jogadores[1].pecasMao[i].ladoB == limitesMesa.ladoD
				|| jogadores[1].pecasMao[i].ladoA == limitesMesa.ladoE || jogadores[1].pecasMao[i].ladoB == limitesMesa.ladoE){
					return 1;
			}
		}
	}
	
	return 0;
}

int verificarVencedorJogoFechado(){
	if(verificarJogoFechado == 0){
		if(jogadores[0].numPieces > jogadores[1].numPieces)
			return 2;
		else if (jogadores[1].numPieces > jogadores[0].numPieces)
			return 1;
		else 
			return somarValorPecas();
	}
	
	return -1;
}

int somarValorPecas(){
	int pecasJogador1 = 0;
	int pecasJogador2 = 0;
	
	for(int i = 0; i < jogadores[0].numPieces; i++)
			pecasJogador1 += (jogadores[0].pecasMao[i].ladoA + jogadores[0].pecasMao[i].ladoB);
		
	for(int i = 0; i < jogadores[1].numPieces; i++)
		pecasJogador2 += (jogadores[1].pecasMao[i].ladoA + jogadores[1].pecasMao[i].ladoB);
		
	if(pecasJogador1 > pecasJogador2)
		return 2;
	return 1;
		
}

void verificarOpcaoUsuario(int opcao){
	if(opcao == 0)
		jogar();
	else if(opcao == 1)
		exit(0);
}

void definirVencedor(){
	if(verificarMaoVazia() != -1){
		exibirMensagemVencedor(verificarMaoVazia());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
	}
	
	if(verificarVencedorJogoFechado() != -1){
		exibirMensagemVencedor(verificarVencedorJogoFechado());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
	}
		
}




int realizarCompraCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum){
	int status = comprarCartas(totalPieces, jogador, jogadorNum);
	
	statusCompra(status);
	
	return status;
}

void jogarPeca(Mesa mesa[28], Jogador jogadores[NUM_JOGADORES], int jogador, int pos, char lado) {
	int posicaoOriginal =  jogadores[jogador].pecasMao[pos].pos; // Guarda a posiÃ§Ã£o da peÃ§a jogada dentro do array principal do jogo
	int posicaoJogada = 0;
	jogadorAtual = jogador;
	
	if(lado == 'D')
		posicaoJogada = qtdPecasMesa;
	else
		jogarLadoEsquerdo(mesa, jogadores, pos);
		
	jogadores[jogador].pecasMao[pos].status = 'M'; //Altera o status da peca para 'M' dentre as pecas na mÃ£o do jogador, indicando que ela foi jogada
	domino[posicaoOriginal].status = 'M'; //Altera o status da peca para 'M' no array original
	mesa[posicaoJogada].ladoE = jogadores[jogador].pecasMao[pos].ladoA;
	mesa[posicaoJogada].ladoD = jogadores[jogador].pecasMao[pos].ladoB;
	qtdPecasMesa++; //Incrementa a variÃ¡vel de controle da mesa
	removerPecaJogada(&jogadores[jogador], pos);
	definirJogadorAtual();
	
	if(qtdPecasMesa == 1){
		limitesMesa.ladoD = mesa[posicaoJogada].ladoE;
		limitesMesa.ladoE = mesa[posicaoJogada].ladoD;
	}
	
	definirVencedor();
	limparTela();
}

void fclearBuffer() 
{ 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inverterPeca(Jogador jogadores[NUM_JOGADORES], int numJogador, int pos){
  int p;
  p = jogadores[numJogador].pecasMao[pos].ladoA;
  jogadores[numJogador].pecasMao[pos].ladoA = jogadores[numJogador].pecasMao[pos].ladoB;
  jogadores[numJogador].pecasMao[pos].ladoB = p;
}

int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]) {
    int escolha;
    
    do {
        escolha = menuPrincipalJogador();

        switch (escolha) {
            case 1: {
            	int posicao;
                
                posicao = receberPosicaoPeca();
	            if (posicao > 0 && posicao <= jogadores[jogadorAtual].numPieces) {
	                verificarJogada(mesa, jogadores, jogadorAtual, posicao-1);
	            } else {
	                interacoesMenu(escolha);
	            }
	                break;
            }
            case 2:
                realizarCompraCartas(domino, &jogadores[jogadorAtual], jogadorAtual);
                break;

            case 3:
                passarVez(); 
				break;   
				
			case 4:
				
				mostrarRegras(opcao);
				break;
            case 0:
            	jogar();
            default:
                interacoesMenu(escolha);
                break;
        }
    } while (escolha != 3);

    return 1;
}

void jogar(){
	int opcao;
	qtdPecasMesa = 0; //a cada novo jogo, inicia a mesa da primeira posiÃ§Ã£o
	gerarSeed();
	
	do {
        opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
                criarCarta(domino);
                embaralharPecas(domino);
                iniciaMesa(mesa);
                
                int numJogadores = numeroJogadores(); // define o nÃºmero de jogadores de acordo com o informado pelo usuÃ¡rio

                distribuirPecas(domino, jogadores, numJogadores);

                int firstPlayer = primeiroJogador(jogadores, mesa); // faz passagem por referÃªncia

                while (menuJogador(jogadores, domino)) {
                    // O loop continua atÃ© que o jogador decida sair
                }
                break;
            }
             case 2:
            	mostrarRegras(opcao);
            	break;
            case 3:
                interacoesMenu(opcao);
                exit(0);
            default:
            	interacoesMenu(opcao);
                
        }
    } while (opcao != 3);
}

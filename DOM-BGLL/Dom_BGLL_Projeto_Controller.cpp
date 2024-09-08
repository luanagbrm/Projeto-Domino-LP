/*
DOM-BGLL - Projeto Domino - Etapa 5
10/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_Controller.h"

FILE *arqmesa;
FILE *pecas;
FILE *sitJogoSalvo;
FILE *dataHoraSalvo;

//FUNCOES INICIAIS PARA ANTES DO INICIO DA PRIMEIRA JOGADA

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

  int pieceAssign = 0;//acessa todas as pecas uma por uma e distribui para um jogador

  for(int i = 0; i < numJogadores; i++){
    jogadores[i].numPieces = 0; // inicializa a quantidade de pecas na mao do usuario, iniciando a distribuicao sempre do inicio do array

    for(int k = 0; k < HAND_PECAS_INICIAL  && pieceAssign < NUM_PECAS; k++){
      totalPieces[pieceAssign].status = '1' + i;
      jogadores[i].pecasMao[k] = totalPieces[pieceAssign++];
      jogadores[i].pecasMao[k].pos = pieceAssign - 1; //guarda dentro de cada peca na mao do jogador a posicao que ela ocupa no array principal do jogo
      jogadores[i].pecasMao[k].status = '1' + i;
      jogadores[i].numPieces++;
      qtdPecasDisponivel--;
    }
  }
}

//FUNCIONALIDADES PARA VERIFICACOES 

// Verifica se a peca jogada se encaixa em algumas das extremidades da mesa
int qtdJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
   Carta pecaJogada = jogadores[jogador].pecasMao[pos];
   int ladoD = limitesMesa.ladoD;
   int ladoE = limitesMesa.ladoE;
   int controle = 0;
  

	//Verifica quantas possibilidades de jogada uma peca pode oferecer ao jogador
  	if(pecaJogada.ladoA == ladoD)
    	controle++;
  	if(pecaJogada.ladoB == ladoD)
    	controle++;
	if(pecaJogada.ladoA == ladoE)
    	controle++;
  	if(pecaJogada.ladoB == ladoE)
    	controle++;
    	
    if(pecaJogada.ladoA == pecaJogada.ladoB)
    	controle = controle/2; //Como os dois lados sao identicos, nao ha necessidade de comparar se ambos os lados da peca podem ser jogados em ambos os lados da mesa 
  	
  	return controle;
	
}

int checarUnicaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
  Carta pecaJogada = jogadores[jogador].pecasMao[pos];
  int ladoD = limitesMesa.ladoD;
  int ladoE = limitesMesa.ladoE;

	//Considerando que ao chegar nessa funcao temos apenas uma jogada possil,
	//encontra qual e' essa jogada e a realiza
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
  
  	//Verifica qual lado da peca condiz com a extremidade escolhida pelo jogador
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
		exibirMensagemJogada(qtdValidas);
		return -1; //Nao ha possibilidade de qualquer jogada valida
	}
		
	if(qtdValidas == 1){
		checarUnicaValida(jogadores, jogadorAtual, pos); //Ha apenas uma jogada valida, logo, o jogo ha fara' automaticamente
		exibirMensagemJogada(qtdValidas);
		return 0;
	}
	
	
	if(qtdValidas > 1){ //ha mais de uma jogada possivel, entao a extremidade a ser jogada sera definida pelo jogador
		fclearBuffer();
		char lado = receberLadoJogada();
		if(checarLadoValida(jogadores, jogadorAtual, pos, lado) == -1){
			exibirMensagemJogada(0);
			menuPrincipalJogador();
			return -1;
		}
		exibirMensagemJogada(qtdValidas);
		return 1;
	}
	
	exibirMensagemJogada(-1);
	return -1;
}

//Encontra a maior peca dupla que esteja na mao de um dos jogadores
int encontrarDupla(Jogador jogador[NUM_JOGADORES], Mesa mesa[28]){
  char lado = 'D';
	
  for(int k = 6; k >= 0; k--){ 
    // Verifica simultaneamente cada peca da mao do jogador 1 e do jogador 2
    // buscando a peca cujo ambos os lados tem valor igual a k
    for(int i = 0; i < 7; i++){ 
      if((jogador[0].pecasMao[i].ladoA == k) && (jogador[0].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 0, i, lado);
        return 1; // Encerra a busca no momento que encontra a maior peca dupla presente em ambas as maos
      }

      //Caso nao encontre a peca dupla na mao do jogador 1, a funcao busca na mao do jogador 2

      if((jogador[1].pecasMao[i].ladoA == k) && (jogador[1].pecasMao[i].ladoB == k)){
        jogarPeca(mesa, jogador, 1, i, lado);
        return 2;
      }
    }
  }

  return -1; // Retorna -1 se nao encontrar nenhuma peca dupla na mao de ambos
}

//Encontra a maior peca na mao dos jogadores considerando a soma
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

//Define qual jogador vai iniciar o jogo e ja joga a primeira peca
int primeiroJogador(Jogador jogadores[NUM_JOGADORES], Mesa mesa[28]) {

    int jogador1 = encontrarDupla(jogadores, mesa); //para buscar o primeiro jogador, inicialmente busca pela maior peca dupla


    if (jogador1 == -1) { //caso nao haja peca dupla,
        jogador1 = encontrarMaior(jogadores); //busca pela peca com a maior soma
    }

    return jogador1;
}

//FUNCIONALIDADES PARA PASSAR A VEZ

int verificarPassarVez(){
	if(qtdPecasDisponivel <= 0){
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

//FUNCIONALIDADES PARA VERIFICAR SE O JOGO TERMINOU

//Verifica se a mao de algum dos jogadores esta sem pecas
int verificarMaoVazia(){
	if(jogadores[0].numPieces == 0)
		return 1;
	else if(jogadores[1].numPieces == 0)
		return 2;
	return -1;
}

//Verifica se algum dos dois jogadores possuem alguma peca que possa ser jogada no tabuleiro
int verificarJogoFechado(){
	if(qtdPecasDisponivel <= 0){
		for(int i = 0; i < jogadores[0].numPieces; i++){
			if(jogadores[0].pecasMao[i].ladoA == limitesMesa.ladoD || jogadores[0].pecasMao[i].ladoB == limitesMesa.ladoD
				|| jogadores[0].pecasMao[i].ladoA == limitesMesa.ladoE || jogadores[0].pecasMao[i].ladoB == limitesMesa.ladoE){
					return 1; //Se encontrar alguma peca na mao do jogador que possa ser jogada no tabuleiro, indica que ainda existe jogadas possiveis
			}
		}
		
		for(int i = 0; i < jogadores[1].numPieces; i++){
			if(jogadores[1].pecasMao[i].ladoA == limitesMesa.ladoD || jogadores[1].pecasMao[i].ladoB == limitesMesa.ladoD
				|| jogadores[1].pecasMao[i].ladoA == limitesMesa.ladoE || jogadores[1].pecasMao[i].ladoB == limitesMesa.ladoE){
					return 1;
			}
		}
	} else {
		return 1; //Ha mais do que 0 pecas disponiveis
	}
	
	return 0; //Se nao encontrar nenhuma jogada valida na mao de ambos os jogadores, indica que o jogo esta' fechado
}

int verificarVencedorJogoFechado(){
	if(verificarJogoFechado() == 0){
		if(jogadores[0].numPieces > jogadores[1].numPieces)
			return 2; //Primeiro verifica a quantidade de pecas de cada jogador
		else if (jogadores[1].numPieces > jogadores[0].numPieces)
			return 1;
		else 
			return somarValorPecas(); //Caso a quantidade de pecas for identica, faz a soma dos lados de todas as pecas na mao do jogador
	}
	
	return -1;
}

//Soma o valor de ambos os lados de cada peca para todas pecas
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
	if(verificarMaoVazia() != -1){ //Primeiro, verifica se algum dos jogadores nao tem pecas na mao
		exibirMensagemVencedor(verificarMaoVazia());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
		return;
	}
	
	//Caso ainda tenha, verifica se o jogo esta' fechado
	if(verificarVencedorJogoFechado() != -1){
		exibirMensagemVencedor(verificarVencedorJogoFechado());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
		return;
	}
		
}

//FUNCIONALIDADES PARA COMPRA DAS PECAS

int comprarCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum) {
	if(qtdPecasDisponivel > 0){
      for (int k = 0; k < NUM_PECAS; k++) {
          	if (totalPieces[k].status == '\0') { //busca por pecas que nao estejam nem na mesa e nem na mao dos jogadores
                  jogador->pecasMao[jogador->numPieces++] = totalPieces[k]; //adiciona a peca disponivel ao fim da mao do usuario
                  totalPieces[k].status = '1' + jogadorNum;
				  qtdPecasDisponivel--;
                  return 1; // Compra feita
        	}
        }
    }
    	printf("%d",qtdPecasDisponivel);
      	return 0; // Nao foi possivel fazer a compra
}

int realizarCompraCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum){
	int status = comprarCartas(totalPieces, jogador, jogadorNum);
	
	statusCompra(status);
	
	return status;
}

//FUNCIONALIDADES PARA JOGADAS

void jogarLadoEsquerdo(Mesa mesa[], Jogador jogadores[NUM_JOGADORES], int pos) {
    for (int i = qtdPecasMesa; i >= 0; i--) { //recebe a posicao da peca que foi jogada
        mesa[i+1] = mesa[i];//e diminui em 1 a posicao de todas as pecas que estao a direita dela
    }
}

void inverterPeca(Jogador jogadores[NUM_JOGADORES], int numJogador, int pos){
  int p;
  p = jogadores[numJogador].pecasMao[pos].ladoA;
  jogadores[numJogador].pecasMao[pos].ladoA = jogadores[numJogador].pecasMao[pos].ladoB;
  jogadores[numJogador].pecasMao[pos].ladoB = p;
}

void jogarPeca(Mesa mesa[28], Jogador jogadores[NUM_JOGADORES], int jogador, int pos, char lado) {
	int posicaoOriginal =  jogadores[jogador].pecasMao[pos].pos; // Guarda a posicao da peca jogada dentro do array principal do jogo
	int posicaoJogada = 0;
	jogadorAtual = jogador;
	
	if(lado == 'D')
		posicaoJogada = qtdPecasMesa;
	else
		jogarLadoEsquerdo(mesa, jogadores, pos);
		
	jogadores[jogador].pecasMao[pos].status = 'M'; //Altera o status da peca para 'M' dentre as pecas na mao do jogador, indicando que ela foi jogada
	domino[posicaoOriginal].status = 'M'; //Altera o status da peca para 'M' no array original
	mesa[posicaoJogada].ladoE = jogadores[jogador].pecasMao[pos].ladoA;
	mesa[posicaoJogada].ladoD = jogadores[jogador].pecasMao[pos].ladoB;
	qtdPecasMesa++; //Incrementa a variavel de controle da mesa
	removerPecaJogada(&jogadores[jogador], pos);
	definirJogadorAtual();
	
	if(qtdPecasMesa == 1){
		limitesMesa.ladoD = mesa[posicaoJogada].ladoE;
		limitesMesa.ladoE = mesa[posicaoJogada].ladoD;
	}
	
	definirVencedor();
	limparTela();
}

void removerPecaJogada(Jogador *jogador, int pos) {
	
    for (int i = pos; i < jogador->numPieces - 1; i++) { //recebe a posicao da peca que foi jogada
        jogador->pecasMao[i] = jogador->pecasMao[i + 1];//e diminui em 1 a posicao de todas as pecas que estao a direita dela
    }
    
    jogador->numPieces--;
}

//FUNCIONALIDADES PARA SALVAR E RECUPERAR DADOS DO JOGO

int armazenarDataHora(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	dataSalvo.ano = tm.tm_year + 1900;
	dataSalvo.mes = tm.tm_mon + 1;
	dataSalvo.dia = tm.tm_mday;
	dataSalvo.hora = tm.tm_hour;
	dataSalvo.minutos = tm.tm_min;
	
	return 0;
}

int salvarPecas(){
	int i;
	
    if((pecas = fopen("CAD_DOMINO", "wb")) == NULL){
    	return -1;
	}
	
	for(i = 0; i < 28; i++){
		if(fwrite(&domino[i], sizeof(Carta), 1, pecas) != 1){
			return -1;
		}
	}
	
	fclose(pecas);
	return 0;
}

int salvarMesa(){
	int i;
	
	if((arqmesa = fopen("CAD_MESA", "wb")) == NULL){
    	return -2;
	}
	
	for(i = 0; i < 28; i++){
		if(fwrite(&mesa[i], sizeof(Mesa), 1, arqmesa) != 1){
			return -1;
		}
	}
	
	fclose(arqmesa);
	return 0;
}


int salvarSitJogo(){
	sitSalva.jogadorComp = 0;
    sitSalva.jogadorJogo = jogadorAtual;
    sitSalva.mesaDJogo = limitesMesa.ladoD;
    sitSalva.mesaEJogo = limitesMesa.ladoE;
    sitSalva.qtdPecasMesa = qtdPecasMesa;
    sitSalva.qtdPecasDisponivel = qtdPecasDisponivel;
    
	
	if((sitJogoSalvo = fopen("CAD_SIT", "wb")) == NULL){
    	return -2;
	}
	
	if(fwrite(&sitSalva, sizeof(sitJogo), 1, sitJogoSalvo) != 1){
		return -1;
	}
	
	fclose(sitJogoSalvo);
	return 0;
}

int salvarDataHora(){
	armazenarDataHora();
    
	
	if((dataHoraSalvo = fopen("CAD_DH", "wb")) == NULL){
    	return -2;
	}
	
	if(fwrite(&dataSalvo, sizeof(dataHora), 1, dataHoraSalvo) != 1){
		return -1;
	}
	
	fclose(dataHoraSalvo);
	return 0;
}



int salvarJogo() {
    if (salvarPecas() != 0 || salvarMesa() != 0 || salvarSitJogo() != 0 || salvarDataHora() != 0) {
        printf("Erro ao salvar o jogo.\n");
        return -1;
    }
    
    printf("Jogo salvo com sucesso.\n");
    return 0;
}

 int recuperarJogoPecas(){	
 
 	int i;
	
    if((pecas = fopen("CAD_DOMINO", "rb")) == NULL){
    	return -2;
	}
	
	for (i = 0; i < 28; i++) {
        size_t result = fread(&domino[i], sizeof(Carta), 1, pecas);
        if (result != 1) {
            fclose(pecas);
            return -1;
        }
    }
	
	fclose(pecas);
	return 0;
 }
 
int recuperarJogoMesa(){
    int i;

    if ((arqmesa = fopen("CAD_MESA", "rb")) == NULL) {
        return -2;
    }
    

    for (i = 0; i < 28; i++) {
        if (fread(&mesa[i], sizeof(Mesa), 1, arqmesa) != 1) {
            fclose(arqmesa);
            return -1;
        }
    }
	
    fclose(arqmesa);
    return 0;
}

int recuperarSitJogo(){  
    if ((sitJogoSalvo = fopen("CAD_SIT", "rb")) == NULL) {
        return -2;
    }
    
    if (fread(&sitSalva, sizeof(sitJogo), 1, sitJogoSalvo) != 1) {
        fclose(sitJogoSalvo);
        return -1;
    }
    
    // Close the file after reading
    fclose(sitJogoSalvo);
	return 0;
}

int recuperarDataHora(){
	dataHoraSalvo = fopen("CAD_DH", "rb");
    if (dataHoraSalvo == NULL) {
        return -1;
    }

    size_t read = fread(&dataSalvo, sizeof(dataHora), 1, dataHoraSalvo);
    if (read != 1) {
        fclose(dataHoraSalvo);
        return -1;
    }
	
    fclose(dataHoraSalvo);

    return 0;
}

int definirDataHora(){
	ano = dataSalvo.ano;
	mes = dataSalvo.mes;
	dia = dataSalvo.dia;
	hora = dataSalvo.hora;
	minutos = dataSalvo.minutos;
	
	return 0;
}

int definirPecasCadaJogador(Carta domino[28]){
	int pecasJ1 = 0;
	int pecasJ2 = 0;
	
	for(int i = 0; i < 28; i++){
		if(domino[i].status == '1'){
			jogadores[0].pecasMao[pecasJ1] = domino[i];
			pecasJ1++;
		}
		
		else if(domino[i].status == '2'){
			jogadores[1].pecasMao[pecasJ2] = domino[i];
			pecasJ2++;
		}
			
	}
	
	jogadores[0].numPieces = pecasJ1;
	jogadores[1].numPieces = pecasJ2;
    
	return 0;
}

int definirSitVariaveis(){
	jogadorAtual = sitSalva.jogadorJogo;
	qtdPecasMesa = sitSalva.qtdPecasMesa;
	qtdPecasDisponivel = sitSalva.qtdPecasDisponivel;
	limitesMesa.ladoD = sitSalva.mesaDJogo;
	limitesMesa.ladoE = sitSalva.mesaEJogo;
	modoJogo = sitSalva.jogadorComp;
    
	return 0;
}

int recuperarJogo(){
	if (recuperarJogoPecas() != 0 || recuperarJogoMesa() != 0 || recuperarSitJogo() != 0) {
        printf("Erro ao recuperar o jogo.\n");
        return -1;
    }
    
    printf("Jogo recuperado com sucesso.\n");
    return 0;
}

int continuarJogo() {
    if (recuperarJogo() != 0) {
        printf("Erro ao recuperar o jogo.\n");
        menuJogador(jogadores,domino);
        return -1; // Indica que houve um erro ao recuperar o jogo
    }
	
	jogoSalvo();
    return 0;
}

//MENU DO JOGADOR E INICIALIZACAO DO JOGO APARTIR DO MENU PRINCIPAL

int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]) {
    int escolha;
    
    do {
        escolha = menuPrincipalJogador();

        switch (escolha) {
            case 1: {
            	int posicao;
                
                posicao = receberPosicaoPeca();
                
	            if (posicao == -1) {
			        break;
			    } else if (posicao > 0 && posicao <= jogadores[jogadorAtual].numPieces) {
			        verificarJogada(mesa, jogadores, jogadorAtual, posicao - 1);
			    } else {
			        interacoesMenu(posicao);
			    }
			    
			    break;
            }
            case 2:
                realizarCompraCartas(domino, &jogadores[jogadorAtual], jogadorAtual);
                break;

            case 3:
                passarVez(); 
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

int novoJogo(){
	qtdPecasMesa = 0; //a cada novo jogo, inicia a mesa da primeira posicao
	qtdPecasDisponivel = NUM_PECAS; 
	
	criarCarta(domino);
    embaralharPecas(domino);
    iniciaMesa(mesa);
     
	int numJogadores = numeroJogadores(); // define o numero de jogadores de acordo com o informado pelo usuario
    
	distribuirPecas(domino, jogadores, numJogadores);

    int firstPlayer = primeiroJogador(jogadores, mesa); // faz passagem por referencia

    while (menuJogador(jogadores, domino)) {
      // O loop continua ate que o jogador decida sair
    }
    
	return 0;
}

void vezDoPc(Jogador jogadores[NUM_JOGADORES], int jogador) {
	
    int donePlay = -1;  // Inicializa como -1 para indicar que nenhuma jogada foi feita ainda
    
    // Verifica todas as pcas na mao do computador para achar uma jogada que seja valida
    for (int i = 0; i < jogadores[jogador].numPieces; i++) {
        int qtdValidas = qtdJogadaValida(jogadores, jogador, i);
        
        if (qtdValidas > 0) {  // verifica se a peca pode ou nao ser jogada
            if (qtdValidas == 1) {  // 
                checarUnicaValida(jogadores, jogador, i);
            } else {  // Caso tenha mais de uma opocao de lado para jogar
                // Decidir automaticamente o lado 
                checarLadoValida(jogadores, jogador, i, 'D');
            }
            
            donePlay = 1;  // indica que uma jogada foi feita com sucesso
            break;  
        }
    }

    // o pc compra pecas, caso nao tenha jogadas validas com as pecas em mao
    if (donePlay == -1) {
        while (qtdPecasDisponivel > 0 && donePlay == -1) {
                comprarCartas(domino, &jogadores[jogador], jogador);
            for (int i = 0; i < jogadores[jogador].numPieces; i++) {
                if (qtdJogadaValida(jogadores, jogador, i) > 0) {
                    checarUnicaValida(jogadores, jogador, i);
                    donePlay = 1;
                    break;
                }
            }
        }
        
        if (donePlay == -1) {
            passarVez();  
        }
    }
}

int jogoSalvo(){
	limparTela();
	definirPecasCadaJogador(domino);
	definirSitVariaveis();
	while (menuJogador(jogadores, domino)) {
      // O loop continua ate que o jogador decida sair
    }
	return 0;
}

void jogar(){
	int opcao;
	recuperarDataHora();
	gerarSeed();
	
	do {
		definirDataHora();
        opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
               	novoJogo();
                break;
            }
            case 2:
            	novoJogo();
            	vezDoPc(jogadores, 1);
            	break;
            case 3:
            	mostrarRegras(opcao);
            	break;
            case 4:
                salvarJogo();
                break;
            case 5:
            	continuarJogo();
            	break;
            case 0:
            	interacoesMenu(opcao);
                exit(0);
            default:
            	interacoesMenu(opcao);
                
        }
    } while (opcao != 0);
}


//LIMPADOR
void fclearBuffer() 
{ 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
DOM-BGLL - Projeto Domino - Etapa 6
24/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_Controller.h"

//PONTEIROS DOS ARQUIVOS
FILE *arqmesa; //arquivo onde serao armazenadas apenas as pecas que ja tinham sido jogadas
FILE *pecas; //arquivo onde serao armazenadas todas as pecas do jogo
FILE *sitJogoSalvo; //situacao das variaveis globais no momento do salvamento do jogo
FILE *dataHoraSalvo; //arquivo para armazenar a data e a hora em que o jogo foi salvo por ultimo

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

int verificarDisponiveis(){
	qtdPecasDisponivel = 0;
	
	for(int i = 0; i < NUM_PECAS; i++){
		if(domino[i].status == '\0'){
			qtdPecasDisponivel++;
		}
	}
	
	return 0;
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
    }
  }
  
  verificarDisponiveis();
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

int verificarSeJogadaValida(){
	int qtdJogadas = 0;
	for(int i = 0; i < jogadores[jogadorAtual].numPieces; i++){
			qtdJogadas += qtdJogadaValida(jogadores, jogadorAtual, i);
	}
	
	return qtdJogadas;
}

int checarUnicaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos) {
  Carta pecaJogada = jogadores[jogador].pecasMao[pos];
  int ladoD = limitesMesa.ladoD;
  int ladoE = limitesMesa.ladoE;

	//Considerando que ao chegar nessa funcao temos apenas uma jogada possivel,
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
			exibirMensagemJogada(qtdValidas);
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
	verificarDisponiveis();
	
	
	if(qtdPecasDisponivel <= 0 && verificarSeJogadaValida() == 0){
		definirJogadorAtual();
		return 1;
	} else {
		return -1;
	}
}

void passarVez(){
	int disponibilidadePecas = verificarPassarVez();
	
	
	exibirMensagemPassarVez(disponibilidadePecas);
}

//FUNCIONALIDADES PARA VERIFICAR SE E QUANDO O JOGO TERMINOU

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
	verificarDisponiveis();
	
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
		if (jogadores[1].numPieces > jogadores[0].numPieces)
			return 1; 
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
		motVitoria = 1;
		exibirMensagemVencedor(verificarMaoVazia());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
		return;
	}
	
	//Caso ainda tenha, verifica se o jogo esta' fechado
	if(verificarVencedorJogoFechado() != -1){
		motVitoria = 2;
		exibirMensagemVencedor(verificarVencedorJogoFechado());
		int opcao = exibirOpcoesJogoFinalizado();
		verificarOpcaoUsuario(opcao);
		return;
	}
		
}

//FUNCIONALIDADES PARA COMPRA DAS PECAS

int comprarCartas(Carta totalPieces[NUM_PECAS]) {	
	verificarDisponiveis();
	if(qtdPecasDisponivel > 0){
	    for (int k = 0; k < NUM_PECAS; k++) {
	        if (totalPieces[k].status == '\0') { //busca por pecas que nao estejam nem na mesa e nem na mao dos jogadores
	                jogadores[jogadorAtual].pecasMao[jogadores[jogadorAtual].numPieces++] = totalPieces[k]; //adiciona a peca disponivel ao fim da mao do usuario
	                totalPieces[k].status = '1' + jogadorAtual;
	                jogadores[jogadorAtual].pecasMao[(jogadores[jogadorAtual].numPieces) - 1].pos = k;
					qtdPecasDisponivel--;
					
					//Guarda quais eram as extremidades da mesa, em partidas contra o computador, nas situacoes em que o jogador compra
					if(modoJogo == 1 && jogadorAtual == 0){
						ultCompra[0] = limitesMesa.ladoD;
						ultCompra[1] = limitesMesa.ladoE;
					}
					
	                return 1; // Compra feita
	        }
	    }
    } else if (qtdPecasDisponivel < 1){
    	return 0; // Nao foi possivel fazer a compra
	}
    
	return -1;    	
}

int realizarCompraCartas(Carta totalPieces[NUM_PECAS]){
	int status = comprarCartas(totalPieces);
	
	
	if(modoJogo == 0 || modoJogo == 1 && jogadorAtual == 0)
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
	ultimaPecaA = jogadores[jogador].pecasMao[pos].ladoA;
	ultimaPecaB = jogadores[jogador].pecasMao[pos].ladoB;
	qtdPecasMesa++; //Incrementa a variavel de controle da mesa
	removerPecaJogada(&jogadores[jogador], pos);
	definirJogadorAtual();
	
	if(qtdPecasMesa == 1){
		limitesMesa.ladoD = mesa[posicaoJogada].ladoE;
		limitesMesa.ladoE = mesa[posicaoJogada].ladoD;
	}
	
	limparTela();
	exibirMensagemPeca();
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
	
	// Abre o arquivo para escrita em binario das pecas
    if((pecas = fopen("CAD_DOMINO", "wb")) == NULL){
    	return -1;
	}
	
    // Escreve cada peca no arquivo
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
	
	// Abre o arquivo para escrita em binario da mesa
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

// Funcao para salvar o estado do jogo em um arquivo binario
int salvarSitJogo(){
	//Dados do jogo 
	sitSalva.jogadorComp = modoJogo;
    sitSalva.jogadorJogo = jogadorAtual;
    sitSalva.mesaDJogo = limitesMesa.ladoD;
    sitSalva.mesaEJogo = limitesMesa.ladoE;
    sitSalva.qtdPecasMesa = qtdPecasMesa;
    sitSalva.qtdPecasDisponivel = qtdPecasDisponivel;
    
	//Escreve a estrutura no arquivo
	if((sitJogoSalvo = fopen("CAD_SIT", "wb")) == NULL){
    	return -2;
	}
	
	if(fwrite(&sitSalva, sizeof(sitJogo), 1, sitJogoSalvo) != 1){
		return -1;
	}
	
	fclose(sitJogoSalvo);
	return 0;
}

//salva a data e a hora em que o jogo foi salvo 
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
        return -1;
    }
    return 0;
}

// Funcao para recuperar as pecas do arquivo binario
 int recuperarJogoPecas(){	
 
 	int i;
	
	//Faz a leitura de cada peca em binario
    if((pecas = fopen("CAD_DOMINO", "rb")) == NULL){
    	return -2;
	}
	
	for (i = 0; i < 28; i++) {
        size_t result = fread(&domino[i], sizeof(Carta), 1, pecas);
        if (result != 1) {
            fclose(pecas);
            return -1;     // Retorna -1 para erro ao ler o arquivo
        }
    }
	
	fclose(pecas);
	return 0;
 }
 
int recuperarJogoMesa(){
    int i;
    
    //Faz a leitura da mesa em binario
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

//Faz a leitura da situacao do jogo que foi salva
int recuperarSitJogo(){  
    if ((sitJogoSalvo = fopen("CAD_SIT", "rb")) == NULL) {
        return -2;
    }
    
    if (fread(&sitSalva, sizeof(sitJogo), 1, sitJogoSalvo) != 1) {
        fclose(sitJogoSalvo);
        return -1;
    }
    
    fclose(sitJogoSalvo);
	return 0;
}

//Faz a leitura dos dos dados salvos da hora e data
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
			jogadores[0].pecasMao[pecasJ1].pos = i;
			pecasJ1++;
		}
		
		else if(domino[i].status == '2'){
			jogadores[1].pecasMao[pecasJ2] = domino[i];
			jogadores[1].pecasMao[pecasJ2].pos = i;
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
        return -1;
    }
    
    return 0;
}

int continuarJogo() {
    int status = recuperarJogo();
    mensagemRecuperarJogo(status);

    if (status != 0) {
        menuJogador(jogadores, domino);
        return -1;
    }

    jogoSalvo();
    return 0; // Indica sucesso na continuacao do jogo
}

//MENU DO JOGADOR E INICIALIZACAO DO JOGO APARTIR DO MENU PRINCIPAL

int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]) {
    int escolha = 9;
		do {
			definirVencedor();
			if(modoJogo == 1 && jogadorAtual == 1){
				preferenciaJogadaComputador(jogadores, 1);
			} else {
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
		                realizarCompraCartas(domino);
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
			}
	} while (escolha != 0);
	
	return 1;
}


int novoJogo(){
	qtdPecasMesa = 0; //a cada novo jogo, inicia a mesa da primeira posicao
	qtdPecasDisponivel = NUM_PECAS; 
	
	criarCarta(domino);
    embaralharPecas(domino);
    iniciaMesa(mesa);
	
	distribuirPecas(domino, jogadores, 2);

    int firstPlayer = primeiroJogador(jogadores, mesa); // faz passagem por referencia

    while (menuJogador(jogadores, domino)) {
      // O loop continua ate que o jogador decida sair
    }
    
	return 0;
	

}



int jogoSalvo(){
	limparTela();
	definirPecasCadaJogador(domino);
	definirSitVariaveis(); //Recupera as variaveis sobre a situacao salva do jogo e ja o inicia partindo dessas informacoes
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
            	modoJogo = 0;
               	novoJogo();
                break;
            }
            case 2: {
            	modoJogo = 1;
            	ultCompra[0] = -2;
				ultCompra[1] = -2;
               	novoJogo();
                break;
            }
            case 3: {
            	if(ultCompra[0] == -2 && qtdPecasMesa == 0){
            		mostrarMensagemMenu(3);
            		break;
				} else {
					limparTela();
               		menuJogador(jogadores,domino);
                	break;
				}
            }
            case 4:{
            	mostrarRegras();
            	break;
			}
            case 5:
            	//Somente permite salvar o jogo caso algum jogo ja tenha sido iniciado
            	if(qtdPecasMesa == 0){
            	    mostrarMensagemMenu(2);
            		break;
				} else {
					salvarJogo();
                	break;
				}
            case 6:
            	if(ano == 0){
            	    mostrarMensagemMenu(1);
					break;
				} else {
					continuarJogo();
            		break;
				}
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

//FUNCIONALIDADES PARA JOGAR CONTRA O COMPUTADOR (SOLO)
int qtdNumMao(int qtd[7], int qtdOrd[7]) {
    int auxiliar;  // variavel auxiliar para a troca de valores no vetor

    
    for (int k = 0; k < 7; k++) {
        qtd[k] = 0; //inicializa todas as posicoes do array como 0
        qtdOrd[k] = k; //inicializa o array com seu determinado indice
    }
    
    // conta a quantidade de vezes que cada num aparece na mao do computador,
    // gerando um array cujo o indice indica o num da peca e o conteudo de cada posicao
    // e' a ocorrencia desse numero na mao do jogador
    for (int cont = 0; cont < jogadores[1].numPieces; cont++) {
        qtd[jogadores[1].pecasMao[cont].ladoA]++; 
        qtd[jogadores[1].pecasMao[cont].ladoB]++;
    }

    // armazena o numero das pecas do jogador considerando a sua ocorrencia, sendo
    // a primeira posicao o numero da peca que ele possui em maior quantidade e o ultimo em menor quantidade
    for (int k = 0; k < 7; k++) {
        for (int i = k + 1; i < 7; i++) {
            if (qtd[qtdOrd[k]] < qtd[qtdOrd[i]]) {
                auxiliar = qtdOrd[k];
                qtdOrd[k] = qtdOrd[i];
                qtdOrd[i] = auxiliar;
            }
        }
   	}

    return 1; 
}

//A partir do valor da extremidade armazenado no momento da ultima compra do jogador 1,
//joga uma peca que deixe o valor que fez o jogador comprar anteriormente como extremidade da mesa
//- "deixar numeros que o outro jogador nao possue como extremidades da mesa faz com que ele seja obrigado a comprar mais pecas"
int forcarCompraPC(int ladoD, int ladoE, int qtdLadoD, int qtdLadoE, int qtd[]){
	
	//Se nenhuma compra tiver sido feita ate o momento, nao prossegue com a funcao
	if(ultCompra[0] == -2 || ultCompra[1] == -2)
		return 0;
	
	int maior = ladoD, menor = ladoE;
	char maiorLado = 'D', menorLado = 'E';
	int maiorCompra, menorCompra;
	
	if(qtdLadoE >= qtdLadoD){
		maior = ladoE;
		menor = ladoD;
		maiorLado = 'E';
		menorLado = 'D';
	}
	
	//Define qual das extremidades possui o numero que aparece mais vezes na mao do computador
	if(qtd[ultCompra[0]] > qtd[ultCompra[1]]){
		maiorCompra = ultCompra[0];
		menorCompra = ultCompra[1];
	} else {
		maiorCompra = ultCompra[1];
		menorCompra = ultCompra[0];
	}
	
	//primeiro, busca a peca que cumpre o papel e, simultaneamente, possui o numero em maior quantidade na mao do computador
	for(int i = 0; i < jogadores[1].numPieces; i++){
		if(jogadores[1].pecasMao[i].ladoA == maior || jogadores[1].pecasMao[i].ladoB == maior) {
			if(jogadores[1].pecasMao[i].ladoA == maiorCompra || jogadores[1].pecasMao[i].ladoB == maiorCompra){
				checarLadoValida(jogadores,1,i,maiorLado);
				return 1;
			}
		} 
	}
	
	//caso nao encontre, busca pela que esta presente em menor quantidade
	for(int i = 0; i < jogadores[1].numPieces; i++){
		if(jogadores[1].pecasMao[i].ladoA == menor || jogadores[1].pecasMao[i].ladoB == menor){
		  	if(jogadores[1].pecasMao[i].ladoA == menorCompra || jogadores[1].pecasMao[i].ladoB == menorCompra){
				checarLadoValida(jogadores,1,i,menorLado);
				return 1;
			} 
		}
	}
	
	return 0; //nenhuma peca na mao do jogador possui numero igual as extremidades no momento da ultima compra
}

//busca por pecas duplas que possuam os numeros da extremidade da mesa
// - "pecas duplas representam apenas um numero, logo, para garantir uma mao variada, e' melhor joga-las antes das demais de mesmo numero"
int buscarDuplaPC(int ladoD, int ladoE, int qtdLadoD, int qtdLadoE){
	int maior = ladoD, menor = ladoE;
	char maiorLado = 'D', menorLado = 'E';
	
	//verifica qual numero dentre os presentes nas extremidades esta presente em maior quantidade na mao do computador
	if(qtdLadoE >= qtdLadoD){
		maior = ladoE;
		menor = ladoD;
		maiorLado = 'E';
		menorLado = 'D';
	}
	
	//primeiro, busca pela peca dupla com o numero em maior qtd
	for(int i = 0; i < jogadores[1].numPieces; i++){
		if(jogadores[1].pecasMao[i].ladoA == maior && jogadores[1].pecasMao[i].ladoB == maior){
				checarLadoValida(jogadores,1,i,maiorLado);
				return 1;
		}
	}
	
	//caso nao encontre, busca pela peca dupla com numero em menor qtd
	for(int i = 0; i < jogadores[1].numPieces; i++){
		if(jogadores[1].pecasMao[i].ladoA == menor && jogadores[1].pecasMao[i].ladoB == menor){
				checarLadoValida(jogadores,1,i,menorLado);
				return 1;
		}
	}
	
	return 0; //nao ha pecas duplas com o mesmo numero de nenhuma das extremidades
	
}

//faz uma jogada priorizando os numeros que o computador possui em maior qtd para garantir que ele possua a mao mais variada possivel
int jogadaQtdPC(int ladoD, int ladoE, int qtdLadoD, int qtdLadoE, int qtdOrd[]){
	int maior = ladoD, menor = ladoE;
	char maiorLado = 'D', menorLado = 'E';
	
	
	if(qtdLadoE > qtdLadoD){
		maior = ladoE;
		menor = ladoD;
		maiorLado = 'E';
		menorLado = 'D';
	}
	
	//primeiro, busca pela peca que possua um numero igual ao da extremidade em maior qtd na mao
	// e, simultaneamente, outro que esteja em maior quantidade no geral
	for(int k = 0; k < 7; k++){
		for(int i = 0; i < jogadores[1].numPieces; i++){
			if(jogadores[1].pecasMao[i].ladoA == maior || jogadores[1].pecasMao[i].ladoB == maior){
				if(jogadores[1].pecasMao[i].ladoA == qtdOrd[k] || jogadores[1].pecasMao[i].ladoB == qtdOrd[k]){
					checarLadoValida(jogadores,1,i,maiorLado);
					return 1;
				}
			}
		}
	}
	
	//caso nao encontre, busca pela peca com numero igual ao da extremidade em menor qtd sob as mesmas condicoes
	for(int k = 0; k < 7; k++){
		for(int i = 0; i < jogadores[1].numPieces; i++){
			if(jogadores[1].pecasMao[i].ladoA == menor || jogadores[1].pecasMao[i].ladoB == menor){
				if(jogadores[1].pecasMao[i].ladoA == qtdOrd[k] || jogadores[1].pecasMao[i].ladoB == qtdOrd[k]){
					checarLadoValida(jogadores,1,i,menorLado);
					return 1;
				}
			}
			
		}
	}
	
	return 0; //nao ha nenhuma jogada possivel
}


//funcao para escolher a melhor jogada do pc
int preferenciaJogadaComputador(Jogador jogadores[NUM_JOGADORES], int pc){
	
	int ladoD = limitesMesa.ladoD;
	int ladoE = limitesMesa.ladoE;
	int qtd[7]; //vetor contendo as quantidades de cada numero
	int qtdOrd[7]; //vetor contendo os numeros que aparecem mais vezes na mao do jogador, em ordem decrescente
	qtdNumMao(qtd, qtdOrd);

	while (1) {
		//primeiro, tenta jogar uma peca que priorize deixar uma peca que o outro jogador teoricamente nao possue como extremidade da mesa
        if (forcarCompraPC(ladoD, ladoE, qtd[ladoD], qtd[ladoE], qtd) == 1) {
            return 1;
        }
		
		//caso nao encontre, busca por uma peca dupla com o valor de uma das extremidades
        if (buscarDuplaPC(ladoD, ladoE, qtd[ladoD], qtd[ladoE]) == 1) {
            return 1;
        }
		
		//caso tambem nao encontre, busca por uma peca qualquer que possa ser jogada, dando prioridade para numeros que o computador tenha em maior quantidade
        if (jogadaQtdPC(ladoD, ladoE, qtd[ladoD], qtd[ladoE], qtdOrd) == 1) {
            return 1;
        }
		
		//caso nao haja nenhuma jogada possivel, o computador compra uma nova peca e tenta jogar novamente seguindo a mesma ordem de prioridade 
        if(realizarCompraCartas(domino) != 0){
			realizarCompraCartas(domino);
			qtdNumMao(qtd, qtdOrd); //atualiza os vetores de quantidade
		} else {
			passarVez(); //caso nao haja mais jogadas validas nem pecas para comprar, passa a vez para o jogador 1
			return 0;
		}

        qtdNumMao(qtd, qtdOrd);
    }
	
	
	return 0;
}

//FUNCOES DO PC
int escolherPecaPC(Jogador jogadores[NUM_JOGADORES], int PC){
	int ladoD = limitesMesa.ladoD;
	int ladoE = limitesMesa.ladoE;
	
	do{
		
		for (int k = 0; k < jogadores[PC].numPieces; k++){
			if(jogadores[PC].pecasMao[k].ladoA == ladoD || jogadores[PC].pecasMao[k].ladoB == ladoD){
				checarLadoValida(jogadores, 1, k, 'D');
				return 0;
			} else if(jogadores[PC].pecasMao[k].ladoA == ladoE || jogadores[PC].pecasMao[k].ladoB == ladoE){
				checarLadoValida(jogadores, 1, k, 'E');
				return 0;
			}
		}
		
		if(realizarCompraCartas(domino) != 0){
			realizarCompraCartas(domino);
		} else {
			verificarPassarVez();
			return 0;
		}
			
	} while (1);

	return 1;
}



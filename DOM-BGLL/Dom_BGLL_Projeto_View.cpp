/*
DOM-BGLL - Projeto Domino - Etapa 5
10/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_View.h"

//FUNCIONALIDADES PARA VISUALIZAR AS PECAS

void mostrarCartas(Carta domino[NUM_PECAS]){
  for(int i = 0; i < NUM_PECAS; i++){
      if(i%7 == 0 )
          printf("\n");
    printf("[%d|%d] ", domino[i].ladoA, domino[i].ladoB);
  }
}

void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogador){
  printf("\n");
    printf("Jogador %d: \n", numJogador + 1);//o i = 1 numera corretamente cada jogador
    for(int k = 0 ; k < jogadores[numJogador].numPieces; k++){
		if(jogadores[numJogador].pecasMao[k].status != 'M')
			printf("%d.[%d|%d] ", k+1, jogadores[numJogador].pecasMao[k].ladoA,jogadores[numJogador].pecasMao[k].ladoB);
    }

    printf("\n");
}

//Mostra todas as pecas da mesa
void mostrarPecasMesa(Mesa mesa[]){
   	printf("\nMesa do Jogo: \n\n");
   	printf("-------------------\n");
    for(int k  = 0; k < qtdPecasMesa; k++)
        printf("[%d|%d]", mesa[k].ladoE, mesa[k].ladoD);
	printf("\n-------------------");
    printf("\n");
}

//Define o numero de jogadores de acordo com o informado pelo usuario
int numeroJogadores(void){
  int numJogadores;
  
  printf("\n");
  printf("Digite o numero de jogadores para a partida (1 ou 2):");

  scanf("%d",&numJogadores);

  while(numJogadores <1||numJogadores > 2 ){//O loop nao deixa o usuario prosseguir ate que o mesmo digite um dado valido
    printf("O numero de jogadores escolhido e' invalido. Digite 1 ou 2");
    scanf("%d",&numJogadores);
  }
  
  limparTela();
  return numJogadores;
}

//FUNCOES DE MENU

int existeDataHora(){
	if(ano == 0){
		printf("6. Recuperar Jogo (Nao ha jogo salvo)\n");
		return 0;
	} else {
		printf("6. Recuperar Jogo (Salvo em: %02d/%02d/%d - %02d:%02d)\n", dia, mes,ano,hora,minutos);
	}
	return 1;
}

//Opcoes do menu principal do jogo
int menuPrincipal() {
    int opcao;
    limparTela();
    printf("\n--- Menu Principal ---\n");
    printf("1. Iniciar Novo Jogo (2 jogadores)\n");
    printf("2. Iniciar Novo Jogo (Contra Pc)\n");
    printf("3. Continuar jogo interrompido\n");
    printf("4. Regras do Jogo\n");
    printf("5. Salvar Jogo (Necessario ter um jogo em andamento)\n");
    existeDataHora();
    printf("0. Sair\n");
    printf("------------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

//Opcoes do menu de acoes do jogador durante o jogo
int menuPrincipalJogador() {
    int escolha;
    mostrarPecasMesa(mesa);
    printf("\n------ VEZ DO JOGADOR %d ------\n", jogadorAtual + 1);
    mostrarPecasJogadorAtual(jogadores, jogadorAtual);
    printf("\n--- Menu do Jogador %d ---\n", jogadorAtual + 1);
    printf("1. Escolher peca para jogar\n");
    printf("2. Comprar peca (%d pecas disponiveis)\n", qtdPecasDisponivel);
	printf("3. Passar vez\n");
    printf("0. Interromper jogo atual\n");
    printf("-----------------------------\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &escolha);
    limparBuffer();
    return escolha;
}

void interacoesMenu(int opcao){
	if(opcao == 0){
		printf("Saindo do jogo...\n");
	} else {
		limparTela();
		printf("Opcao invalida. Tente novamente.\n");
	}
		
}

int mostrarRegras(){
    int alt;
    do{
        limparTela();
        printf("\nRegras Gerais  \n");
        printf("\n---------------------------------------------");
        printf("\n- Cada jogador inicia com 7 pecas aleatorias\n");
        printf("\n- Pode-se comprar quantas vezes for necessarias, sendo permitido blefe\n");
        printf("\n- O jogo inicia com o jogador que possui a maior peca cujo os dois lados tenham o mesmo valor, caso nenhum dos jogadores possuam uma peca com essas caracteristicas, inicia o jogador que tiver a peca de maior soma\n");
        printf("\n- Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas que se encontram nas 2 extremidas da mesa(lado E e D) \n");
        printf("\n- O jogador so podera passar a vez se nao possuir mais pecas para comprar\n");
        printf("\n- A partida termina quando um dos jogadores colocar a sua ultima peca na mesa ou no momento que nao existir mais nenhuma jogada possivel\n");
        printf("\n- Em casos de nao haver mais movimentos possiveis, vence quem tiver menos pecas na mao\n");
        printf("\n- Em caso de empate, vence o jogador que tiver a menor soma de pontos das pecas que restaram em sua mao\n");
        printf("\n---------------------------------------------");
        printf("\nDigite 0 para voltar o menu\n");
        scanf("%d", &alt);
        limparBuffer();
    } while (alt != 0);
    
    return alt;
}

//FUNCOES PARA ESCOLHA DE JOGADAS

int receberPosicaoPeca() {
    int posicao;
    int numPieces = jogadores[jogadorAtual].numPieces; // Recupera o numero de pecas do jogador atual
    
    do {
        printf("Escolha a posicao da peca que deseja jogar (1 a %d) [0 para voltar]: ", numPieces);
        scanf("%d", &posicao);
        
        if (posicao == 0) {
        	limparTela();
            return -1; 
        } else if (posicao < 1 || posicao > numPieces) {
            printf("Posicao invalida. Por favor, insira um numero entre 1 e %d.\n", numPieces);
            posicao = -1; // Define um número inválido para repetir o loop
        }
    } while (posicao < 1 || posicao > numPieces); // Loop ate que uma posicao valida seja fornecida
	
    return posicao;
}

char receberLadoJogada() {
    char lado;
    char error = 'e';
    do {
        printf("Escolha em qual lado voce deseja jogar (E para esquerda | D para direita):\n");
        scanf("%c", &lado);
        
        limparBuffer();

        lado = toupper(lado);

        if (lado == 'E' || lado == 'D') {
            return lado;
        } else {
            printf("Opcao invalida.");
        }
        
    } while (lado != 'E' ||  lado != 'D');
    
    return lado;
}

//FUNCIONALIDADES DE LIMPEZA

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(){
	system("cls||clear");
}

//FUNCOES DE MESNSAGENS DURANTE A PARTIDA DO JOGO

void exibirMensagemJogada(int status){
	if(status == 0){
		limparTela();
		printf("Nao ha jogada possivel com essa peca\n");
		return;
	}
	
	if(status == 1){
		limparTela();
		printf("Como havia apenas uma possibilidade de jogada, a peca foi jogada automaticamente\n");
		return;
	}
	
	if(status > 1){
		limparTela();
		printf("Peca jogada na extremidade escolhida\n");
		return;
	}
	
	if(status == -1){
		limparTela();
		printf("Jogada invalida\n");
		return;
	}	
}

void statusCompra(int status){
	if(status == 1){
		limparTela();
		printf("\nCompra feita com sucesso\n");
	} else {
		limparTela();
		printf("Nao ha pecas para comprar");
	}	
}

void exibirMensagemPassarVez(int status){
	if(status == 1){
		limparTela();
		printf("Passada a vez para Jogador %d\n", jogadorAtual + 1);
	} else if (status == -1){
		limparTela();
		printf("Ainda ha pecas para compra, nao e' permitido passar\n");
	} else {
		printf("Problema desconhecido. Nos informe, por favor\n");
	}
}

void mensagemRecuperarJogo(int status) {
    switch (status) {
        case 0:
            printf("Jogo recuperado com sucesso.\n");
            break;
        case -1:
            printf("Erro ao recuperar o jogo.\n");
            break;
        default:
            printf("Status desconhecido.\n");
            break;
    }
}

void exibirMensagemPeca(int ultimaPecaA, int ultimaPecaB){
    printf("A ultima peca jogada foi [%d | %d]", ultimaPecaA, ultimaPecaB);
}

//FUNCOES DE MESNSAGENS APOS A FINALIZACAO DE UMA PARTIDA

void exibirMensagemVencedor(int status){
	if(status == 1){
		limparTela();
		printf("JOGADOR 1 E' O VENCEDOR DA PARTIDA!\n");
	} else {
		limparTela();
		printf("JOGADOR 2 E' O VENCEDOR DA PARTIDA!\n");
	}
}

int exibirOpcoesJogoFinalizado(){
	int opcao;
	
	do{
		printf("\nPressione 0 para voltar ao menu principal\nPressione 1 para sair do jogo\n");
		scanf("%d", &opcao);
	
		if(opcao == 0)
			return opcao;
			
		if(opcao == 1)
			return opcao;
			
		else
			printf("Opcao invalida\n");
		
	}while(opcao != 0);
	
	return -1;
}

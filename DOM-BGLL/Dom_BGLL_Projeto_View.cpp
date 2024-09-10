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
    printf("[%d|%d] ", domino[i].ladoA, domino[i].ladoB, domino[i].status, i);
  }
}

void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogador){
  printf("\n");
    printf("Jogador %d: \n", numJogador + 1);//o i = 1 numera corretamente cada jogador
    for(int k = 0 ; k < jogadores[numJogador].numPieces; k++){
		if(jogadores[numJogador].pecasMao[k].status != 'M')
			printf("%d.[%d|%d] ", k+1, jogadores[numJogador].pecasMao[k].ladoA,jogadores[numJogador].pecasMao[k].ladoB, jogadores[numJogador].pecasMao[k].pos);
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
		printf("4. Continuar Jogo (Nao ha jogo salvo)\n");
		return 0;
	} else {
		printf("4. Continuar Jogo (Salvo em: %02d/%02d/%d - %02d:%02d)\n", dia, mes,ano,hora,minutos);
	}
}

//Opcoes do menu principal do jogo
int menuPrincipal() {
    int opcao;
    limparTela();
    printf("\n--- Menu Principal ---\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Regras do Jogo\n");
    printf("3. Salvar Jogo\n");
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
    printf("0. Sair\n");
    printf("-----------------------------\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &escolha);
    limparBuffer();
    return escolha;
}

void interacoesMenu(int opcao){
	if(opcao == 2 || opcao == 3){
		printf("Saindo do jogo...\n");
	} else {
		limparTela();
		printf("Opcao invalida. Tente novamente.\n");
	}
		
}

void mostrarRegras(int choice){
	limparTela();
	printf("\nRegras Gerais  \n");
	printf("\n---------------------------------------------");
	printf("\n- Cada jogador inicia com 7 pecas aleatorias\n");
	printf("\n- Pode-se comprar quantas vezes for necessarias, sendo permitido blefe\n");
	printf("\n- O jogo inicia com o jogador que possui a maior peaÂ§a cujo os dois lados tenham o mesmo valor, caso nenhum dos jogadores possuam uma peaÂ§a com essas caracteristicas, inicia o jogador que tiver a peca de maior soma\n");
	printf("\n- Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas que se encontram nas 2 extremidas da mesa(lado E e D) \n");
	printf("\n- O jogador so podera passar a vez se nao possuir mais pecas para comprar\n");
	printf("\n- A partida termina quando um dos jogadores colocar a sua ultima peca na mesa ou no momento que nao existir mais nenhuma jogada possivel\n");
	printf("\n- Em casos de nao haver mais movimentos possiveis, vence quem tiver menos pecas na mao\n");
	printf("\n- Em caso de empate, vence o jogador que tiver a menor soma de pontos das pecas que restaram em sua mao\n");
}

//FUNCOES PARA ESCOLHA DE JOGADAS

int receberPosicaoPeca() {
    int posicao;
    int numPieces = jogadores[jogadorAtual].numPieces; // Retrieve the number of pieces for the current player
    
    do {
        printf("Escolha a posicao da peca que deseja jogar (1 a %d) [0 para voltar]: ", numPieces);
        scanf("%d", &posicao);
        
        if (posicao == 0) {
        	limparTela();
            return -1; 
        } else if (posicao < 1 || posicao > numPieces) {
            printf("Posicao invalida. Por favor, insira um numero entre 1 e %d.\n", numPieces);
            posicao = -1; // Set to an invalid number to repeat the loop
        }
    } while (posicao < 1 || posicao > numPieces); // Loop until a valid position is provided
	
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
	} else{
		printf("O problema é otro");
	}
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

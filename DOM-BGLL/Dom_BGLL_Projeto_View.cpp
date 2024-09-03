/*
DOM-BGLL - Projeto Domino - Etapa 4
27/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#include "Dom_BGLL_Projeto_View.h"


void mostrarCartas(Carta domino[NUM_PECAS]){
  for(int i = 0; i < NUM_PECAS; i++){
      if(i%7 == 0 )
          printf("\n");
    printf("[%d|%d] ", domino[i].ladoA, domino[i].ladoB);
  }
}

//void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogadores){	
//  printf("\n");
//  for(int i = 0; i < numJogadores; i++){
//    printf("Jogador %d: \n", i + 1);//o i = 1 numera corretamente cada jogador
//    for(int k = 0 ; k < jogadores[i].numPieces; k++){
//		if(jogadores[i].pecasMao[k].status != 'M')
//			printf("[%d|%d]",jogadores[i].pecasMao[k].ladoA,jogadores[i].pecasMao[k].ladoB);
//    }
//
//    printf("\n");
//  }
//  printf("\n");
//}

void mostrarPecasJogadorAtual(Jogador jogadores[NUM_JOGADORES], int numJogador){
  printf("\n");
    printf("Jogador %d: \n", numJogador + 1);//o i = 1 numera corretamente cada jogador
    for(int k = 0 ; k < jogadores[numJogador].numPieces; k++){
		if(jogadores[numJogador].pecasMao[k].status != 'M')
			printf("%d.[%d|%d]  ", k+1, jogadores[numJogador].pecasMao[k].ladoA,jogadores[numJogador].pecasMao[k].ladoB);
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

//Define o nÃºmero de jogadores de acordo com o informado pelo usuÃ¡rio
int numeroJogadores(void){
  int numJogadores;
  
  printf("\n");
  printf("Digite o numero de jogadores para a partida (1 ou 2):");

  scanf("%d",&numJogadores);

  while(numJogadores <1||numJogadores > 2 ){//O loop nao deixa o usuÃ¡rio prosseguir ate que o mesmo digite um dado valido
    printf("O numero de jogadores escolhido e' invalido. Digite 1 ou 2");
    scanf("%d",&numJogadores);
  }
  
  limparTela();
  return numJogadores;
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

//OpÃ§Ãµes do menu principal do jogo
int menuPrincipal() {
    int opcao;
    printf("\n--- Menu Principal ---\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Regras do Jogo\n");
    printf("3. Sair\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void mostrarRegras(int choice){
//	printf("\n---------------------------------------------");
	printf("\nRegras Gerais  \n");
//	printf("\n---------------------------------------------");
	printf("\n- Cada jogador inicia com 7 pecas aleatorias\n");
	printf("\n- Pode-se comprar quantas vezes for necessarias, sendo permitido blefe\n");
	printf("\n- O jogo inicia com o jogador que possui a maior peça cujo os dois lados tenham o mesmo valor, caso nenhum dos jogadores possuam uma peça com essas caracteristicas, inicia o jogador que tiver a peca de maior soma\n");
	printf("\n- Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas que se encontram nas 2 extremidas da mesa(lado E e D) \n");
	printf("\n- O jogador so podera passar a vez se nao possuir mais pecas para comprar\n");
	printf("\n- A partida termina quando um dos jogadores colocar a sua ultima peca na mesa ou no momento que nao existir mais nenhuma jogada possivel\n");
	printf("\n- Em casos de nao haver mais movimentos possiveis, vence quem tiver menos pecas na mao\n");
	printf("\n- Em caso de empate, vence o jogador que tiver a menor soma de pontos das pecas que restaram em sua mao\n");
}

//OpÃ§Ãµes do menu de aÃ§Ãµes do jogador durante o jogo
int menuPrincipalJogador() {
    int escolha;
    mostrarPecasMesa(mesa);
    printf("\n------ VEZ DO JOGADOR %d ------\n", jogadorAtual + 1);
    mostrarPecasJogadorAtual(jogadores, jogadorAtual);
    printf("\n--- Menu do Jogador %d ---\n", jogadorAtual + 1);
    printf("1. Escolher peca para jogar\n");
    printf("2. Comprar peca\n");
	printf("3. Passar vez\n");
	printf("4 - ver regras do Jogo");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    return escolha;
}

int receberPosicaoPeca(){
	int posicao;
	printf("Escolha a posicao da peca que deseja jogar (1 a %d): ", jogadores[jogadorAtual].numPieces);
    scanf("%d", &posicao);
    return posicao;
}

char receberLadoJogada(){
	char lado;
	printf("Escolha em qual lado voce deseja jogar (E para esquerda | D para direita):\n");
    scanf("%c", &lado);
    limparTela();
    return toupper(lado);
}

void limparTela(){
	system("cls||clear");
}

void exibirMensagemJogada(int status){
	if(status == 0){
		limparTela();
		printf("Nao ha jogada possivel com essa peca");
		return;
	}
	
	if(status == 1){
		limparTela();
		printf("Como havia apenas uma possibilidade de jogada, a peca foi jogada automaticamente");
		return;
	}
	
	if(status > 1){
		limparTela();
		printf("Peca jogada na extremidade escolhida");
		return;
	}
	
	if(status == -1){
		limparTela();
		printf("Jogada invalida");
		return;
	}	
}

void exibirMensagemPassarVez(int status){
	if(status == 1){
		limparTela();
		printf("Passada a vez para Jogador %d", jogadorAtual + 1);
	} else {
		limparTela();
		printf("Ainda ha pecas para compra, nao e' permitido passar");
	}
}

void exibirMensagemVencedor(int status){
	if(status == 1){
		limparTela();
		printf("Jogador 1 e' o vencedor da partida!");
	} else {
		limparTela();
		printf("Jogador 2 e' o vencedor da partida!");
	}
}

int exibirOpcoesJogoFinalizado(){
	int opcao;
	
	do{
		printf("\nPressione 0 para voltar ao menu principal ou 1 para sair do jogo\n");
		scanf("%d", opcao);
	
		if(opcao == 0)
			return opcao;
			
		if(opcao == 1)
			return opcao;
			
		else
			printf("Opcao invalida\n");
		
	}while(opcao != 0);
	
	return -1;
}

void interacoesMenu(int opcao){
	if(opcao == 2)
		printf("Saindo do jogo...\n");
	else
		printf("Opcao invalida. Tente novamente.\n");
}




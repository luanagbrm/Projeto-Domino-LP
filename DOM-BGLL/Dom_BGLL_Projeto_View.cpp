/*
DOM-BGLL - Projeto Dominó - Etapa 3
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
			printf("[%d|%d]",jogadores[numJogador].pecasMao[k].ladoA,jogadores[numJogador].pecasMao[k].ladoB);
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

//Define o número de jogadores de acordo com o informado pelo usuário
int numeroJogadores(void){
  int numJogadores;
  
  printf("\n");
  printf("Digite o numero de jogadores para a partida (1 ou 2):");

  scanf("%d",&numJogadores);

  while(numJogadores <1||numJogadores > 2 ){//O loop nao deixa o usuário prosseguir ate que o mesmo digite um dado valido
    printf("O numero de jogadores escolhido e' invalido. Digite 1 ou 2");
    scanf("%d",&numJogadores);
  }
  
  return numJogadores;
}


void statusCompra(int status){
	if(status == 1)
		printf("\nCompra feita com sucesso\n");
	else
		printf("Nao ha pecas para comprar");
}

//Opções do menu principal do jogo
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
	printf("\n- Cada jogador incia com 7 peças aleatórias\n");
	printf("\n- Pode-se comprar quantas vezes for necessário\n");
	printf("\n- O jogo incia com o jogador que possui a peça [6|6] ou o que tiver com a peca de numero repetido mais alto\n");
	printf("\n- Os jogadores devem colocar pecas que tenhamo os mesmos numeros das pecas que se encontram nas 2 extremidas da mesa( lado e e D) \n");
	printf("\n- O jogador so podera passar a vez se ele nao possuir nenhuma peca possivel para ser jogada ou se nao possuir mais pecas para comprar\n");
	printf("\n- A partida termina quando esgotar o estoque de cartas para compra ou quando um dos jogadores colocar a sua ultima peca na mesa\n");
	printf("\n- Em casos onde nenhum dos jogadores poderem continuar a partida, vence quem tiver menos pecas na mao\n");
	printf("\n- Em caso de empate, vence o jogador que tiver o menor numero de pontos das pecas que ficaram\n");
}

//Opções do menu de ações do jogador durante o jogo
int menuPrincipalJogador() {
    int escolha;
    //system("cls||clear");
    mostrarPecasMesa(mesa);
    printf("\n------ VEZ DO JOGADOR %d ------\n", jogadorAtual + 1);
    mostrarPecasJogadorAtual(jogadores, jogadorAtual);
    printf("\n--- Menu do Jogador %d ---\n", jogadorAtual + 1);
    printf("1. Escolher peca para jogar\n");
    printf("2. Comprar peca\n");
    printf("3. Sair\n");
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
	printf("Escolha em qual lado você deseja jogar (E para esquerda | D para direita):\n");
    scanf("%c", &lado);
    return lado;
}

void interacoesMenu(int opcao){
	if(opcao == 2)
		printf("Saindo do jogo...\n");
	else
		printf("Opcao invalida. Tente novamente.\n");
}





/*
DOM-BGLL - Projeto Domino - Etapa 6
24/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_MODEL_H
#define DOM_BGLL_PROJETO_MODEL_H

#define NUM_PECAS 28
#define HAND_PECAS_INICIAL 7
#define HAND_PECAS_MAX 21
#define NUM_JOGADORES 2


typedef struct{
  int ladoA;
  int ladoB;
  char status; //NULL ('\0'), 'M', '1', '2'
  int pos; //guarda a posicao da peca na array original
} Carta;

typedef struct{
  int playedCards;
  int ladoE;
  int ladoD;
} Mesa;

//Structure que representa cada jogador 
typedef struct{
  Carta pecasMao[HAND_PECAS_MAX];//pecasMao e' um array da estrutura "Cartas" que representa as cartas que cada jogador tem, podendo ter tamanho maximo de 21 pecas (total - inicial)
  int numPieces; //variavel para saber a quantidadde de cartas na mao de cada jogador
}Jogador;

//struct utilizada para salvar e recuperar jogo
typedef struct{
  int jogadorJogo;
  int jogadorComp;
  int mesaDJogo;
  int mesaEJogo;
  int qtdPecasMesa;
  int qtdPecasDisponivel;
}sitJogo;

//struct para salvar data e hora do Jogo salvo
typedef struct{
	int ano;
  	int mes;
  	int dia;
  	int hora;
 	int minutos;
}dataHora;


Carta domino[28];
Mesa limitesMesa; //guarda o valor das extremidades da mesa para facilitar comparacoes
Mesa mesa[28];
Jogador jogadores[2];
int qtdPecasMesa = 0; //variavel de controle da qtd de pecas que ja foram jogadas na mesa
int qtdPecasDisponivel; //variavel de controle da quantidade de pecas que ainda estao disponiveis para compra
int jogadorAtual; // define de que jogador e' o turno atual
int modoJogo;
int ano = 0, mes, dia, hora, minutos;
sitJogo sitSalva;
dataHora dataSalvo;
int ultCompra[2] = {-2,-2};
int ultJogada[2] = {-2,-2};
int ultimaPecaA = -8;
int ultimaPecaB = -8;
int motVitoria = 0;
void criarCarta(Carta domino[NUM_PECAS]);
void iniciaMesa(Mesa mesa[28]);



#endif

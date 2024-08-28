#include "Dom_BGLL_Projeto_Controller.cpp"


int main(){
  srand( (unsigned)time(0) );
  int carta;

  criarCarta(domino);
  embaralharPecas(domino);
  iniciaMesa(mesa);//incia antes de pedir a quantidade de jogadores

  int numPlayer = playerNumber();//Variavel para a chamada da funcao playerNumber()

  pieceGiveAway(domino, players, numPlayer);

  printf("\n");	
  showHandPieces(players, numPlayer);
  printf("\n");

  int firstPlayer = primeiroJogador(players, mesa);//faz passagem por referencia
  jogadorAtual = firstPlayer - 1;
  printf("\n\nA partida começa com o jogador %d com a peca [%d|%d]\n",firstPlayer, mesa[0].ladoE, mesa[0].ladoD);
  
  showHandPieces(players, numPlayer);
  showTablePieces(mesa);
  
  printf("\nfala uma peça ai pai %d\n", jogadorAtual);
  scanf("%d", &carta);
  jogarPeca(mesa, players, jogadorAtual, carta - 1);

  showTablePieces(mesa);
  showHandPieces(players, numPlayer);
  
  printf("\nfala uma peça ai pai %d\n", jogadorAtual);
  scanf("%d", &carta);
  jogarPeca(mesa, players, jogadorAtual, carta - 1);
  
  
  showTablePieces(mesa);
  showHandPieces(players, numPlayer);
  
  printf("\nfala uma peça ai pai %d\n", jogadorAtual);
  scanf("%d", &carta);
  jogarPeca(mesa, players, jogadorAtual, carta - 1);
  
  showTablePieces(mesa);
  showHandPieces(players, numPlayer);

  printf("\nTodas as cartas do jogo\n");
  mostrarCartas(domino);

  return 0;
}
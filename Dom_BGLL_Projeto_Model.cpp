#include "Dom_BGLL_Projeto_Model.h"

void criarCarta(Carta domino[NUM_PECAS]){
  Carta peca;
  int j = 0;

  for(int i = 0; i <= 6; i++){
    for(int k = i; k <= 6; k++){
      peca.ladoA = i;
      peca.ladoB = k;
      peca.pos = j;
      peca.status = '\0';
      domino[j] = peca;
      j++;
    }
  }
}

//Funcao para inciar a mesa como vazia
void iniciaMesa(Mesa mesa[28]){
   mesa[0].ladoE = -7;//-7 e uma sentinela 
   mesa[0].ladoD = -7;
}
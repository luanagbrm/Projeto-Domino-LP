#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
	int ladoA;
	int ladoB;
	int status;
}Carta;

void criarCarta(Carta domino[28]){
	Carta peca;
	int j = 0;
	
	for(int i = 0; i <= 6; i++){
		for(int k = i; k <= 6; k++){
			peca.ladoA = i;
			peca.ladoB = k;
			domino[j] = peca;
			j++;
		}
	}
}



void mostrarCartas(Carta domino[28]){	
	for(int i = 0; i < 28; i++){
	    if(i%7 == 0 )
	        printf("\n");
		printf("[%d | %d]", domino[i].ladoA, domino[i].ladoB);
	}
}

void embaralharPecas(Carta domino[28]){
	Carta peca2;
	int p;
	
	for(int i = 0; i < 28;i++){
		peca2 = domino[i];
		p = rand() % 28;
		domino[i] = domino[p];
		domino[p] = peca2; 
	}
}

int main(){
 	srand( (unsigned)time(0) );
	Carta domino[28];
		
	criarCarta(domino);
	
	mostrarCartas(domino);
	embaralharPecas(domino);
	printf("\n");
	mostrarCartas(domino);
	embaralharPecas(domino);
	printf("\n");
	mostrarCartas(domino);
	
	return 0;
}

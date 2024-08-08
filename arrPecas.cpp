#include <stdio.h>

typedef struct{
	int ladoA;
	int ladoB;
	int status;
}Peca;

void criarPecas(Peca array[28]){
	Peca peca;
	int j = 0;
	
	for(int i = 0; i <= 6; i++){
		for(int k = i; k <= 6; k++){
			peca.ladoA = i;
			peca.ladoB = k;
			array[j] = peca;
			j++;
		}
	}
}

void mostrarPecas(Peca array[28]){	
	for(int i = 0; i < 28; i++){
		printf("[%d | %d]", array[i].ladoA, array[i].ladoB);
	}
}

int main(){
	Peca array[28];
	
	criarPecas(array);
	mostrarPecas(array);
	return 0;
}

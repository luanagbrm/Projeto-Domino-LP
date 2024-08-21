/*
DOM-BGLL - Projeto Dominó - Etapa 2
20/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

 A pasta Model.h contém os dados e estruturas que serão manipulados
*/

typedef struct{
	int ladoA;
	int ladoB;
	int status;
} Carta;

Carta domino[28];

void criarCarta(Carta domino[28]);

void inciaMesa(Mesa mesaDoJogo);

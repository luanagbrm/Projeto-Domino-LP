//O view e responsavel pela visualizacao dos dados


#include "DOM_BGLL_Projeto_View.h"

#include <stdio.h>

int opcao;

//Função para mostrar todas as cartas do jogo
void mostrarCartas(Carta domino[28]){	
	for(int i = 0; i < 28; i++){
	    if(i%7 == 0 )
	        printf("\n"); //Para melhorar a visualização, mostra apenas 7 peças por linha
	    printf("[%d | %d]", domino[i].ladoA, domino[i].ladoB);
	}
}

/*
 //Menu de funcionalidades do jogo
void mostrarMenu(){
	do{
	     printf("\n---------------------------------------\n");
             printf("MENU - Escolha uma opcao: \n");
             printf("1 - Mostrar cartas\n");
             printf("2 - Embaralhar cartas\n");
             printf("3 - Sair\n");
             printf("\n---------------------------------------\n");
	     scanf("%d",&opcao);
        
        
        switch(opcao) 
        {
            case 1:
                mostrarCartas(domino);          erro nessa linha
                printf("\n\nCartas disponiveis do jogo");
		break;
            case 2:
                embaralharPecas(domino);
                mostrarCartas(domino);
                printf("\n\nCartas embaralhadas");
                break;
            case 3:
                printf("Saindo do jogo");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        
    }while(opcao != 3);
}
*/

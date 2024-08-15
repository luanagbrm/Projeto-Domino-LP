/*
DOM-BGLL - Projeto Dominó - Etapa 2
14/08/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos

A Etapa 2 consiste de criar 7 arquivos com a finalidade de separar o projeto de acordo com o Padrao MVC
*/

#include "Dom_BGLL_Projeto_Model.cpp"
#include "Dom_BGLL_Projeto_Controller.cpp"

int main()
{
    criarCarta(domino);
    mostrarCartas(domino);
    printf("\n");
    embaralharPecas(domino);
    mostrarCartas(domino);
    printf("\n");
    embaralharPecas(domino);
    mostrarCartas(domino);
    printf("\n");
    embaralharPecas(domino);
    mostrarCartas(domino);

    return 0;
}

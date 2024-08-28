#include "Dom_BGLL_Projeto_Controller.cpp"


int main() {
    int opcao;

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1:
                iniciaJogo();
                break;
            case 2:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 2);

    return 0;
}
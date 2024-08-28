#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variáveis globais
#define NUM_PECAS 28
#define HAND_PECAS_INICIAL 7
#define HAND_PECAS_MAX 21
#define NUM_JOGADORES 2

// Estrutura sobre as informações de cada carta do dominó
typedef struct {
    int ladoA;
    int ladoB;
    char status;
    int pos;
} Carta;

typedef struct {
    int playedCards;
    int ladoE;
    int ladoD;
} Mesa;

// Estrutura que representa cada jogador 
typedef struct {
    Carta hand[HAND_PECAS_MAX];
    int numPieces;
} Player;

Carta domino[NUM_PECAS];
Mesa limitesMesa;
Mesa mesa[28];
Player players[NUM_JOGADORES];
int index = 0;
int jogadorAtual = 0;

// Função para criar cartas
void criarCarta(Carta domino[NUM_PECAS]) {
    Carta peca;
    int j = 0;

    for (int i = 0; i <= 6; i++) {
        for (int k = i; k <= 6; k++) {
            peca.ladoA = i;
            peca.ladoB = k;
            peca.pos = j;
            peca.status = '\0';
            domino[j] = peca;
            j++;
        }
    }
}

void definirJogadorAtual() {
    jogadorAtual = (jogadorAtual == 0) ? 1 : 0;
}

// Função para mostrar todas as cartas do jogo
void mostrarCartas(Carta domino[NUM_PECAS]) {
    for (int i = 0; i < NUM_PECAS; i++) {
        if (i % 7 == 0)
            printf("\n");
        printf("[%d|%d] --- status: %c \n\n", domino[i].ladoA, domino[i].ladoB, domino[i].status);
    }
}

// Função para embaralhar as cartas
void embaralharPecas(Carta domino[NUM_PECAS]) {
    Carta peca2;
    int p;

    for (int i = 0; i < 28; i++) {
        peca2 = domino[i];
        p = rand() % 28;
        domino[i] = domino[p];
        domino[p] = peca2;
    }
}

// Função para distribuir as peças para os jogadores
void pieceGiveAway(Carta totalPieces[NUM_PECAS], Player players[NUM_JOGADORES], int numPlayers) {
    int pieceAssign = 0;

    for (int i = 0; i < numPlayers; i++) {
        players[i].numPieces = 0;

        for (int k = 0; k < HAND_PECAS_INICIAL && pieceAssign < NUM_PECAS; k++) {
            totalPieces[pieceAssign].status = '1' + i;
            players[i].hand[k] = totalPieces[pieceAssign++];
            players[i].hand[k].pos = pieceAssign - 1;
            players[i].hand[k].status = '1' + i;
            players[i].numPieces++;
        }
    }
}

void removerPecaJogada(Player *player, int pos) {
    for (int i = pos; i < player->numPieces - 1; i++) {
        player->hand[i] = player->hand[i + 1];
    }
    player->numPieces--;
}

int checarJogadaValida(Player players[NUM_JOGADORES], int player, int pos) {
    Carta pecaJogada = players[player].hand[pos];
    int ladoD = limitesMesa.ladoD;
    int ladoE = limitesMesa.ladoE;

    if (index == 0) {
        limitesMesa.ladoE = pecaJogada.ladoA;
        limitesMesa.ladoD = pecaJogada.ladoB;
        return 1;
    }

    if (pecaJogada.ladoA == ladoD) {
        limitesMesa.ladoD = pecaJogada.ladoB;
        return 1;
    } else if (pecaJogada.ladoB == ladoD) {
        limitesMesa.ladoD = pecaJogada.ladoA;
        return 1;
    } else if (pecaJogada.ladoA == ladoE) {
        limitesMesa.ladoE = pecaJogada.ladoB;
        return 1;
    } else if (pecaJogada.ladoB == ladoE) {
        limitesMesa.ladoE = pecaJogada.ladoA;
        return 1;
    }

    return -1;
}

void jogarPeca(Mesa mesa[28], Player players[NUM_JOGADORES], int player, int pos) {
    int validadeJogada = checarJogadaValida(players, player, pos);
    int posicaoOriginal = players[player].hand[pos].pos;

    if (validadeJogada == 1 || (mesa[index].ladoD == -7 && mesa[index].ladoE == -7)) {
        players[player].hand[pos].status = 'M';
        mesa[index].ladoE = players[player].hand[pos].ladoA;
        mesa[index].ladoD = players[player].hand[pos].ladoB;
        domino[posicaoOriginal].status = 'M';
        index++;
    }

    removerPecaJogada(&players[player], pos);
    definirJogadorAtual();
}

int encontrarDupla(Player player[NUM_JOGADORES], Mesa mesa[28]) {
    for (int k = 6; k >= 0; k--) {
        for (int i = 0; i < 7; i++) {
            if ((player[0].hand[i].ladoA == k) && (player[0].hand[i].ladoB == k)) {
                jogarPeca(mesa, player, 0, i);
                return 1;
            }

            if ((player[1].hand[i].ladoA == k) && (player[1].hand[i].ladoB == k)) {
                jogarPeca(mesa, player, 1, i);
                return 2;
            }
        }
    }

    return -1;
}

int encontrarMaior(Player player[NUM_JOGADORES]) {
    int i = 0;

    for (int k = 12; k >= 0; k--) {
        if ((player[0].hand[i].ladoA + player[0].hand[i].ladoB) == k) {
            jogarPeca(mesa, player, 0, i);
            return 1;
        }

        if ((player[1].hand[i].ladoA + player[1].hand[i].ladoB) == k) {
            jogarPeca(mesa, player, 1, i);
            return 1;
        }
    }

    return -1;
}

int primeiroJogador(Player players[NUM_JOGADORES], Mesa mesa[28]) {
    int jogador1 = encontrarDupla(players, mesa);

    if (jogador1 == -1) {
        jogador1 = encontrarMaior(players);
    }

    return jogador1;
}

void showHandPieces(Player players[NUM_JOGADORES], int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        printf("Jogador %d: \n", i + 1);
        for (int k = 0; k < players[i].numPieces; k++) {
            if (players[i].hand[k].status != 'M')
                printf("[%d|%d]", players[i].hand[k].ladoA, players[i].hand[k].ladoB);
        }
        printf("\n");
    }
}

// Função para iniciar a mesa como vazia
void iniciaMesa(Mesa mesa[28]) {
    mesa[0].ladoE = -7;
    mesa[0].ladoD = -7;
}

// Função para comprar cartas caso a peça tenha status '\0', retorna 1 se a peça for comprada e 0 se não há peças para a compra
int buyCards(Carta totalPieces[NUM_PECAS], Player *player, int playerNum) {
    for (int k = 0; k < NUM_PECAS; k++) {
        if (totalPieces[k].status == '\0') {
            player->hand[player->numPieces++] = totalPieces[k];
            totalPieces[k].status = '1' + playerNum;
            printf("\nCompra feita com sucesso\n");
            return 1;
        }
    }

    printf("Nao ha pecas para comprar");
    return 0;
}

// Mostra todas as peças da mesa
void showTablePieces(Mesa mesa[]) {
    printf("\nMesa do Jogo: \n\n");
    printf("-------------------\n");
    for (int k = 0; k < index; k++)
        printf("[%d|%d]", mesa[k].ladoE, mesa[k].ladoD);
    printf("\n-------------------");
    printf("\n");
}

// Função para exibir o menu principal
int exibirMenu() {
    int opcao;
    printf("\n--- Menu Principal ---\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Sair\n");
    printf("\n-------------------\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

// Função para iniciar o jogo
void iniciaJogo() {
    srand(time(NULL));
    criarCarta(domino);
    embaralharPecas(domino);
    pieceGiveAway(domino, players, NUM_JOGADORES);
    iniciaMesa(mesa);
    primeiroJogador(players, mesa);

    int posicaoEscolhida = 0;
    int jogadaValida = 1;

    while (1) {
        showHandPieces(players, NUM_JOGADORES);
        showTablePieces(mesa);

        printf("\nJogador %d, escolha a posicao da sua peca (0 para comprar): ", jogadorAtual + 1);
        scanf("%d", &posicaoEscolhida);

        if (posicaoEscolhida == 0) {
            jogadaValida = buyCards(domino, &players[jogadorAtual], jogadorAtual);
            if (jogadaValida == 1) {
                continue;
            } else {
                break;
            }
        }

        if (posicaoEscolhida <= players[jogadorAtual].numPieces) {
            jogarPeca(mesa, players, jogadorAtual, posicaoEscolhida - 1);
        } else {
            printf("\nJogada invalida. Tente novamente.\n");
        }
    }
}

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

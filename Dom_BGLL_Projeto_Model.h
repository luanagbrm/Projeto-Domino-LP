//Estruturas importatantes que irao serem constantemente usadas tanto no controller quanto no view
typedef struct {
    int ladoA;
    int ladoB;
    int status; 
} Carta;

typedef struct {
    Carta hand[7];  
    int numPieces;  
} Player;

//Prototipo das funcoes utilizadas no model.cpp
void criarCarta(Carta domino[28]);
void embaralharPecas(Carta domino[28]);
void pieceGiveAway(Carta totalPieces[28], Player players[2], int numPlayers);

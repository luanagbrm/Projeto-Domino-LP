/*
DOM-BGLL - Projeto Domino - Etapa 5
10/09/2024 - Grupo:BGLL

Nome dos integrantes:

- Beatriz Lima Morais
- Grazielle Batista de Almeida
- Luana Gabrielle Rodrigues Macedo
- Lucas Ferri dos Santos
*/

#ifndef DOM_BGLL_PROJETO_CONTROLLER_H
#define DOM_BGLL_PROJETO_CONTROLLER_H

#include "Dom_BGLL_Projeto_View.cpp"
#include "Dom_BGLL_Projeto_Model.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>


void gerarSeed();
void jogar();
void definirJogadorAtual();
void embaralharPecas(Carta domino[NUM_PECAS]);
void distribuirPecas(Carta totalPieces[28], Jogador jogadores[NUM_JOGADORES], int numJogadores);
int menuJogador(Jogador jogadores[NUM_JOGADORES], Carta domino[NUM_PECAS]);
void removerPecaJogada(Jogador *jogador, int pos);
int checarJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos);
int encontrarDupla(Jogador jogador[NUM_JOGADORES], Mesa mesa[28]);
int encontrarMaior(Jogador jogador[NUM_JOGADORES]);
int primeiroJogador(Jogador jogadores[NUM_JOGADORES], Mesa mesa[28]);
int comprarCartas(Carta totalPieces[NUM_PECAS], Jogador *jogador, int jogadorNum);
int numeroJogadores(void);
void jogarLadoEsquerdo(Mesa mesa[]);
void jogarPeca(Mesa mesa[28], Jogador jogadores[NUM_JOGADORES], int jogador, int pos, char lado);
void fclearBuffer();
void inverterPeca(Jogador jogadores[NUM_JOGADORES], int numJogador, int pos);
int verificarJogada(Mesa mesa[], Jogador jogadores[NUM_JOGADORES], int pos);
int checarLadoValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos, int lado);
int checarUnicaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos);
int qtdJogadaValida(Jogador jogadores[NUM_JOGADORES], int jogador, int pos);
int verificarPassarVez();
void passarVez();
int somarValorPecas();
int verificarVencedorJogoFechado();
int verificarJogoFechado();
int verificarMaoVazia();
void verificarOpcaoUsuario(int opcao);
int salvarJogo();
int salvarPecas();
int salvarMesa();
int salvarSitJogo();
int recuperarJogo();
int continuarJogo();
int jogoSalvo();
int novoJogo();
void vezDoPc(Jogador jogadores[NUM_JOGADORES], int jogador);
int recuperarJogoPecas();
int recuperarJogoMesa();
int recuperarSitJogo();
int definirPecasCadaJogador(Carta domino[28]);
int definirSitVariaveis();
int armazenarDataHora();

#endif

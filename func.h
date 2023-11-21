#ifndef FUNC_H
#define FUNC_H
#include "func_rank.c"
#include "func_jogo.c"
#include "func_aux.c"
void menu();
void limpaBuffer();
void limparTerminal();
void exibirCreditos();
void carregarRanking();
void exibirRanking();
void atualizaArquivoRanking();
void gravaVencedor(char vencedor[]);
int verificarVitoriaProxima(char jogo[3][3], char jogador, int* linha, int* coluna);
char* novoJogoComPessoas(char jogador1[], char jogador2[]);
char* novoJogoContraComputador(char jogador[]);
int verificarVitoriaProxima(char jogo[3][3], char jogador, int* linha, int* coluna);

#endif // FUNC_H
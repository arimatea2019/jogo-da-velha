#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


// Protótipos das funções
int verificarVitoriaProxima(char jogo[3][3], char jogador, int* linha, int* coluna) {
    // Verifica linhas
    for (int i = 0; i < 3; i++) {
        if (jogo[i][0] == jogador && jogo[i][1] == jogador && jogo[i][2] == ' ') {
            *linha = i;
            *coluna = 2;
            return 1;
        } else if (jogo[i][0] == jogador && jogo[i][2] == jogador && jogo[i][1] == ' ') {
            *linha = i;
            *coluna = 1;
            return 1;
        } else if (jogo[i][1] == jogador && jogo[i][2] == jogador && jogo[i][0] == ' ') {
            *linha = i;
            *coluna = 0;
            return 1;
        }
    }

    // Verifica colunas
    for (int j = 0; j < 3; j++) {
        if (jogo[0][j] == jogador && jogo[1][j] == jogador && jogo[2][j] == ' ') {
            *linha = 2;
            *coluna = j;
            return 1;
        } else if (jogo[0][j] == jogador && jogo[2][j] == jogador && jogo[1][j] == ' ') {
            *linha = 1;
            *coluna = j;
            return 1;
        } else if (jogo[1][j] == jogador && jogo[2][j] == jogador && jogo[0][j] == ' ') {
            *linha = 0;
            *coluna = j;
            return 1;
        }
    }

    // Verifica diagonais
    if (jogo[0][0] == jogador && jogo[1][1] == jogador && jogo[2][2] == ' ') {
        *linha = 2;
        *coluna = 2;
        return 1;
    } else if (jogo[0][0] == jogador && jogo[2][2] == jogador && jogo[1][1] == ' ') {
        *linha = 1;
        *coluna = 1;
        return 1;
    } else if (jogo[1][1] == jogador && jogo[2][2] == jogador && jogo[0][0] == ' ') {
        *linha = 0;
        *coluna = 0;
        return 1;
    } else if (jogo[0][2] == jogador && jogo[1][1] == jogador && jogo[2][0] == ' ') {
        *linha = 2;
        *coluna = 0;
        return 1;
    } else if (jogo[0][2] == jogador && jogo[2][0] == jogador && jogo[1][1] == ' ') {
        *linha = 1;
        *coluna = 1;
        return 1;
    } else if (jogo[1][1] == jogador && jogo[2][0] == jogador && jogo[0][2] == ' ') {
        *linha = 0;
        *coluna = 2;
        return 1;
    }

    return 0; // O computador não pode vencer na próxima jogada
}

char* novoJogoComPessoas(char jogador1[], char jogador2[]) {
    int l, c, linha, coluna, jogador, ganhou, jogadas;
    int opcao;
    char jogo[3][3];

    do {
        jogador = 1;
        ganhou = 0;
        jogadas = 0;

        for (l = 0; l < 3; l++) {
            for (c = 0; c < 3; c++) {
                jogo[l][c] = ' ';
            }
        }

        do {
            printf("\n\n\t A   B   C\n\n");

            for (l = 0; l < 3; l++) {
                for (c = 0; c < 3; c++) {
                    if (c == 0)
                        printf("\t");
                    printf(" %c ", jogo[l][c]);
                    if (c < 2)
                        printf("|");
                    if (c == 2)
                        printf("  %d", l);
                }

                if (l < 2)
                    printf("\n\t-----------");

                printf("\n");
            }

            do {
                printf("\n%s = 0\n%s = X\n", jogador1, jogador2);
                printf("\n%s: Digite a linha e a coluna que deseja jogar (por exemplo, A0): ", (jogador == 1) ? jogador1 : jogador2);
                char entrada[4];
                scanf("%s", entrada);

                // Verifique se o jogador digitou "sair"
                if (strcasecmp(entrada, "sair") == 0) {
                    printf("\nJogo encerrado a pedido do jogador.\n");
                    return NULL;
                }

                char coluna_char = toupper(entrada[0]);
                linha = entrada[1] - '0';
                coluna = coluna_char - 'A';

                if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != ' ') {
                    printf("Coordenadas inválidas. Por favor, digite novamente.\n");
                }
            } while (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != ' ');

            if (jogador == 1) {
                jogo[linha][coluna] = '0';
                jogador++;
            } else {
                jogo[linha][coluna] = 'X';
                jogador = 1;
            }
            jogadas++;

            if (jogo[0][0] == '0' && jogo[0][1] == '0' && jogo[0][2] == '0' ||
                jogo[1][0] == '0' && jogo[1][1] == '0' && jogo[1][2] == '0' ||
                jogo[2][0] == '0' && jogo[2][1] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu por linha!\n", jogador1);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[0][1] == 'X' && jogo[0][2] == 'X' ||
                jogo[1][0] == 'X' && jogo[1][1] == 'X' && jogo[1][2] == 'X' ||
                jogo[2][0] == 'X' && jogo[2][1] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! %s venceu por linha!\n", jogador2);
                ganhou = 2;
            }

            if (jogo[0][0] == '0' && jogo[1][0] == '0' && jogo[2][0] == '0' ||
                jogo[0][1] == '0' && jogo[1][1] == '0' && jogo[2][1] == '0' ||
                jogo[0][2] == '0' && jogo[1][2] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu por coluna!\n", jogador1);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[1][0] == 'X' && jogo[2][0] == 'X' ||
                jogo[0][1] == 'X' && jogo[1][1] == 'X' && jogo[2][1] == 'X' ||
                jogo[0][2] == 'X' && jogo[1][2] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! %s venceu por coluna!\n", jogador2);
                ganhou = 2;
            }

            if (jogo[0][0] == '0' && jogo[1][1] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu na diag. principal!\n", jogador1);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[1][1] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! %s venceu na diag. principal!\n", jogador2);
                ganhou = 2;
            }

            if (jogo[0][2] == '0' && jogo[1][1] == '0' && jogo[2][0] == '0') {
                printf("\nParabens! %s venceu na diag. secundaria!\n", jogador1);
                ganhou = 1;
            }

            if (jogo[0][2] == 'X' && jogo[1][1] == 'X' && jogo[2][0] == 'X') {
                printf("\nParabens! %s venceu na diag. secundaria!\n", jogador2);
                ganhou = 2;
            }
        } while (ganhou == 0 && jogadas < 9);

        printf("\n\n\t A   B   C\n\n");
        for (l = 0; l < 3; l++) {
            for (c = 0; c < 3; c++) {
                if (c == 0)
                    printf("\t");
                printf(" %c ", jogo[l][c]);
                if (c < 2)
                    printf("|");
                if (c == 2)
                    printf("  %d", l);
            }
            if (l < 2)
                printf("\n\t-----------");
            printf("\n");
        }

        // Grava o vencedor no arquivo de ranking
        if (ganhou != 0) {
            if (ganhou == 1) {
                gravaVencedor(jogador1);
            } else {
                gravaVencedor(jogador2);
            }
        } else {
            printf("\nO jogo finalizou sem ganhador!\n");
        }
        limpaBuffer();
        printf("\nDigite 1 para jogar novamente ou qualquer outra tecla para sair: ");
        scanf("%d", &opcao);

    } while (opcao == 1);

    return NULL;
}

// Função para jogar contra o computador
char* novoJogoContraComputador(char jogador[]) {
    int l, c, linha, coluna, jogadorAtual, ganhou, jogadas;
    int opcao;
    char jogo[3][3];

    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    do {
        jogadorAtual = 1;
        ganhou = 0;
        jogadas = 0;

        for (l = 0; l < 3; l++) {
            for (c = 0; c < 3; c++) {
                jogo[l][c] = ' ';
            }
        }

        do {
            printf("\n\n\t A   B   C\n\n");

            for (l = 0; l < 3; l++) {
                for (c = 0; c < 3; c++) {
                    if (c == 0)
                        printf("\t");
                    printf(" %c ", jogo[l][c]);
                    if (c < 2)
                        printf("|");
                    if (c == 2)
                        printf("  %d", l);
                }

                if (l < 2)
                    printf("\n\t-----------");

                printf("\n");
            }

            if (jogadorAtual == 1) {
                // Vez do jogador humano
                do {
                    printf("\n%s = 0\nComputador = X\n", jogador);
                    printf("\n%s: Digite a linha e a coluna que deseja jogar (por exemplo, A0) ou 'sair' para encerrar: ", jogador);
                    char entrada[10];
                    scanf("%s", entrada);

                    // Verifique se o jogador digitou "sair"
                    if (strcasecmp(entrada, "sair") == 0) {
                        printf("\nJogo encerrado a pedido do jogador.\n");
                        return NULL;
                    }

                    char coluna_char = toupper(entrada[0]);
                    linha = entrada[1] - '0';
                    coluna = coluna_char - 'A';

                    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != ' ') {
                        printf("Coordenadas inválidas. Por favor, digite novamente.\n");
                    }
                } while (linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || jogo[linha][coluna] != ' ');
            } else {
                // Vez do computador
                if (verificarVitoriaProxima(jogo, 'X', &linha, &coluna)) {
                    // Se o computador pode vencer na próxima jogada, faça essa jogada
                    printf("Computador escolheu a posição %c%d\n", 'A' + coluna, linha);
                } else if (verificarVitoriaProxima(jogo, '0', &linha, &coluna)) {
                    // Se o jogador pode vencer na próxima jogada, bloqueie-o
                    printf("Computador bloqueou o jogador em %c%d\n", 'A' + coluna, linha);
                } else {
                    // Caso contrário, faça uma jogada aleatória
                    do {
                        linha = rand() % 3;
                        coluna = rand() % 3;
                    } while (jogo[linha][coluna] != ' ');

                    printf("Computador escolheu a posição %c%d\n", 'A' + coluna, linha);
                }
            }

            // Atualiza o tabuleiro com a jogada
            if (jogadorAtual == 1) {
                jogo[linha][coluna] = '0';
            } else {
                jogo[linha][coluna] = 'X';
            }
            jogadas++;

            // Verifica se alguém ganhou
            if (jogo[0][0] == '0' && jogo[0][1] == '0' && jogo[0][2] == '0' ||
                jogo[1][0] == '0' && jogo[1][1] == '0' && jogo[1][2] == '0' ||
                jogo[2][0] == '0' && jogo[2][1] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu por linha!\n", jogador);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[0][1] == 'X' && jogo[0][2] == 'X' ||
                jogo[1][0] == 'X' && jogo[1][1] == 'X' && jogo[1][2] == 'X' ||
                jogo[2][0] == 'X' && jogo[2][1] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! Computador venceu por linha!\n");
                ganhou = 2;
            }

            if (jogo[0][0] == '0' && jogo[1][0] == '0' && jogo[2][0] == '0' ||
                jogo[0][1] == '0' && jogo[1][1] == '0' && jogo[2][1] == '0' ||
                jogo[0][2] == '0' && jogo[1][2] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu por coluna!\n", jogador);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[1][0] == 'X' && jogo[2][0] == 'X' ||
                jogo[0][1] == 'X' && jogo[1][1] == 'X' && jogo[2][1] == 'X' ||
                jogo[0][2] == 'X' && jogo[1][2] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! Computador venceu por coluna!\n");
                ganhou = 2;
            }

            if (jogo[0][0] == '0' && jogo[1][1] == '0' && jogo[2][2] == '0') {
                printf("\nParabens! %s venceu na diag. principal!\n", jogador);
                ganhou = 1;
            }

            if (jogo[0][0] == 'X' && jogo[1][1] == 'X' && jogo[2][2] == 'X') {
                printf("\nParabens! Computador venceu na diag. principal!\n");
                ganhou = 2;
            }

            if (jogo[0][2] == '0' && jogo[1][1] == '0' && jogo[2][0] == '0') {
                printf("\nParabens! %s venceu na diag. secundaria!\n", jogador);
                ganhou = 1;
            }

            if (jogo[0][2] == 'X' && jogo[1][1] == 'X' && jogo[2][0] == 'X') {
                printf("\nParabens! Computador venceu na diag. secundaria!\n");
                ganhou = 2;
            }

            // Alterna entre jogador e computador
            jogadorAtual = 3 - jogadorAtual;

        } while (ganhou == 0 && jogadas < 9);

        printf("\n\n\t A   B   C\n\n");
        for (l = 0; l < 3; l++) {
            for (c = 0; c < 3; c++) {
                if (c == 0)
                    printf("\t");
                printf(" %c ", jogo[l][c]);
                if (c < 2)
                    printf("|");
                if (c == 2)
                    printf("  %d", l);
            }
            if (l < 2)
                printf("\n\t-----------");
            printf("\n");
        }

        // Grava o vencedor no arquivo de ranking
        if (ganhou != 0) {
            if (ganhou == 1) {
                gravaVencedor(jogador);
            } else {
                gravaVencedor("Computador");
            }
        } else {
            printf("\nO jogo finalizou sem ganhador!\n");
        }
        limpaBuffer();
        printf("\nDigite 1 para jogar novamente ou qualquer outra tecla para sair: ");
        scanf("%d", &opcao);
        

    } while (opcao == 1);

    return NULL;
}
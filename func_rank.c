#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// Inclui a biblioteca apropriada para manipulação do terminal, dependendo do sistema operacional
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#define MAX_JOGADORES 50// Define o limite de jogadores

// Estrutura para armazenar informações sobre um jogador
typedef struct {
    char nome[50];
    int vitorias;
} Jogador;

Jogador jogadores[MAX_JOGADORES];  // Variável global para armazenar os jogadores
int totalJogadores = 0; // Variável global para armazenar o total de jogadores

void carregarRanking() {
    FILE *arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL) {
        printf("Ranking nao encontrado.\n");
        return;
    }

    int i = 0;

    while (fscanf(arquivo, "%49s", jogadores[i].nome) == 1 && i < 10) {
        i++;
    }

    fclose(arquivo);

    totalJogadores = i;
}

void exibirRanking() {
    printf("\n=== Ranking ===\n");
    FILE *arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL) {
        printf("Ranking vazio, atualizando ranking.\n");
        
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        fflush(stdout);

#ifdef _WIN32
        Sleep(100);
#else
        usleep(50000);
#endif
    }
    
    fclose(arquivo);

    // Pergunta se deseja atualizar o ranking e voltar ao menu principal
    printf("\nDeseja atualizar o ranking? (S/N): ");
    char resposta[2];
    scanf("%1s", resposta);

    if (toupper(resposta[0]) == 'S') {
        // Atualiza o arquivo de ranking
        atualizaArquivoRanking();
        exibirRanking();
    } else if (toupper(resposta[0]) != 'N') {
        // Tratamento de entrada inválida
        printf("Entrada invalida. Por favor, insira 'S' para sim ou 'N' para não.\n");
        exibirRanking(); // Chama a função novamente para nova entrada
        return;
    }

    // Retorna ao menu principal
    printf("\nPressione qualquer tecla para voltar ao menu principal.\n");
    limpaBuffer();
    getchar();
    limparTerminal();
    menu();// Chamada para a função do menu principal
}

// Função para gravar o vencedor no arquivo de ranking
void gravaVencedor(char vencedor[]) {
     // Verifica se o jogador já está na lista
    int jogadorEncontrado = -1;
    for (int i = 0; i < totalJogadores; ++i) {
        if (strcmp(jogadores[i].nome, vencedor) == 0) {
            jogadorEncontrado = i;
            break;
        }
    }

    // Se o jogador já existe na lista, atualiza suas vitórias
    if (jogadorEncontrado != -1) {
        jogadores[jogadorEncontrado].vitorias++;
    } else {
        // Se não existe na lista, verifica se há espaço para adicionar um novo jogador
        if (totalJogadores < MAX_JOGADORES) {
            // Cria um novo jogador com o nome do vencedor e uma vitória
            strcpy(jogadores[totalJogadores].nome, vencedor);
            jogadores[totalJogadores].vitorias = 1;
            totalJogadores++;
        } else {
            printf("Limite de jogadores atingido.\n");
            return;
        }
    }
}

void atualizaArquivoRanking() {
    FILE *arquivo;
    arquivo = fopen("ranking.txt", "a+"); // Abre o arquivo para leitura e escrita (cria se não existir)

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de ranking.\n");
        exit(1);
    }

    // Verifica se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);

    if (tamanho == 0) {
        // Se o arquivo está vazio, escreve os jogadores nele
        for (int i = 0; i < totalJogadores; ++i) {
            fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].vitorias);
        }
    } else {
        // Se não está vazio, faz a atualização dos jogadores
        for (int i = 0; i < totalJogadores; ++i) {
            char linha[100];
            int jogadorEncontrado = 0;

            rewind(arquivo); // Volta ao início do arquivo

            // Procura o jogador atual no arquivo
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                char nomeArquivo[50];
                int vitoriasArquivo;
                sscanf(linha, "%s %d", nomeArquivo, &vitoriasArquivo);

                if (strcmp(jogadores[i].nome, nomeArquivo) == 0) {
                    // Se o jogador já existe, atualiza suas vitórias
                    fseek(arquivo, -(strlen(linha) + 1), SEEK_CUR); // Volta para o início da linha
                    fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].vitorias);
                    jogadorEncontrado = 1;
                    break;
                }
            }

            // Se não encontrou o jogador no arquivo, adiciona-o
            if (!jogadorEncontrado) {
                fprintf(arquivo, "%s %d\n", jogadores[i].nome, jogadores[i].vitorias);
            }
        }
    }

    fclose(arquivo);
}


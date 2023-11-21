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

// Função para limpar o buffer de entrada
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para limpar o terminal
void limparTerminal() {
#ifdef _WIN32
    system("cls");  // Comando para limpar o terminal no Windows
#else
    system("clear");  // Comando para limpar o terminal em sistemas Unix/Linux (incluindo MacOS)
#endif
}

// Função para exibir os créditos a partir do arquivo "creditos.txt"
void exibirCreditos() {
    // Abre o arquivo "creditos.txt" em modo leitura
    FILE *arquivo = fopen("creditos.txt", "r");
    
    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de créditos.\n");
        return;
    }

    printf("\n=== Créditos ===\n");

    // Lê cada linha do arquivo e imprime na tela
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        
        // Garante que a saída seja imediatamente exibida
        fflush(stdout);

        // Adiciona uma pequena pausa para a leitura do arquivo ser mais visível
#ifdef _WIN32
        Sleep(100);  // Pausa para sistemas Windows
#else
        usleep(50000);  // Pausa para sistemas Unix (Linux, macOS)
#endif
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    // Exibe uma mensagem e aguarda o usuário pressionar qualquer tecla para sair
    printf("\nPressione qualquer tecla para voltar ao menu\n");

    // Limpa o buffer de entrada
    limpaBuffer();
    // Aguarda o usuário pressionar qualquer tecla
    getchar();
    limparTerminal();
    menu();
}

//menu principal
void menu() {
    int escolha;

    do {
        carregarRanking();
        // Imprime o título do menu
        printf("\n=== Jogo da Velha ===\n");
        // Imprime as opções do menu
        printf("1. Novo Jogo\n");
        printf("2. Ranking\n");
        printf("3. Créditos\n"); // Nova opção
        printf("0. Sair\n");

        // Solicita a escolha do usuário
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                int modoJogo;
                printf("\nEscolha o modo de jogo:\n");
                printf("1. Jogar com outra pessoa\n");
                printf("2. Jogar contra o computador\n");
                scanf("%d", &modoJogo);
                limparTerminal();  // Chama uma função para limpar o terminal

                if (modoJogo == 1) {
                    char jogador1[50], jogador2[50];
                    printf("Digite o nome do Jogador 1: ");
                    scanf("%s", jogador1);
                    printf("Digite o nome do Jogador 2: ");
                    scanf("%s", jogador2);
                    char* vencedor = novoJogoComPessoas(jogador1, jogador2);
                    
                } else if (modoJogo == 2) {
                    char jogador[50];
                    printf("Digite o seu nome: ");
                    scanf("%s", jogador);
                    char* vencedor = novoJogoContraComputador(jogador);
                    
                } else {
                    printf("Opcao invalida. Tente novamente.\n");
                }
                break;
            }
            case 2:
                exibirRanking();  // Chama a função para exibir o ranking
                break;
            case 3:
                exibirCreditos(); // Chama a função para exibir créditos
                break;
            case 0:
                printf("Salvando o ranking!\n");
                atualizaArquivoRanking();
                printf("Saindo do Jogo da Velha. Ate logo!\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                
        }

    } while (escolha != 0);  // Continua o loop do menu enquanto a escolha do usuário for diferente de 0
}
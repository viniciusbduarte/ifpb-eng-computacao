#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Define as dimensões do campo de jogo
#define LARGURA 60
#define ALTURA 20

// Estrutura que representa um nó da cobra
typedef struct No {
    int x, y;           // Coordenadas do nó
    struct No *proximo; // Ponteiro para o próximo nó
} No;

// Variáveis globais
No *cabeca = NULL, *cauda = NULL; // Ponteiros para a cabeça e cauda da cobra
int comidaX, comidaY;             // Coordenadas da comida
int jogoAcabou = 0;               // Flag para indicar se o jogo acabou
int direcao = 'd';                // Direção inicial da cobra (direita)
int pontuacao = 0;                // Pontuação atual
int recorde = 0;                  // Recorde de pontuação

// Função para gerar a comida em uma posição aleatória
void gerarComida() {
    comidaX = (rand() % (LARGURA - 2)) + 1;
    comidaY = (rand() % (ALTURA - 2)) + 1;
}

// Função para inicializar a cobra no centro do campo
void iniciarCobra() {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->x = LARGURA / 2;
    novoNo->y = ALTURA / 2;
    novoNo->proximo = NULL;
    cabeca = cauda = novoNo;
    gerarComida();
    jogoAcabou = 0;
    direcao = 'd';
    pontuacao = 0;
}

// Função para mover a cobra na direção atual
void moverCobra() {
    int novoX = cabeca->x, novoY = cabeca->y;

    // Calcula a nova posição da cabeça da cobra
    if (direcao == 'w') novoY--;
    else if (direcao == 's') novoY++;
    else if (direcao == 'a') novoX--;
    else if (direcao == 'd') novoX++;

    // Verifica se a cobra colidiu com as paredes
    if (novoX <= 0 || novoX >= LARGURA - 1 || novoY <= 0 || novoY >= ALTURA - 1) {
        jogoAcabou = 1;
        return;
    }

    // Verifica se a cobra colidiu consigo mesma
    No *temp = cabeca;
    while (temp) {
        if (temp->x == novoX && temp->y == novoY) {
            jogoAcabou = 1;
            return;
        }
        temp = temp->proximo;
    }

    // Cria um novo nó para a nova cabeça da cobra
    No *novaCabeca = (No *)malloc(sizeof(No));
    novaCabeca->x = novoX;
    novaCabeca->y = novoY;
    novaCabeca->proximo = cabeca;
    cabeca = novaCabeca;

    // Verifica se a cobra comeu a comida
    if (novoX == comidaX && novoY == comidaY) {
        pontuacao++;
        gerarComida();
    } else {
        // Remove o último nó da cobra (cauda) se não comeu a comida
        temp = cabeca;
        while (temp->proximo->proximo) {
            temp = temp->proximo;
        }
        free(temp->proximo);
        temp->proximo = NULL;
        cauda = temp;
    }
}

// Função para desenhar a cobra em ASCII (tela inicial)
void desenharCobraASCII() {
    printf("\n\n           /^\\/^\\\n");
    printf("           _|__|  O|\n");
    printf("    /\\     /~     \\_/ \\\n");
    printf("    \\____|__________/  \\\n");
    printf("           \\_______      \\\n");
    printf("                   `\\     \\                 \\\n");
    printf("                     |     |                  \\\n");
    printf("                    /      /                    \\\n");
    printf("                   /     /                       \\\\\n");
    printf("                 /      /                         \\ \\\n");
    printf("                /     /                            \\  \\\n");
    printf("              /     /             _----_            \\   \\\n");
    printf("             /     /           _-~      ~-_         |   |\n");
    printf("            (      (        _-~    _--_    ~-_     _/   |\n");
    printf("             \\      ~-____-~    _-~    ~-_    ~-_-~    /\n");
    printf("               ~-_           _-~          ~-_       _-~\n");
    printf("                  ~--______-~                ~-___-~\n");
    printf("\n\n                        THE SNAKE GAME\n");
}

// Função para desenhar o campo de jogo, a cobra e a comida
void desenhar() {
    system("cls");

    // Exibe a pontuação e o recorde no topo da tela
    for (int i=0; i <LARGURA; i++)printf("#");
    printf("\n");
    for (int i=0; i <LARGURA/4; i++)printf(" ");
    printf("Pontos: %d   |   Recorde: %d\n", pontuacao, recorde);

    // Desenha o campo de jogo
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1) {
                printf("#"); // Desenha as paredes
            } else if (i == comidaY && j == comidaX) {
                printf("*"); // Desenha a comida
            } else {
                int ehCorpo = 0;
                No *temp = cabeca;
                while (temp) {
                    if (temp->x == j && temp->y == i) {
                        printf("O"); // Desenha a cobra
                        ehCorpo = 1;
                        break;
                    }
                    temp = temp->proximo;
                }
                if (!ehCorpo) {
                    // Exibe o "GAME OVER" dentro do campo
                    if (jogoAcabou) {
                        int centroX = (LARGURA - 25) / 2;
                        int centroY = ALTURA / 2 - 4;
                        if (i == centroY && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 1 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#       GAME OVER       #"[j - centroX]);
                        } else if (i == centroY + 2 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 4 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else if (i == centroY + 5 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#  PLAY AGAIN? (s/n)    #"[j - centroX]);
                        } else if (i == centroY + 6 && j >= centroX && j < centroX + 25) {
                            printf("%c", "#########################"[j - centroX]);
                        } else {
                            printf(" ");
                        }
                    } else {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
}

// Função para capturar a entrada do usuário e alterar a direção da cobra
void entrada() {
    if (_kbhit()) {
        char tecla = _getch();
        if ((tecla == 'w' && direcao != 's') ||
            (tecla == 's' && direcao != 'w') ||
            (tecla == 'a' && direcao != 'd') ||
            (tecla == 'd' && direcao != 'a')) {
            direcao = tecla;
        }
    }
}

// Função para exibir a tela de pré-jogo com animações
void PreJogo(){
    system("cls");
    desenharCobraASCII();
    Sleep(1000);
    system("cls");
    printf("  ####\n ##  ##\n     ##\n   ###\n     ##\n ##  ##\n  ####\n");
    Sleep(1000);
    system("cls");
    printf(" ####\n ##  ##\n     ##\n   ###\n  ##\n ##  ##\n ######\n");
    Sleep(1000);
    system("cls");
    printf("  ##\n ###\n  ##\n  ##\n  ##\n  ##\n######\n");
    Sleep(1000);
    system("cls");
    printf("  ####     ####      ##\n ##  ##   ##  ##     ##\n ##       ##  ##     ##\n ## ###   ##  ##     ##\n ##  ##   ##  ##\n ##  ##   ##  ##\n  ####     ####      ##\n");
    Sleep(1000);
}

// Função para liberar a memória alocada para a cobra
void limparCobra() {
    No *temp;
    while (cabeca) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

// Função principal
int main() {
    char opcao;
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    do {
        PreJogo(); // Exibe a tela de pré-jogo
        iniciarCobra(); // Inicializa a cobra e a comida
        while (!jogoAcabou) {
            desenhar(); // Desenha o campo de jogo
            entrada(); // Captura a entrada do usuário
            moverCobra(); // Move a cobra
            Sleep(100); // Pausa para controlar a velocidade do jogo
        }
        if (pontuacao > recorde) {
            recorde = pontuacao; // Atualiza o recorde se necessário
        }
        desenhar(); // Desenha a tela final do jogo
        opcao = _getch(); // Captura a opção do usuário para jogar novamente ou sair
        limparCobra(); // Libera a memória alocada para a cobra
    } while (opcao == 's' || opcao == 'S'); // Repete o jogo se o usuário escolher jogar novamente
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LARGURA 60
#define ALTURA 25

// Estrutura para representar a posição da cobra
typedef struct No {
    int x, y;
    struct No *proximo;
} No;

No *cabeca = NULL, *cauda = NULL;
int comidaX, comidaY, jogoAcabou = 0, direcao = 'd';

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gerarComida() {
    comidaX = (rand() % (LARGURA - 2)) + 1;
    comidaY = (rand() % (ALTURA - 2)) + 1;
}

void iniciarCobra() {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->x = LARGURA / 2;
    novoNo->y = ALTURA / 2;
    novoNo->proximo = NULL;
    cabeca = cauda = novoNo;
    gerarComida();
    jogoAcabou = 0;
    direcao = 'd';
}

void moverCobra() {
    int novoX = cabeca->x, novoY = cabeca->y;
    if (direcao == 'w') novoY--;
    else if (direcao == 's') novoY++;
    else if (direcao == 'a') novoX--;
    else if (direcao == 'd') novoX++;

    // Verifica colisão com as bordas
    if (novoX <= 0 || novoX >= LARGURA - 1 || novoY <= 0 || novoY >= ALTURA - 1) {
        jogoAcabou = 1;
        return;
    }

    // Verifica colisão com o próprio corpo
    No *temp = cabeca;
    while (temp) {
        if (temp->x == novoX && temp->y == novoY) {
            jogoAcabou = 1;
            return;
        }
        temp = temp->proximo;
    }

    // Move a cobra
    No *novaCabeca = (No *)malloc(sizeof(No));
    novaCabeca->x = novoX;
    novaCabeca->y = novoY;
    novaCabeca->proximo = cabeca;
    cabeca = novaCabeca;

    // Se a cobra não comer a comida, remove o último segmento
    if (novoX == comidaX && novoY == comidaY) {
        gerarComida();
    } else {
        temp = cabeca;
        while (temp->proximo->proximo) {
            temp = temp->proximo;
        }
        free(temp->proximo);
        temp->proximo = NULL;
        cauda = temp;
    }
}

void desenhar() {
    system("cls");
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1) {
                printf("#");
            } else if (i == comidaY && j == comidaX) {
                printf("*");
            } else {
                int ehCorpo = 0;
                No *temp = cabeca;
                while (temp) {
                    if (temp->x == j && temp->y == i) {
                        printf("O");
                        ehCorpo = 1;
                        break;
                    }
                    temp = temp->proximo;
                }
                if (!ehCorpo) printf(" ");
            }
        }
        printf("\n");
    }
}

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

void limparCobra() {
    No *temp;
    while (cabeca) {
        temp = cabeca;
        cabeca = cabeca->proximo;
        free(temp);
    }
}

int main() {
    char opcao;
    srand(time(NULL));
    do {
        iniciarCobra();
        while (!jogoAcabou) {
            desenhar();
            entrada();
            moverCobra();
            Sleep(100);
        }
        desenhar();
        printf("Game Over!\n");
        printf("Deseja jogar novamente? (s/n): ");
        opcao = _getch();
        limparCobra();
    } while (opcao == 's' || opcao == 'S');
    return 0;
}

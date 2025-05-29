#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

// Inicializa o tabuleiro com 0 e adiciona alguns navios (valor 3)
void inicializarTabuleiro() {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Exemplo de navios
    tabuleiro[2][2] = 3;
    tabuleiro[3][3] = 3;
    tabuleiro[4][4] = 3;
}

// Imprime o tabuleiro
void exibirTabuleiro() {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Cria matriz cone (forma piramidal apontando para baixo)
void criarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            if (j >= centro - i && j <= centro + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz cruz
void criarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            if (i == centro || j == centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz octaedro (forma de losango)
void criarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica uma habilidade no tabuleiro com base em uma matriz de habilidade e ponto de origem
void aplicarHabilidade(int matriz[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO &&
                    tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = 5;  // Marca como área de habilidade
                }
            }
        }
    }
}

// Função principal
int main() {
    inicializarTabuleiro();

    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(cone, 2, 2);       // Aplicar cone em (2,2)
    aplicarHabilidade(cruz, 6, 6);       // Aplicar cruz em (6,6)
    aplicarHabilidade(octaedro, 4, 7);   // Aplicar octaedro em (4,7)

    exibirTabuleiro();

    return 0;
}

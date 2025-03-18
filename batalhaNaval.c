#include <math.h>
#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define TAMANHO_HABILIDADE 5

int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro Nivel Aventureiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio pode ser posicionado
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (direcao == 1 ? i : 0);  // Direção vertical
        int c = coluna + (direcao == 0 ? i : 0); // Direção horizontal
        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != AGUA) {
            return 0; // Fora dos limites ou posição ocupada
        }
    }
    return 1;
}

// Função para posicionar o navio horizontal/vertical
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (direcao == 1 ? i : 0);
        int c = coluna + (direcao == 0 ? i : 0);
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para verificar se o navio diagonal pode ser posicionado
int podePosicionarDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = direcao == 0 ? coluna + i : coluna - i;
        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO || c < 0 || tabuleiro[l][c] != AGUA) {
            return 0; // Fora dos limites ou posição ocupada
        }
    }
    return 1;
}

// Função para posicionar o navio diagonal
void posicionarNavioDiagonal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + i;
        int c = direcao == 0 ? coluna + i : coluna - i;
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro Nivel Mestre:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf("0 "); // Água
            else if (tabuleiro[i][j] == 3)
                printf("3 "); // Navio
            else if (tabuleiro[i][j] == 5)
                printf("5 "); // Área afetada por habilidade
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar uma matriz em forma de cone
void criarCone(int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Função para criar uma matriz em forma de cruz
void criarCruz(int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Função para criar uma matriz em forma de octaedro (losango)
void criarOctaedro(int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - TAMANHO_HABILIDADE / 2) + abs(j - TAMANHO_HABILIDADE / 2) <= TAMANHO_HABILIDADE / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Função para sobrepor a matriz de habilidade no tabuleiro
void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int x = linha + i - TAMANHO_HABILIDADE / 2;
            int y = coluna + j - TAMANHO_HABILIDADE / 2;
            if (x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1) {
                    tabuleiro[x][y] = 5;
                }
            }
        }
    }
}

int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0}; // Inicializa o tabuleiro com água (0)

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 4;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;

    // **Posicionando o navio horizontalmente**
    if (colunaNavioHorizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = 3;
        }
    } else {
        printf("Erro: O navio horizontal excede os limites do tabuleiro!\n");
    }

    // **Posicionando o navio verticalmente**
    if (linhaNavioVertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = 3;
        }
    } else {
        printf("Erro: O navio vertical excede os limites do tabuleiro!\n");
    }

    // **Exibindo o tabuleiro**
    printf("\nTabuleiro Nível Novato:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // **Navio horizontal**
    if (podePosicionar(tabuleiro, 2, 3, 0, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, 2, 3, 0, TAMANHO_NAVIO);
    } else {
        printf("Erro ao posicionar o navio horizontal!\n");
    }

    // **Navio vertical**
    if (podePosicionar(tabuleiro, 5, 6, 1, TAMANHO_NAVIO)) {
        posicionarNavio(tabuleiro, 5, 6, 1, TAMANHO_NAVIO);
    } else {
        printf("Erro ao posicionar o navio vertical!\n");
    }

    // **Navio diagonal para a direita (↘)**
    if (podePosicionarDiagonal(tabuleiro, 0, 0, 0, TAMANHO_NAVIO)) {
        posicionarNavioDiagonal(tabuleiro, 0, 0, 0, TAMANHO_NAVIO);
    } else {
        printf("Erro ao posicionar o navio diagonal para a direita!\n");
    }

    // **Navio diagonal para a esquerda (↙)**
    if (podePosicionarDiagonal(tabuleiro, 2, 9, 1, TAMANHO_NAVIO)) {
        posicionarNavioDiagonal(tabuleiro, 2, 9, 1, TAMANHO_NAVIO);
    } else {
        printf("Erro ao posicionar o navio diagonal para a esquerda!\n");
    }

    // **Exibir o tabuleiro final**
    exibirTabuleiro(tabuleiro);

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Cria as matrizes das habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Sobrepõe as habilidades em posições específicas
    sobreporHabilidade(tabuleiro, cone, 2, 2);
    sobreporHabilidade(tabuleiro, cruz, 5, 5);
    sobreporHabilidade(tabuleiro, octaedro, 7, 7);

    // Exibe o tabuleiro com as áreas afetadas
    imprimirTabuleiro(tabuleiro);

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}

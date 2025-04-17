#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300

typedef struct {
    int linha;
    int coluna;
} Point;

typedef struct {
    Point data[MAX * MAX];
    int frente;
    int tras;
} Queue;

void iniciarFila(Queue* q) {
    q->frente = q->tras = 0;
}

int filaVazia(Queue* q) {
    return q->frente == q->tras;
}

void enfileirar(Queue* q, Point p) {
    q->data[q->tras++] = p;
}

Point desenfileirar(Queue* q) {
    return q->data[q->frente++];
}

void bfs(char** grid, int linhas, int colunas, int r, int c, int visitado[MAX][MAX]) {
    Queue q;
    iniciarFila(&q);

    visitado[r][c] = 1;
    enfileirar(&q, (Point){r, c});

    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (!filaVazia(&q)) {
        Point current = desenfileirar(&q);
        int linha = current.linha;
        int coluna = current.coluna;

        for (int i = 0; i < 4; i++) {
            int new_r = linha + directions[i][0];
            int new_c = coluna + directions[i][1];

            if (new_r >= 0 && new_r < linhas &&
                new_c >= 0 && new_c < colunas &&
                grid[new_r][new_c] == '1' &&
                !visitado[new_r][new_c]) {

                visitado[new_r][new_c] = 1;
                enfileirar(&q, (Point){new_r, new_c});
            }
        }
    }
}

int numIslands(char** grid, int gridSize, int* gridcolunaSize) {
    int visitado[MAX][MAX] = {0};
    int linhas = gridSize;
    int colunas = gridcolunaSize[0];
    int islands = 0;

    for (int r = 0; r < linhas; r++) {
        for (int c = 0; c < colunas; c++) {
            if (grid[r][c] == '1' && !visitado[r][c]) {
                bfs(grid, linhas, colunas, r, c, visitado);
                islands++;
            }
        }
    }

    return islands;
}

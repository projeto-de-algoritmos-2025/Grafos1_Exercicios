#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 401

typedef struct {
    int size;
    int capacidade;
    int* data;
} List;

typedef struct {
    List* adj;
    int in_degree[MAX_K];
} Graph;

void initList(List* list) {
    list->size = 0;
    list->capacidade = 4;
    list->data = (int*)malloc(list->capacidade * sizeof(int));
}

void appendToList(List* list, int value) {
    if (list->size == list->capacidade) {
        list->capacidade *= 2;
        list->data = (int*)realloc(list->data, list->capacidade * sizeof(int));
    }
    list->data[list->size++] = value;
}

void freeList(List* list) {
    free(list->data);
}

void initGraph(Graph* graph, int k) {
    graph->adj = (List*)malloc((k + 1) * sizeof(List));
    for (int i = 0; i <= k; i++) {
        initList(&graph->adj[i]);
    }
    memset(graph->in_degree, 0, sizeof(graph->in_degree));
}

void addEdge(Graph* graph, int u, int v) {
    appendToList(&graph->adj[u], v);
    graph->in_degree[v]++;
}

void freeGraph(Graph* graph, int k) {
    for (int i = 0; i <= k; i++) {
        freeList(&graph->adj[i]);
    }
    free(graph->adj);
}

int* topologicalSort(Graph* graph, int k) {
    int* queue = (int*)malloc(k * sizeof(int));
    int frente = 0, tras = 0;
    
    for (int i = 1; i <= k; i++) {
        if (graph->in_degree[i] == 0) {
            queue[tras++] = i;
        }
    }
    
    int* order = (int*)malloc(k * sizeof(int));
    int idx = 0;
    
    while (frente < tras) {
        int u = queue[frente++];
        order[idx++] = u;
        
        for (int i = 0; i < graph->adj[u].size; i++) {
            int v = graph->adj[u].data[i];
            graph->in_degree[v]--;
            if (graph->in_degree[v] == 0) {
                queue[tras++] = v;
            }
        }
    }
    
    free(queue);
    
    if (idx != k) {
        free(order);
        return NULL;
    }
    
    return order;
}

int** buildMatrix(int k, int** rowConditions, int rowConditionsSize, int* rowConditionsColSize,
                 int** colConditions, int colConditionsSize, int* colConditionsColSize,
                 int* returnSize, int** returnColumnSizes) {
    
    Graph rowGraph, colGraph;
    initGraph(&rowGraph, k);
    initGraph(&colGraph, k);

    for (int i = 0; i < rowConditionsSize; i++) {
        int u = rowConditions[i][0];
        int v = rowConditions[i][1];
        addEdge(&rowGraph, u, v);
    }

    for (int i = 0; i < colConditionsSize; i++) {
        int u = colConditions[i][0];
        int v = colConditions[i][1];
        addEdge(&colGraph, u, v);
    }
    

    int* rowOrder = topologicalSort(&rowGraph, k);
    int* colOrder = topologicalSort(&colGraph, k);
    

    if (!rowOrder || !colOrder) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        free(rowOrder);
        free(colOrder);
        freeGraph(&rowGraph, k);
        freeGraph(&colGraph, k);
        return NULL;
    }
    

    int rowPos[MAX_K] = {0};
    int colPos[MAX_K] = {0};
    
    for (int i = 0; i < k; i++) {
        rowPos[rowOrder[i]] = i;
        colPos[colOrder[i]] = i;
    }
    
 
    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    *returnSize = k;
    
    for (int i = 0; i < k; i++) {
        result[i] = (int*)calloc(k, sizeof(int));
        (*returnColumnSizes)[i] = k;
    }
    
    
    for (int num = 1; num <= k; num++) {
        result[rowPos[num]][colPos[num]] = num;
    }
    
   
    free(rowOrder);
    free(colOrder);
    freeGraph(&rowGraph, k);
    freeGraph(&colGraph, k);
    
    return result;
}
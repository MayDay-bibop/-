#ifndef LAB5_H
#define LAB5_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#define START 1
#define END 4
#define V   9
#define INF 9999999
typedef struct EdgeNode {
    int to; // номер вершины соседа
    int w; // вес
    struct EdgeNode* next;
} EdgeNode;

typedef struct Graph {
    EdgeNode* head[V]; // списки смежности
} Graph;

static inline EdgeNode* newEdge(int to, int w) {
    EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));
    if (!e) return NULL;
    e->to = to;     // куда ведёт ребро
    e->w = w;       // вес
    e->next = NULL; // пока следующий = NULL (конец списка)
    return e;
}


void graphInit(Graph* g);
void addEdge(Graph* g, int u, int v, int w);
int buildFromFile (Graph* g);
void printPathDij(int parent[], int v);
int minDist(const int dist[], const int used[]);
void dijkstra(Graph* g, int start, int end);
void printPathFloyd(int next[V][V], int u, int v);
void floyd(Graph* g, int start, int end);
void freeGraph(Graph* g);
int main5();

#endif
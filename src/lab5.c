#include "../include/lab5.h"

void graphInit(Graph* g) {
    for (int i = 0; i < V; ++i) g->head[i] = NULL;
}

void addEdge(Graph* g, int u, int v, int w) {
    EdgeNode* e = newEdge(v, w);
    if (!e) return;
    e->next = g->head[u];
    g->head[u] = e;
}

int buildFromFile (Graph* g) {
    graphInit(g);
    FILE *fp = fopen ("graph.txt", "rt");
    if(!fp) {
        printf("файл не открылся\n");
        return 0;
    }

    int u, v, w;
    while (fscanf(fp, "%d %d %d", &u, &v, &w)==3)
    {
        if (u < 1 || u > V || v < 1 || v > V) // границы значений 
        {
            printf("неверное значение вершины: %d %d\n", u, v);
            continue;
        }
        addEdge(g, u - 1, v - 1, w); // ориентированный граф
    }

    fclose(fp);
    return 1;
}

void printPathDij(int parent[], int v)
{
    if (parent[v] == -1) 
    {
        printf("%d", v + 1);
        return;
    }
    printPathDij(parent, parent[v]);
    printf(" -> %d", v + 1);
}

int minDist(const int dist[], const int used[])
{
    int min = INF, idx = -1;
    for (int v = 0; v < V; v++)
        if (!used[v] && dist[v] < min)  // жадный выбор
        {
            min = dist[v];
            idx = v;
        }
    return idx;
}

void dijkstra(Graph* g, int start, int end) 
{
    int dist[V], used[V], parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        used[i] = 0;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDist(dist, used);
        if (u == -1) break;
        used[u] = 1;

        for (EdgeNode* e = g->head[u]; e; e = e->next) {
            int v = e->to;
            int w = e->w;
            if (!used[v] && dist[u] != INF &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    if (dist[end] == INF) printf("дейкстра: пути от %d до %d нет\n", start + 1, end + 1);
    else {
        printf("дейкстра: расстояние от %d до %d = %d\n", start + 1, end + 1, dist[end]);
        printf("путь: ");
        printPathDij(parent, end);
        printf("\n");
    }
}

void printPathFloyd(int next[V][V], int u, int v) {
    if (next[u][v] == -1) {
        printf("путь не существует\n");
        return;
    }
    int cur = u;
    printf("%d", cur + 1);
    while (cur != v) {
        cur = next[cur][v];
        printf(" -> %d", cur + 1);
    }
    printf("\n");
}

void floyd(Graph* g, int start, int end) {
    int dist[V][V], next[V][V];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next[i][j] = j;
            } else {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
        for (EdgeNode* e = g->head[i]; e; e = e->next) {
            int v = e->to;
            int w = e->w;
            if (w < dist[i][v]) { 
                dist[i][v] = w;
                next[i][v] = v;
            }
        }
    }

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    int nd = dist[i][k] + dist[k][j];
                    if (nd < dist[i][j]) {
                        dist[i][j] = nd;
                        next[i][j] = next[i][k];
                    }
                }

    if (dist[start][end] == INF || next[start][end] == -1) {
        printf("флойд: пути от %d до %d нет\n", start + 1, end + 1);
    } else {
        printf("флойд: расстояние от %d до %d = %d\n",
               start + 1, end + 1, dist[start][end]);
        printf("путь: ");
        printPathFloyd(next, start, end);
    }
}

void freeGraph(Graph* g) 
{
    for (int i = 0; i < V; ++i) {
        EdgeNode* cur = g->head[i];
        while (cur) {
            EdgeNode* nxt = cur->next;
            free(cur);
            cur = nxt;
        }
        g->head[i] = NULL;
    }
}
int main5()
{
    Graph g;

    if (!buildFromFile(&g))      // читаем graph.txt
        return 1;
    int choice;
    printf("1 - дейкстра\n");
    printf("2 - флойд–уоршелл\n");
    printf("выбор: ");
    if (scanf("%d", &choice) != 1) return 0;

    if (choice == 1) dijkstra(&g, START, END);
    else if (choice == 2) floyd(&g, START, END);
    else printf("ыыы\n");

    return 0;
}

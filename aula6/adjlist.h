#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "limits.h"

#define Vertex int

typedef struct node_struct *Node; // ponteiro para noh

// noh da lista de adjacencia
struct node_struct {
  Vertex x;
  int weight;
  bool visited;
  Node next; // aponta para o proximo no
};

// o (Di)Grafo armazena o nro de vertices, o nro de arcos/arestas e um ponteiro para a lista de adjacencia
struct graph {
  int V;     // qtde de vertices
  int A;     // qtde de arcos/arestas
  Node *adj; // ponteiro para array de vertices
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V) {
  Graph G = (Graph)malloc(sizeof(*G));
  G->V = V;
  G->A = 0;
  G->adj = (Node *)malloc(V * sizeof(Node *));
  for (int i = 0; i < V; i++) {
    G->adj[i] = NULL;
  }
  return G;
}

Node newArc(Vertex w, int weight) {
  Node a = (Node)malloc(sizeof(*a));
  a->x = w;
  a->weight = weight;
  a->next = NULL;
  return a;
}

void insertArc(Graph G, Vertex v, Vertex w, int weight) {
  // verifica se o vertice w já existe na lista de nodeacencia de v
  Node last = G->adj[v];
  for (Node v_node = G->adj[v]; v_node != NULL; v_node = v_node->next) {
    if (v_node->x == w) return;
    last = v_node;
  }
  // insere arco no inicio da lista
  if(G->adj[v] == NULL) {
    G->adj[v] = newArc(w, weight);
  } else { // insere arco no final da lista
    last->next = newArc(w, weight);
  }
  G->A++;
}

void insertEdge(Graph G, Vertex v, Vertex w, int weight) {
  insertArc(G, v, w, weight);
  insertArc(G, w, v, weight);
  G->A--;
}

void removeArc(Graph G, Vertex v, Vertex r) {
  if (G->adj[v] == NULL) { // nao existe arco saindo de v
    return;
  }
  Node node = G->adj[v];
  for (Node r_node = G->adj[v]; r_node != NULL; r_node = r_node->next) { // cc, percorre lista
    if (r_node->x == r) {  // se eh o vertice a ser retirado
      G->A--;
      if (G->adj[v] == r_node) { // se for o primeiro da lista
        G->adj[v] = r_node->next;
        return;
      }
      node->next = r_node->next;
      return;
    } else {
      node = r_node; // guarda referencia do anterior
    }
  }
}

void removeEdge(Graph G, Vertex v, Vertex w) {
  removeArc(G, v, w);
  removeArc(G, w, v);
  G->A++;
}

void destroyGraph(Graph G) {
  if (G != NULL) {
    for(int i; i < G->V; i++) {
      free(G->adj[i]);
    }
    free(G->adj);
    free(G);
  }
}

void printGraph(Graph G) {
  printf("\nTotal of vertices: %d, total of arcs/edges: %d\n", G->V, G->A);
  for (int i = 0; i < G->V; i++) {
    printf("Vertex %d, arcs: ", i);
    for (Node print = G->adj[i]; print != NULL; print = print->next) {
      printf("  -> %d (peso %d)", print->x, print->weight);
    }
    printf("\n");
  }
}

void clearVisited(Graph G) {
  for (int i = 0; i < G->V; i++) {
    G->adj[i]->visited = false;
  }
}

void DFS(Graph G, Vertex x) {
  G->adj[x]->visited = true;
  printf("visited %d \n", x);
  for (Node p = G->adj[x]; p != NULL; p = p->next) {
    Vertex y = p->x;
    if (!(G->adj[y]->visited)) {
      DFS(G, y);
    }
  }
}

void startDFS(Graph G, Vertex start) {
  clearVisited(G);
  printf("DFS\n");
  DFS(G, start);
}

void BFS(Graph G, Vertex x) {
  Vertex *queue = (Vertex *)malloc(sizeof(Vertex) * G->V);
  int start = 0, end = 0;
  queue[end++] = x;
  while (start != end) {
    Vertex elem = queue[start++];
    if (!(G->adj[elem]->visited)) {
      G->adj[elem]->visited = true;
      printf("visited %d \n", elem);
      for (Node p = G->adj[elem]; p != NULL; p = p->next) {
        Vertex w = p->x;
        if (!(G->adj[w]->visited)) {
          queue[end++] = w;
        }
      }
    }
  }
  free(queue);
}

void startBFS(Graph G, Vertex start) {
  clearVisited(G);
  printf("BFS\n");
  BFS(G, start);
}

bool simplePath(Graph G, Vertex start, Vertex end) {
  G->adj[start]->visited = true;
  for (Node p = G->adj[start]; p != NULL; p = p->next) {
    if (p->x == end) {
      return true;
    }
    if (G->adj[p->x]->visited == false) {
      if (simplePath(G, p->x, end)) {
        return true;
      }
    }
  }
  return false;
}

void startSimplePath(Graph G, Vertex start, Vertex end) {
  clearVisited(G);
  if (simplePath(G, start, end)) {
    printf("Simple path %d--%d exists!\n", start, end);
  } else {
    printf("Simple path %d--%d does NOT exists!\n", start, end);
  }
}


Graph copyGraph(Graph G) {
  Graph C = initGraph(G->V);
  for(int i = 0; i < G->V; i++) {
      for(Node p = G->adj[i]; p != NULL; p = p->next) {
          insertEdge(C, i, p->x, p->weight);
      }
  }
  return C;
}

int path(Graph C, Vertex v, int *stack, int *index) {
  while (C->adj[v] != NULL) {
      (*index)++;
      stack[*index] = v;
      Vertex w = C->adj[v]->x;
      removeEdge(C, v, w);
      v = w;
  }
  return 1;
}

void eulerPath(Graph G, Vertex v, Vertex end) {
  Graph C = copyGraph(G);
  Vertex *stack = (Vertex *)malloc(sizeof(Vertex)*C->V);
  int index = -1;
  printf("\nEuler Path: -> %d", end);
  while(path(C, v, stack, &index) && index >=0) {
      v = stack[index--];
      printf(" -> %d", v);
  }
  printf("\n");
  free(stack);
  destroyGraph(C);
}

void checkEulerPath(Graph G) {
  int *degree = (int *)calloc(G->V, sizeof(int));
  Vertex odds[3];
  int n_odds = 0;
  for(int i = 0; i < G->V; i++) {
      for(Node p = G->adj[i]; p != NULL; p = p->next) {
          degree[i]++;
      }
      if (degree[i] % 2 != 0) {
          odds[n_odds] = i;
          n_odds++;
          if(n_odds > 2) {
              printf("An Euler path does NOT exist.\n");
              free(degree);
              return;
          }
      }
  }
  if (n_odds == 2) {
      printf("An Euler PATH exists.\n");
      eulerPath(G, odds[0], odds[1]);
  } else {
      printf("An Euler CICLE exists.\n");
      eulerPath(G, 0, 0);
  }
  free(degree);
}

bool hamiltonPath(Graph G, Vertex start, Vertex end, int n) {
  if( start == end) {
    if(((n + 1) == G->V)) {
      printf("\n");
      return true;
    } else if(n != 0) {
      return false;
    }
  }
  G->adj[start]->visited = true;
  for(Node p = G->adj[start]; p != NULL; p = p->next) {
    if(!(G->adj[p->x]->visited) || p->x == end) {
      if(hamiltonPath(G, p->x, end, n + 1)) {
        printf("| %d -> %d ", start, p->x);
        return true;
      }
    }
  }
  G->adj[start]->visited = false;
  return false;
}

bool checkHamiltonPath(Graph G, Vertex start, Vertex end) {
  clearVisited(G);
  printf("\nHamilton Path: ");
  return hamiltonPath(G, start, end, 0);
}

void topologicalSortDAG(Digraph D) {
  int start = 0, end = 0;
  Vertex queue[D->V]; // fila de vertices
  int in[D->V]; // lista de quantidade de arestas incidentes
  for (int v = 0; v < D->V; v++) { // inicializa lista de incidencia
    in[v] = 0;
  }
  for (int v = 0; v < D->V; v++) {
    for (Node p = D->adj[v]; p != NULL; p = p->next) {
      // se v-w existe, incrementa in[w]
      in[p->x]++;
    }
  }
  for (int v = 0; v < D->V; v++) {
    if (in[v] == 0) {  // para cada v fonte
      queue[end++] = v; // coloca na fila
    }
  }
  printf("Topological Sorting: ");
  while (end != start) {
    Vertex x = queue[start++]; // retira elemento da fila
    printf("%d ", x);
    // para cada adjacente de x
    for (Node p = D->adj[x]; p != NULL; p = p->next) {
      in[p->x]--; // decrementa a quantidade de arestas incidentes
      if (in[p->x] == 0) {  // e verifica se foi igualada a zero
        queue[end++] = p->x; // coloca no fim da fila
      }
    }
  }
  if (start != D->V) {
    printf("...\nNot a DAG.");
  }
  printf("\n");
}

void dijkstra(Graph G, Vertex s) {
  int distance[G->V];
  Vertex parent[G->V];
  for (int i = 0; i < G->V; i++) {
    distance[i] = INT_MAX;
    parent[i] = -1;
    if (G->adj[i] != NULL) {
      G->adj[i]->visited = false;
    }
  }
  Vertex v = s;
  distance[s] = 0;
  while (G->adj[v]->visited == false) {
    G->adj[v]->visited = true;
    for (Node p = G->adj[v]; p != NULL; p = p->next) { // visitar vizinhos
      Vertex u = p->x;
      if (distance[u] > distance[v] + p->weight) {
        distance[u] = distance[v] + p->weight;
        parent[u] = v;
      }
    }
    // substitui fila de prioridade
    int min_dist = INT_MAX;
    int v_aux = v;
    for (int i = 0; i < G->V; i++) {
      if ((G->adj[i] != NULL) && (G->adj[i]->visited == false) &&
          (distance[i] < min_dist)) {
        min_dist = distance[i];
        v = i;
      }
    }
  }
  printf("\nDijstra:\n");
  for (int i = 0; i < G->V; i++) {
    printf("Distance from %d to %d = %d\n", s, i, distance[i]);
    Vertex path[G->V];
    Vertex p = i;
    int index = 0;
    while (p != s) {
      path[index++] = p;
      p = parent[p];
    }
    path[index] = p;
    for(int a = index; a > -1; a--) {
      printf(" --> %d", path[a]);
    }
    printf("\n");
  }
}

void floydAllPath(Digraph G) {
  // Inicializa uma matriz d de largura VxV que irá guardar os pesos
  int **d = (int **)malloc(G->V * sizeof(int *));
  for (int i = 0; i < G->V; i++) {
    d[i] = (int *)malloc(sizeof(int) * G->V);
    for (int j = 0; j < G->V; j++) {
      if (i == j) {
        d[i][j] = 0; // Distância de um vértice para ele mesmo é zero
        d[j][i] = 0;
      } else {
        d[i][j] = INT_MAX; // Inicializa outras distâncias como infinito
      }
    }
    // Preenche as distâncias diretas conhecidas
    for (Node p = G->adj[i]; p != NULL; p = p->next) {
      Vertex w = p->x;
      d[i][w] = p->weight;
    }
  }

  for (int k = 0; k < G->V; k++) { // Para cada vértice
    for (int s = 0; s < G->V; s++) { // Para cada origem s
      if (d[s][k] != INT_MAX && s != k) { // Se existe caminho s->k
        for (int dest = 0; dest < G->V; dest++) { // para cada dest intermediario
          if (d[k][dest] != INT_MAX && s != dest) { // Se existe k->dest
            if ((d[s][k] + d[k][dest]) < d[s][dest]) { // Custo de s->k + custo de k->dest é menor que custo s->dest?
              d[s][dest] = d[s][k] + d[k][dest]; // Atualiza a distância mínima
            }
          }
        }
      }
    }
  }
  printf("\nFloyd Warshall: \n\n");
  for (int s = 0; s < G->V; s++) {
    for (int i = 0; i < G->V; i++) {
      if (d[s][i] == INT_MAX) {
        printf("Não há caminho de %d para %d\n", s, i);
      } else {
        printf("Distancia de %d para %d: %d\n", s, i, d[s][i]);
      }
    }
    printf("\n");
  }
  for (int i = 0; i < G->V; i++)
    free(d[i]);
  free(d);
}
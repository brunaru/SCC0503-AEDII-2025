#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
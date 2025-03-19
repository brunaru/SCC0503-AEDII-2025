#include <stdio.h>
#include <stdlib.h>

#define Vertex int

typedef struct node *Link; // ponteiro para noh

// noh da lista de adjacencia
struct node {
  Vertex w;
  Link next; // aponta para o proximo no
};

// o (Di)Grafo armazena o nro de vertices, o nro de arcos/arestas e um ponteiro
// para a lista de adjacencia
struct graph {
  int V;     // qtde de vertices
  int A;     // qtde de arcos/arestas
  Link *adj; // ponteiro para array de vertices
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V) {
  Graph G = (Graph)malloc(sizeof(*G));
  G->V = V;
  G->A = 0;
  G->adj = (Link *)malloc(V * sizeof(Link *));
  for (int i = 0; i < V; i++) {
    G->adj[i] = NULL;
  }
  return G;
}

Link newArc(Vertex w, Link next) {
  Link a = (Link)malloc(sizeof(*a));
  a->w = w;
  a->next = next;
  return a;
}

void insertArc(Graph G, Vertex v, Vertex w) {
  // verifica se o vertice w já existe na lista de adjacencia de v
  for (Link v_adj = G->adj[v]; v_adj != NULL; v_adj = v_adj->next) {
    if (v_adj->w == w)
      return;
  }
  // insere arco no inicio da lista de adjacencia
  G->adj[v] = newArc(w, G->adj[v]);
  G->A++;
}

void insertEdge(Graph G, Vertex v, Vertex w) {
  insertArc(G, v, w);
  insertArc(G, w, v);
}

void removeArc(Graph G, Vertex v, Vertex r) {
  if (G->adj[v] == NULL) { // nao existe arco saindo de v
    return;
  }
  Link previous = G->adj[v];
  for (Link p = G->adj[v]; p != NULL; p = p->next) { // cc, percorre lista
    if (p->w == r) {  // se eh o vertice a ser retirado
      G->A--;
      if (G->adj[v] == p) { // se for o primeiro da lista
        G->adj[v] = p->next;
        return;
      }
      previous->next = p->next;
      return;
    } else {
      previous = p; // guarda referencia do anterior
    }
  }
}

void removeEdge(Graph G, Vertex v, Vertex w) {
  removeArc(G, v, w);
  removeArc(G, w, v);
}

void destroyGraph(Graph G) {
  if (G != NULL) {
    for(int i; i < G-> V; G++) {
      free(G->adj[i]);
    }
    free(G->adj);
    free(G);
  }
}

void printGraph(Graph G) {
  printf("\nTotal of vertices: %d, total of arcs: %d\n", G->V, G->A);
  for (int i = 0; i < G->V; i++) {
    printf("* Vertex %d, arcs: \n", i);
    for (Link p = G->adj[i]; p != NULL; p = p->next) {
      printf("  -> %d\n", p->w);
    }
  }
}

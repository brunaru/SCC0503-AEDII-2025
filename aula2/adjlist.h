#include <stdio.h>
#include <stdlib.h>

#define Vertex int

typedef struct node_struct *Node; // ponteiro para noh

// noh da lista de adjacencia
struct node_struct {
  Vertex x;
  Node next; // aponta para o proximo no
};

// o (Di)Grafo armazena o nro de vertices, o nro de arcos/arestas e um ponteiro para a lista de adjacencia
struct graph {
  int V;     // qtde de vertices
  int A;     // qtde de arcos/arestas
  Node *node; // ponteiro para array de vertices
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V) {
  Graph G = (Graph)malloc(sizeof(*G));
  G->V = V;
  G->A = 0;
  G->node = (Node *)malloc(V * sizeof(Node *));
  for (int i = 0; i < V; i++) {
    G->node[i] = NULL;
  }
  return G;
}

Node newArc(Vertex w, Node next) {
  Node a = (Node)malloc(sizeof(*a));
  a->x = w;
  a->next = next;
  return a;
}

void insertArc(Graph G, Vertex v, Vertex w) {
  // verifica se o vertice w já existe na lista de nodeacencia de v
  for (Node v_node = G->node[v]; v_node != NULL; v_node = v_node->next) {
    if (v_node->x == w)
      return;
  }
  // insere arco no inicio da lista
  G->node[v] = newArc(w, G->node[v]);
  G->A++;
}

void insertEdge(Graph G, Vertex v, Vertex w) {
  insertArc(G, v, w);
  insertArc(G, w, v);
  G->A--;
}

void removeArc(Graph G, Vertex v, Vertex r) {
  if (G->node[v] == NULL) { // nao existe arco saindo de v
    return;
  }
  Node node = G->node[v];
  for (Node r_node = G->node[v]; r_node != NULL; r_node = r_node->next) { // cc, percorre lista
    if (r_node->x == r) {  // se eh o vertice a ser retirado
      G->A--;
      if (G->node[v] == r_node) { // se for o primeiro da lista
        G->node[v] = r_node->next;
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
    for(int i; i < G-> V; G++) {
      free(G->node[i]);
    }
    free(G->node);
    free(G);
  }
}

void printGraph(Graph G) {
  printf("\nTotal of vertices: %d, total of arcs/edges: %d\n", G->V, G->A);
  for (int i = 0; i < G->V; i++) {
    printf("Vertex %d, arcs: ", i);
    for (Node print = G->node[i]; print != NULL; print = print->next) {
      printf("  -> %d", print->x);
    }
    printf("\n");
  }
}

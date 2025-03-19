#include <stdio.h>
#include <stdlib.h>

#define Vertex int

typedef struct
{
  Vertex v;
  Vertex w;
} Arc;

struct arclist
{
  int size;
  Arc *arcs;
};

typedef struct arclist *Graph;
#define Edge Arc

Graph initGraph()
{
  Graph G = (Graph)malloc(sizeof(*G));
  G->size = 0;
  G->arcs = NULL;
  return G;
}

Arc newArc(Vertex v, Vertex w)
{
  Arc e;
  e.v = v;
  e.w = w;
  return e;
}

void destroyGraph(Graph G)
{
  free(G->arcs);
  G->size = 0;
}

void insertArc(Graph G, Vertex v, Vertex w)
{
  for (int i = 0; i < (G->size); i++)
  {
    if ((G->arcs[i].v == v) && (G->arcs[i].w == w))
    {
      return;
    }
  }
  Arc newa = newArc(v, w);
  G->size++;
  G->arcs = (Arc *)realloc(G->arcs, sizeof(Arc) * G->size);
  G->arcs[G->size - 1] = newa;
}

void insertEdge(Graph G, Vertex v, Vertex w)
{
  insertArc(G, v, w);
  insertArc(G, w, v);
}

void removeArc(Graph G, Vertex v, Vertex w)
{
  for (int i = 0; i < (G->size); i++)
  {
    if ((G->arcs[i].v == v) && (G->arcs[i].w == w))
    {
      G->arcs[i] = G->arcs[G->size - 1];
      G->size--;
      G->arcs = (Arc *)realloc(G->arcs, sizeof(Arc) * G->size);
      return;
    }
  }
}

void removeEdge(Graph G, Vertex v, Vertex w)
{
  removeArc(G, v, w);
  removeArc(G, w, v);
}

void printGraph(Graph G)
{
  for (int i = 0; i < (G->size); i++)
  {
    printf("(%d -- %d)\n", G->arcs[i].v, G->arcs[i].w);
  }
}
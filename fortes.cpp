/*
 * =====================================================================================
 *
 *       Filename:  fortes.cpp
 *
 *    Description:  This graph works is to find the connected components of a graph,
 *                  it can be connect or not the input graph.
 *
 *        Version:  1.0
 *        Created:  18/06/17 15:44:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alessandro Elias, GRR20110589, ae11@c3sl.ufpr.br
 *        Company:  C3SL
 *
 * =====================================================================================
 */

#include "fortes.h"

VertexSetByName VertexesByName;
VertexSetById VertexesById;


/*______________________________________________________________________________________*/

int main(void)
{
  Agraph_t *g;

  g = agread(stdin, NULL);
  Graph G(agnnodes(g));
  G.name = agnameof(g);

  ReadGraph(g, &G);
  agclose(g);

  cout << "strict digraph resultado_" << G.name << " {" << endl;
  G.GetAllStrongConnectedComponents();
  G.Show();
  cout << '}' << endl;

  return 0;
}

inline void GetNeighborhood(Agraph_t*, Agnode_t*, Graph*);
void ReadGraph(Agraph_t *g, Graph *G)
{
    Agnode_t *v;
    Vertex u;
    UINT Id;

    Id = 0;
    for( v = agfstnode(g); v; v = agnxtnode(g, v) ) {
        u.Id = Id;
        u.name = agnameof(v);
        VertexesById[Id] = u;
        VertexesByName[u.name] = Id++;
    }

    for( Agnode_t *u = agfstnode(g); u; u = agnxtnode(g, u) ) {
      GetNeighborhood(g, u, G);
    }
}

inline void GetNeighborhood(Agraph_t *g, Agnode_t *u, Graph *G)
{
    Agedge_t *edge;
    UINT tailID, headID;

    for( edge = agfstout(g, u); edge; edge = agnxtout(g, edge) ) {
        tailID = VertexesByName[agnameof(agtail(edge))];
        headID = VertexesByName[agnameof(aghead(edge))];
        VertexesById[tailID].Neighborhood.push_back(headID);
	G->addEdge(tailID, headID);
    }
}

void Graph::GetStrongConnectedComponents(int u, int pre[], int low[], Stack *s, bool IsInStack[])
{
  static int time = 0;

  pre[u] = low[u] = ++time;
  s->push(u);
  IsInStack[u] = true;

  // Interaja com todos os vértices adjacentes à u
  list<int>::iterator i;
  for( i = adj[u].begin(); i != adj[u].end(); ++i ) {
    int v = *i;  // v é o vértice adjacente corrente à u

    if( pre[v] == NOT_VISITED ) {
      GetStrongConnectedComponents(v, pre, low, s, IsInStack);

      /*
       * Verifique se a sub árvore enraizada em v existe
       * ancestral de u, otendo o mínimo.
       */
      low[u]  = min(low[u], low[v]);
    }

    /*
     * Atualize low point de u somente se v está na apilha
     */
    else if( IsInStack[v] == true )
      low[u]  = min(low[u], pre[v]);
  }

  int w = 0;
  static int count_cluster = 1;
  if( low[u] == pre[u] ) {
    cout << "subgraph cluster" << count_cluster++ << " {" << endl;
    while( s->top() != u ) {
      w = (int) s->top();
      cout << '\t' << VertexesById[w].name << ";" << endl;
      IsInStack[w] = false;
      s->pop();
    }
    w = (int) s->top();
    cout << '\t' << VertexesById[w].name << ";" << endl;
    IsInStack[w] = false;
    s->pop();
    cout << "}" << endl;
  }
}

void Graph::GetAllStrongConnectedComponents(void)
{
  int *pre = new int[V];
  int *low = new int[V];
  bool *isInStack = new bool[V];
  Stack *s = new Stack();

  for (int i = 0; i < V; i++)
    {
      pre[i] = NOT_VISITED;
      low[i] = NOT_VISITED;
      isInStack[i] = false;
    }

  for (int i = 0; i < V; i++)
    if( pre[i] == NOT_VISITED )
      GetStrongConnectedComponents(i, pre, low, s, isInStack);

}

void Graph::Show(void)
{
  Vertex *u;

  for( auto each_v : VertexesById ) {
    u = &VertexesById[each_v.first];
    for( auto each_arc : u->Neighborhood ) {
      cout << '\t' << '"' << u->name << "\" -> \"" << VertexesById[each_arc].name << "\";" << endl;
    }
  }
}

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

#ifndef __FORTES_H__
#define __FORTES_H__

#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <graphviz/cgraph.h>

#define NOT_VISITED  -1

using namespace std;

typedef unsigned int UINT;
typedef std::vector<UINT> VertexSet;
typedef std::unordered_map<std::string, int> AttributeSet;

typedef struct __Vertex {
  UINT Id;
  UINT OutDegree;
  int Set;
  struct __Vertex *Parent;
  std::string name;
  AttributeSet attributes;
  VertexSet Neighborhood;
} Vertex;
typedef std::unordered_map<UINT, Vertex> VertexSetById;
typedef std::unordered_map<std::string, UINT> VertexSetByName;


typedef std::list<int> AdjacentSet;
typedef std::stack<int> Stack;
class Graph
{
  int V; // number of vertexes
  AdjacentSet *adj;

  void GetStrongConnectedComponents(int u, int pre[], int low[], Stack *s, bool IsInStack[]);

 public:
  string name;

  Graph(int V) {
	this->V = V;
	adj = new AdjacentSet[V];
  }

  void addEdge(int v, int w) { adj[v].push_back(w);  }
  void GetAllStrongConnectedComponents(void);
  void Show(void);
};

/*
 * Prototypes
 */
void ReadGraph(Agraph_t*, Graph*);
void PrintVertexes(void);

#endif /* __FORTES_H__ */

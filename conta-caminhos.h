#ifndef __CONTA_CAMINHOS__H
#define __CONTA_CAMINHOS__H

typedef unsigned int UINT;
typedef vector<UINT> VertexSet;
typedef unordered_map<string, UINT> AttrNameSet;

typedef struct __Vertex {
  UINT Id;
  UINT degree;
  string name;
  AttrNameSet attributes;
  VertexSet Neighborhood;
} Vertex;
typedef unordered_map<UINT, Vertex> VertexSetById;
typedef unordered_map<string, UINT> VertexSetByName;


/*
 * Prototypes
 */
void ReadGraph(Agraph_t *g);
void PrintVertexes(void);
void GetNeighborhood(Agraph_t *g, Agnode_t *u);

#endif __CONTA_CAMINHOS__H

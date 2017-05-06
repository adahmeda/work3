#ifndef __CONTA_CAMINHOS_H__
#define __CONTA_CAMINHOS_H__   1

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

typedef unsigned int UINT;
typedef std::vector<UINT> VertexSet;
typedef std::unordered_map<std::string, int> AttributeSet;

typedef struct __Vertex {
  UINT Id;
  UINT degree;
  int Set;
  struct __Vertex *Parent;
  std::string name;
  AttributeSet attributes;
  VertexSet Neighborhood;
} Vertex;
typedef std::unordered_map<UINT, Vertex> VertexSetById;
typedef std::unordered_map<std::string, UINT> VertexSetByName;

/*
 * Prototypes
 */
void ReadGraph(Agraph_t *g);
void PrintVertexes(void);
inline void GetNeighborhood(Agraph_t *g, Agnode_t *u);
inline void GetAttributes(AttributeSet *attributes, Agraph_t *g, Agnode_t *v);
void CountPaths(void);
void Count(Vertex *x);
inline void ShowAttributes(AttributeSet *as);
inline void GetAttributes(Vertex *r, Vertex *v);


#endif /*__CONTA_CAMINHOS_H__*/

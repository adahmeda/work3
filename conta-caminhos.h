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

#endif /*__CONTA_CAMINHOS_H__*/

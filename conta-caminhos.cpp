#include <graphviz/cgraph.h>
#include "conta-caminhos.h"

using namespace std;

/*
 * Prototypes
 */
void ReadGraph(Agraph_t *g);
void PrintVertexes(void);
void GetNeighborhood(Agraph_t *g, Agnode_t *u);


VertexSetById VertexesById;
VertexSetByName VertexesByName;


/*_________________________________________________________________________________*/
int main(void)
{
    auto g = agread(stdin, NULL);
    ReadGraph(g);
    PrintVertexes();
    agclose(g);

    return 0;
}

void ReadGraph(Agraph_t *g)
{
    Vertex v;
    UINT Id;

    Id = 0;
    for( Agnode_t *u = agfstnode(g); u; u = agnxtnode(g, u) ) {
        v.Id = Id;
        v.name = agnameof(u);
        v.degree = agdegree(g, u, FALSE, TRUE);
        VertexesById[Id] = v;
        VertexesByName[v.name] = Id++;
    }

    for( Agnode_t *u = agfstnode(g); u; u = agnxtnode(g, u) ) {
        GetNeighborhood(g, u);
    }
}

inline void GetNeighborhood(Agraph_t *g, Agnode_t *u)
{
    Agedge_t *edge;
    UINT tailID, headID;

    for( edge = agfstout(g, u); edge; edge = agnxtout(g, edge) ) {
        tailID = VertexesByName[agnameof(agtail(edge))];
        headID = VertexesByName[agnameof(aghead(edge))];
        VertexesById[tailID].Neighborhood.push_back(headID);
    }
}

void PrintVertexes(void)
{
    for( auto it = VertexesById.begin(); it != VertexesById.end(); ++it ) {
        cout << " " << it->first << ":" << VertexesById[it->first].name;
    }
    cout << endl;

    for( auto it = VertexesById.begin(); it != VertexesById.end(); ++it ) {
        cout << " " << VertexesById[it->first].Id << ":" << VertexesById[it->first].name << ":" << VertexesById[it->first].degree << endl;
        cout << "Neighborhood:" << endl << "\t";
        for( auto it2 = VertexesById[it->first].Neighborhood.begin();
             it2 != VertexesById[it->first].Neighborhood.end();
             ++it2 ) {
            cout << *it2 << " ";
       }
        cout << endl;
    }
}

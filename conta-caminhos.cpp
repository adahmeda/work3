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
AttributeSet Attributes;


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
    Agnode_t *v;
    Vertex u;
    UINT Id;

    Id = 0;
    for( v = agfstnode(g); v; v = agnxtnode(g, v) ) {
        u.Id = Id;
        u.name = agnameof(v);
        u.degree = agdegree(g, v, FALSE, TRUE);
        GetAttributes(&u.attributes, g, v);
        VertexesById[Id] = u;
        VertexesByName[u.name] = Id++;
    }

    for( Agnode_t *u = agfstnode(g); u; u = agnxtnode(g, u) ) {
        GetNeighborhood(g, u);
    }
}

inline void GetAttributes(AttributeSet *attributes, Agraph_t *g, Agnode_t *v)
{
    Agsym_t *sym;

    for( sym = agnxtattr(g, AGNODE, NULL); sym; sym = agnxtattr(g, AGNODE, sym) ) {
        (*attributes)[sym->name] = atoi(agxget(v, sym));
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
    for( auto it : VertexesById ) {
        cout << " " << it.first << ":" << VertexesById[it.first].name;
    }
    cout << "\n\n";

    for( auto it = VertexesById.begin(); it != VertexesById.end(); ++it ) {
        cout << " " << VertexesById[it->first].Id << ":" << VertexesById[it->first].name << ":" << VertexesById[it->first].degree << endl;
        cout << "Attributes:" << endl;
        for( auto it3 : VertexesById[it->first].attributes ) {
            cout << "\t" << it3.first << ":" << it3.second;
        }
        cout << endl << "Neighborhood:" << endl << "\t";
        for( auto it2 = VertexesById[it->first].Neighborhood.begin();
             it2 != VertexesById[it->first].Neighborhood.end();
             ++it2 ) {
            cout << *it2 << " ";
       }
       cout << endl;
    }
}

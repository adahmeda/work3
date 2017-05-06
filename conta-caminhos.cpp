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
    agclose(g);

    CountPaths();
    //PrintVertexes();

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
    cout << "Id:VertexName:Degree" << endl;
    for( auto it : VertexesById ) {
        cout << " " << it.first << ":" << VertexesById[it.first].name;
    }
    cout << "\n\n";

    for( auto it = VertexesById.begin(); it != VertexesById.end(); ++it ) {
        cout << " " << VertexesById[it->first].Id << ":" << VertexesById[it->first].name << ":" << VertexesById[it->first].degree << endl;
        cout << "\tAttributes: Attr:Value" << endl;
        for( auto it3 : VertexesById[it->first].attributes ) {
            cout << "\t" << it3.first << ":" << it3.second;
        }
        cout << endl << "\tNeighborhood: Id of Vertexes" << endl << "\t";
        for( auto it2 = VertexesById[it->first].Neighborhood.begin();
             it2 != VertexesById[it->first].Neighborhood.end();
             ++it2 ) {
            cout << *it2 << ":" << VertexesById[*it2].name << ' ';
       }
       cout << endl;
    }
}

void CountPaths(void)
{
    Vertex *v;

    for( auto it : VertexesById ) {
        v = &VertexesById[it.first];
        v->Set = 0;
        v->Parent = NULL;
    }

    for( auto it : VertexesById ) {
        if( VertexesById[it.first].Set == 0 ) {
            Count(&(VertexesById[it.first]));
        }
    }
}

void Count(Vertex *r)
{
    Vertex *v;

    cout << "raiz=" << r->name << ".Set=" << r->Set << endl << "\tVizinhança: ";
    for( auto it : VertexesById[r->Id].Neighborhood ) {
        v = &VertexesById[it];
        cout << v->name << ' ';
    }
    cout << endl << endl;

    r->Set = 1;
    for( auto it : VertexesById[r->Id].Neighborhood ) {
        v = &VertexesById[it];
        cout << '\t' << r->name << "-->" << v->name << ".Set=" <<  v->Set << endl;
        if( v->Set == 0 ) {
            cout << "\tprocesse(" << r->name << "-->" << v->name << ")" << endl;
            GetAttributes(r, v);
            ShowAttributes(&v->attributes);
        } else if( v->Set == 1 ) {
            v->Parent = r;
            cout << "\tCalling recursion..." << endl;
            Count(v);
        }
    }
    cout << r->name << endl;
    r->Set = 2;
}

inline void ShowAttributes(AttributeSet *as)
{
    cout << "\tAttributes: ";
    for( auto it : *as ) {
        cout << it.first << ":" << it.second << ", ";
    }
    cout << endl;
}

inline void GetAttributes(Vertex *r, Vertex *v)
{
    for( auto it : v->attributes ) {
        if( it.second
    }
}

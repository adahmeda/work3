#include <graphviz/cgraph.h>
#include "conta-caminhos.h"

using namespace std;

VertexSetById VertexesById;
VertexSetByName VertexesByName;
AttributeSet Attributes;
string GraphName;


/*_________________________________________________________________________________*/
int main(void)
{
    Agraph_t *g;

    g = agread(stdin, NULL);
    GraphName = agnameof(g);

    ReadGraph(g);
    agclose(g);

    CountPaths();
    PrintVertexes();

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
        u.OutDegree = agdegree(g, v, false, true);
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

void CountPaths(void)
{
    Vertex *v;
    UINT count;
    UINT n;

    for( auto it : VertexesById ) {
        v = &VertexesById[it.first];
        v->Set = 0;
        v->Parent = NULL;
    }

    count = 0;
    n = (UINT)VertexesById.size();
    while ( count != n ) {
        for( auto it : VertexesById ) {
            v = &VertexesById[it.first];
            if( v->Set == 0 ) {
                if( Count(v) ) ++count;
            }
        }
    }
}

bool Count(Vertex *r)
{
    Vertex *v;

    r->Set = 1;
    for( auto it : VertexesById[r->Id].Neighborhood ) {
        v = &VertexesById[it];
        if( v->Set == 0 ) {
            if( CheckChildCondition(r, v) ) {
                r->Set = 0;
                return false;
            }
            GetAttributes(r, v);
        } else if( v->Set == 1 ) {
            v->Parent = r;
            Count(v);
        } else if( v->Set == 2 ) {
            GetAttributes(r, v);
        }
    }
    r->Set = 2;

    return true;
}

inline bool CheckChildCondition(Vertex *r, Vertex *v)
{
    for( auto each_attr : v->attributes ) {
        if( each_attr.second != 0 )
            return false;
    }

    return true;
}

inline void GetAttributes(Vertex *r, Vertex *v)
{
    for( auto it : v->attributes ) {
        if( it.second != 0 ) {
            if( v->OutDegree == 0 ) {
                if( r->attributes[it.first] >= 1 )
                    r->attributes[it.first] = it.second + 1;
                else
                    r->attributes[it.first] = 1;
            }else { /* vertex child is not a sink. */
                if( r->attributes[it.first] >= 1 )
                    r->attributes[it.first] += it.second;
                else
                    r->attributes[it.first] = it.second;
            }
        }
    }
}

void PrintVertexes(void)
{
    Vertex *v;
    AttributeSet::iterator each_attr;
    int count;

    cout << "strict digraph resultado_" << GraphName << " {" << endl;
    for( auto each_v : VertexesById ) {
        v = &VertexesById[each_v.first];
        cout << "\t\"" << v->name << '"';
        // Show attributes.
        each_attr = v->attributes.begin();
        count = 0;
        if( each_attr->second > 0 ) {
            cout << " [" << each_attr->first << '=' << each_attr->second;
            ++count;
        }
        for( ++each_attr; each_attr != v->attributes.end(); ++each_attr ) {
            if( each_attr->second > 0 ) {
                if( count == 0 )
                    cout << " [";
                else
                    cout << ',';
                cout << each_attr->first << '=' << each_attr->second;
                ++count;
            }
        }
        if( count > 0 )
            cout << "];";
        cout << endl;
        // Show vertexes and arcs.
        for( auto each_arc : v->Neighborhood ) {
            cout << '\t' << '"' << v->name << "\" -> \"" << VertexesById[each_arc].name << "\";" << endl;
        }
    }
    cout << '}' << endl;
    cout << flush;
}

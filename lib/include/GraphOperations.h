#ifndef TRABALHO_1_REFATORADO_GRAPHOPERATIONS_H
#define TRABALHO_1_REFATORADO_GRAPHOPERATIONS_H

#include "Graph.h"

class GraphOperations{
private:
    static bool verifyIsSameType(Graph * g1, Graph * g2);

protected:
    static Graph * unionUndirectedGraph(Graph *g1, Graph *g2);
    static Graph * unionDirectedGraph(Graph *g1, Graph *g2);

    static Graph * intersectionUndirectedGraph(Graph *g1, Graph *g2);
    static Graph * intersectionDirectedGraph(Graph *g1, Graph *g2);

    static Graph * differenceUndirectedGraph(Graph *g1, Graph *g2);
    static Graph * differenceDirectedGraph(Graph *g1, Graph *g2);

public:
    static Graph * Union(Graph * graph1, Graph * graph2);
    static Graph * Intersection(Graph * graph1, Graph * graph2);
    static Graph * Difference(Graph * graph1, Graph * graph2);
    static vector<Node*> RedePert(Graph * graph);

    vector<Node *> AGRR(Graph *graph);

    vector<Node *> AGRA(Graph *graph);

    void removeNodesFromVector(vector<Node *> &notSelectedNodes, Edge *edge) const;
};

#endif //TRABALHO_1_REFATORADO_GRAPHOPERATIONS_H

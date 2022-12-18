
#include "../include/Graph.h"
#include "../include/GraphOperations.h"
#include "iostream"
using namespace std;

// region Aux functions

bool GraphOperations::verifyIsSameType(Graph *g1, Graph *g2) {
    if(g1->isDirected() == g2->isDirected()){
        if(g1->isWeightedNode() == g2->isWeightedNode())
            if(g1->isWeightedEdge() == g2->isWeightedEdge())
                return true;
    }
    return false;
}

// region Union
Graph * GraphOperations::unionUndirectedGraph(Graph * g1, Graph * g2) {

    Graph * finalGraph = new Graph(g1->getOrder(),
                                   g1->isDirected(),
                                   g1->isWeightedEdge(),
                                   g1->isWeightedNode());

    if(g1->getOrder() >= g2->getOrder()) {

        for(auto node : g1->getAllNodes())
            for(auto edge : node->getAllUndirectedEdges()) {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }

        // Adiciona as arestas do G2 que nao estão presentes em G1
        for (auto node: g2->getAllNodes()) {
            for (auto edge: node->getAllUndirectedEdges()) {
                    finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    else {

        for(auto node : g2->getAllNodes())
            for(auto edge : node->getAllUndirectedEdges())
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());

        // Adiciona as arestas do G1 que nao estão presentes em G2
        for (auto node: g1->getAllNodes()) {
            for (auto edge: node->getAllUndirectedEdges()) {
                    finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    return finalGraph;
}

Graph * GraphOperations::unionDirectedGraph(Graph * g1, Graph * g2){

    Graph *finalGraph = nullptr;

    // O grafo uniao terá ordem do maior grafo
    if(g1->getOrder() >= g2->getOrder()) {
        finalGraph = new Graph(g1->getOrder(),
                                      g1->isDirected(),
                                      g1->isWeightedEdge(),
                                      g1->isWeightedNode());
    }
    else{
        finalGraph = new Graph(g2->getOrder(),
                                      g1->isDirected(),
                                      g1->isWeightedEdge(),
                                      g1->isWeightedNode());
    }

    // Copia todos nos e arestas de g1 para final graph
    for (auto node: g1->getAllNodes()) {
        for (auto edge: node->getAllOutputEdges())
            finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
    }

    // adiciona todos nos e arestas de g2 no finalGraph
    for (auto node: g2->getAllNodes()) {
        for (auto edge: node->getAllOutputEdges())
            finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
    }

    g1->generateAdjacencyList("../lib/output/GRAFO-1.txt");
    g2->generateAdjacencyList("../lib/output/GRAFO-2.txt");
    finalGraph->generateAdjacencyList("../lib/output/123Rogergueds.txt");

    return finalGraph;
}
// endregion

// region Intersection

Graph * GraphOperations::intersectionUndirectedGraph(Graph * g1, Graph * g2){

    Graph * finalGraph = new Graph(g1->getOrder(),
                                   g1->isDirected(),
                                   g1->isWeightedEdge(),
                                   g1->isWeightedNode());


    for(auto node : g1->getAllNodes()){
        for(auto edge : node->getAllUndirectedEdges()) {
            if (g2->getNode(node->getID())->searchEdge(edge->getTargetId())) {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    return finalGraph;
}

Graph * GraphOperations::intersectionDirectedGraph(Graph * g1, Graph * g2){

    Graph * finalGraph = new Graph(g1->getOrder(),
                                   g1->isDirected(),
                                   g1->isWeightedEdge(),
                                   g1->isWeightedNode());


    for(auto node : g1->getAllNodes()){
        for(auto edge : node->getAllOutputEdges()){
            if(g2->getNode(node->getID())->searchOutputEdge(edge->getTargetId()))
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
        }
    }

    return finalGraph;
}

// endregion

// region Difference
Graph * GraphOperations::differenceUndirectedGraph(Graph * g1, Graph * g2){
    Graph * finalGraph = new Graph(g1->getOrder(),
                                   g1->isDirected(),
                                   g1->isWeightedEdge(),
                                   g1->isWeightedNode());

    Graph * intersection = Intersection(g1, g2);

    for(auto node : g1->getAllNodes())
        for(auto edge : node->getAllUndirectedEdges()){
            if(intersection->searchNode(node->getID()))
                if(!intersection->getNode(node->getID())->searchEdge(edge->getTargetId()))
                    finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
        }

    return finalGraph;

}

Graph * GraphOperations::differenceDirectedGraph(Graph * g1, Graph * g2){
    return nullptr;
}

// endregion

Graph * GraphOperations::Union(Graph * g1, Graph * g2) {
    if(!verifyIsSameType(g1, g2)){
        cerr << endl << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if(g1->isDirected()){
        return unionDirectedGraph(g1, g2);
    }
    else{
        return unionUndirectedGraph(g1, g2);
    }
}

Graph * GraphOperations::Intersection(Graph * g1, Graph * g2){
    if(!verifyIsSameType(g1, g2)){
        cerr << endl << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if(g1->isDirected()){
        return intersectionDirectedGraph(g1, g2);
    }
    else{
        return intersectionUndirectedGraph(g1, g2);
    }
}

Graph * GraphOperations::Difference(Graph *g1, Graph *g2) {
    if(!verifyIsSameType(g1, g2)){
        cerr << endl << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if(g1->isDirected()){
        return differenceDirectedGraph(g1, g2);
    }
    else{
        return differenceUndirectedGraph(g1, g2);
    }
}

vector<Node*> GraphOperations::RedePert(Graph * graph){

    // Este vetor armazenará a sequencia de nós (conjunto solução)
    vector<Node*> finalSequence;
    finalSequence.clear();

    graph->generateAdjacencyList("../lib/output/lista de adjacencia.txt");

    // Insere na solução todos os nós que nao possuem dependência
//    for(auto node : graph->getAllNodes()) {
//        if (node->getAllInputEdges().empty()) {
//            node->setVisited(true);
//            finalSequence.push_back(node);
//        }
//    }

    //INSERE NA SOLUÇÃO OS QUE NAO POSSUEM DEPENDECIA
    // REMOVE NOS INPUT_EDGES OS QUE ESTAO NA SOLUCAO
    // Repito ate que todos vertices tenham sido visitados

    for(auto node : graph->getAllNodes()){
        if(node->getAllInputEdges().empty()) {
            finalSequence.push_back(node);
            node->setVisited(true);
        }
        if(node->getVisited())
        {
            for(auto nodeDependentes: node->getAllOutputEdges())
                graph->removeEdge(nodeDependentes->getTargetId(), node->getID());
        }
    }

    return finalSequence;
}
#ifndef TRABALHO_1_REFATORADO_GRAPH_H
#define TRABALHO_1_REFATORADO_GRAPH_H

#include <fstream>
#include "Node.h"

class Graph{
private:
    int order;
    bool directed;
    bool weighted_edge;
    bool weighted_node;
    Node *nodes;

protected:
    void insertNodeSortBySequence();
    void insertNodeSortById();
    void insertNodeSortByWeightedEdge();
    void insertNodeSortByWeightedNode();

    void insertUndirectedEdge(int originID, int targetID, float weight);
    void generateGraphVizDirected(ofstream& outFile);
    void generateGraphVizUndirected(ofstream& outFile);
    void removeUndirectedEdge(int id, int targetID);
    void removeDirectedEdge(int originID, int targetID);

    void MinimalDominantSubsetDirected(string output_path);

public:
    Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    ~Graph();

    int getNumNodesVisited();
    int getOrder();
    int getNumberOfEdges();
    bool isDirected();
    bool isWeightedEdge();
    bool isWeightedNode();

    void orderByID();
    void orderByWeight();
    void orderByDegree();

    void insertNode(int id, float weight);
    void removeNode(int id);
    bool searchNode(int id);
    Node * getNode(int id);

    void insertEdge(int id, int target_id, float weight);
    void removeEdge(int id, int targetID);

    vector<Node*> getAllNodes();
    void generateAdjacencyList(string output_path);
    void generateGraphViz(string output_path);

    void MinimalDominantSubset(string output_path);
};


#endif //TRABALHO_1_REFATORADO_GRAPH_H

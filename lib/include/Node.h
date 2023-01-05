//
// Created by pedro on 09/12/2022.
//

#ifndef TRABALHO_1_REFATORADO_NODE_H
#define TRABALHO_1_REFATORADO_NODE_H

#include "Edge.h"
#include "queue"
#include "vector"

using namespace std;

class Node{
private:
    int id;
    float weight;
    vector<Edge*> fan_out;
    vector<Edge*> fan_in;
    vector<Edge*> fan;

protected:
    Edge * getUndirectedEdge(int targetID);
    Edge * getInputEdge(int targetID);
    Edge * getOutputEdge(int targetID);


public:
    Node(int id, float weight);
    ~Node();

    int getID();
    float getWeight();

    int getOutDegree();
    int getInDegree();
    int getDegree();

    void setWeight(float weight);

    bool searchEdge(int targetID);
    bool searchInputEdge(int orignID);
    bool searchOutputEdge(int targetID);

    Edge * getEdge(int targetID);

    vector<Edge*> getAllInputEdges();
    vector<Edge*> getAllOutputEdges();

    void insertInputEdge(int targetID, float weight);
    void insertOutputEdge(int targetID, float weight);

    // Essa funcao deve ser utilizada atravez da classe "Graph".
    void insertUndirectedEdge(int targetID, float weight);

    void removeAllEdges();
    void removeAllInputEdges();
    void removeAllOutputEdges();
    void removeInputEdge(int id);
    void removeOutputEdge(int id);
    void removeUndirectedEdge(int id);

    void orderEdgesByWeight();
    void orderEdgesByID();

    void removeAllUndirectedEdges();

    bool searchUndirectedEdge(int edgeID);

    vector<Edge *> getAllUndirectedEdges();

    int getSumWeights();

};

#endif //TRABALHO_1_REFATORADO_NODE_H

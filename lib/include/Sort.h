#ifndef TRABALHO_1_REFATORADO_SORT_H
#define TRABALHO_1_REFATORADO_SORT_H

#include <vector>
#include <string>
#include "Node.h"

using namespace std;

class Sort{
private:

protected:
    static int PartitionNodeID(vector<Node*> &v, int start, int end);
    static void QuickSortNodeIDAux(vector<Node*> &v, int start, int end );

    static int PartitionEdgeID(vector<Edge*> &v, int start, int end);
    static void QuickSortEdgeIDAux(vector<Edge*> &v, int start, int end );

    static int PartitionEdgeWeight(vector<Edge*> &v, int start, int end);
    static void QuickSortEdgeWeightAux(vector<Edge*> &v, int start, int end );

    static int PartitionNodeWeight(vector<Node*> &v, int start, int end);
    static void QuickSortNodeWeightAux(vector<Node*> &v, int start, int end );

public:
    static void SortByID(vector<Node*> &v);
    static void SortByID(vector<Edge*> &v);

    static void SortByWeight(vector<Node*> &v);
    static void SortByWeight(vector<Edge*> &v);

    static void SortByWeightAndEdges(vector<Node *> &v);
};

#endif //TRABALHO_1_REFATORADO_SORT_H

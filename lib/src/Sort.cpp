#include "../include/Sort.h"

// TODO: Verificar se é end = v.size() ou end = ( v.size() - 1 )

void Sort::SortByID(vector<Node*> &v) {
    QuickSortNodeIDAux(v, 0, v.size() - 1);
}

void Sort::SortByID(vector<Edge *> &v) {
    QuickSortEdgeIDAux(v, 0, v.size() - 1);
}

void Sort::SortByWeight(vector<Edge*> &v){
    QuickSortEdgeWeightAux(v, 0, v.size() - 1);
};

void Sort::SortByWeight(vector<Node*> &v){
    QuickSortNodeWeightAux(v, 0, v.size() - 1);
};

// region Ordenacao dos nós pelo id
int Sort::PartitionNodeID(vector<Node*> &v, int start, int end){
    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i]->getID() < v[pivot]->getID()){
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;
}

void Sort::QuickSortNodeIDAux(vector<Node*> &v, int start, int end ){
    if(start<end){
        int p = PartitionNodeID(v,start,end);
        QuickSortNodeIDAux(v,start,p-1);
        QuickSortNodeIDAux(v,p+1,end);
    }
}
// endregion

// region Ordenacao das arestas pelo id
int Sort::PartitionEdgeID(vector<Edge*> &v, int start, int end){
    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i]->getTargetId() < v[pivot]->getTargetId()){
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;
}

void Sort::QuickSortEdgeIDAux(vector<Edge*> &v, int start, int end ){
    if(start<end){
        int p = PartitionEdgeID(v,start,end);
        QuickSortEdgeIDAux(v,start,p-1);
        QuickSortEdgeIDAux(v,p+1,end);
    }
}
// endregion

// region Ordenacao das arestas pelo peso

int Sort::PartitionEdgeWeight(vector<Edge*> &v, int start, int end){
    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i]->getWeight() < v[pivot]->getWeight()){
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;
}

void Sort::QuickSortEdgeWeightAux(vector<Edge*> &v, int start, int end ){
    if(start<end){
        int p = PartitionEdgeWeight(v,start,end);
        QuickSortEdgeWeightAux(v,start,p-1);
        QuickSortEdgeWeightAux(v,p+1,end);
    }
}

// endregion

// region Ordenacao dos nós pelo peso

int Sort::PartitionNodeWeight(vector<Node*> &v, int start, int end){
    int pivot = end;
    int j = start;
    for(int i=start;i<end;++i){
        if(v[i]->getWeight() < v[pivot]->getWeight()){
            swap(v[i],v[j]);
            ++j;
        }
    }
    swap(v[j],v[pivot]);
    return j;
}

void Sort::QuickSortNodeWeightAux(vector<Node*> &v, int start, int end ){
    if(start<end){
        int p = PartitionNodeWeight(v,start,end);
        QuickSortNodeWeightAux(v,start,p-1);
        QuickSortNodeWeightAux(v,p+1,end);
    }
}

// endregion

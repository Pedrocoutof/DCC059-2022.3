#include "../include/Graph.h"
#include "iostream"
#include "../include/Sort.h"

using namespace std;

Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node){
    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->nodes.clear();
}

Graph::~Graph() {}


bool Graph::searchNode(int id) {
    for (auto node : this->nodes)
        if(node->getID() == id)
            return true;

    return false;
}

void Graph::generateAdjacencyList(string output_path) {
    ofstream out;
    out.open(output_path);

    if(this->directed) {

        for (auto node: nodes) {
            out << endl << "[" << (node)->getID() << "]";

            out << "\n\tIn : <";
            for (auto edge: (node)->getAllInputEdges()) {
                out << (edge)->getTargetId() << ", ";
            }
            out << ">" << endl;

            out << "\tOut : <";
            for (auto edge: node->getAllOutputEdges()) {
                out << (edge)->getTargetId() << ", ";
            }
            out << ">" << endl;

        }
    }

    else{

        for (auto node: nodes) {
            out << endl << "[" << (node)->getID() << "]";

            out << "\t : <";
            for (auto edge: (node)->getAllUndirectedEdges()) {
                out << (edge)->getTargetId() << ", ";
            }
            out << ">" << endl;

        }
    }
}

void Graph::orderByID() {
    Sort::SortByID(this->nodes);

    for( auto it : nodes){
        it->orderEdgesByID();
    }
}

void Graph::orderByWeight(){

    if(this->weighted_node){
        Sort::SortByWeight(nodes);

        for(auto node : this->nodes)
            node->orderEdgesByID();
    }

    else{
        Sort::SortByID(this->nodes);

        for(auto node : this->nodes)
            node->orderEdgesByWeight();
    }
}

void Graph::orderByDegree() {
    Sort::SortByDegree(this->nodes);
}

// region Inserts

void Graph::insertUndirectedEdge(int originID, int targetID, float weight) {
    getNode(originID)->insertUndirectedEdge(targetID, weight);
    getNode(targetID)->insertUndirectedEdge(originID, weight);
}

void Graph::insertNode(int id, float weight) {
    Node * newNode = new Node(id, weight);
    this->nodes.push_back(newNode);
}

void Graph::insertEdge(int id, int target_id, float weight){

    // Verificamos se existe o no de origem
    if(getNode(id) == nullptr)
        this->insertNode(id, weight);

    // Verificamos se existe o no de destino
    if(getNode(target_id) == nullptr)
        this->insertNode(target_id, weight);

    // caso seja direcionado
    if(this->directed){
        // Insere na origem uma aresta para o destino
        this->getNode(id)->insertOutputEdge(target_id, weight);

        // Insere no destino uma aresta de entrada
        this->getNode(target_id)->insertInputEdge(id, weight);
    }

        // caso NÃO seja direcionado
    else{

        // evita multi-aresta
        if(getNode(id)->searchEdge(target_id))
            return;

        this->insertUndirectedEdge(id, target_id, weight);
    }

}
// endregion

// region Removes

void Graph::removeEdge(int id, int targetID) {
    if(this->directed){
        this->removeDirectedEdge(id, targetID);
    }
    else{
        removeUndirectedEdge(id, targetID);
    }
}

void Graph::removeUndirectedEdge(int id, int targetID){
    // Por ser bidirecional deve-se remover de ORIGEM->ALVO && ALVO->ORIGEM
    this->getNode(id)->removeUndirectedEdge(targetID);
    this->getNode(targetID)->removeUndirectedEdge(id);
}

void Graph::removeDirectedEdge(int originID, int targetID){
    // Remove a aresta de saida
    this->getNode(originID)->removeOutputEdge(targetID);

    // Remove a aresta de entrada
    this->getNode(targetID)->removeInputEdge(originID);
}

void Graph::removeNode(int id) {
    auto it = nodes.begin();

    for( ; it != nodes.end() ;it++){
        if( (*it)->getID() == id){
            nodes.erase(it);
        }
    }

}
// endregion

// region Graphviz

void Graph::generateGraphVizUndirected(ofstream& outFile) {
    outFile << "strict graph Graph {";

    if(this->weighted_node){
        for(auto node : this->nodes){
            outFile << endl << node->getID() << "[label=" << node->getWeight() << "]";
        }
    }

    for(auto node : this->nodes){
        for(auto edge : node->getAllUndirectedEdges()){

            outFile << endl << node->getID();
            outFile << "--" << edge->getTargetId();

            if(weighted_edge){
                outFile << "[label=" << edge->getWeight() << "]";
            }
        }
    }
    outFile << endl << "}";
}

void Graph::generateGraphVizDirected(ofstream& outFile) {
    outFile << "strict digraph Digraph {";

    if(this->weighted_node){
        for(auto node : this->nodes){
            outFile << endl << node->getID() << "[weight=" << node->getWeight() << "]";
        }
    }

    for(auto node : this->nodes){
        for(auto edge : node->getAllOutputEdges()){

            outFile << endl << node->getID();
            outFile << "->" << edge->getTargetId();

            if(weighted_edge){
                outFile << "[label=" << edge->getWeight() << "]";
            }
        }
    }
    outFile << endl << "}";
}

// TODO : Consertar erro para criacao de instancias maiores
void Graph::generateGraphViz(string output_path) {
    ofstream outFile;
    outFile.open(output_path);

    if(outFile.is_open()){
        if(this->directed){
            generateGraphVizDirected(outFile);
            return;
        }
        else{
            generateGraphVizUndirected(outFile);
            return;
        }
    }
    else{
        cerr << endl << "Nao foi possivel abrir arquivo de saida para gerar o GraphViz.";
        exit(404);
    }

}

// endregion

// region Get's

Node * Graph::getNode(int id) {
    for (auto node : this->nodes)
        if(node->getID() == id)
            return node;

    return nullptr;
}

int Graph::getOrder() {
    return this->order;

    // Ou pode ser implementada com:
    // return this->nodes.size();
}

int Graph::getNumberOfEdges() {

    int total = 0;

    if(directed){
        for(Node* it : nodes){
            total += it->getOutDegree();
            total += it->getInDegree();
        }
    }

    else{
        for(Node* it : nodes){
            total += it->getDegree();
        }
        total = total / 2; // Teorema do aperto de mão
    }

    return total;
}

bool Graph::isDirected() {
    return this->directed;
}

bool Graph::isWeightedEdge() {
    return this->weighted_edge;
}

bool Graph::isWeightedNode() {
    return this->weighted_node;
}

vector<Node*> Graph::getAllNodes(){
    return this->nodes;
}

// endregion

bool verificaNosVisitados(vector<bool> arr){
    for(auto index: arr)
        if(index == false)
            return false;

    return true;
}

// Estrutura auxiliar para inserir de forma ordenada os nós na pq
struct compDegree{
    bool operator() (Node* const n1, Node* const n2){
        if (n1->getOutDegree() != n2->getOutDegree()){
            return n1->getOutDegree() < n2->getOutDegree();
        }
        else{
            return n1->getWeight() < n2->getWeight();
        }
    }
};

void Graph::MinimalDominantSubsetDirected(string output_path) {

}

void Graph::MinimalDominantSubset(string output_path){
    if(this->directed){
        cerr << endl << "Ainda nao implementado : " << __LINE__;
    }
    else{
        cerr << endl << "Ainda nao implementado : " << __LINE__;
    }
}
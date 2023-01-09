#include "../include/Node.h"
#include "../include/Sort.h"

Node::Node(int id, float weight){
    this->id = id;
    this->weight = weight;
    this->fan_in.clear();
    this->fan_out.clear();
    this->fan.clear();
}

Node::~Node() {}

void Node::setWeight(float weight) {
    this->weight = weight;
}

void Node::orderEdgesByID() {
    Sort::SortByID(this->fan_in);
    Sort::SortByID(this->fan_out);
    Sort::SortByID(this->fan);
}

void Node::orderEdgesByWeight() {
    Sort::SortByWeight(this->fan_in);
    Sort::SortByWeight(this->fan_out);
    Sort::SortByWeight(this->fan);
}

// region Inserts

void Node::insertUndirectedEdge(int targetID, float weight){
    Edge * newEdge = new Edge(targetID, weight);
    this->fan.push_back(newEdge);
};

void Node::insertInputEdge(int originID, float weight) {

    if(searchInputEdge(originID))
        return;

    Edge * newEdge = new Edge(originID, weight);
    this->fan_in.push_back(newEdge);
}

void Node::insertOutputEdge(int targetID, float weight) {

    if(searchOutputEdge(targetID))
        return;

    Edge * newEdge = new Edge(targetID, weight);
    this->fan_out.push_back(newEdge);
}
// endregion

// region Removes
void Node::removeAllEdges() {
    this->fan_in.clear();
    this->fan_out.clear();
    this->fan.clear();
}

void Node::removeAllInputEdges() {
    this->fan_in.clear();
}

void Node::removeAllOutputEdges() {
    this->fan_out.clear();
}

void Node::removeAllUndirectedEdges(){
    this->fan.clear();
}

void Node::removeInputEdge(int originID) {
    auto it = fan_in.begin();

    for( ; it != fan_in.end() ;it++){
        if( (*it)->getTargetId() == originID){
            fan_in.erase(it);
        }
    }
}

void Node::removeOutputEdge(int targetID) {
    auto it = fan_out.begin();

    for( ; it != fan_out.end() ;it++){
        if( (*it)->getTargetId() == targetID){
            fan_out.erase(it);
        }
    }
}

void Node::removeUndirectedEdge(int id){
    auto it = fan.begin();

    for( ; it != fan.end() ;it++){
        if( (*it)->getTargetId() == id){
            fan.erase(it);
        }
    }
}


// endregion

// region Search's
bool Node::searchEdge(int targetID) {
    if(searchUndirectedEdge(targetID)){
        return true;
    }

    if(searchOutputEdge(targetID))
        return true;

    if(searchInputEdge(targetID))
        return true;

    return false;
}

bool Node::searchUndirectedEdge(int edgeID){
    for(auto it : this->fan){
        if(it->getTargetId() == edgeID)
            return true;
    }

    return false;
}

bool Node::searchInputEdge(int originID) {
    for(auto it : this->fan_in){
        if(it->getTargetId() == originID)
            return true;
    }

    return false;
}

bool Node::searchOutputEdge(int targetID) {
    for(auto it : this->fan_out){
        if(it->getTargetId() == targetID)
            return true;
    }
    return false;
}
// endregion

// region Get's
int Node::getInDegree() {
    return this->fan_in.size();
}

int Node::getOutDegree() {
    return this->fan_out.size();
}

int Node::getID() {
    return this->id;
}

float Node::getWeight() {
    return this->weight;
}

Edge * Node::getEdge(int targetID) {
    Edge * search;

    search = getUndirectedEdge(targetID);
    if( search != nullptr)
        return search;

    search = getInputEdge(targetID);
    if( search != nullptr)
        return search;

    search = getOutputEdge(targetID);
    if(search != nullptr)
        return search;

    return nullptr;
}

Edge * Node::getUndirectedEdge(int targetID){

    for(auto it : this->fan){
        if(it->getTargetId() == targetID)
            return it;
    }

    return nullptr;
}

Edge * Node::getInputEdge(int originID) {

    for(auto it : this->fan_in){
        if(it->getTargetId() == originID)
            return it;
    }

    return nullptr;
}

Edge * Node::getOutputEdge(int targetID) {

    for(auto it : this->fan_out){
        if(it->getTargetId() == targetID)
            return it;
    }

    return nullptr;
}

vector<Edge*> Node::getAllInputEdges(){
    return this->fan_in;
}

vector<Edge*> Node::getAllOutputEdges(){
    return this->fan_out;
}

vector<Edge*> Node::getAllUndirectedEdges(){
    return this->fan;
}
// endregion

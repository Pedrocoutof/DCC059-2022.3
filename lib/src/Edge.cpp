#include "../include/Edge.h"

Edge::Edge(int targetID, float weight) {
    this->targetID = targetID;
    this->weight = weight;
}

Edge::~Edge() {}

int Edge:: getTargetId(){
    return targetID;
}

float Edge::getWeight(){
    return weight;
}

void Edge::setWeight(float weight) {
    this->weight = weight;
}
//
// Created by pedro on 09/12/2022.
//

#ifndef TRABALHO_1_REFATORADO_EDGE_H
#define TRABALHO_1_REFATORADO_EDGE_H

class Edge{
private:
    int targetID;
    float weight;

public:
    Edge(int targetID, float weight);
    ~Edge();

    int getTargetId();

    float getWeight();
    void setWeight(float weight);


};

#endif //TRABALHO_1_REFATORADO_EDGE_H

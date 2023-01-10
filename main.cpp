#include <iostream>
#include "lib/include/Graph.h"
#include "lib/include/Sort.h"
#include "lib/include/GraphOperations.h"

/*
 * TODO:
 *      Implementar a funcao para realizar a diferença entre grafos
 *          "       "   "     "   Rede Pert
 *          "       "   "     "   problema do subconjunto dominante
 */

using namespace std;

const string OUTPUT_PATH = "./lib/output/";
const string INPUT_PATH = "./lib/input/";

void printError(int line, string arquivo ,string message){
    cerr <<  endl << "[ERRO - " + arquivo + " : " << line << "] " + message;
}

ifstream selectFile(){

    ifstream nameFiles;
    nameFiles.open(INPUT_PATH + "nome_arquivos.txt");

    if(nameFiles.is_open()){

        string name_title;
        int idSelected = -1;

        for(int id = 0; nameFiles.peek() != EOF; id++){
            nameFiles >> name_title;
            cout << endl << "[" << id << "] - " << name_title;
        }

        cout << endl << "\t>> ";
        cin >> idSelected;
        nameFiles.clear();
        nameFiles.seekg(0);

        for(int id = 0; nameFiles.peek() != EOF; id++){
            nameFiles >> name_title;
            if(idSelected == id)
            {
                ifstream selectedFile;
                selectedFile.open(INPUT_PATH + name_title);
                return selectedFile;
            }
        }

    }
    printError(__LINE__, "main", "Nao foi possivel abrir arquivo selecionado");
    exit(-1);
}

Graph * readFile(ifstream& input_file, bool directed, bool weightedEdge, bool weightedNode){
    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    input_file >> order;

    Graph * graph = new Graph(order, directed, weightedEdge, weightedNode);

    // Sem peso nas arestas e no nó
    if(!graph->isWeightedEdge() && !graph->isWeightedNode()){
        while(input_file >> idNodeSource >> idNodeTarget) {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    }

    // Peso nas arestas
    else if(graph->isWeightedEdge() && !graph->isWeightedNode() ){
        float edgeWeight;
        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);

        }

    }

    // Peso nos nós
    else if(graph->isWeightedNode() && !graph->isWeightedEdge()){
        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }

    // Peso nas arestas e nós
    else if(graph->isWeightedNode() && graph->isWeightedEdge()){
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;
        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }

    return graph;

};

void PrintVector(vector<Node*> v){

    for(auto i : v)
        cout<< i->getID() <<" ";

    cout<<"\n\n";
}

int main(int argc, char *argv[]) {


    if(argc != 6){
        //printError(__LINE__, "main", "Nao foi passado o numero de parametros correto.");

        ifstream file1, file2;
        file1 = selectFile();
        //file2 = selectFile();

        bool directed = false, weightedEdge = false, weightedNode = true;

        Graph * g1 = readFile(file1, directed, weightedEdge, weightedNode);
        //Graph * g2 = readFile(file2, directed, weightedEdge, weightedNode);

//        g1->generateGraphViz(OUTPUT_PATH + "g1.dot");
//        g2->generateGraphViz(OUTPUT_PATH + "g2.dot");
//
//
//        Graph * _union = GraphOperations::Union(g1, g2);
//        _union->generateGraphViz(OUTPUT_PATH + "union.dot");
//        _union->generateAdjacencyList(OUTPUT_PATH + "union.txt");
//
//        Graph * _intersection = GraphOperations::Intersection(g1, g2);
//        _intersection->generateGraphViz(OUTPUT_PATH + "intersection.dot");
//        _intersection->generateAdjacencyList(OUTPUT_PATH + "intersection.txt");
//
//        Graph * _difference = GraphOperations::Difference(g1, g2);
//        _difference->generateGraphViz(OUTPUT_PATH + "difference.dot");
//        _difference->generateAdjacencyList(OUTPUT_PATH + "difference.txt");
//
        vector<Node*> _redePert = GraphOperations::RedePert(g1);
        //PrintVector(_redePert);
    }

    return 0;
}

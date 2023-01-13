#include <iostream>
#include "lib/include/Graph.h"
#include "lib/include/Sort.h"
#include "lib/include/GraphOperations.h"
#include "string"

/*
 * TODO:
 *      Implementar a funcao para realizar a diferença entre grafos
 *          "       "   "     "   Rede Pert
 *          "       "   "     "   problema do subconjunto dominante
 */

using namespace std;

const string OUTPUT_PATH = "./lib/output/";
const string INPUT_PATH = "./lib/input/";

void printError(int line, string arquivo, string message)
{
    cerr << endl
         << "[ERRO - " + arquivo + " : " << line << "] " + message;
}

ifstream selectFile()
{

    ifstream nameFiles;
    nameFiles.open(INPUT_PATH + "nome_arquivos.txt");

    if (nameFiles.is_open())
    {

        string name_title;
        int idSelected = -1;

        for (int id = 0; nameFiles.peek() != EOF; id++)
        {
            nameFiles >> name_title;
            cout << endl
                 << "[" << id << "] - " << name_title;
        }

        cout << endl
             << "\t>> ";
        cin >> idSelected;
        nameFiles.clear();
        nameFiles.seekg(0);

        for (int id = 0; nameFiles.peek() != EOF; id++)
        {
            nameFiles >> name_title;
            if (idSelected == id)
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

Graph *readFile(ifstream &input_file, bool directed, bool weightedEdge, bool weightedNode)
{
    // Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    input_file >> order;

    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    // Sem peso nas arestas e no nó
    if (!graph->isWeightedEdge() && !graph->isWeightedNode())
    {
        while (input_file >> idNodeSource >> idNodeTarget)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, 0);
        }
    }

    // Peso nas arestas
    else if (graph->isWeightedEdge() && !graph->isWeightedNode())
    {
        float edgeWeight;
        while (input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
        }
    }

    // Peso nos nós
    else if (graph->isWeightedNode() && !graph->isWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight;

        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    // Peso nas arestas e nós
    else if (graph->isWeightedNode() && graph->isWeightedEdge())
    {
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;
        while (input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
        }
    }

    return graph;
};

Graph *readFilePartTwo(ifstream &input_file, bool directed, bool weightedEdge, bool weightedNode)
{
    // bool directed = false, weightedEdge = false, weightedNode = true;
    int order = 0;
    string line;
    int weightNode = 0;

    input_file >> line; // ignora primeira linha
    input_file >> order;

    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);

    for (line.clear(); line != "******************WEIGHTS*****************************"; input_file >> line)
    {
    }

    for (int i = 0; i < order; i++)
    {
        input_file >> weightNode;
        graph->insertNode(i, weightNode);
    }

    input_file >> line; // ignora primeira linha

    int connected = 0;

    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {

            input_file >> connected;

            if ((connected == 1) && (i != j))
                graph->insertEdge(i, j, 0);
        }
    }

    return graph;
}

void PrintVector(vector<Node *> v)
{
    cout << endl;
    for (auto i : v)
        cout << i->getID() << " ";

    cout << "\n\n";
}

int main(int argc, char *argv[])
{

    if (argc != 6)
    {
        printError(__LINE__, "main.cpp", "Numero de paramentros incorreto.");
    }
    else
    {

        cout << argv[0] << endl;
        cout << argv[1] << endl;
        cout << argv[2] << endl;
        cout << argv[3] << endl;
        cout << argv[4] << endl;
        cout << argv[5] << endl;

        int select = 0;
        cout << endl
             << "[1] - Algoritmo Guloso";
        cout << endl
             << "[2] - Algoritmo Guloso Randomizado Adaptativo";
        cout << endl
             << "[3] - Algoritmo Guloso Randomizado Reativo";
        cout << endl
             << "\t>> ";
        cin >>
            select;

        ifstream file;
        int sum = 0;
        float alpha =0;
        int literatura = 0;
        file.open(argv[1]);
        Graph *g = readFilePartTwo(file, stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
        vector<Node *> sol = vector<Node*>();
        switch (select)
        {
        case 1:
            sol = GraphOperations::AlgortimoGuloso(g);
            sum = 0;
            for (auto node : sol)
            {
                cout << endl
                     << "ID: " << node->getID() << "\tPeso: " << node->getWeight() << endl;
                sum += node->getWeight();
            }
            cout << endl
                 << " = " << sum<<endl;
            break;

        case 2:
            sum = 0;
            cout << "\nSelecione o valor de alpha: \n\t>> ";
            cin >> alpha;
            sol = GraphOperations::AGRA(g, alpha);
            for (auto node : sol)
            {
                cout << endl
                     << "ID: " << node->getID() << "\tPeso: " << node->getWeight() << endl;
                sum += node->getWeight();
            }
            cout << endl
                 << " = " << sum<<endl;
            break;
        case 3:
            sum = 0;
            cout << "Selecione o valor de alpha: \n\t>> ";
            cin >> alpha;
            cout << endl;

            cout << "Selecione o valor de literatura: \n\t>> ";
            cin >> literatura;
            cout << endl;

            sol = GraphOperations::AGRR(g, alpha, literatura);
            for (auto node : sol)
            {
                cout << endl
                     << "ID: " << node->getID() << "\tPeso: " << node->getWeight() << endl;
                sum += node->getWeight();
            }
            cout << endl
                 << " = " << sum<<endl;
            break;

        default:
            break;
        }
    }

    return 0;
}

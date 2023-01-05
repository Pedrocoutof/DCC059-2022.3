
#include "../include/Graph.h"
#include "../include/GraphOperations.h"
#include "iostream"
#include "../include/Sort.h"

using namespace std;

// region Aux functions

bool GraphOperations::verifyIsSameType(Graph *g1, Graph *g2)
{
    if (g1->isDirected() == g2->isDirected())
    {
        if (g1->isWeightedNode() == g2->isWeightedNode())
            if (g1->isWeightedEdge() == g2->isWeightedEdge())
                return true;
    }
    return false;
}

// region Union
Graph *GraphOperations::unionUndirectedGraph(Graph *g1, Graph *g2)
{

    Graph *finalGraph = new Graph(g1->getOrder(),
                                  g1->isDirected(),
                                  g1->isWeightedEdge(),
                                  g1->isWeightedNode());

    if (g1->getOrder() >= g2->getOrder())
    {

        for (auto node : g1->getAllNodes())
            for (auto edge : node->getAllUndirectedEdges())
            {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }

        // Adiciona as arestas do G2 que nao estão presentes em G1
        for (auto node : g2->getAllNodes())
        {
            for (auto edge : node->getAllUndirectedEdges())
            {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    else
    {

        for (auto node : g2->getAllNodes())
            for (auto edge : node->getAllUndirectedEdges())
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());

        // Adiciona as arestas do G1 que nao estão presentes em G2
        for (auto node : g1->getAllNodes())
        {
            for (auto edge : node->getAllUndirectedEdges())
            {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    return finalGraph;
}

Graph *GraphOperations::unionDirectedGraph(Graph *g1, Graph *g2)
{

    Graph *finalGraph = nullptr;

    // O grafo uniao terá ordem do maior grafo
    if (g1->getOrder() >= g2->getOrder())
    {
        finalGraph = new Graph(g1->getOrder(),
                               g1->isDirected(),
                               g1->isWeightedEdge(),
                               g1->isWeightedNode());
    }
    else
    {
        finalGraph = new Graph(g2->getOrder(),
                               g1->isDirected(),
                               g1->isWeightedEdge(),
                               g1->isWeightedNode());
    }

    // Copia todos nos e arestas de g1 para final graph
    for (auto node : g1->getAllNodes())
    {
        for (auto edge : node->getAllOutputEdges())
            finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
    }

    // adiciona todos nos e arestas de g2 no finalGraph
    for (auto node : g2->getAllNodes())
    {
        for (auto edge : node->getAllOutputEdges())
            finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
    }

    g1->generateAdjacencyList("../lib/output/GRAFO-1.txt");
    g2->generateAdjacencyList("../lib/output/GRAFO-2.txt");
    finalGraph->generateAdjacencyList("../lib/output/123Rogergueds.txt");

    return finalGraph;
}
// endregion

// region Intersection

Graph *GraphOperations::intersectionUndirectedGraph(Graph *g1, Graph *g2)
{

    Graph *finalGraph = new Graph(g1->getOrder(),
                                  g1->isDirected(),
                                  g1->isWeightedEdge(),
                                  g1->isWeightedNode());

    for (auto node : g1->getAllNodes())
    {
        for (auto edge : node->getAllUndirectedEdges())
        {
            if (g2->getNode(node->getID())->searchEdge(edge->getTargetId()))
            {
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
            }
        }
    }

    return finalGraph;
}

Graph *GraphOperations::intersectionDirectedGraph(Graph *g1, Graph *g2)
{

    Graph *finalGraph = new Graph(g1->getOrder(),
                                  g1->isDirected(),
                                  g1->isWeightedEdge(),
                                  g1->isWeightedNode());

    for (auto node : g1->getAllNodes())
    {
        for (auto edge : node->getAllOutputEdges())
        {
            if (g2->getNode(node->getID())->searchOutputEdge(edge->getTargetId()))
                finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
        }
    }

    return finalGraph;
}

// endregion

// region Difference
Graph *GraphOperations::differenceUndirectedGraph(Graph *g1, Graph *g2)
{
    Graph *finalGraph = new Graph(g1->getOrder(),
                                  g1->isDirected(),
                                  g1->isWeightedEdge(),
                                  g1->isWeightedNode());

    Graph *intersection = Intersection(g1, g2);

    for (auto node : g1->getAllNodes())
        for (auto edge : node->getAllUndirectedEdges())
        {
            if (intersection->searchNode(node->getID()))
                if (!intersection->getNode(node->getID())->searchEdge(edge->getTargetId()))
                    finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
        }

    return finalGraph;
}

Graph *GraphOperations::differenceDirectedGraph(Graph *g1, Graph *g2)
{
    Graph *finalGraph = new Graph(g1->getOrder(),
                                  g1->isDirected(),
                                  g1->isWeightedEdge(),
                                  g1->isWeightedNode());

    Graph *intersection = Intersection(g1, g2);

    for (auto node : g1->getAllNodes())
        for (auto edge : node->getAllOutputEdges())
        {
            if (intersection->searchNode(node->getID()))
                if (!intersection->getNode(node->getID())->searchEdge(edge->getTargetId()))
                    finalGraph->insertEdge(node->getID(), edge->getTargetId(), edge->getWeight());
        }

    return finalGraph;
}

// endregion

// endregion

Graph *GraphOperations::Union(Graph *g1, Graph *g2)
{
    if (!verifyIsSameType(g1, g2))
    {
        cerr << endl
             << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if (g1->isDirected())
    {
        return unionDirectedGraph(g1, g2);
    }
    else
    {
        return unionUndirectedGraph(g1, g2);
    }
}

Graph *GraphOperations::Intersection(Graph *g1, Graph *g2)
{
    if (!verifyIsSameType(g1, g2))
    {
        cerr << endl
             << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if (g1->isDirected())
    {
        return intersectionDirectedGraph(g1, g2);
    }
    else
    {
        return intersectionUndirectedGraph(g1, g2);
    }
}

Graph *GraphOperations::Difference(Graph *g1, Graph *g2)
{
    if (!verifyIsSameType(g1, g2))
    {
        cerr << endl
             << "Nao eh possivel realizar a uniao de dois grafos diferentes";
        return nullptr;
    }

    if (g1->isDirected())
    {
        return differenceDirectedGraph(g1, g2);
    }
    else
    {
        return differenceUndirectedGraph(g1, g2);
    }
}

bool nodeIsInSolution(vector<Node *> solution, Node *nodeSearch)
{

    if (solution.empty())
        return true;

    for (auto x : solution)
    {
        if (x->getID() == nodeSearch->getID())
            return true;
    }

    return false;
}

bool verifyPred(Node *node, vector<Node *> solution)
{
    bool flag = false;

    for (auto inputEdge : node->getAllInputEdges())
    {
        for (auto sNode : solution)
        {
            if (inputEdge->getTargetId() == sNode->getID())
            {
                flag = true;
                break;
            }
        }

        if (flag == false)
        {
            return false;
        }
    }

    return true;
}

bool isInSol(Node *x, vector<Node*> S)
{
    for (auto predX : x->getAllInputEdges())
        for (auto sol : S)
            if (predX->getTargetId() != sol->getID())
                return false;
    return true;
}

vector<Node *> GraphOperations::RedePert(Graph *graph)
{
    graph->generateGraphViz("./testegrafo.dot");
    graph->generateAdjacencyList("./testegrafoADJ.txt");

    // Este vetor armazenará a sequencia de nós (conjunto solução)
    vector<Node *> S;
    S.clear();

    int alpha[graph->getOrder()];
    int beta[graph->getOrder()];
    bool visited[graph->getOrder()];

    for (int i = 0; i < graph->getOrder(); i++)
    {
        beta[i] = 0;
        alpha[i] = 0;
        visited[i] = false;
    }

    int oldAlpha = 0;
    int newAlpha = 0;

    // Insere na solução todos os nós que nao possuem dependência
    for (auto node : graph->getAllNodes())
        if (node->getAllInputEdges().empty())
        {
            S.push_back(node);
            visited[node->getID() - 1] = true;
        }
    vector<Node *> NoList = graph->getAllNodes(); 
    for (auto x : NoList)
    {
        for (auto nodeS : S)
            if (x->getID() != nodeS->getID() && isInSol(x, S)){ //verifica a condiçao do enquanto
                
                
                S.push_back(x);
                 
            }
        // Se nao cair na condição add dnv o vertice no e vai para o proximo
        NoList.push_back(x);
                
    }

    for (int i = 0; i < graph->getOrder(); i++)
    {
        cout << "\n\nNo: " << graph->getNode(i + 1)->getID() << "  Alpha: " << alpha[i] << "\n";
    }

    return S;
}

//algoritmo guloso randomizado reativo
vector<Node *> GraphOperations::AGRR(Graph *graph){
    vector<Node *> selectedNodes;
    vector<Node *> notSelectedNodes = graph->getAllNodes();
    Sort *sort = new Sort();
    //criterio
    sort->SortByWeightAndEdges(notSelectedNodes);
    while(!notSelectedNodes.empty()){
        int range = notSelectedNodes.size();
        int randN = rand() % range + 0;
        //adicionando um vértice aleatório dos não selecionados entre os vértices selecionados
        Node* selectedNode = notSelectedNodes.at(randN);
        selectedNodes.push_back(selectedNode);
        //removendo os adjacentes do selecionado dos não selecionados
        for(auto edge: selectedNode->getAllUndirectedEdges()){
            removeNodesFromVector(notSelectedNodes, edge);
        }
        auto it = notSelectedNodes.begin();
        //removendo o nó
        for( ; it != notSelectedNodes.end() ;it++){
            if( (*it)->getID() == selectedNode->getID()){
                notSelectedNodes.erase(it);
            }
        }


    }
    return selectedNodes;
}

void GraphOperations::removeNodesFromVector(vector<Node *> &notSelectedNodes, Edge *edge) const {
    auto it = notSelectedNodes.begin();
    for( ; it != notSelectedNodes.end() ;it++){
        //se id do vértice for igual alvo da aresta remove
        if( (*it)->getID() == edge->getTargetId()){
            notSelectedNodes.erase(it);
        }
    }
}



//algoritmo guloso randomizado adaptativo
vector<Node *> GraphOperations::AGRA(Graph *graph){
    vector<Node *> selectedNodes;
    vector<Node *> notSelectedNodes = graph->getAllNodes();
    Sort *sort = new Sort();
    int range = notSelectedNodes.size()/10;
    int randN = rand() % range + 0;
    int randomNode;
    for(int i =0; i>randN;i++){
        randomNode = rand() % (range * 10) + 0;
        Node* selectedNode = notSelectedNodes.at(randomNode);
        selectedNodes.push_back(selectedNode);
        //removendo os adjacentes do selecionado dos não selecionados
        for(auto edge: selectedNode->getAllUndirectedEdges()){
            removeNodesFromVector(notSelectedNodes, edge);
        }
    }
    //criterio
    sort->SortByWeightAndEdges(notSelectedNodes);
    while (!notSelectedNodes.empty()){
        Node* selectedNode = notSelectedNodes.back();
        selectedNodes.push_back(selectedNode);
        for(auto edge: selectedNode->getAllUndirectedEdges()){
            removeNodesFromVector(notSelectedNodes, edge);
        }
        //removendo o nó
        notSelectedNodes.pop_back();
    }
    return selectedNodes;
}


#include "../include/Graph.h"
#include "../include/GraphOperations.h"
#include "iostream"
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

bool isInSol(Node *x, vector<Node *> S)
{
    for (auto predX : x->getAllInputEdges())
        for (auto sol : S)
            if (predX->getTargetId() != sol->getID())
                return true;
    return false;
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
    }

    int oldAlpha = 0;
    int newAlpha = 0;
    int edgeWeight = 0;
    int contagem = 0;
    // Insere na solução todos os nós que nao possuem dependência
    for (auto node : graph->getAllNodes())
        if (node->getAllInputEdges().empty())
        {
            S.push_back(node);
        }
    vector<Node *> NoList;
    NoList.clear();
    for (auto x : graph->getAllNodes()) // CALCULA ALPHA
    {
        oldAlpha = 0;
        contagem = x->getInDegree();
        for (auto sol : S)
        {
            if (x->searchInputEdge(sol->getID()))
            {
                // cout << "Dentro do 1 for: ID: " << x->getID() << " Alpha: " << alpha[x->getID() - 1] << "\n";
                newAlpha = sol->getEdge(x->getID())->getWeight() + alpha[sol->getID() - 1];
                // cout << "Peso aresta: " << sol->getEdge(x->getID())->getWeight() << endl;
                // cout << "New alpha: " << newAlpha << " Old alpha: " << oldAlpha << endl;
                if (newAlpha > oldAlpha)
                    oldAlpha = newAlpha;
                // cout << "Old alpha: " << oldAlpha << endl
                    //  << "==========" << endl;
            }
        }
        if (isInSol(x, S))
        {
            // cout << "No: " << x->getID() << " entrou, Peso oldAlpha: " << oldAlpha << endl;
            alpha[x->getID() - 1] = oldAlpha;
            // S.push_back(x);

            for (auto y : graph->getAllNodes())
            {
                oldAlpha = 0;
                for (auto sol : S)
                {
                    if (y->searchInputEdge(sol->getID()))
                    {
                        // cout << "Dentro do 2 for: ID: " << y->getID() << " Alpha: " << alpha[y->getID() - 1] << endl;
                        newAlpha = sol->getEdge(y->getID())->getWeight() + alpha[sol->getID() - 1];
                        // cout << "Peso aresta: " << sol->getEdge(y->getID())->getWeight() << endl;
                        // cout << "New alpha: " << newAlpha << " Old alpha: " << oldAlpha << endl
                            //  << endl;
                        if (newAlpha > oldAlpha)
                            oldAlpha = newAlpha;
                    }
                }
                if (isInSol(y, S))
                {
                    alpha[y->getID() - 1] = oldAlpha;
                    S.push_back(y);
                }
            }
        }
    }

    for (int i = 0; i < graph->getOrder(); i++)
    {
        cout << "\nNo: " << graph->getNode(i + 1)->getID() << "  Alpha: " << alpha[i] << "\n";
    }

    return S;
}

vector<Node *> GraphOperations::RedePert3(Graph *graph)
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
        }
    vector<Node *> NoList;
    NoList.clear();
    for (auto x : graph->getAllNodes())
    {
        for (auto nodeS : S)
            if (x->getID() != nodeS->getID() && isInSol(x, S))
            { // verifica a condiçao do enquanto

                cout << "teste antes";
                for (auto nodeSol : S)
                {
                    oldAlpha = alpha[x->getID() - 1];
                    if (x->searchInputEdge(nodeSol->getID()))
                    {
                        Edge *edge = nodeSol->getEdge(x->getID());
                        newAlpha = edge->getWeight() + alpha[nodeSol->getID() - 1];
                        if (oldAlpha < newAlpha)
                            alpha[x->getID() - 1] = newAlpha;
                    }
                }
                S.push_back(x);
                // for (auto verfNo : NoList)
                // {
                //     for (auto nodeSolVerf : S)
                //     {
                //         oldAlpha = alpha[verfNo->getID() - 1];
                //         if (verfNo->searchInputEdge(nodeSolVerf->getID()))
                //         {
                //             Edge *edgeVerf = nodeSolVerf->getEdge(x->getID());
                //             newAlpha = edgeVerf->getWeight() + alpha[nodeSolVerf->getID() - 1];
                //             if (oldAlpha < newAlpha)
                //                 alpha[verfNo->getID() - 1] = newAlpha;
                //             S.push_back(verfNo);
                //         }
                //     }
                // }
                cout << "teste dps";
            }
            else
            {
                break;
            }
    }

    for (int i = 0; i < graph->getOrder(); i++)
    {
        cout << "\n\nNo: " << graph->getNode(i + 1)->getID() << "  Alpha: " << alpha[i] << "\n";
    }

    return S;
}

vector<Node *> GraphOperations::RedePert2(Graph *graph)
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

    queue<Node *> q;

    // Insere na solução todos os nós que nao possuem dependência
    for (auto node : graph->getAllNodes())
    {
        if (node->getAllInputEdges().empty())
        {
            S.push_back(node);
        }

        else
        {
            q.push(node);
        }
    }

    while (!q.empty())
    {
        Node *x = q.front();

        cout << "\nID: " << x->getID();

        // Verifico se todos os predecessores de x foram atingidos
        bool predsInSolution = true;
        for (auto pred : x->getAllInputEdges())
        {
            if (!predsInSolution)
                break;

            for (auto nodeSolution : S)
            {
                if (pred->getTargetId() != nodeSolution->getID())
                {
                    predsInSolution = false;
                    q.push(x);
                    q.pop();
                    break;
                }

                else if (pred->getTargetId() == x->getAllInputEdges().back()->getTargetId())
                {
                    S.push_back(x);
                    q.pop();
                }
            }
        }
    }

    for (auto x : S)
    {
        cout << x->getID() << " ";
    }

    /*for (int i = 0; i < graph->getOrder(); i++)
    {
        cout << "\n\nNo: " << graph->getNode(i + 1)->getID() << "  Alpha: " << alpha[i] << "\n";
    }*/

    return S;
}


#include "../include/Graph.h"
#include "../include/GraphOperations.h"
#include "iostream"
#include "../include/Sort.h"
#include <ctime>
#include <thread>

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

int statusNode[999];

void defaultStatus(int status)
{
    for (int i = 0; i < 999; i++)
    {
        statusNode[i] = status;
    }
}

void setStatus(int idNode, int status)
{
    statusNode[idNode - 1] = status;
}

int getStatus(int idNode)
{
    return statusNode[idNode - 1];
}

// region Algoritmo Guloso
double funcaoCriterio(Node *node)
{

    int n_nodesNotAdj = 0;

    for (auto edge : node->getAllUndirectedEdges())
        if (getStatus(edge->getTargetId()) == 0)
            n_nodesNotAdj++;

    return (n_nodesNotAdj + 1.0) / node->getWeight();
}

// Estrutura auxiliar para inserir de forma ordenada os nós na pq
struct compBestNode
{
    bool operator()(Node *const n1, Node *const n2)
    {
        return funcaoCriterio(n1) < funcaoCriterio(n2);
    }
};

/*
 * Caso o status = 0 -> Não visitado
 *               = 1 -> Adjacente a Solução
 */
vector<Node *> GraphOperations::AlgortimoGuloso(Graph *graph)
{
    const int N_SOL_ADJ = 0;
    const int ADJ_SOL = 1;
    const int SOL = 2;
    priority_queue<Node *, vector<Node *>, compBestNode> candidatos = priority_queue<Node *, vector<Node *>, compBestNode>();
    vector<Node *> _solution = vector<Node *>();
    defaultStatus(N_SOL_ADJ);

    for (auto node : graph->getAllNodes())
    {
        candidatos.push(node);
    }

    while (!candidatos.empty())
    {
        priority_queue<Node *, vector<Node *>, compBestNode> aux = candidatos;

        //        IMPRESSÃO TESTE
        //        cout << endl << " === Melhores nos === ";
        //        while(!aux.empty()){
        //            cout << endl << "ID: " << aux.top()->getID() << " : " << funcaoCriterio(aux.top());
        //            aux.pop();
        //        }
        //        cout << endl <<"================== " << endl;
        //        FIM IMPRESSÃO TESTE

        //        Pegamos o melhor nó
        Node *_bestNode = candidatos.top();

        //      Insere ele na solução
        _solution.push_back(_bestNode);
        setStatus(_bestNode->getID(), SOL);

        //      Remove ele da fila de candidatos
        candidatos.pop();

        //      Agora, deve 'setar' todos seus adj como 'ADJ_SOL'
        for (auto edge : _bestNode->getAllUndirectedEdges())
        {
            setStatus(edge->getTargetId(), ADJ_SOL);
        }

        //      Remove os que são adj a solução da lista de candidatos
        aux = candidatos;
        candidatos = priority_queue<Node *, vector<Node *>, compBestNode>();
        while (!aux.empty())
        {

            //            Caso o nó não estiver contemplado
            if (getStatus(aux.top()->getID()) == N_SOL_ADJ)
            {
                candidatos.push(aux.top());
            }

            aux.pop();
        }
    }

    return _solution;
}

// algoritmo guloso randomizado reativo
vector<Node *> GraphOperations::AGRR(Graph *graph, float alfa, float bestLiteratura)
{
    const int N_SOL_ADJ = 0;
    const int ADJ_SOL = 1;
    const int SOL = 2;

    // nos da solução
    vector<Node *> selectedNodes;
    // lista de candidatos
    vector<Node *> candidatos = graph->getAllNodes();
    Sort *sort = new Sort();
    // solução final
    vector<Node *> solution;
    // lista de todas as soluções encontradas
    vector<vector<Node *>> possibleSolutions;
    int numIter = 2500;
    int K = 250;
    int i = 1;
    float q = 0;
    float A = 0;
    float p = 1;
    int j = 0;

    // criterio
    // ordena a lista de candidatos de acordo com o critério
    sort->SortByWeightAndEdges(candidatos);
    vector<Node *> aux(candidatos);
    defaultStatus(N_SOL_ADJ);
    while (i <= numIter)
    {
        alfa = alfa * p;
        while (j < K)
        {

            while (!candidatos.empty())
            {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            unsigned seed = time(NULL);
            srand(seed);    
                int range = (candidatos.size() * alfa) + 1;
                int randN = rand() % range + 0;
                cout << "Aleatorio: " << randN << endl;
                // adicionando um vértice aleatório dos não selecionados entre os vértices selecionados
                Node *selectedNode = candidatos.at(randN);
                selectedNodes.push_back(selectedNode);
                setStatus(selectedNode->getID(), SOL);
                // removendo os adjacentes do selecionado dos não selecionados
                for (auto edge : selectedNode->getAllUndirectedEdges())
                {
                    setStatus(edge->getTargetId(), ADJ_SOL);
                }
                auto it = candidatos.begin();
                // removendo o nó
                for (; it != candidatos.end(); it++)
                {
                    if ((*it)->getID() == selectedNode->getID())
                    {
                        candidatos.erase(it);
                        break;
                    }
                }
                aux = candidatos;
                candidatos.clear();
                while (!aux.empty())
                {

                    //            Caso o nó não estiver contemplado
                    if (getStatus(aux.front()->getID()) == N_SOL_ADJ)
                    {
                        candidatos.push_back(aux.front());
                    }

                    aux.erase(aux.begin());
                }
            }

            possibleSolutions.push_back(selectedNodes);
            if (!solution.empty())
            {
                if (compareSolutions(selectedNodes, solution))
                {
                    solution = selectedNodes;
                }
            }
            if (solution.empty())
            {
                solution = selectedNodes;
            }
            j++;
        }
        float bestWeight = 0;
        ;
        for (auto sol : solution)
        {
            bestWeight += sol->getWeight();
        }
        float aux = 0;
        float qAux = 0;
        for (auto sols : possibleSolutions)
        {
            aux = 0;
            for (auto sol : sols)
            {
                aux += sol->getWeight();
                A += aux / bestLiteratura;
                qAux += A;
            }
        }
        A = A / possibleSolutions.size();
        i++;
        q = (bestWeight / A);
        p = q / qAux;
    }
    return solution;
}

// algoritmo guloso randomizado adaptativo
vector<Node *> GraphOperations::AGRA(Graph *graph, float alfa)
{
    const int N_SOL_ADJ = 0;
    const int ADJ_SOL = 1;
    const int SOL = 2;

    // nos da solução
    vector<Node *> selectedNodes;
    // lista de candidatos
    vector<Node *> candidatos = graph->getAllNodes();
    // solução final
    vector<Node *> solution;
    // lista de todas as soluções encontrada
    vector<vector<Node *>> possibleSolutions;
    Sort *sort = new Sort();
    int numIter = 500;
    int range = candidatos.size() * alfa;
    int randN = rand() % range + 2;
    int randomNode;
    int i = 1;
    // criterio
    // ordenando a lista de nós de acordo com o critério
    sort->SortByWeightAndEdges(candidatos);
    defaultStatus(N_SOL_ADJ);
    vector<Node *> aux(candidatos);
    while (i < numIter)
    {
        i++;
        unsigned seed = time(NULL);

        srand(seed);
       while(randN>0)
        {
           randN--;
            randomNode = rand() % range + 0;
            Node *selectedNode = candidatos.at(randomNode);
            selectedNodes.push_back(selectedNode);
            setStatus(selectedNode->getID(), SOL);
            // removendo os adjacentes do selecionado dos não selecionados
            for (auto edge : selectedNode->getAllUndirectedEdges())
            {
                setStatus(edge->getTargetId(), ADJ_SOL);
            }
            auto it = candidatos.begin();
            // removendo o nó
            for (; it != candidatos.end(); it++)
            {
                if ((*it)->getID() == selectedNode->getID())
                {
                    candidatos.erase(it);
                    break;
                }
            }
        }
        aux = candidatos;
        candidatos.clear();
        while (!aux.empty())
        {

            //            Caso o nó não estiver contemplado
            if (getStatus(aux.front()->getID()) == N_SOL_ADJ)
            {
                candidatos.push_back(aux.front());
            }

            aux.erase(aux.begin());
        }

        while (!candidatos.empty())
        {
            Node *selectedNode = candidatos.front();
            selectedNodes.push_back(selectedNode);
            setStatus(selectedNode->getID(), SOL);
            for (auto edge : selectedNode->getAllUndirectedEdges())
            {
                setStatus(edge->getTargetId(), ADJ_SOL);
            }
            auto it = candidatos.begin();
            // removendo o nó
            for (; it != candidatos.end(); it++)
            {
                if ((*it)->getID() == selectedNode->getID())
                {
                    candidatos.erase(it);
                    break;
                }
            }
            aux = candidatos;
            candidatos.clear();
            while (!aux.empty())
            {

                //            Caso o nó não estiver contemplado
                if (getStatus(aux.front()->getID()) == N_SOL_ADJ)
                {
                    candidatos.push_back(aux.front());
                }

                aux.erase(aux.begin());
            }
        }

        possibleSolutions.push_back(selectedNodes);
        if (!solution.empty())
        {
            if (compareSolutions(selectedNodes, solution))
            {
                solution = selectedNodes;
            }
        }
        if (solution.empty())
        {
            solution = selectedNodes;
        }
    }
    return solution;
}

bool GraphOperations::compareSolutions(vector<Node *> &selectedNodes, vector<Node *> &solution)
{

    float solutionWeight = 0;
    float selectedNodesWeight = 0;
    for (auto node : solution)
    {
        solutionWeight += node->getWeight();
    }
    for (auto node : selectedNodes)
    {
        selectedNodesWeight += node->getWeight();
    }
    return solutionWeight < selectedNodesWeight;
}

// enregion

/* Solução antiga
vector<Node*> GraphOperations::AlgortimoGuloso(Graph * graph){

    priority_queue<Node*, vector<Node*>, compBestNode> pq;
    pq = priority_queue<Node*, vector<Node*>, compBestNode> ();
    vector<Node*> _solution;
    _solution = vector<Node*>();

    for(auto node : graph->getAllNodes()){
        pq.push(node);
    }

    while(!pq.empty()) {

        //Imprimindo o melhor pro pior no
        priority_queue<Node *, vector<Node *>, compBestNode> aux;
        aux = pq;
        cout << endl << " === Melhores nos === ";
        while(!aux.empty()){
            cout << endl << "ID: " << aux.top()->getID() << " : " << funcaoCriterio(aux.top());
            aux.pop();
        }
        cout << endl <<"================== " << endl;
        // FIM IMPRESSÃO TESTE

        // Insere o melhor nó na solução
        pq.top()->setStatus(2);
        Node *_bestNode = pq.top();
        _solution.push_back(_bestNode);
        pq.pop();

        // REMOVE TODOS OS ADJ DO NO DA SOLUÇÃO
        // TODO : verificar se os nos adj são vértices de corte
        for(auto adj : _bestNode->getAllUndirectedEdges()) {
            //cout << endl << "Adj: " << adj->getTargetId();
            aux = priority_queue<Node *, vector<Node *>, compBestNode> ();
            while(!pq.empty()){

                if(pq.top()->getID() !=  adj->getTargetId()){
                    aux.push(pq.top());
                }

                pq.pop();
            }
            pq = aux;
        }
    }

    vector<Node*> vector = std::vector<Node*>();

    while(!pq.empty()){
        vector.push_back(pq.top());
        pq.pop();
    }

    return _solution;
}
*/
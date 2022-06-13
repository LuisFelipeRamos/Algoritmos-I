#include <iostream>
#include <bits/stdc++.h>

/* Essa estrutura é um utilitário auxiliar para a criação de uma função de comparação entre pares de inteiros,
utilizada como função de comparação da estrutura da fila de prioridades(priority queue) da biblioteca padrão. */
struct Compare{

    /* Descrição: função de comparação entre dois pares de inteiros, que compara o segundo valor de ambos os pares.
    Entrada: dois pares de inteiros.
    Saída: verdadeiro se o valor do primeiro par for maior, falso caso contrário. */
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2){
        return p1.second < p2.second;
    }
};


/* Descrição: Função para o cálculo do caminho de gargalo máximo partindo de um vértice específico para todos os outros em um grafo.
Entrada: referência para o grafo representado em sua forma de lista de adjacências, ou seja, um vector que contêm listas de pares, e um inteiro que
representa o identificador do vértice de origem.
Saída: vetor que contêm o valor do gargalo máximo de caminho entre o vértice desejado e o resto do grafo. */
std::vector<int> widestPathAlgorithm(std::vector<std::list<std::pair<int, int>>>& graph, int& src){

    int numberOfNodes = graph.size();

    /* Vetor auxiliar para armazenar o valor dos gargalos máximos, inicialmente com os valores mínimos permitidos para um inteiro. */
    std::vector<int> widestPathVector(numberOfNodes, INT_MIN);
    widestPathVector.at(src) = INT_MAX;

    /* Vetor auxiliar para armazenar quais vértices do grafo já foram visitados. */
    std::vector<bool> visited(numberOfNodes, 0);

    /* Fila de prioridades utilizada para organizar os vértices e os gargalos de seus caminhos conhecidos até o momento
    na forma desejada. */
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
    pq.push({src, INT_MAX});

    /* Enquanto a fila de prioridades não estiver vazia, existem valores que ainda não foram checados. */
    while (!pq.empty()){
        
        /* Pega valores do elemento do topo da lista e exclui esse elemento. */
        int currVertex = pq.top().first;
        int currVertexWidestPath = pq.top().second;
        pq.pop();

        /* Se o vértice já foi visitado, é ignorado. */
        if (visited.at(currVertex)) continue;
        
        visited.at(currVertex) = 1;
        widestPathVector.at(currVertex) = currVertexWidestPath;
        
        /* Para cada vizinho do vértice, checamos. */
        for (auto vertexWeightPair : graph.at(currVertex)){
            
            int currAdjVertex = vertexWeightPair.first; 

            /* Se o vértice já foi visitado, é ignorado. */
            if (visited.at(currAdjVertex)) continue;

            int currAdjWeight = vertexWeightPair.second;
            
            /* O valor do gargalo analisado para o vértice é o mínimo entre o gargalo do vértice ascendente e o peso do caminho entre eles. */
            int currAdjVertexWidestPath = std::min(widestPathVector.at(currVertex), currAdjWeight);

            /* Novo elemento é adicionado na fila de prioridades. */
            pq.push({currAdjVertex, currAdjVertexWidestPath});
            
        }

    }

    widestPathVector.at(src) = 0;

    return widestPathVector;
}


int main(int argc, char* argv[]){

    int numberOfCities;
    int numberOfHighways;
    int numberOfConsults;

    /* Leitura do número de cidades, rodovias e consultas. */
    std::cin >> numberOfCities >> numberOfHighways >> numberOfConsults;
   
    std::vector<std::list<std::pair<int, int>>> graph(numberOfCities);

    int uCity, vCity, weight;
    
    /* Leitura dos vértices e arestas do grafo que representa a malha rodoviária. */
    for (int i = 0; i < numberOfHighways; i++){
        std::cin >> uCity >> vCity >> weight;
        graph[uCity - 1].push_back({vCity - 1, weight});
    }

    int src, dest;

    std::vector<std::vector<int>> widestPathVectorForEachOrigin(numberOfCities, std::vector<int>());
    
    /* Leitura das consultas e, para cada uma delas, chamada do algoritmo de widestPath, se necessário. */
    for (int i = 0; i < numberOfConsults; i++){
        std::cin >> src >> dest;

        src = src - 1;
        dest = dest - 1;

        if (widestPathVectorForEachOrigin.at(src).empty()){
            widestPathVectorForEachOrigin.at(src) =  widestPathAlgorithm(graph, src);
        }

        int widestPathValue = widestPathVectorForEachOrigin.at(src).at(dest);

        std::cout << widestPathValue << std::endl;
    }

    return 0;
}
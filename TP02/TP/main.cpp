#include <iostream>
#include <bits/stdc++.h>

/* Essa estrutura é um utilitário auxiliar para a criação de uma função de comparação entre pares de inteiros,
utilizada como função de comparação da estrutura da fila de prioridades(priority queue) da biblioteca padrão. */
struct Compare{

    public:

    /* Descrição: função de comparação entre dois pares de inteiros, que compara o segundo valor de ambos os pares.
    Entrada: dois pares de inteiros.
    Saída: verdadeiro se o valor do primeiro par for maior, falso caso contrário. */
    bool operator()(std::pair<int, int>& p1, std::pair<int, int>& p2){
        return p1.second < p2.second;
    }
};


/* Descrição: Função para o cálculo do caminho de gargalo máximo entre dois vértices em um grafo
Entrada:
Saída: */
int widestPathAlgorithm(std::vector<std::list<std::pair<int, int>>>& graph, int s, int t){
    s = s - 1;
    t = t - 1;

    int numberOfNodes = graph.size();

    std::vector<int> widest(numberOfNodes, INT_MIN);
    widest.at(s) = INT_MAX;

    std::vector<bool> visited(numberOfNodes, 0);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
    pq.push({s, INT_MAX});

    while (!pq.empty()){
        int currVertex = pq.top().first;
        int currWidestValue = pq.top().second;
        pq.pop();

        if (visited.at(currVertex)) continue;
        
        visited.at(currVertex) = 1;
        widest.at(currVertex) = currWidestValue;
        

        for (auto vertexWeightPair : graph[currVertex]){
            
            int currNewVertex = vertexWeightPair.first;

            if (visited.at(currNewVertex)) continue;

            int currNewWeight = vertexWeightPair.second;
            
            int widestValue = std::min(widest.at(currVertex), currNewWeight);

            pq.push({currNewVertex, widestValue});
            
        }

    }

    return widest[t];
}


int main(int argc, char* argv[]){

    int numberOfCities;
    int numberOfHighways;
    int numberOfConsults;

    std::cin >> numberOfCities >> numberOfHighways >> numberOfConsults;
   
    std::vector<std::list<std::pair<int, int>>> graph(numberOfCities);

    int uCity, vCity, weight;
  
    for (int i = 0; i < numberOfHighways; i++){
        std::cin >> uCity >> vCity >> weight;
        graph[uCity - 1].push_back({vCity - 1, weight});
    }

    int src, dest;

    for (int i = 0; i < numberOfConsults; i++){
        std::cin >> src >> dest;
        std::cout << widestPathAlgorithm(graph, src, dest) << std::endl; 
    }


    
    return 0;
}
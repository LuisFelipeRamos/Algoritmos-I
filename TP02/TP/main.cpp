#include <iostream>
#include <bits/stdc++.h>

# define INF 0x3f3f3f3f

void print(std::vector<std::vector<int>> graph, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << graph.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

typedef std::pair<int, int> iPair;

int djkistra(std::list<std::pair<int, int>> graph[], int s, int numberOfNodes){
    s = s - 1;
    std::vector<int> parents(numberOfNodes, -1);
    std::vector<int> processed(numberOfNodes, 0);
    processed.at(s) = 1;

    std::vector<int> widest(numberOfNodes, INT_MIN);
    widest.at(s) = INT_MAX;


    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;
    pq.push({0, s});

    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for (auto e : graph[u]){
            int v = e.first;
            int weight = e.second;
            int distance = std::max(widest[v], std::min(widest[u], weight));

            if (distance > widest[v]){
                widest[v] = distance;
                parents[v] = u;
                pq.push({distance, v});
            }

        }

    }
    for (int i = 0; i < numberOfNodes; i++){
        std::cout << i << " : " << widest[i] << std::endl;
    }

    return 0;
}

int main(int argc, char* argv[]){

    int numberOfCities;
    int numberOfHighways;
    int numberOfConsults;

    std::cin >> numberOfCities >>numberOfHighways >> numberOfConsults;

    std::list<std::pair<int, int>> graph[numberOfHighways];

    int uCity, vCity, weight;
    for (int i = 0; i < numberOfHighways; i++){
        std::cin >> uCity >> vCity >> weight;
        graph[uCity - 1].push_back({vCity - 1, weight});
    }


    int k = djkistra(graph, 4, numberOfHighways);

    
    return 0;
}
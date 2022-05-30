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

int widestPath(std::list<std::pair<int, int>> graph[], int s, int t, int numberOfNodes){
    s = s - 1;
    t = t - 1;

    std::vector<int> widest(numberOfNodes, INT_MIN);
    widest.at(s) = INT_MAX;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(s);

    while (!pq.empty()){
        int currSrcVertex = pq.top();
        pq.pop();

        for (auto vertexWeightPair : graph[currSrcVertex]){
            int currDestVertex = vertexWeightPair.first;
            int currWeight = vertexWeightPair.second;
            int distance = std::max(widest[currDestVertex], std::min(widest[currSrcVertex], currWeight));

            if (distance > widest[currDestVertex]){
                widest[currDestVertex] = distance;
                pq.push(currDestVertex);
            }
        }
    }

    return widest[t];
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

    int s, t;
    for (int i = 0; i < numberOfConsults; i++){
        std::cin >> s >> t;
        std::cout << widestPath(graph, s, t, numberOfHighways) << std::endl;
    }


    
    return 0;
}
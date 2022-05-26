#include "PreferenceList.hpp"

#include <algorithm>
#include <cctype>

std::pair<int, int> moveBike(std::pair<int, int> bikeCoordinates, std::pair<int, int> move){
    bikeCoordinates.first += move.first;
    bikeCoordinates.second += move.second;
    return {bikeCoordinates.first, bikeCoordinates.second};
}

bool outOfBounds(int row, int col, int mapRows, int mapCols){
    return (row >= mapRows || row < 0 || col >= mapCols || col < 0);
}

std::vector<int> getDistancesBikeToVisitors(std::pair<int, int> bikeCoordinates, std::vector<std::vector<char>>& map, int mapRows, int mapCols, int numVisitors){
    std::vector<int> distancesBikeToVisitors(numVisitors, 0);

    /* Vetor de coordenadas visitadas, onde, se visitadas, armazenam a distância da bicicleta para cada um dos visitantes. */
    int visited[mapRows][mapCols];
    for (int i = 0; i < mapRows; i++){
        for (int j = 0; j < mapCols; j++){
            visited[i][j] = -1;
        }
    }

    /* Movimentos que a bicicleta pode fazer para alcançar o visitante. */
    std::pair<int, int> moves[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /* Fila que armazena as coordenadas conforme são visitadas. */
    std::queue<std::pair<int, int>> coordinatesQueue;
    coordinatesQueue.push(bikeCoordinates);
    visited[bikeCoordinates.first][bikeCoordinates.second] = 0;

    /* Laço que é percorrido enquanto não forem visitadas todas as coordenadas do mapa. */
    while (!coordinatesQueue.empty()){
        std::pair<int, int> currBikeCoordinates = coordinatesQueue.front();
        int currDistance = visited[currBikeCoordinates.first][currBikeCoordinates.second];

        /* Testa, para cada possível movimento da bicicleta, a próxima coordenada. */
        for (int i = 0; i < 4; i++){
            std::pair<int, int> newBikeCoordinates = moveBike(currBikeCoordinates, moves[i]);
            int newRow = newBikeCoordinates.first;
            int newCol = newBikeCoordinates.second;

            /* Se o movimenta leva a bicicleta para um local fora do mapa, ele é ignorado. */
            if (outOfBounds(newRow, newCol, mapRows, mapCols)){
                continue;
            } 

            /* Se o movimento não leva a um obstáculo e nem a uma coordenada já visitada, ele é analisado. */
            if (map.at(newRow).at(newCol) != obstacle && visited[newRow][newCol] < 0){
                coordinatesQueue.push(newBikeCoordinates);
                visited[newRow][newCol] = currDistance + 1;

                /* Se a coordenada for uma letra, quer dizer que é um dos visitantes, então a distância em questão é salva
                para o vetor de distâncias entre bicicleta e visitantes. */
                if (isalpha(map.at(newRow).at(newCol))){
                    int index = map.at(newRow).at(newCol) - 'a';
                    distancesBikeToVisitors.at(index) = visited[newRow][newCol];
                }
            }  
        }
        coordinatesQueue.pop();
    }

    return distancesBikeToVisitors;
}

std::vector<std::vector<int>> getDistancesBikesToVisitors(std::vector<std::pair<int, int>>& bikesCoordinates, std::vector<std::vector<char>>& map, int mapRows, int mapCols, int numVisitors){
    std::vector<std::vector<int>> distancesBikesToVisitors;

    /* Para cada bicicleta, a função de cálculo de distância entre bicicleta e visitantes é chamada. */
    for (std::pair<int, int> bikeCoordinates : bikesCoordinates){
        std::vector<int> distanceBikeToVisitors = getDistancesBikeToVisitors(bikeCoordinates, map, mapRows, mapCols, numVisitors);
        distancesBikesToVisitors.push_back(distanceBikeToVisitors);
    }
    return distancesBikesToVisitors;
}



bool cmpBikesPreferences(const std::pair<int, int>& p1, const std::pair<int, int>& p2){
    if (p1.first == p2.first){
        return p1.second < p2.second;
    }
    return p1.first < p2.first;
}

bool cmpVisitorsPreferences(const std::pair<int, int>& p1, const std::pair<int, int>& p2){
    if (p2.first == p1.first){
        return p2.second == p1.second;
    }
    return p2.first < p1.first;
}

std::vector<std::vector<int>> getPreferenceMatrix(std::vector<std::vector<int>>& rankingMatrix, bool ascendingOrder){ /* ver esse ascending order ai */
    std::vector<std::vector<int>> preferenceMatrix = rankingMatrix;
    std::vector<std::pair<int, int>> valueIndexVector(preferenceMatrix.size(), {-1, -1});
    if (ascendingOrder){
        for (std::vector<int>& preferenceList : preferenceMatrix){
            for (size_t i = 0; i < preferenceMatrix.size(); i++){
                valueIndexVector.at(i) = {preferenceList.at(i), i};
            } 
            std::stable_sort(valueIndexVector.begin(), valueIndexVector.end(), cmpBikesPreferences);
            for (size_t i = 0; i < preferenceMatrix.size(); i++){
                preferenceList.at(i) = valueIndexVector.at(i).second;
            }
        }
    }
    else{
        for (std::vector<int>& preferenceList : preferenceMatrix){
            for (size_t i = 0; i < preferenceMatrix.size(); i++){
                valueIndexVector.at(i) = {preferenceList.at(i), i};
            } 
            std::stable_sort(valueIndexVector.begin(), valueIndexVector.end(), cmpVisitorsPreferences);
            for (size_t i = 0; i < preferenceMatrix.size(); i++){
                preferenceList.at(i) = valueIndexVector.at(i).second;
            }   
        }
    }

    return preferenceMatrix;
}

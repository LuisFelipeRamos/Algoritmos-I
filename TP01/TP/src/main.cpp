#include <iostream>
#include <vector>

#include "PreferenceList.hpp"
#include "GaleShapley.hpp"


int main(int argc, char* argv[]){

    int numVisitorsBikes;
    std::cin >> numVisitorsBikes;
    
    int mapRows, mapCols;
    std::cin >> mapRows >> mapCols;
  

    /* Vetor de tamanho igual ao número de bicicletas, armazena o par de coordenadas de cada bicicleta lida do mapa. */
    std::vector<std::pair<int, int>> bikesCoordinates(numVisitorsBikes, {-1, -1});

    /* Leitura do mapa da lagoa, quando uma bicicleta é encontrada suas coordenadas são armazenadas em um vetor. */
    std::vector<std::vector<char>> map(mapRows, std::vector<char>(mapCols));
    for (int i = 0; i < mapRows; i++){
        for (int j = 0; j < mapCols; j++){
            std::cin >> map.at(i).at(j);
            if (std::isdigit(map.at(i).at(j))){
                int bikeID = map.at(i).at(j) - '0'; /* Linha utilizada para obtenção do inteiro que representa a ID da bicicleta. */
                bikesCoordinates.at(bikeID) = {i, j};
            }
        }
    }

    /* Leitura da matriz de preferências dos visitantes. */
    std::vector<std::vector<int>> visitorsPreferenceRanks(numVisitorsBikes, std::vector<int>(numVisitorsBikes));
    for (int i = 0; i < numVisitorsBikes; i++){
        for (int j = 0; j < numVisitorsBikes; j++){
            std::cin >> visitorsPreferenceRanks.at(i).at(j);
        }
    }

    /* Pego a matriz de preferências das bicicletas. */
    std::vector<std::vector<int>> distancesBikesToVisitors = getDistancesBikesToVisitors(bikesCoordinates, map, mapRows, mapCols, numVisitorsBikes);

    /* Armazeno matrizes de preferências. */
    std::vector<std::vector<int>> visitorsPreferenceMatrix = getPreferenceMatrix(visitorsPreferenceRanks, false);
    std::vector<std::vector<int>> bikesPreferenceMatrix = getPreferenceMatrix(distancesBikesToVisitors, true);

    std::vector<int> stableMatching = GaleShapley(visitorsPreferenceMatrix, distancesBikesToVisitors);


    for (size_t i = 0; i < stableMatching.size(); i++){
        std::cout << char(i + 'a') << " " << stableMatching.at(i) << std::endl;
    }

    return 0;
}
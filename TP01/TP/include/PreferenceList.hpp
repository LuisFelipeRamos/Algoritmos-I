#pragma once

#include <queue>
#include <vector>

#define obstacle '-'

/* Essa biblioteca contêm funções para o cálculo da distância entre uma bicicleta e cada um dos visitantes,
de acordo com as especificações passadas pelo enunciado do trabalho prático, assim como funcções para ordenar
as listas de preferências de ambas as entidades, visitantes e bicicletas, para obter as matrizes de preferências 
desejadas pelas especificações do trabalho. */

/* Descrição: função que calcula a nova posição da bicicleta após realizar um movimento.
Entrada: coordenadas atuais da bicicleta e o movimento que ela irá fazer.
Saída: nova posição da bicicleta após ela realizar o movimento. */
std::pair<int, int> moveBike(std::pair<int, int> bikeCoordinates, std::pair<int, int> move);

/* Descrição: função que calcula se a a posição passada como parâmetro está fora dos limites do mapa.
Entrada: posição a ser checada e o tamanho do mapa.
Saída: verdadeiro se a posição estiver fora do mapa, falso caso contrário. */
bool outOfBounds(int row, int col, int mapRows, int mapCols);

/* Descrição: função que calcula a distância entre uma bicicleta e cada uma das pessoas presentes
no mapa da lagoa. 
Entrada: coordenadas da bicicleta, o mapa da lagoa, os inteiros que indicam o tamanho do mapa e o número de visitantes.
Saída: vetor que contêm as distâncias calculadas . */
std::vector<int> getDistancesBikeToVisitors(std::pair<int, int> bikeCoordinates, std::vector<std::vector<char>>& map, int mapRows, int mapCols, int numVisitors);

/* Descição: função que calcula as distâncias entre cada uma das biciletas para todas as pessoas.
Entrada: coordenadas de todas as bicicletas, o mapa da lagoa, os inteiros que indicam o tamanho do mapa e o número de visitantes.
Saída: matriz que contêm as distâncias calculadas. */
std::vector<std::vector<int>> getDistancesBikesToVisitors(std::vector<std::pair<int, int>>& bikesCoordinates, std::vector<std::vector<char>>& map, int mapRows, int mapCols, int numVisitors);

/* Descrição: função de comparação para uma ordenação ascendente.
Entrada: referências para os pares de inteiros que devem ser comparados na ordenação.
Saída: verdadeiro se a comparação for verdadeira, falso caso contrário. */
bool cmpBikesPreferences(const std::pair<int, int>& p1, const std::pair<int, int>& p2);

/* Descrição: função de comparação para uma ordenação descendente.
Entrada: referências para os pares de inteiros que devem ser comparados na ordenação.
Saída: verdadeiro se a comparação for verdadeira, falso caso contrário. */
bool  cmpVisitorsPreferences(const std::pair<int, int>& p1, const std::pair<int, int>& p2);

/* Descrição: função que ordena a matriz de preferências desejada de acordo com as notas dadas pra cada ID, 
em ordem descendente ou ascendente.
Entrada: referência para a matriz de preferências para ser ordenada e valor booleano para indicar a ordem.
Saída: matriz de preferências ordenada e organizada. */
std::vector<std::vector<int>> getPreferenceMatrix(std::vector<std::vector<int>>& rankingMatrix, bool ascendingOrder);
#pragma once

#include <vector>

/* Essa biblioteca contêm as funcionalidades para a aplicação do algoritmo de casamento
estável de Gale-Shapley. */

/* Descrição: função utilizada para comparar se uma bicicleta prefere um novo visitante do que seu par já alocado.
Entrada: ID do visitante que propõe, ID da bicicleta que recebe a proposta, vetor com as alocações momentâneas de pares das bicicletas
e matriz com as distâncias de cada bicicleta pra cada visitante.
Saída: verdadeiro se a bicicleta prefere o novo visitante, falso caso contrário. */
bool bikePrefersVisitorToCurrentMatch(int& bikeID, int& visitorID, std::vector<int>& bikesMatching, std::vector<std::vector<int>> distancesBikesToVisitors);

/* Descrição: função que implementa o algoritmo de casamento estável de Gale-Shapley. O primeiro parâmetro 
é a matriz de preferência de quem irá fazer as propostas, e o segundo é de quem recebe as propostas.
Entrada: matrizes de preferências dos visitantes e matriz com as distâncias de cada bicicleta para cada visitante.
Saída: vetor com os casamentos formados,dando preferência aos visitantes. */
std::vector<int> GaleShapley(std::vector<std::vector<int>>& visitorsPreferences, std::vector<std::vector<int>>& distancesBikesToVisitors);
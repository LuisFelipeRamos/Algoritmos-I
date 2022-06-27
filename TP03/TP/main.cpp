#include <iostream>

#include <bits/stdc++.h>

/* Descrição: essa função checa se uma determinada mesa, no caso, um retângulo, cabe dentro de um histograma.
Entrada: referência para um vetor de inteiros que representa o histograma, assim como as dimensões da mesa/retângulo.
Saída: verdadeiro se cabe na casa, falso caso contrário. */
bool tableFitsHistogram(std::vector<int>& histogram, int& tableLength, int& tableWidth){

    int numberOfBars = int(histogram.size());

    std::stack<int> histogramIndexes;

    int i = 0;

    while (i < numberOfBars){

        if (histogramIndexes.empty() || histogram.at(histogramIndexes.top()) <= histogram.at(i)){
            histogramIndexes.push(i++);
        }

        else{

            int currSmallestBar = histogramIndexes.top();
            histogramIndexes.pop();

            int maxLength = histogramIndexes.empty() ? i : i - histogramIndexes.top() - 1;
            int maxWidth = histogram.at(currSmallestBar);


            if ((tableWidth <= maxWidth && tableLength <= maxLength) || (tableWidth <= maxLength && tableLength <= maxWidth)) {
                return true;
            }
        }
    }

    while (!histogramIndexes.empty()){

        int currSmallestBar = histogramIndexes.top();
        histogramIndexes.pop();

        int maxLength = histogramIndexes.empty() ? i : i - histogramIndexes.top() - 1;
        int maxWidth = histogram.at(currSmallestBar);

        if ((tableWidth <= maxWidth && tableLength <= maxLength) || (tableWidth <= maxLength && tableLength <= maxWidth)) {
            return true;
        }    
    }

    return false;
}

/* Descrição: essa função chama, para cada histograma obtido no desing da casa, a função que checa se a mesa cabe no histograma.
Entrada: vetor de histogramas para cada iteração de histogramas pelo design da casa, assim como as dimensões da mesa.
Saída: verdadeiro se a mesa cabe na casa, falso caso contrário. */
bool tableFitsHouse(std::vector<std::vector<int>>& houseMatrixHistograms, int& tableLength, int& tableWidth){
    for (std::vector<int> histogram : houseMatrixHistograms){
        if (tableFitsHistogram(histogram, tableLength, tableWidth)){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]){

    /* Leitura das dimensões da casa. */
    int houseLength, houseWidth;
    std::cin >> houseLength >> houseWidth;

    /* Leitura da planta da casa. */
    std::vector<std::vector<char>> houseDesing(houseLength, std::vector<char>(houseWidth, ' '));
    for (int i = 0; i < houseLength; i++){
        for (int j = 0; j < houseWidth; j++){
            std::cin >> houseDesing.at(i).at(j);
        }
    }

    /* Criação dos histogramas representativos para cada iteração de cima pra baixo no design da casa. */
    std::vector<std::vector<int>> houseMatrixHistograms(houseLength, std::vector<int>(houseWidth, 0));
    for (int i = 0; i < houseLength; i++){
        
        for (int j = 0; j < houseWidth; j++){

            bool emptySpace = houseDesing.at(i).at(j) != '#';

            if (i == 0){
                houseMatrixHistograms.at(i).at(j) = !emptySpace ? 0 : 1;
                continue;
            }

            if (!emptySpace){
                houseMatrixHistograms.at(i).at(j) = 0;
            }
            else{
                houseMatrixHistograms.at(i).at(j) = houseMatrixHistograms.at(i - 1).at(j) + 1;
            }
        }
    }

    /* Leitura do número de mesas na lista de entrada. */
    int numberOfTables;
    std::cin >> numberOfTables;

    /* Variáveis auxiliares para as dimensões e área da mesa. */
    int tableLength, tableWidth;
    int tableArea;

    /* Variáveis que armazenam temporariamente a maior área e as dimensões da mesa que a possui. */
    std::pair<int, int> maxAreaTableSizes = {INT_MIN, INT_MIN};
    int maxArea = INT_MIN;

    /* Maior dimensão da casa, útil para armazenar na matriz de mesas que cabem na casa quais cabem e quais não. */
    int maxHouseSide = houseLength > houseWidth ? houseLength : houseWidth;
    std::vector<std::vector<int>> tablesThatFitHouse(maxHouseSide + 1, std::vector<int>(maxHouseSide + 1, 2));

    /* Laço percorrido para cada mesa na lista de entrada. */
    for (int i = 0; i < numberOfTables; i++){

        /* Leitura das coordenadas da mesa. */
        std::cin >> tableLength >> tableWidth;

        /* Variáveis para armazenar se a mesa rotacionada ou não cabe na casa. */
        int tableFits = tablesThatFitHouse.at(tableLength).at(tableWidth);
        int tableFitsRotated = tablesThatFitHouse.at(tableWidth).at(tableLength);

        /* Se não couber, é ignorada. */
        if ((tableFits == 0) || (tableFitsRotated == 0)){
            continue;
        }

        /* Se couber e estiver armazenada, sua área é analisada e a área máxima atualizada se necessário. */
        else if ((tableFits == 1) || (tableFitsRotated == 1)){
            tableArea = tableLength * tableWidth;
            if (tableArea > maxArea){
                maxArea = tableArea;
                maxAreaTableSizes = {tableLength, tableWidth};
            }
            else if(tableArea == maxArea){
                if (tableWidth > maxAreaTableSizes.second){
                    maxAreaTableSizes = {tableLength, tableWidth};
                }
            }
            else{
                continue;
            }
        }

        /* Se não se sabe nada sobre as coordenadas, checa-se se ela cabe na casa, e, caso positivo, a área é analisada e a área máxima atualizada 
        se necessário. */
        else if (tableFitsHouse(houseMatrixHistograms, tableLength, tableWidth)){
            for (int m = 0; m < tableLength + 1; m++){
                for (int n = 0;  n < tableWidth + 1; n++){
                    tablesThatFitHouse.at(m).at(n) = 1;
                    tablesThatFitHouse.at(n).at(m) = 1;
                }
            }
    
            tableArea = tableLength * tableWidth;
            if (tableArea > maxArea){
                maxArea = tableArea;
                maxAreaTableSizes = {tableLength, tableWidth};
            }
            else if(tableArea == maxArea){
                if (tableWidth > maxAreaTableSizes.second){
                    maxAreaTableSizes = {tableLength, tableWidth};
                }
            }
            else{
                continue;
            }
        }

        /* Se não couber, atualizamos na matriz auxiliar os tamanhos que não cabem na mesa junto com ela. */
        else{
            for (int m = tableLength; m < maxHouseSide + 1; m++){
                for (int n = tableWidth; n < maxHouseSide + 1; n++){
                    tablesThatFitHouse.at(m).at(n) = 0;
                    tablesThatFitHouse.at(n).at(m) = 0;
                }
            }
        }        
    }

    std::cout << maxAreaTableSizes.first << " " << maxAreaTableSizes.second << std::endl;

    return 0;
}

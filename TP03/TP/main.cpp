#include <iostream>

#include <bits/stdc++.h>


bool tableFitsHistogram(std::vector<int>& histogram, int tableLength, int tableWidth){

    std::size_t numberOfBars = histogram.size();

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

bool tableFitsHouse(std::vector<std::vector<int>>& houseMatrixHistograms, int tableLength, int tableWidth){
    bool tableFitsHouse;
    for (std::vector<int> histogram : houseMatrixHistograms){
        if (tableFitsHistogram(histogram, tableLength, tableWidth)){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]){

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

    int numberOfTables;
    std::cin >> numberOfTables;

    int tableLength, tableWidth;
    int tableArea;

    std::pair<int, int> maxAreaTableSizes = {INT_MIN, INT_MIN};
    int maxArea = INT_MIN;

    for (int i = 0; i < numberOfTables; i++){
        std::cin >> tableLength >> tableWidth;
        if (tableFitsHouse(houseMatrixHistograms, tableLength, tableWidth)){
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
    }

    std::cout << maxAreaTableSizes.first << " " << maxAreaTableSizes.second << std::endl;

    return 0;
}

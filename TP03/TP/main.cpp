#include <iostream>

#include <bits/stdc++.h>


bool tableFitsHistogram(std::vector<int>& histogram, int tableLength, int tableWidth){

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

bool tableFitsHouse(std::vector<std::vector<int>>& houseMatrixHistograms, int tableLength, int tableWidth){
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

    int maxHouseSide = houseLength > houseWidth ? houseLength : houseWidth;

    std::vector<std::vector<int>> tablesThatFitHouse(maxHouseSide + 1, std::vector<int>(maxHouseSide + 1, 2));

    for (int i = 0; i < numberOfTables; i++){

        std::cin >> tableLength >> tableWidth;

        int tableFits = tablesThatFitHouse.at(tableLength).at(tableLength);
        int tableFitsRotated = tablesThatFitHouse.at(tableWidth).at(tableLength);

        if ((tableFits == 0) || (tableFitsRotated == 0)){
            continue;
        }

        if ((tableFits == 1) || (tableFitsRotated == 1)){
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

        else{
            for (int m = tableLength; m < maxHouseSide + 1; m++){
                for (int n = tableWidth; n < maxHouseSide + 1; n++){
                    tablesThatFitHouse.at(m).at(n) = 0;
                    tablesThatFitHouse.at(n).at(m) = 0;
                }
            }
        }        
    }

    for (int i = 0; i < tablesThatFitHouse.size(); i++){
        for (int j = 0; j < tablesThatFitHouse.at(i).size(); j++){
            std::cout << tablesThatFitHouse.at(i).at(j) << " ";
        }
        std::cout << "\n";
    }

    std::cout << maxAreaTableSizes.first << " " << maxAreaTableSizes.second << std::endl;

    return 0;
}

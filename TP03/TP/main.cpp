#include <iostream>

#include <bits/stdc++.h>

int maxHistogramArea(std::vector<int>& histogram, int left, int right){
    if (left > right) return INT_MIN;
    if (left == right) return histogram.at(left);
    
    int min = histogram.at(left);;
    int minIndex = left;

    for (std::size_t i = left + 1; i < right; i++){
        if (histogram.at(i) < min){
            min = histogram.at(i);
            minIndex = i;
        }
    }
    return std::max({int(min * (right - left)), maxHistogramArea(histogram, left, minIndex - 1), maxHistogramArea(histogram, minIndex + 1, right)});
}


bool fitsInHouse(int tableLength, int tableWidth, std::vector<std::vector<int>> houseMatrixHistograms){

    return false;
};


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


    for (int i = 0; i < numberOfTables; i++){
        std::cin >> tableLength >> tableWidth;
        tableArea = tableLength * tableWidth;
    }

    for (auto a : houseMatrixHistograms){
        for (auto b: a){
            std::cout << b;
        }
        std::cout << std::endl;
    }

    std::cout << "-------------------\n";

    for (auto e : houseMatrixHistograms){
        std::cout << maxHistogramArea(e, 0, e.size() - 1) << std::endl;
    }


    return 0;
}
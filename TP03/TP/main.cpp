#include <iostream>

#include <bits/stdc++.h>

int main(int argc, char* argv[]){

    int houseHeight, houseWidth;
    std::cin >> houseHeight >> houseWidth;

    std::vector<std::vector<char>> houseDesing(houseHeight, std::vector<char>(houseWidth, ' '));
    for (int i = 0; i < houseHeight; i++){
        for (int j = 0; j < houseWidth; j++){
            std::cin >> houseDesing.at(i).at(j);
        }
    }

    int numberOfTables;
    std::cin >> numberOfTables;

    int tableWidth, tableHeight;
    for (int i = 0; i < numberOfTables; i++){
        std::cin >> tableWidth >> tableHeight;
    }



    return 0;
}
#include "GaleShapley.hpp"

#include <stack>

#include <iostream>


bool bikePrefersVisitorToCurrentMatch(int& bikeID, int& visitorID, std::vector<int>& bikesMatching, std::vector<std::vector<int>> distancesBikesToVisitors){
    return (distancesBikesToVisitors.at(bikeID).at(visitorID) < distancesBikesToVisitors.at(bikeID).at(bikesMatching.at(bikeID)) ||
    (distancesBikesToVisitors.at(bikeID).at(visitorID) == distancesBikesToVisitors.at(bikeID).at(bikesMatching.at(bikeID)) && visitorID < bikesMatching.at(bikeID)));
}

std::vector<int> GaleShapley(std::vector<std::vector<int>>& visitorsPreferences, std::vector<std::vector<int>>& distancesBikesToVisitors){
    
    size_t numberOfBikes = visitorsPreferences.size();
    size_t numberOfVisitors = visitorsPreferences.size();

    /* Vetores auxiliares que armazenam os pares de casamentos para visitantes e bicicletas. */
    std::vector<int> visitorsMatching(numberOfBikes, -1);
    std::vector<int> bikesMatching(numberOfVisitors, -1);

    /* Vetor que armazena um contador de quantas bicicletas já receberam proposta de dado visitante. */
    std::vector<int> visitorsProposalCounter(numberOfBikes, 0);

    /* Pilha para armazenar visitantes que ainda não possuem pares. */
    std::stack<int> unmatchedVisitors;
    for (size_t i = 0; i < numberOfVisitors; i++){
        unmatchedVisitors.push(i);
    }

    while (!unmatchedVisitors.empty()){

        int currVisitorID = unmatchedVisitors.top();
        
        int numberOfVisitorProposals = visitorsProposalCounter.at(currVisitorID);

        int currBikeID = visitorsPreferences.at(currVisitorID).at(numberOfVisitorProposals);

        if (bikesMatching.at(currBikeID)  == -1){
            unmatchedVisitors.pop();
            bikesMatching.at(currBikeID) = currVisitorID;
            visitorsMatching.at(currVisitorID) = currBikeID;
            visitorsProposalCounter.at(currVisitorID)++;
        }
        
        else if(bikePrefersVisitorToCurrentMatch(currBikeID, currVisitorID, bikesMatching, distancesBikesToVisitors)){
            unmatchedVisitors.pop();
            unmatchedVisitors.push(bikesMatching.at(currBikeID));
            bikesMatching.at(currBikeID) = currVisitorID;
            visitorsMatching.at(currVisitorID) = currBikeID;
            visitorsProposalCounter.at(currVisitorID)++;  
        }
        else{
            visitorsProposalCounter.at(currVisitorID)++;
        }
    }
    
    return visitorsMatching;
}
#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <utility>

// Sets up the AdjacencyList class, declaring all the private and public variables and functions
class AdjacencyList {

 // AdjacencyList's private variables and functions
private:

    // Declares the different private-variable maps that will be utilized in this class
    std::map<int, std::vector<std::pair<int, float>>> graphOfWeb; // BASED OFF INSTRUCTIONS RECOMMENDATION TO USE AN <INT, VECTOR<PAIR<INT, FLOAT>>> FOR THE ADJACENCY LIST
    std::map<std::string, int> urlIdMap;
    std::map<int, int> numOutPages;

    // Declares the different private functions that will be utilized in this class
    int addLinkHelper(const std::string& page);
    void initOutdegree();
    void setupDefaultRankings(std::map<int, float>& pageRanks);
    std::map<int, float> updateRankings(const std::map<int, float>& pageRanks);


 // AdjacencyList's public variables and functions
public:

    // Declares the public functions of the class that will be called in main
    void addLink(const std::string& fromPage, const std::string& toPage);
    std::map<std::string, float> calculateRankings(int powerIterations);
};

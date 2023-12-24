#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include "AdjacencyList.h"
using namespace std;

// Takes in the user input and sets up the adjacency list correspondingly.  CODE LAYOUT IS BASED OFF THE SIMPLIFIED PAGE RANK INSTRUCTION'S CODE FOR MAIN
int main(){

	// Variables used to set up the adjacency list
	int num_lines, power_iterations;
	string from, to;
	cin >> num_lines;
	cin >> power_iterations;
	AdjacencyList webGraph;
	vector<string> urlNames;

	// Reads the user's input for each line the user provides, and adds a link to the graph with the details provided on the line
	for (int i = 0; i < num_lines; i++){
		cin >> from;
		cin >> to;
		webGraph.addLink(from, to);
	}
	map<string, float> finalRankingsMap = webGraph.calculateRankings(power_iterations);

	// Adds each url in the ranking map to a vector, and then sorts the vector alpahabetically 
	for (auto& entry : finalRankingsMap) {
		urlNames.push_back(entry.first);
	}
	std::sort(urlNames.begin(), urlNames.end());

	// Prints out the urls and their rankings
	for (auto& entry : urlNames) {
		cout << entry << " ";
		cout << fixed << setprecision(2) << finalRankingsMap[entry] << endl;
	}

}
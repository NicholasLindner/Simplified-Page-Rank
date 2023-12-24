#include "AdjacencyList.h"
using namespace std;

// A helper function of the addLink function
int AdjacencyList::addLinkHelper(const string& page) {

	auto entry = urlIdMap.find(page);

	// If the page is NOT already in the urlIdMap, it creates a new page section in the urlIdMap, graphOfWeb, and numOutPages, and returns the ID
	if (entry == urlIdMap.end()) {
		int id = urlIdMap.size() + 1;
		urlIdMap[page] = id;

		vector<pair<int, float>> vec;
		graphOfWeb[id] = vec;
		numOutPages[id] = 0;

		return id;
	}

	// If page is already in the urlIdMap, it just returns the ID of the page
	else {
		return entry->second;
	}
}

// Adds a link to the graph of the web
void AdjacencyList::addLink(const string& fromPage, const string& toPage) {

	// Set up page's IDs
	int fromPageId = addLinkHelper(fromPage); 
	int toPageId = addLinkHelper(toPage); 

	// Adds fromPage/rank pair to the toPage's vector
	graphOfWeb[toPageId].push_back(make_pair(fromPageId, 0.f)); 
	numOutPages[fromPageId]++;
}

// Initializes the outdegree value of each webpage
void AdjacencyList::initOutdegree() {

	// Outer loop iterates for each page, inner loop iterates for each element in the given vector 
	for (auto& graphElement : graphOfWeb) {

		for (auto& vecElement : graphElement.second) {
			float outdegree = 1.f / numOutPages[vecElement.first];
			vecElement.second = outdegree;
		}
	}
}

// Initializes the default rankings that each page holds, which is just 1 divided by total pages
void AdjacencyList::setupDefaultRankings(map<int, float>& pageRankings) {

	int numPages = graphOfWeb.size();
	for (auto& graphElement : graphOfWeb) {
		pageRankings[graphElement.first] = 1.f / numPages;
	}
}

// Creates new page rankings for each page by using the previous power iteration's rankings and updating them
map<int, float> AdjacencyList::updateRankings(const map<int, float>& pageRankings) {

	map<int, float> newPageRankings;

	// Outer loop iterates for each page, inner loop iterates for each element in the given vector 
	for (auto& graphElement : graphOfWeb) {
		float individalRank = 0.f;

		for (auto& vecElement : graphElement.second) {
			individalRank += pageRankings.at(vecElement.first) * vecElement.second;
		}
		newPageRankings[graphElement.first] = individalRank;
	}

	return newPageRankings;
}

// General calculate rankings function
map<string, float> AdjacencyList::calculateRankings(int powerIterations) {

	// Initializes the outdegree of each page and creates a map of the page rankings (which orginally has default rankings initialized)
	initOutdegree();
	map<int, float> pageRankings;
	setupDefaultRankings(pageRankings);
	
	// Updates the rankings for each power iteration
	for (int i = 0; i < powerIterations - 1; i++) {
		pageRankings = updateRankings(pageRankings);
	}

	// Converts the ID's back into urls for the final map to be returned and printed out
	map<string, float> finalMap;

	for (auto& entry : urlIdMap) {
		finalMap[entry.first] = pageRankings[entry.second];
	}

	return finalMap;
}


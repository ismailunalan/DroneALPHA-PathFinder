#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    for (int i = 0; i < 81 ;i++) {
        visited[i] = false;
        for (int j = 0; j < 81 ;j++) {
            distanceMatrix[i][j] = -1;
        }
    }
    // TODO: Your code here
    // Initialize all distances to a value representing no direct connection
    // Initialize all provinces as unvisited
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int row = 0;
    int col = 0;
    while (std::getline(file, line)) {
        std::stringstream distanceInfos(line);
        std::string value;
        col = 0;
        while (std::getline(distanceInfos,value,',')){
            distanceMatrix[row][col] = std::stoi(value);
            distanceMatrix[col][row] = std::stoi(value);
            col++;
        }
        row++;
    }

    file.close();

    // TODO: Your code here
    // Read each line in the CSV file
    // Read each cell separated by a comma
    // Convert cell to an integer and store in distanceMatrix
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    int distance = getDistance(provinceA, provinceB);
    return (distance != -1 && distance <= maxDistance);
    // TODO: Your code here
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    visited[province] = true;
    // TODO: Your code here
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    return visited[province] == true;
    // TODO: Your code here
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for (int i = 0; i < 81 ;i++) {
        visited[i] = false;
    }
    // TODO: Your code here
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    int count = 0;
    for (int i = 0; i < 81 ;i++) {
        if (visited[i] == true) {
            count++;
        }
    }
    return count;
    // TODO: Your code here
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    return distanceMatrix[provinceA][provinceB];
    // TODO: Your code here
}
#include "RoutePlanner.h"
#include <iostream>
#include <fstream>
#include <math.h>

// Array to help you out with name of the cities in order
const std::string cities[81] = {
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik",
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne",
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta",
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya",
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya",
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat",
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir",
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce"
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0),calculatedCities(81, false) {
    map.loadDistanceData(distance_data);
    map.resetVisited();
    std::fill(priorityProvinces, priorityProvinces + MAX_PRIORITY_PROVINCES, -1);
    std::fill(weatherRestrictedProvinces, weatherRestrictedProvinces + MAX_WEATHER_RESTRICTED_PROVINCES, -1);
    loadPriorityProvinces(priority_data);
    loadWeatherRestrictedProvinces(restricted_data);
    // TODO:
    // Load map data from file
    // Mark all provinces as unvisited initially
    // Load priority provinces
    // Load restricted provinces
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int i = 0;
    while (std::getline(file,line)) {
        std::string code = "";
        for (char ch : line) {
            if (std::isdigit(ch)) {
                code += ch;
            }
        }
        int provinceCode = std::stoi(code);
        priorityProvinces[i] = provinceCode;
        i++;
    }
    // TODO: Your code here
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    int i = 0;
    while (std::getline(file,line)) {
        std::string code = "";
        for (char ch : line) {
            if (std::isdigit(ch)) {
                code += ch;
            }
        }
        int restricted = std::stoi(code);
        weatherRestrictedProvinces[i] = restricted;
        i++;
    }
    file.close();
    // TODO: Your code here
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    for (int i = 0 ; i < MAX_PRIORITY_PROVINCES; i++) {
        if (priorityProvinces[i] == province)
            return true;
    }
    return false;
    // TODO: Your code here
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    for (int i = 0 ; i < MAX_WEATHER_RESTRICTED_PROVINCES; i++) {
        if (weatherRestrictedProvinces[i] == province)
            return true;
    }
    return false;
    // TODO: Your code here
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    map.markAsVisited(startingCity);
    route.push_back(startingCity);
    if (isPriorityProvince(startingCity)) {
        numPriorityProvinces++;
    }
    enqueueNeighbors(startingCity);

    while (!isExplorationComplete()) {
        if (!queue.isEmpty()) {
            int currentProvince = queue.dequeue();
            exploreFromProvince(currentProvince);
        } else if (!stack.isEmpty()) {
            backtrack();
        }
    }

    displayResults();
    // TODO: Your code here
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    if (map.isVisited(province)) {
        return;
    }

    map.markAsVisited(province);
    route.push_back(province);

    if(isPriorityProvince(province)) {
        numPriorityProvinces++;
    }

    enqueueNeighbors(province);
    // TODO: Your code here
}

void RoutePlanner::enqueueNeighbors(int province) {
    for (int i = 0; i < 81; i++) {
        if (!map.visited[i] && map.isWithinRange(province,i,maxDistance)) {
            if (!calculatedCities[i]) {
                totalDistanceCovered += map.getDistance(province, i);
                calculatedCities[i] = true;
            }
            if (isPriorityProvince(i)) {
                queue.enqueuePriority(i);
            }else if (!isWeatherRestricted(i)) {
                queue.enqueue(i);
            }else if (isWeatherRestricted(i)) {
                std::cout << "Province " << cities[i] <<" is weather-restricted. Skipping." << std::endl;
            }
        }
    }
    // TODO: Enqueue priority & non-priority neighbors to the queue according to given constraints
}

void RoutePlanner::backtrack() {
    if (!stack.isEmpty()) {
        int currentProvince = stack.pop();
        enqueueNeighbors(currentProvince);
    }
    // If you reach a dead-end province
    // TODO: Your code here
}

bool RoutePlanner::isExplorationComplete() const {
    return queue.isEmpty() && stack.isEmpty();
    // TODO: Your code here
}

void RoutePlanner::displayResults() const {
    std::cout << "----------------------------" << std::endl;
    std::cout << "Journey Completed!" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Total Number of Provinces Visited: " << map.countVisitedProvinces() << std::endl;
    std::cout << "Total Distance Covered: " << totalDistanceCovered << " km " << std::endl;

    std::cout << "Route Taken:" << std::endl;
    for (size_t i = 0; i < route.size(); i++) {
        std::cout << cities[route[i]];
        std::cout << " -> ";
    }
    std::cout << "End" << std::endl << std::endl;

    std::cout << "Priority Provinces Status: " << std::endl;
    int visitedPriority = 0;
    for (int i = 0; i < numPriorityProvinces; i++) {
        if (priorityProvinces[i] == -1)
            continue;
        if (map.isVisited(priorityProvinces[i])) {
            std::cout << "- " << cities[priorityProvinces[i]] << " (Visited)" << std::endl;
            visitedPriority++;
        }else if(!map.isVisited(priorityProvinces[i])){
            std::cout << "- " << cities[priorityProvinces[i]] << " (Not Visited)" << std::endl;
        }
    }

    std::cout << std::endl << "Total Priority Provinces Visited: " << visitedPriority << " out of " << numPriorityProvinces << std::endl;
    if (visitedPriority == numPriorityProvinces) {
        std::cout << "Success: All priority provinces were visited.";
    }else {
        std::cout << "Warning: Not all priority provinces were visited.";
    }
    // TODO: Your code here
    // Display "Journey Completed!" message
    // Display the total number of provinces visited
    // Display the total distance covered
    // Display the route in the order visited
    // Priority Province Summary
}



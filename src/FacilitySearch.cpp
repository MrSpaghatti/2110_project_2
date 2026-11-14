#include "FacilitySearch.h"
#include "DataLoader.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>

namespace {
    std::string lower(std::string up){
        std::transform(up.begin(), up.end(), up.begin(), [](unsigned char c){ return std::tolower(c);});
        return up;
    }
}

void searchFacilityByName(const std::vector<Facility>& facilities,
                          const std::string& query) {
    std::string trimmed = DataLoader::trim(query);
    if (trimmed.empty()){
        std::cout << "Error: Enter a facility name to search." << std::endl;
        return;
    }
    int matched = 0;
    for (const auto& fac : facilities){
        if (lower(fac.name) == lower(trimmed)){
            matched += 1;
            std::cout << fac.id << " | " << fac.name << " | " << fac.building << " | " << fac.category << std::endl;
        }
    }
    if (matched == 0){
        std::cout << trimmed << " not found." << std::endl;
    } else {
        std::cout << "Match Count: " << matched << std::endl;
    }

}

void searchFacilityByCategory(const std::vector<Facility>& facilities,
                              const std::string& query) {
    std::string trimmed = DataLoader::trim(query);
    if (trimmed.empty()){
        std::cout << "Error: Enter a facility category to search." << std::endl;
        return;
    }
    int matched = 0;
    for (const auto& fac : facilities){
        if (lower(fac.category) == lower(trimmed)){
            matched += 1;
            std::cout << fac.id << " | " << fac.name << " | " << fac.building << " | " << fac.category << std::endl;
        }
    }
    if (matched == 0){
        std::cout << trimmed << " not found." << std::endl;
    } else {
        std::cout << "Match Count: " << matched << std::endl;
    }
}

void printFacilityCategoryReport(const std::vector<Facility>& facilities) {
    if (facilities.empty()){
        std::cout << "No facilities are available to report." << std::endl;
        std::cout << "Total facilities: 0" << std::endl;
        return;
    }

    std::vector<std::pair<std::string, int>> groups;

    for (const auto& fac : facilities){
        bool found = false;
        for (auto& g : groups){
            if (lower(g.first) == lower(fac.category)){
                g.second += 1;
                found = true;
                break;
            }
        }
        if (!found){
            groups.push_back({fac.category, 1});
        }
    }
    const double total = static_cast<double>(facilities.size());
    for (const auto& g : groups){
        std::cout << g.first << ": " << g.second << " (" << std::fixed << std::setprecision(1) << (g.second * 100.0 / total) << "%)" << std::endl;
    }
    std::cout << "Total facilities: " << facilities.size() << std::endl;
}

// ===========================================================================
// main.cpp -- program entry point, file loading, and the Final menu.
// Authors: Logan Conrad (options 1-4, 16)
//          Hoang Le (options 5-8, 17)
//          Matthew Ojeh Jr. (menu shell, options 9-15)
//
// Purpose: selects the data directory, constructs the four data structures,
// hands them to DataLoader, then runs the menu loop that dispatches each
// option to a single class method. The classes do the work; main only reads
// input, calls one method, and returns to the menu (NFR-2).
//
// Menu numbering follows the specification exactly (UI-7) because scripted
// testing depends on it. The Final menu has 17 options plus 0 to exit.
// ===========================================================================
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "CampusGraph.h"
#include "DataLoader.h"
#include "DepartmentTree.h"
#include "Facility.h"
#include "FacilitySearch.h"
#include "HashTable.h"

namespace {

void printMenu() {
    std::cout << "\n1  View all facilities\n"
              << "2  Search facility by ID\n"
              << "3  Search facility by name\n"
              << "4  Search facility by category\n"
              << "5  View campus graph\n"
              << "6  Display graph counts and degrees\n"
              << "7  Find reachable buildings (BFS)\n"
              << "8  Find shortest path (BFS)\n"
              << "9  Add department\n"
              << "10 Search department\n"
              << "11 Display department hierarchy\n"
              << "12 Preorder traversal\n"
              << "13 Postorder traversal\n"
              << "14 Level-order traversal\n"
              << "15 Department statistics\n"
              << "16 Facility category report\n"
              << "17 Graph connectivity report\n"
              << "0  Exit\n"
              << "Enter choice: ";
}

// Reads a whole line so names may contain spaces (UI-4, UI-5).
bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    return static_cast<bool>(std::getline(std::cin, out));
}

// Accepts only a whole non-negative integer; blank, words and out-of-range
// values are reported as invalid instead of being silently converted.
bool parseChoice(const std::string& input, int& out) {
    std::size_t first = 0;
    std::size_t last = input.size();
    while (first < last && std::isspace(static_cast<unsigned char>(input[first]))) ++first;
    while (last > first && std::isspace(static_cast<unsigned char>(input[last - 1]))) --last;
    if (first == last) return false;
    int value = 0;
    for (std::size_t i = first; i < last; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) return false;
        value = value * 10 + (input[i] - '0');
        if (value > 1000000) return false;
    }
    out = value;
    return true;
}

}  // namespace

int main(int argc, char* argv[]) {
    // 1. data directory: argv[1] when supplied, else the supplied data/ (NFR-10)
    const std::string dir = (argc > 1) ? argv[1] : "data/";

    // 2. declare the pieces
    std::vector<Facility> facilities;
    HashTable table;
    CampusGraph graph;
    DepartmentTree tree;
    DataLoader loader;

    // 3. load; all warnings and per-file summaries print from inside the loader
    loader.load(dir, facilities, table, graph, tree);

    // 4. menu loop
    bool running = true;
    while (running) {
        printMenu();
        std::string line;
        if (!std::getline(std::cin, line)) break;  // EOF exits cleanly

        int choice = 0;
        if (!parseChoice(line, choice)) {
            std::cout << "Invalid choice: enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1: {  // LOGAN -- list facilities (FAC-2)
                if (facilities.empty()) {
                    std::cout << "No facilities are loaded.\n";
                } else {
                    for (const auto& f : facilities) {
                        std::cout << f.id << " | " << f.name << " | "
                                  << f.building << " | " << f.category << "\n";
                    }
                }
                std::cout << "Total facilities: " << facilities.size() << "\n";
                break;
            }
            case 2: {  // LOGAN -- search by ID (FAC-3, HASH-6)
                std::string raw;
                if (!readLine("Enter facility ID: ", raw)) { running = false; break; }
                const std::string id = HashTable::normalize(DataLoader::trim(raw));
                if (!HashTable::validId(id)) {
                    std::cout << "Invalid facility ID format: " << DataLoader::trim(raw)
                              << " (expected F followed by exactly three digits)\n";
                } else if (const Facility* found = table.find(id)) {
                    std::cout << "ID: " << found->id << "\n"
                              << "Name: " << found->name << "\n"
                              << "Building: " << found->building << "\n"
                              << "Category: " << found->category << "\n";
                } else {
                    std::cout << "Facility not found: " << id << "\n";
                }
                break;
            }
            case 3: {  // LOGAN -- search by name (FAC-4)
                std::string name;
                if (!readLine("Enter facility name: ", name)) { running = false; break; }
                searchFacilityByName(facilities, name);
                break;
            }
            case 4: {  // LOGAN -- search by category (FAC-5)
                std::string category;
                if (!readLine("Enter facility category: ", category)) { running = false; break; }
                searchFacilityByCategory(facilities, category);
                break;
            }
            case 5: {  // HOANG -- display graph
                graph.display();
                break;
            }
            case 6: {  // HOANG -- counts and degrees
                graph.displayDegrees();
                break;
            }
            case 7: {  // HOANG -- BFS
                std::string start;
                if (!readLine("Enter starting building: ", start)) { running = false; break; }
                graph.bfs(DataLoader::trim(start));
                break;
            }
            case 8: {  // HOANG -- shortest path (BFS)
                // TODO(hoang): prompt for start and destination, then call the
                // shortest-path method once CampusGraph declares it.
                std::cout << "Shortest path is not implemented yet.\n";
                break;
            }
            case 9: {  // OJ -- add department
                std::string name;
                if (!readLine("Enter department name: ", name)) { running = false; break; }
                std::string parent;
                if (!tree.empty()) {
                    if (!readLine("Enter parent department: ", parent)) { running = false; break; }
                }
                std::string reason;
                if (tree.add(DataLoader::trim(name), DataLoader::trim(parent), reason)) {
                    std::cout << "Department added: " << DataLoader::trim(name) << "\n";
                } else {
                    std::cout << "Department rejected: " << reason << "\n";
                }
                break;
            }
            case 10: {  // OJ -- search department
                std::string name;
                if (!readLine("Enter department name: ", name)) { running = false; break; }
                tree.search(DataLoader::trim(name));
                break;
            }
            case 11: {  // OJ -- hierarchy
                tree.displayHierarchy();
                break;
            }
            case 12: {  // OJ -- preorder
                tree.preorder();
                break;
            }
            case 13: {  // OJ -- postorder
                // TODO(oj): call the postorder method once DepartmentTree declares it.
                std::cout << "Postorder traversal is not implemented yet.\n";
                break;
            }
            case 14: {  // OJ -- level-order
                // TODO(oj): call the level-order method once DepartmentTree declares it.
                std::cout << "Level-order traversal is not implemented yet.\n";
                break;
            }
            case 15: {  // OJ -- department statistics
                // TODO(oj): call the statistics method once DepartmentTree declares it.
                std::cout << "Department statistics are not implemented yet.\n";
                break;
            }
            case 16: {  // LOGAN -- facility category report (RPT-2)
                printFacilityCategoryReport(facilities);
                break;
            }
            case 17: {  // HOANG -- graph connectivity report
                // TODO(hoang): call the connectivity report once CampusGraph declares it.
                std::cout << "Graph connectivity report is not implemented yet.\n";
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default: {
                std::cout << "Invalid choice: enter a number from the menu.\n";
                break;
            }
        }
    }

    return 0;
}

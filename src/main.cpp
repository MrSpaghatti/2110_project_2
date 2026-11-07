// ===========================================================================
// main.cpp -- program entry point, file loading, and the Milestone 1 menu.
// Authors: Logan Conrad (menu shell, options 1-2)
//          Hoang Le (options 3-5)
//          Matthew Ojeh Jr. (options 6-9)
//
// Purpose: selects the data directory, constructs the four data structures,
// hands them to DataLoader, then runs the menu loop that dispatches each
// option to a single class method. The classes do the work; main only reads
// input, calls one method, and returns to the menu (NFR-2).
//
// Menu numbering follows the specification exactly (UI-7) because scripted
// testing depends on it.
// ===========================================================================
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "CampusGraph.h"
#include "DataLoader.h"
#include "DepartmentTree.h"
#include "Facility.h"
#include "HashTable.h"

namespace {

void printMenu() {
    std::cout << "\n1 View all facilities\n"
              << "2 Search facility by ID\n"
              << "3 View campus graph\n"
              << "4 Display graph counts and degrees\n"
              << "5 Find reachable buildings (BFS)\n"
              << "6 Add department\n"
              << "7 Search department\n"
              << "8 Display department hierarchy\n"
              << "9 Run preorder traversal\n"
              << "0 Exit\n"
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
            case 3: {  // HOANG -- display graph
                graph.display();
                break;
            }
            case 4: {  // HOANG -- counts and degrees
                graph.displayDegrees();
                break;
            }
            case 5: {  // HOANG -- BFS
                std::string start;
                if (!readLine("Enter starting building: ", start)) { running = false; break; }
                graph.bfs(DataLoader::trim(start));
                break;
            }
            case 6: {  // OJ -- add department
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
            case 7: {  // OJ -- search department
                std::string name;
                if (!readLine("Enter department name: ", name)) { running = false; break; }
                tree.search(DataLoader::trim(name));
                break;
            }
            case 8: {  // OJ -- hierarchy
                tree.displayHierarchy();
                break;
            }
            case 9: {  // OJ -- preorder
                tree.preorder();
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

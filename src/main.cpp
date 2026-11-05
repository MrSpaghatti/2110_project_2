// ===========================================================================
// main.cpp -- program entry, file loading, and the Milestone 1 menu.
// OWNER: Logan (the shell) + one case block per owner, marked below.
//
// This is the merge point: three people add cases to one file, so keep every
// case inside its own { } block and never reformat anyone else's block.  The
// classes do the work; main only reads input, calls one method, and comes back
// to the menu (NFR-2).
//
// Menu numbers are graded -- scripted testing depends on them (UI-7).  Do not
// renumber, do not insert options, do not "improve" the wording of the list.
//
// WHAT main() HAS TO DO, IN THIS ORDER (build after each step):
//   1. pick the data directory: argv[1] if given, else "data/"      (NFR-10)
//   2. declare the pieces: vector<Facility> facilities; HashTable table;
//      CampusGraph graph; DepartmentTree tree; DataLoader loader;
//   3. loader.load(dir, facilities, table, graph, tree);
//      every warning and load summary prints from inside the loader
//   4. loop: show the menu, read the choice, dispatch, repeat until 0 (UI-1)
//   5. return 0 -- tree nodes free themselves through unique_ptr children
//
// INPUT RULES THAT LOSE POINTS (UI-4, UI-5):
//   - read the menu choice as a whole line, then convert it; blank, a word, or
//     an out-of-range number means print an error and show the menu again
//   - never cin >> into a string that holds a NAME -- spaces are required
//   - after a failed numeric conversion, clear() the stream and ignore() the
//     rest of the line, otherwise the same bad input is read forever
//
// MILESTONE 1 MENU -- exact numbering, section 6.9
//   1  View all facilities .............. Logan -> loop facilities printing
//                                          id | name | building | category,
//                                          then the total (FAC-2)
//   2  Search facility by ID ............ Logan -> normalize + validate, then
//                                          table.find(): invalid format vs not
//                                          found vs found are three different
//                                          messages (FAC-3, HASH-6)
//   3  View campus graph ................ Hoang -> graph.display()
//   4  Display graph counts and degrees . Hoang -> graph.displayDegrees()
//   5  Find reachable buildings (BFS) ... Hoang -> prompt for a start,
//                                          graph.bfs(start)
//   6  Add department ................... OJ    -> prompt name; ask for a
//                                          parent ONLY if the tree is not
//                                          empty; tree.add(name, parent, why)
//   7  Search department ................ OJ    -> prompt name, tree.search()
//   8  Display department hierarchy ..... OJ    -> tree.displayHierarchy()
//   9  Run preorder traversal ........... OJ    -> tree.preorder()
//   0  Exit
//
// Each case is 3-5 lines once the class method exists.  If a case needs more,
// the logic belongs in the class instead.
//
// TYPING ORDER: step 1-3 + a bare menu loop first (that is a commit), then the
// cases.  A menu that prints and exits on 0 is worth committing on its own.
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

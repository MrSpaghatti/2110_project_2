SMART CAMPUS NAVIGATION AND FACILITY ANALYTICS SYSTEM
FINAL PROJECT

PURPOSE
This C++ program loads campus buildings, walkway connections, facilities, and
academic departments from four text files. It provides facility listing, ID
lookup through a custom hash table, facility name and category search, a
facility category report, campus graph display with degree statistics, BFS
reachability, shortest-path search, a graph connectivity report, and department
tree insertion, search, indented hierarchy display, preorder/postorder/
level-order traversal, and tree statistics.

BUILD (UNT CSE CELL / LINUX)
From the project root directory, run:
    g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o campus

If make is installed, the same build is available as:
    make
The Makefile uses this exact command line, so either path produces ./campus.

RUN
Use the supplied data directory:
    ./campus
Or supply another directory containing the four required files:
    ./campus testdata/collision

The program expects buildings.txt, connections.txt, facilities.txt, and
departments.txt inside the selected directory. The default is data/.
Do not run the command from a different working directory unless you provide
the correct relative or absolute data-directory path.

DIRECTORY LAYOUT
project root/
  include/       C++ header files
  src/           C++ implementation files, including main.cpp
  data/          Four sample-format starter data files
  testdata/
    collision/   Small custom dataset to demonstrate hash collisions
    graph/       Graph/BFS test cases: unknown building, two components,
                 reversed duplicate, self-connection
    tree/        Department-tree cases: unknown-parent, duplicate-name,
                 root-only, empty, and sample
  Makefile       Same build command as above
  README.txt
  CONTRIBUTIONS.txt
  design_document.txt
  test_results.txt
  .gitignore

FINAL MENU
1  View all facilities
2  Search facility by ID
3  Search facility by name
4  Search facility by category
5  View campus graph
6  Display graph counts and degrees
7  Find reachable buildings (BFS)
8  Find shortest path (BFS)
9  Add department
10 Search department
11 Display department hierarchy
12 Preorder traversal
13 Postorder traversal
14 Level-order traversal
15 Department statistics
16 Facility category report
17 Graph connectivity report
0  Exit

Menu numbering follows the specification section 6.9. Exit is accepted both at
the listed terminating option and at 0, so scripted input that ends with 0
exits cleanly as well. Unrecognized input at the menu prompt prints an error
and returns to the menu instead of terminating the program.

STATUS
All seventeen menu operations are implemented by their module owners:
- Options 1-4 and 16: facility listing, ID lookup, name search, category
  search, and the facility category report.
- Options 5-8 and 17: campus graph display, degree counts, BFS reachability,
  shortest path, and the connectivity report.
- Options 9-15: department insertion, search, hierarchy display, preorder,
  postorder, level-order traversal, and tree statistics.

Behavioral checks are recorded in test_results.txt: the Milestone 1 rows for
loading, hash/search, graph/BFS, and tree/menu, plus the Final rows for name
and category search, shortest path, postorder/level-order, tree statistics,
the category report, the connectivity report, and the error-handling cases.

CELL CHECK
Confirmed on cell01-cse with g++ 11.4.0 (Ubuntu 22.04) for the Milestone 1
package: the source builds clean under the command above, with no warnings, and
the menu behaved exactly as recorded in test_results.txt. The Final source is
re-verified on the same toolchain before submission and that transcript is
recorded in test_results.txt alongside the Milestone 1 run. Before submitting,
confirm that the same source, data, and documentation are present in the GitHub
repository and in the ZIP, and that no executable is included in either.
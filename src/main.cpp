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
#include <iostream>
#include <string>
#include <vector>

#include "CampusGraph.h"
#include "DataLoader.h"
#include "DepartmentTree.h"
#include "Facility.h"
#include "HashTable.h"

// type int main() below, then one case per menu number

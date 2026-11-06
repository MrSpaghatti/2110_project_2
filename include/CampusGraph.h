// ===========================================================================
// Program:CampusGraph -- campus buildings as a graph.  
// Assigned Member: Hoang Le
// Date: 11/5/2026


// Purpose: holds every building as a vertex and every walkway as an
// undirected edge with no weight.  Display, degree counts and BFS all read
// this one object, so the program only ever has one representation of the
// campus (GRAPH-5).
//


// DECLARATIONS TO TYPE (in this order):
//   static std::string normalize(const std::string& value);
//       lowercase copy, used by every case-insensitive comparison
//   int indexOf(const std::string& name) const;
//       vertex index for a name, -1 when unknown.  const: it only reads
//   bool addBuilding(const std::string& name);
//       false for blank or duplicate-ignoring-case (the loader then rejects)
//   bool addConnection(const std::string& a, const std::string& b,
//                      std::string& reason);
//       reason is filled on rejection: unknown building, self-connection, or
//       duplicate/reversed duplicate.  Adds BOTH endpoints when it succeeds
//   bool hasBuilding(const std::string& name) const;
//   std::string canonicalName(const std::string& name) const;
//       spelling from buildings.txt, "" when unknown.  This is why facilities
//       show "Science Building" even when a data file wrote another case
//   void display() const;         GRAPH-3: one building per line, neighbors in
//                                 insertion order, "(no connections)" if none
//   void displayDegrees() const;  GRAPH-4: totals, then every degree
//   void bfs(const std::string& start) const;   BFS-1..BFS-3
//   std::size_t buildingCount() const;
//   std::size_t connectionCount() const;
//
// PRIVATE DATA YOU MUST DECLARE (the .cpp uses these exact names):
//   struct Vertex { std::string name; std::vector<int> neighbors; };
//   std::vector<Vertex> vertices_;   insertion order = buildings.txt order
//   std::size_t edges_ = 0;          each undirected edge counted ONCE
//
// QUESTIONS TO BE ABLE TO ANSWER OUT LOUD (the demo can ask any of these):
//   - Why store neighbor indexes instead of neighbor names?
//   - Why keep edges_ when you could sum all degrees and divide by two?
//   - indexOf() is a linear scan -- why is that fine here, when HASH-6 bans a
//     scan for facility IDs?
//   - Does BFS mark a vertex visited on enqueue or on dequeue?  What breaks
//     if you pick the other one?
//
// Nothing else goes in this header: no iostream (the .cpp prints), no
// capacity constant, no fixed-size array (NFR-5).
// ===========================================================================
#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include <cstddef>
#include <string>
#include <vector>

class CampusGraph {
public:
    // Used for case-insensitive comparisons so names like "Library" and "library"
    // can be treated as the same building.
    static std::string normalize(const std::string& value);

    // Returns the index of a building name, or -1 if not found.
    int indexOf(const std::string& name) const;

    // Adds a building only if the name is non-empty and not already present.
    bool addBuilding(const std::string& name);

    // Adds an undirected connection between two buildings. The reason explains why
    // the connection was rejected (unknown building, self-link, or duplicate).
    bool addConnection(const std::string& a, const std::string& b,
                       std::string& reason);

    // Checks whether the graph currently contains a building with the given name.
    bool hasBuilding(const std::string& name) const;

    // Returns the exact building name from the original data file, preserving the
    // canonical spelling even if the input used a different case.
    std::string canonicalName(const std::string& name) const;

    // Prints the campus graph in insertion order, showing each building and its
    // connected neighbors.
    void display() const;

    // Prints the total building count and the degree of every building.
    void displayDegrees() const;

    // Performs a breadth-first traversal from the given building.
    void bfs(const std::string& start) const;

    // Returns how many buildings and connections exist in the graph.
    std::size_t buildingCount() const;
    std::size_t connectionCount() const;

private:
    // Each vertex stores its original name and the indexes of its neighbors.
    // Storing indexes keeps the graph compact and makes updates efficient.
    struct Vertex {
        std::string name;
        std::vector<int> neighbors;
    };

    // vertices_ preserves the order buildings were added from buildings.txt.
    std::vector<Vertex> vertices_;

    // Each undirected edge is counted once, even though it appears in both
    // endpoints' neighbor lists.
    std::size_t edges_ = 0;
};

#endif

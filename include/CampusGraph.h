// ===========================================================================
// CampusGraph.h -- campus buildings as an undirected, unweighted graph.
// Author: Hoang Le
//
// Purpose: holds every building as a vertex and every walkway as an
// undirected edge with no weight. Display, degree counts, and BFS all read
// this one object, so the program only ever has one representation of the
// campus (GRAPH-5).
//
// Neighbors are stored as vertex indexes rather than names so insertion order
// and connectivity stay cheap to maintain. edges_ counts each undirected edge
// once even though both endpoints keep it in their own adjacency list.
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

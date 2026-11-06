// ===========================================================================
// Program: CampusGraph.cpp -- adjacency-list campus graph and BFS.
// Assigned Member: Hoang Le
// Date: 11/5/2026


// Purpose: stores campus buildings as vertices and walkway connections as
// undirected edges, then supports display, degree reporting, and BFS reachability.


// Design notes:
//   - each vertex keeps its original building name and a list of neighbor indexes
//   - neighbors are stored as indexes so insertion order and connectivity are easy
//     to maintain without rewriting names every time a connection is added
//   - edges_ counts each undirected edge once even though both endpoints keep the
//     connection in their own adjacency list
//   - BFS marks a node visited when it is enqueued to avoid duplicate queueing
// ===========================================================================

#include "CampusGraph.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <vector>

namespace {

bool hasNeighbor(const std::vector<int>& neighbors, int target) {
    return std::find(neighbors.begin(), neighbors.end(), target) != neighbors.end();
}

}  // namespace

std::string CampusGraph::normalize(const std::string& value) {
    // Lowercase the incoming string so comparisons are case-insensitive.
    std::string normalized = value;
    for (char& ch : normalized) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return normalized;
}

int CampusGraph::indexOf(const std::string& name) const {
    const std::string key = normalize(name);

    // A linear scan is fine here because the graph is small and the building count
    // is not high enough to require a hash map.
    for (std::size_t i = 0; i < vertices_.size(); ++i) {
        if (normalize(vertices_[i].name) == key) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool CampusGraph::addBuilding(const std::string& name) {
    // Ignore blank names and duplicate names regardless of capitalization.
    if (name.empty() || indexOf(name) >= 0) {
        return false;
    }

    vertices_.push_back({name, {}});
    return true;
}

bool CampusGraph::addConnection(const std::string& a,
                               const std::string& b,
                               std::string& reason) {
    const int firstIndex = indexOf(a);
    const int secondIndex = indexOf(b);

    // Both buildings must already exist before the connection can be added.
    if (firstIndex < 0) {
        reason = "unknown building: " + a;
        return false;
    }
    if (secondIndex < 0) {
        reason = "unknown building: " + b;
        return false;
    }

    // A building cannot connect to itself.
    if (firstIndex == secondIndex) {
        reason = "self-connection";
        return false;
    }

    // Reject duplicates and reversed duplicates such as A|B and B|A.
    if (hasNeighbor(vertices_[firstIndex].neighbors, secondIndex)) {
        reason = "duplicate or reversed connection";
        return false;
    }

    // Since the graph is undirected, each edge is stored in both adjacency lists.
    vertices_[firstIndex].neighbors.push_back(secondIndex);
    vertices_[secondIndex].neighbors.push_back(firstIndex);
    ++edges_;
    return true;
}

bool CampusGraph::hasBuilding(const std::string& name) const {
    return indexOf(name) >= 0;
}

std::string CampusGraph::canonicalName(const std::string& name) const {
    const int index = indexOf(name);
    return (index < 0) ? "" : vertices_[index].name;
}

void CampusGraph::display() const {
    if (vertices_.empty()) {
        std::cout << "No buildings are loaded.\n";
        return;
    }

    for (const auto& vertex : vertices_) {
        std::cout << vertex.name << ":";

        if (vertex.neighbors.empty()) {
            std::cout << " (no connections)";
        } else {
            for (const int neighborIndex : vertex.neighbors) {
                std::cout << " " << vertices_[neighborIndex].name;
            }
        }

        std::cout << "\n";
    }
}

void CampusGraph::displayDegrees() const {
    // The total number of edges is tracked once, even though each endpoint keeps
    // a copy of the connection in its adjacency list.
    std::cout << "Total buildings: " << vertices_.size() << "\n";
    std::cout << "Total connections: " << edges_ << "\n";

    for (const auto& vertex : vertices_) {
        std::cout << vertex.name << " degree: " << vertex.neighbors.size() << "\n";
    }
}

void CampusGraph::bfs(const std::string& start) const {
    const int startIndex = indexOf(start);
    if (startIndex < 0) {
        std::cout << "Unknown building: " << start << "\n";
        return;
    }

    // BFS explores neighbors level by level. We mark a node as visited when it is
    // enqueued so that we don't re-add it to the queue multiple times.
    std::vector<bool> visited(vertices_.size(), false);
    std::vector<int> distance(vertices_.size(), -1);
    std::queue<int> queue;

    visited[startIndex] = true;
    distance[startIndex] = 0;
    queue.push(startIndex);

    std::size_t reached = 0;

    while (!queue.empty()) {
        const int current = queue.front();
        queue.pop();
        ++reached;

        std::cout << vertices_[current].name << " (distance " << distance[current] << ")\n";

        for (const int neighborIndex : vertices_[current].neighbors) {
            if (!visited[neighborIndex]) {
                visited[neighborIndex] = true;
                distance[neighborIndex] = distance[current] + 1;
                queue.push(neighborIndex);
            }
        }
    }

    std::cout << "Reachable: " << reached << " of " << vertices_.size()
              << " buildings\n";
}

std::size_t CampusGraph::buildingCount() const {
    return vertices_.size();
}

std::size_t CampusGraph::connectionCount() const {
    return edges_;
}

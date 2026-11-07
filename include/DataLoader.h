#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>

#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "Facility.h"
#include "HashTable.h"

class DataLoader {
    public:
        static std::string trim(const std::string& val);

        bool load(const std::string& dir, std::vector<Facility>& facs, HashTable& table, CampusGraph& graph, DepartmentTree& tree) const;

    private:
        static std::vector<std::string> split(const std::string& line);
};

#endif

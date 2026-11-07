// Purpose: Reads, validates, and loads the four campus data files in the
//          required order. Author: Logan Conrad.
//
// This is the only class that knows the filename and the line number, which is
// why every rejection warning prints from here; the data structures only answer
// yes/no and hand back a reason string.
//
// Validation order per record: field count, then empty required fields, then ID
// format, then unknown reference, then duplicate.
//
// Two traps: check duplicates BEFORE inserting (table.find first) so a rejected
// duplicate never bumps the collision counter -- HASH-7 counts accepted
// insertions only; and take a facility's building from graph.canonicalName(),
// not the raw field, or the displayed case won't match buildings.txt.

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

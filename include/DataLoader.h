// ===========================================================================
// DataLoader -- reads and validates the four campus files.  OWNER: Logan
//
// Purpose: opens buildings.txt, connections.txt, facilities.txt and
// departments.txt in that order, splits each line on '|', trims the fields,
// hands each record to the right structure, and prints one warning per
// rejected line plus one summary line per file (LOAD-1..LOAD-5).
//
// WHY THIS CLASS EXISTS: it is the only place that knows the filename and the
// line number, so it is the only place that can print a useful warning.  The
// data structures just answer yes/no and hand back a reason string.
//
// DECLARATIONS TO TYPE (in this order -- src/DataLoader.cpp defines them):
//   static std::string trim(const std::string& value);
//       strips spaces, tabs, \r and \n from both ends only.  Spaces INSIDE a
//       name stay, so "Student  Union" keeps its double space (section 4.1)
//   static std::vector<std::string> split(const std::string& line);
//       splits on '|' and trims each field; a line with no '|' returns one
//       field, which is how the field-count check rejects it
//   bool load(const std::string& dir,
//             std::vector<Facility>& facilities,
//             HashTable& table,
//             CampusGraph& graph,
//             DepartmentTree& tree) const;
//       returns false if any file could not be opened; printing and rejection
//       counting happen inside.  const because the loader owns no data
//
// VALIDATION ORDER PER RECORD (section 4.1): field count, then empty required
// fields, then ID format, then unknown reference, then duplicate.  Any valid
// reason is accepted by the grader, but pick one order and keep it.
//
// TWO TRAPS THAT COST POINTS:
//   - check duplicates BEFORE insert (table.find first), so a rejected
//     duplicate never bumps the collision counter -- HASH-7 counts accepted
//     insertions only
//   - facilities take their building name from graph.canonicalName(), not from
//     the raw field, or the displayed case won't match buildings.txt
//
// This class has no data members.  Everything it fills is passed in by main.
// ===========================================================================
#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>

#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "Facility.h"
#include "HashTable.h"

class DataLoader {
    // type the declarations here, in the order listed above
};

#endif

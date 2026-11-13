// ===========================================================================
// FacilitySearch.h -- facility name search, category search, and the facility
// category report (FAC-4, FAC-5, RPT-2).
// Author: Logan Conrad
//
// All three operations only READ the accepted facility records, so they take
// the vector by const reference and never modify it. The specification allows
// a straightforward linear scan for name and category search (Section 6.2),
// so no hash table is used here -- the ID hash table stays the only custom
// hash structure in the project.
// ===========================================================================
#ifndef FACILITYSEARCH_H
#define FACILITYSEARCH_H

#include <string>
#include <vector>

#include "Facility.h"

// ---------------------------------------------------------------------------
// FAC-4 -- Search facility by name.
//
// Input:  facilities -- every accepted facility, in file order.
//         query      -- the raw line the user typed at the prompt.
//
// Contract:
//   1. Trim leading/trailing whitespace from query. If nothing is left,
//      print an error and return (a blank name is not a search).
//   2. Compare query against each facility's name IGNORING CASE. The match
//      is on the COMPLETE name -- partial matching is not required.
//   3. Print every match in file order, all four fields, one facility per
//      line, then the match count.
//   4. If nothing matches, print a not-found message that echoes the query.
//
// Edge cases the rubric checks: case differences, outer whitespace, two
// facilities with the same name (the sample data has two "Room 101" -- both
// must be returned), and an empty result.
// ---------------------------------------------------------------------------
void searchFacilityByName(const std::vector<Facility>& facilities,
                          const std::string& query);

// ---------------------------------------------------------------------------
// FAC-5 -- Search facility by category.
//
// Input:  facilities -- every accepted facility, in file order.
//         query      -- the raw line the user typed at the prompt.
//
// Contract:
//   1. Trim outer whitespace; blank input is an error, not a search.
//   2. Compare against each facility's category IGNORING CASE, complete
//      match only.
//   3. Print every match in file order with all four fields, then the count.
//   4. No matches -> a not-found message that echoes the query.
// ---------------------------------------------------------------------------
void searchFacilityByCategory(const std::vector<Facility>& facilities,
                              const std::string& query);

// ---------------------------------------------------------------------------
// RPT-2 -- Facility category report.
//
// Input: facilities -- every accepted facility, in file order.
//
// Contract:
//   1. Group facilities by category IGNORING CASE, but DISPLAY the spelling
//      of the FIRST accepted facility in that group. ("Library" and
//      "library" are one group; whichever appeared first is what prints.)
//   2. For each group print: category, count, and percentage of all accepted
//      facilities with EXACTLY ONE decimal place.
//   3. Print the total number of facilities.
//   4. If there are no facilities: say none are available and show a total
//      of zero. Never divide by zero.
//
// Group order is not specified; first-appearance order is a defensible
// choice and keeps the output stable between runs.
// ---------------------------------------------------------------------------
void printFacilityCategoryReport(const std::vector<Facility>& facilities);

#endif  // FACILITYSEARCH_H

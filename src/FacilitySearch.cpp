// ===========================================================================
// FacilitySearch.cpp -- implementation of the Final-phase facility searches
// and the category report (FAC-4, FAC-5, RPT-2).
// Author: Logan Conrad
//
// The contracts live in FacilitySearch.h. This file is the part you type.
// Each function below is a stub so the project compiles and the menu is
// testable end to end; replace the body, keep the signature.
// ===========================================================================
#include "FacilitySearch.h"

#include <iostream>

// FAC-4 -- see the contract in FacilitySearch.h.
void searchFacilityByName(const std::vector<Facility>& facilities,
                          const std::string& query) {
    (void)facilities;
    (void)query;
    // TODO(logan): trim, reject blank, scan case-insensitively on the
    // complete name, print every match in file order, then the count.
    std::cout << "Name search is not implemented yet.\n";
}

// FAC-5 -- see the contract in FacilitySearch.h.
void searchFacilityByCategory(const std::vector<Facility>& facilities,
                              const std::string& query) {
    (void)facilities;
    (void)query;
    // TODO(logan): trim, reject blank, scan case-insensitively on the
    // complete category, print every match in file order, then the count.
    std::cout << "Category search is not implemented yet.\n";
}

// RPT-2 -- see the contract in FacilitySearch.h.
void printFacilityCategoryReport(const std::vector<Facility>& facilities) {
    (void)facilities;
    // TODO(logan): group ignoring case, keep the first spelling, count,
    // percentage to one decimal, total, and the empty case without a
    // division by zero.
    std::cout << "Facility category report is not implemented yet.\n";
}

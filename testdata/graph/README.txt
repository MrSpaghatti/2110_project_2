GRAPH TEST DATA -- OWNER: Hoang

Every folder here is a complete data directory, so it needs all four files even
when the case only exercises connections.txt.  Leave the unrelated files with a
single comment line (examples below) so the loader prints a clean 0 accepted.

Run one with:   ./campus testdata/graph/<folder>

Create these four folders:

1) self-connection/
   connections.txt:  Library|Library
   expected: rejected, reason names the self-connection, 0 connections total

2) reversed-duplicate/
   buildings.txt:    Library / Student Union
   connections.txt:  Library|Student Union
                     Student Union|Library
   expected: first accepted, second rejected as a duplicate, Library degree 1

3) unknown-building/
   connections.txt:  Library|Space Needle
   facilities.txt:   F001|Test Desk|Space Needle|Library
   expected: both rejected and the reason names the unknown building

4) two-components/
   buildings: Library, Student Union, Observatory, Radio Tower
   connections: Library|Student Union  and  Observatory|Radio Tower
   expected: two separate components, BFS from Library reaches 2 of 4

Stub file contents for the unused files:
   buildings.txt:    # BuildingName
   facilities.txt:   # FacilityID|FacilityName|BuildingName|Category

A second rule worth testing in every folder: put a blank line at the top and a
line starting with # in the middle -- both must be ignored, not counted as
rejected records.

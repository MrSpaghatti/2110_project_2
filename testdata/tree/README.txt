TREE TEST DATA -- OWNER: OJ

Every folder here is a complete data directory, so it needs all four files even
when the case only exercises departments.txt.  Leave the unrelated files with a
single comment line so the loader prints a clean 0 accepted.

Run one with:   ./campus testdata/tree/<folder>

Create these four folders:

1) unknown-parent/
   departments.txt:  University|NONE
                     Computer Science|Nowhere University
   expected: second record rejected, reason names the unknown parent

2) duplicate-name/
   departments.txt:  University|NONE
                     Physics|NONE2
                     physics|University
   expected: "Physics" accepted, "physics" rejected as a duplicate regardless
   of capitalization.  (Swap the second line for a real parent -- the point is
   the case-insensitive duplicate, not the parent.)

3) root-only/
   departments.txt:  University|NONE
   expected: hierarchy shows one line, statistics 1 department / 1 leaf /
   height 0 -- and searching the root shows parent None, 0 children, depth 0

4) empty/
   departments.txt:  # DepartmentName|ParentName
   expected: adding the first department from the menu asks for NO parent and
   becomes the root; hierarchy and preorder print the empty-tree message

Stub file contents for the unused files:
   buildings.txt:   # BuildingName
   connections.txt: # BuildingA|BuildingB

Also copy data/departments.txt into a 5) sample/ folder so the normal tree
(nested, 4 leaves, height 2) can be exercised without touching data/.

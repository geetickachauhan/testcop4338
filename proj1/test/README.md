geometry
=======

C program that creates a list of points and sorts them, creates a list of line segments and sorts them. It also creates a list of rectangles and sorts them by area.

Usage
-----
reverse path-to-text subroutine

ex: reverse documents/example.txt A

The document may be up to 100 lines long with 80 characters in each line.
The program assumes each line is terminated by a new-line character “\n”

Arguments
---------
The first argument <path-to-text> may be a path to any text document.
The second argument <reverse-subroutine> may be either “A”, “B”, “C” or “D”.

Subroutines
-----------
A: Prints out line segments length from different points. Finally, displays the total tour length.
B: Sorts the points according to their X coordinate. Prints out line segments length from different points. Finally, displays the total tour length.
C: Sorts the original line segments by length. Prints out line segments length from different points. Finally, displays the total tour length.
D: Creates rectangles from the original points. Sorts rectangles by area and prints it out.

License
-------
reverse is Copyright (c) 2015 Tyler Lozano, Geeticka Chauhan. It is free software, and may be redistributed under the terms specified in the LICENSE file.


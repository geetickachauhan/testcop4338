nba
=======

C program that parses a list of players 

Usage
-----
nba subroutine option

ex: 
nba A Santiago
nba B PPG
nba C
nba D

The document is assumed to be players.txt and must be edited and rebuilt to take another document.
The program assumes each line is terminated by a new-line character “\n”.

Arguments
---------
The first argument <subroutine> may be either “A”, “B”, “C” or “D”.
The second optional argument may be an option passed to A or B as player_Name or {PPG|APG|RPG|SPG} respectively.

Subroutines
-----------
A: Prints <player_name>'s ID, PPG, APG, RPG, SPG, and MPG to stdout

B: Prints a sorted list of all players in descending order according to their APG, PPG, RPG, or SPG to stdout

Options: APG, PPG, SPG, RPG

C: Prints to stdout the best offensive and defensive player according to the following formulas:
	Defense value = (RPG * 5 + SPG * 3) / MPG
	Offense value = (PPG + APG * 2 + RPG / 2) / MPG

D: Prints to stdout the MVP after tallying 3 votes per player according to the following rules:
	1. Any vote by oneself for oneself is disregarded
	2. Multiple votes for the same player will result in only counting the max-weighted vote
	3. 1st vote is 3 points, 2nd vote is 2 points, and 3rd vote is 1 point

License
-------
nba is Copyright (c) 2015 Tyler Lozano, Geeticka Chauhan. It is free software, and may be redistributed under the terms specified in the LICENSE file.


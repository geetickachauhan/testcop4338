#include "lib.h"


/** Interprets list of points as line segments and prints their info
 * 
 * sorts list in ascending order according to the length of each line 
 * list is pre-initialized Struct as an interface for an array of Topology
 * f is the file to be parsed for points
 */
void C(List *list, FILE *f)
{
	parse_shapes(f, list, distance, 1);
	qsort(list->tops, list->filled, sizeof(Topology), comp);
	print_list(list, LINES, TOTAL);
}

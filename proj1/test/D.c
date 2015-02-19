#include "lib.h"
#include <stdlib.h>


/** Interprets list of points as rectangles and prints their info
 *
 * list is sorted in ascending order according to the area of each rect
 * list is pre-initialized Struct as an interface for an array of Topology
 * f is the file to be parsed for points
 */
void D(List *list, FILE *f)
{
	//last arg 2 partitions list into 2 point segments, no overlap
	parse_shapes(f, list, area, 2);
	qsort(list->tops, list->filled, sizeof(Topology), comp);
	print_list(list, RECTS, "");
}

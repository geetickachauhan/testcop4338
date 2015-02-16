#include "lib.h"

void C(List *list, FILE *f)
{
	parse_shapes(f, list, distance, 1);
	qsort(list->tops, list->filled, sizeof(Topology), comp);
	print_list(list, LINES, TOTAL);
}

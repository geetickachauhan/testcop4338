#include "lib.h"

void D(List *list, FILE *f)
{
	parse_shapes(f, list, area, 2);
	qsort(list->tops, list->filled, sizeof(Topology), comp);
	print_list(list, RECTS, "");
}

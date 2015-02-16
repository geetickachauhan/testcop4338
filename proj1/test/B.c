#include "lib.h"
#include <math.h>
#include <stdlib.h>

void B(List *list, FILE *f)
{
	List real_list;
	initialize(&real_list);
	parse_shapes(f, list, xdistance, 0);
	qsort(list->tops, list->filled, sizeof(Topology), comp);
	
	Point prev = {0, 0};
	Point curr = {0, 0};
	int first = 1;
	printf("I'm here!\n");
	while(first <= (list->filled))
	{
		Topology t = get(list, first-1);
		curr = t.p1;
		if(first == 1){prev = curr; first++ ; continue;}
		Topology tmp = {prev, curr};
		tmp.magnitude = distance(&tmp);
		append(&real_list, tmp);
		prev = curr;
		first++;
	}

	print_list(&real_list, LINES, TOTAL);
	free_list(&real_list);
}

#include "lib.h" //doesnt need this 

void A(List *list, FILE *f)
{
	parse_shapes(f, list, distance, 1);
	print_list(list, LINES, TOTAL);
}

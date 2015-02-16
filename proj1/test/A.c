#include "lib.h" //doesnt need this 

/** Interprets list of points as line segments and prints their info
 * list is pre-initialized Struct as an interface for an array of Topology
 * f is the file to be parsed for points
 */
void A(List *list, FILE *f)
{
	//last arg 1 represents partition step through data set
	//that is, every new point is also a new line
	//distance is the function used to return Topology's magnitude
	parse_shapes(f, list, distance, 1);
	//args LINES and TOTAL are predefined format strings to printf
	print_list(list, LINES, TOTAL); 
}

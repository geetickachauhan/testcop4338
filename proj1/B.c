#include "lib.h"
#include <math.h>


/** Interprets list of points as line segments and prints their info
 *
 * must order the points by x value and parses the list again
 * to create a new list that is then sent to stdout with printf 
 * list is pre-initialized Struct as an interface for an array of Topology
 * f is the file to be parsed for points
 */
void B(List *list, FILE *f)
{
	List real_list; // second list to have lines added to it
	initialize(&real_list);
	parse_shapes(f, list, xdistance, 0); //list of points, only T->p1 used
	//sorted by T->p1->x value
	qsort(list->tops, list->filled, sizeof(Topology), comp);	

	//slight modification of parse_shapes function; refer for understanding
	Point prev = {0, 0};
	Point curr = {0, 0};
	int first = 1;
	while(first <= (list->filled))//while list of points is full
	{
		Topology t = get(list, first-1);//get first point
		curr = t.p1;//current point
		//prevents topology without two elements
		if(first == 1){prev = curr; first++ ; continue;}
		Topology tmp = {prev, curr};
		tmp.magnitude = distance(&tmp);
		append(&real_list, tmp);
		prev = curr;//acts like previous in linked-list
		first++;
	}

	print_list(&real_list, LINES, TOTAL);
	free_list(&real_list);
}

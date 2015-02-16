#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** initializes Struct elements and allocates memory for array
 * according to initial capacity constraint, can be changed if necessary
 */
void initialize(List *list)
{
	list->filled = 0;
	list->capacity = INITIAL_CAPACITY;

	list->tops = malloc(sizeof(Topology) * list->capacity); 
}

/** adds Topology to end of list
 */
void append(List *list, Topology t)
{
	grow_list(list);//check if list is too small and needs to grow

	list->tops[list->filled++] = t;
}

/** get Topology from list according to index
 */
Topology get(List *list, int index)
{
	if (index < 0 || list->filled <= index) {
		perror("Error in list.get");
		exit(0);
	}
	return list->tops[index];
}

/** make array backing list bigger to accomodate new elements,
 * but make twice as big in order to reduce running time to O(log)
 */
void grow_list(List *list)
{
	if (list->capacity <= list->filled) {
		list->capacity *= 2;
		list->tops = realloc(list->tops, sizeof(Topology) * list->capacity);
	}
}

/** frees each element in list so no memory leak occurs
 */
void free_list(List *list)
{
	free(list->tops);
}

/** prints list
 *
 * takes format strings for body of information and end declaration
 */
void print_list(List *list, const char *format_string, const char *end_string)
{
	int i;
	float acc = 0;
	for (i = 0; i < (list->filled); i++)
       	{
		Topology tmp = get(list, i);
		printf(format_string, i, tmp.p1.x, tmp.p1.y, tmp.p2.x, tmp.p2.y, tmp.magnitude); acc += tmp.magnitude;
	}
	if(strcmp(end_string, "")) 
                printf(end_string, acc);
}

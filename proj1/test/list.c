#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(List *list)
{
	list->filled = 0;
	list->capacity = INITIAL_CAPACITY;

	list->tops = malloc(sizeof(Topology) * list->capacity); 
}

void append(List *list, Topology t)
{
	grow_list(list);

	list->tops[list->filled++] = t;
}

Topology get(List *list, int index)
{
	if (index < 0 || list->filled <= index) {
		perror("Error in list.get");
		exit(0);
	}
	return list->tops[index];
}

void grow_list(List *list)
{
	if (list->capacity <= list->filled) {
		list->capacity *= 2;
		list->tops = realloc(list->tops, sizeof(Topology) * list->capacity);
	}
}

void free_list(List *list)
{
	free(list->tops);
}

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

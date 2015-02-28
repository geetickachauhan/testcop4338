#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef struct {
//	int filled; //how filled it is
//	int capacity; //total available slots
//	Player *players; //array of Player
//} List;

/** initializes Struct elements and allocates memory for array
 * according to initial capacity constraint, can be changed if necessary
 */
void initialize(List *list)
{
	list->filled = 0;
	list->capacity = INITIAL_CAPACITY;

	list->players = malloc(sizeof(Player) * list->capacity); 
}

/** adds Player to end of list
 */
void append(List *list, Player t)
{
	grow_list(list);//check if list is too small and needs to grow

	list->players[list->filled++] = t;
}

/** get Player from list according to index
 */
Player get(List *list, int index)
{
	if (index < 0 || list->filled <= index) {
		perror("Error in list.get");
		exit(0);
	}
	return list->players[index];
}

/** make array backing list bigger to accomodate new elements,
 * but make twice as big in order to reduce running time to O(log)
 */
void grow_list(List *list)
{
	if (list->capacity <= list->filled) {
		list->capacity *= 2;

		list->players = realloc(list->players, sizeof(Player) * list->capacity);
	}
}

/** frees each element in list so no memory leak occurs
 */
void free_list(List *list)
{
	free(list->players);
}

/** prints list
 *
 * takes format strings for body of information and end declaration
 */
void print_list(List *list, const char *format_string)
{
	int i;
	Player p;
	for (i = 0; i < (list->filled); i++)
       	{
		p = get(list, i);
		printf(format_string, p.id, p.name, p.PPG, p.APG, p.RPG, p.SPG, p.MPG, p.vote1, p.vote2, p.vote3); }
}

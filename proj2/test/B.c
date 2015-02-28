#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PPG(const void *ip1, const void *ip2)
{
	Player p1 = *((Player *) ip1);
	Player p2 = *((Player *) ip2);
	if (p1.PPG > p2.PPG) return -1;
	if (p1.PPG < p2.PPG) return 1;	
	return 0;
}

int APG(const void *ip1, const void *ip2)
{
	Player p1 = *((Player *) ip1);
	Player p2 = *((Player *) ip2);
	if (p1.APG > p2.APG) return -1;
	if (p1.APG < p2.APG) return 1;	
	return 0;
}

int RPG(const void *ip1, const void *ip2)
{
	Player p1 = *((Player *) ip1);
	Player p2 = *((Player *) ip2);
	if (p1.RPG > p2.RPG) return -1;
	if (p1.RPG < p2.RPG) return 1;	
	return 0;
}

int SPG(const void *ip1, const void *ip2)
{
	Player p1 = *((Player *) ip1);
	Player p2 = *((Player *) ip2);
	if (p1.SPG > p2.SPG) return -1;
	if (p1.SPG < p2.SPG) return 1;	
	return 0;
}

void print_player(Player* pi)
{
	Player p = *pi;
	printf("\n%d %s %f %f %f %f %f %d %d %d\n", p.id, p.name, p.PPG, p.APG, p.RPG, p.SPG, p.MPG, p.vote1, p.vote2, p.vote3);
}

void print_PPG(List *list)
{
	int i;
	Player p;
	for (i = 0; i < (list->filled); i++)
       	{
		p = get(list, i);
		printf("\n%d %s %f", p.id, p.name, p.PPG);
	}
}

void print_APG(List *list)
{
	int i;
	Player p;
	for (i = 0; i < (list->filled); i++)
       	{
		p = get(list, i);
		printf("\n%d %s %f", p.id, p.name, p.APG);
	}
}

void print_RPG(List *list)
{
	int i;
	Player p;
	for (i = 0; i < (list->filled); i++)
       	{
		p = get(list, i);
		printf("\n%d %s %f", p.id, p.name, p.RPG);
	}
}

void print_SPG(List *list)
{
	int i;
	Player p;
	for (i = 0; i < (list->filled); i++)
       	{
		p = get(list, i);
		printf("\n%d %s %f", p.id, p.name, p.SPG);
	}
}

void B(List* list,  char* choice)
{

	//qsort(list->players, list->filled, sizeof(Player), PPG); 
	if (strcmp("PPG", choice) == 0)
	{
	qsort_r(list->players, list->filled, sizeof(Player), PPG); 
	print_PPG(list);
	}

	else if (strcmp("APG", choice) == 0)
	{
	qsort_r(list->players, list->filled, sizeof(Player), APG); 
	print_APG(list);
	}

	else if (strcmp("RPG", choice) == 0)
	{
	qsort_r(list->players, list->filled, sizeof(Player), RPG); 
	print_RPG(list);
	}

	else if (strcmp("SPG", choice) == 0)
	{
	qsort_r(list->players, list->filled, sizeof(Player), SPG); 
	print_SPG(list);
	}

	else printf("%s not a valid option", choice);
}


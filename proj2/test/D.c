#include <search.h>
#include "lib.h"
#include <stdlib.h>
void addvote(int vote, int *max, int *maxd, int points)
{
	char str[15];
	sprintf(str, "%d", vote);
	ENTRY tmp;
	tmp.key = str;
	ENTRY* id;
	id = hsearch(tmp, FIND);
	if( id == NULL)
	{
		tmp.data =  (void *) points;
		hsearch(tmp, ENTER);
	}

	else
	{
		(id->data) += points;
		if((int)(id -> data) > *maxd)
		{
			*max = (int) strtol((id->key), (char **)NULL, 10);
			*maxd = (int )(id->data);
		}
	}
}

void D(List * list)
{
	int maxd = 0;
	int max = 0;
	if(hcreate(list->filled)==0)
	{
		perror("Hashtable creation failed!");
		exit(0);
	}	

	int i;
	Player p;
	for (i = 0; i < (list->filled); i++) {
		p = get(list, i);
		if (p.vote1 != p.id) {
		addvote(p.vote1, &max, &maxd, 3);		
		}
		if (p.vote2 != p.id && p.vote2 != p.vote1) {
		addvote(p.vote2, &max, &maxd, 2);
		}
		if (p.vote3 != p.id && p.vote3 != p.vote1 && p.vote3 != p.vote2) {
		addvote(p.vote3, &max, &maxd, 1);
		}
	}

	for (i = 0; i < (list->filled); i++) {
		p = get(list, i);
		if (p.id == max) {
			printf("\nThe MVP is %s, with %d point(s).\n", p.name, maxd);
		}
	}
	hdestroy();
}

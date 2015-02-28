#include "lib.h"
#include <math.h>

typedef struct {
	char* pname;
	int id, vote1, vote2, vote3;
	float PPG, APG, RPG, SPG, MPG;
} Player;


// compares two players by their magnitude
// this function is to be passed to qsort
//int comp(const void *ip1, const void *ip2)
//{
//	Player p1 = *((Player *) ip1);
//	Player p2 = *((Player *) ip2);
//	if (p1.<insert> > p2.<insert>) return 1;
//	if (p1.<insert> < t2.<insert>) return -1;	
//	return 0;
//}


#include "lib.h"
#include <math.h>

float area(Topology *t)
{
	float d1 = fabs((t->p1).x - (t->p2).x);	
	float d2 = fabs((t->p1).y - (t->p2).y);
	return d1 * d2;
}

float distance(Topology *t)
{
	float d1 = fabs((t->p1).x - (t->p2).x);	
	float d2 = fabs((t->p1).y - (t->p2).y);
	return sqrt(pow(d1,2) + pow(d2, 2));

}

float xdistance(Topology *t)
{
	return t->p1.x;
}

int comp(const void *it1, const void *it2)
{
	Topology t1 = *((Topology *) it1);
	Topology t2 = *((Topology *) it2);
	if (t1.magnitude > t2.magnitude) return 1;
	if (t1.magnitude < t2.magnitude) return -1;	
	return 0;
}


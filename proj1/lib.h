#include <stdio.h>

#define INITIAL_CAPACITY 100
#define LINES "Line[%d]: <%.2f, %.2f>, <%.2f, %.2f> -- Length = %.2f\n"
#define TOTAL "Total Tour Length = %.2f\n"
#define RECTS "Rectangle[%d]: <%.2f, %.2f>, <%.2f, %.2f> -- Area = %.2f\n"

typedef struct  {
	float x;
	float y;
} Point;

typedef struct  {
	Point p1;
	Point p2;
	float magnitude;
} Topology;

float area(Topology *t);
float distance(Topology *t);
float xdistance(Topology *t);
int comp(const void *it1, const void *it2);

typedef struct {
	int filled; //how filled it is
	int capacity; //total available slots
	Topology *tops; //array of Topology
} List;

void D(List *list, FILE *f);
void C(List *list, FILE *f);
void B(List *list, FILE *f);
void A(List *list, FILE *f);
void initialize(List *list);

void append(List *list, Topology t);

Topology get(List *list, int index);

void set(List *list, int index, Topology t);

void grow_list(List *list);

void free_list(List *list);

void print_list(List *list, const char *format_string, const char *end_string);

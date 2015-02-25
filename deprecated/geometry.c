#include<stdio.h>
#include<math.h>

// generic typedef to allow for type independent operations, otherwise multiple fns required
// points are merely topologies with one point and magnitude equal to their x dimension
// although distance from origin might be more appropriate
typedef struct _Topology 
{
	Point *pts;
	float magnitude;
} Topology;

// struct used to define Topology since a topology is just a collection of points
typedef struct _Point
{
	float x;
	float y;
} Point;

typedef struct LinkedList
{
    Topology T;
    struct LinkedList *next;
}LL;
/* grows the array dynamically and catches realloc fail so as to prevent memory leak
 * need to keep pointer to array size to call this functional iteratively
 */
Point* grow_array(Point* pts, int* size)
{
	Point* tmp;
	if((tmp = realloc(pts, sizeof(Point) * size * 2)) == NULL)
	{
		perror("Realloc failed.");
		exit(0);
	}
	pts = tmp;
}

Point* parse_points(FILE *f)
{
	unsigned int* size; size* = 16; // size of two floats is 16
	unsigned int i = 0;
	Point* pts = pts[16];
	while((fscanf(f, "%f %f %*[\n]", x, y)) != EOF)
	{
		if (++i > size) 
                {
			grow_array(pts, size);
		}
		Point p;
		p.x = x; p.y = y;
		pts[i] = p;
	}
	return pts;
}

/* builds an Topology array based on Point array, magnitude function, and partition_step
 * it can build lines with n points and a distance function; geometry uses p_step 1 for lines
 * ...rectangles with n even points and an area function; geometry uses p_step 2 for rectangles
 */
Topology* build_shapes(Point *pts, float (*mag)(float), int partition_step)
{
	
}

float area(Topology t)
{
	float d1 = abs( (t.pts)->x - (++t.pts)->x); // dimension1 = (x of 1st pt) - (x of 2nd pt)
	float d2 = abs( (t.pts)->y - (++t.pts)->y); // "       "2 "  y               y          "
	return d1 * d2;
}

float distance(Topology t)
{
	float d1 = abs( (t.pts)->x - (++t.pts)->x); // same as area fn
	float d2 = abs( (t.pts)->y - (++t.pts)->y);
	return sqrt(pow(d1,2) + pow(d2,2)); // use pythagorean theorem A^2+B^2=C^2
}

// to be used with qsort or other sorting algorithm in the sorting of topologies
int comp(const void *t1, const void *t2)
{
	Topology t1 = *((Topology*) t1);
	Topology t2 = *((Topology*) t2);
        //should be t1.magnitude since t1 is not a pointer
	if (t1.magnitude > t2.magnitude) return 1;
	if (t1.magnitude < t2.magnitude) return -1;
	return 0;
}

int main(int argc, const char*argv[])
{
    if(argc != 3)
    {
        printf("reverse only takes 2 arguments, you passed %d.\n", (argc-1));
        exit(0);
    }
    
    FILE *file;
    if((file = fopen(argv[1], "r")) == NULL)
    {
        perror("FOPEN");
        exit(0);
    }
    return(0);
    switch(*argv[2]){
		case 'A': partA(file); break;
		case 'B': partB(file); break;
		case 'C': partC(file); break;
                case 'D': partD(file); break;
		default: printf("Invalid argument to reverse. Please refer to README for list of options and arguments.");
	}

}
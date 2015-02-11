#include<stdio.h>
#include<math.h>

// generic typedef to allow for type independent operations, otherwise multiple fns required
// points are merely topologies with one point and magnitude equal to their x dimension
// although distance from origin might be more appropriate
typedef struct _Topology 
{
	Point pt1;
        Point pt2;
	float magnitude;
} Topology;

// struct used to define Topology since a topology is just a collection of points
typedef struct _Point
{
	float x;
	float y;
} Point;

typedef struct _LinkedListPoints
{
    Point p;
    struct _LinkedListPoints *next;
}LinkedListPoints;

typedef struct _LinkedListShapes
{
    Topology T;
    struct _LinkedListShapes *next;
}LinkedListShapes;

int sizeOfPoints = 0; //store the size of linked list of points
int sizeOfShapes = 0; //store the size of rectangle 

LinkedListPoints* createPoints(FILE *f)
{
    LinkedListPoints *head, *list, *prev;
    head = p = prev = NULL;
    float x;
    float y;
    while((fscanf(f, "%f %f %*[\n]", x, y)) != EOF)
    {
        sizeOfPoints++;
        //create a new node
        list = (LinkedListPoints*)malloc(sizeof(LinkedListPoints));
        
        //populate the node
        (list->p).x = x;
        (list->p).y = y;
        p->next = prev;
        head = p;
        prev = p;
    }
    
}


//pass the head of the linkedlistpoints
// second parameter to indicate if its a line or a rectangle
// 1 for line, 2 for rectangle
LinkedListShapes* createShape(LinkedListPoints* head, int shape)
{
    LinkedListShapes *head, *list, *prev;
    LinkedListPoints* iterator = head;
    LinkedListPoints* iterator1 = iterator.next;
    float x1;
    float y1;
    float x2;
    float y2;
    if(iterator == null || iterator.next == null)
    {
        printf("list is empty\n"); //line segment cant be made without two points
        return null;
    }
    int i = 0;
    do
    {
        i++;
        sizeOfShapes++;
        list = (LinkedListShapes*)malloc(sizeof(LinkedListShapes));
        x1 = (list->T).pt1.x = (iterator->p).x;
        y1 = (list->T).pt1.y = (iterator->p).y;
        
        x2 = (list->T).pt2.x = (iterator1->p).x;
        y2 = (list->T).pt2.y = (iterator1->p).y;
        if(shape ==1)
        {
            (list->T).magnitude = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
        }
        if(shape == 2)
        {
            float d1 = abs( x1 - x2); // dimension1 = (x of 1st pt) - (x of 2nd pt)
            float d2 = abs( y1 - y2); // "       "2 "  y               y          "
            (list->T).magnitude = d1 * d2;
        }
        iterator = iterator.next;
        iterator1 = iterator1.next;
    }while(iterator1.next != NULL && i< (sizeOfPoints/2));
            
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
    switch(*argv[2])
    {
        case 'A': partA(file); break;
        case 'B': partB(file); break;
        case 'C': partC(file); break;
        case 'D': partD(file); break;
        default: printf("Invalid argument to reverse. Please refer to README for list of options and arguments.");
    }
    return(0);
}



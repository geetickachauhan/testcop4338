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
    int size;
    struct _LinkedListPoints *next;
}LinkedListPoints;

typedef struct _LinkedListShapes
{
    Topology T;
    int size;
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
       // sizeOfPoints++;
        //create a new node
        list = (LinkedListPoints*)malloc(sizeof(LinkedListPoints));
        (list->size)++;
        //populate the node
        (list->p).x = x;
        (list->p).y = y;
        p->next = prev;
        head = p;
        prev = p;
    }
    return head;
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
       // i++;
        //sizeOfShapes++;
        list = (LinkedListShapes*)malloc(sizeof(LinkedListShapes));
        (list->size)++;
        x1 = (list->T).pt1.x = (iterator->p).x;
        y1 = (list->T).pt1.y = (iterator->p).y;
        
        x2 = (list->T).pt2.x = (iterator1->p).x;
        y2 = (list->T).pt2.y = (iterator1->p).y;
        if(shape ==1)
        {
            int val = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
            (list->T).magnitude = roundf(val *100)/100; // round to the 
            //2 decimals. 
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
    
    return head;
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
    
    LinkedListPoints * LLP = createPoints(file); //this is the head of the 
    //point file 
    
    switch(*argv[2])
    {
        case 'A': partA(LLP); break;
        case 'B': partB(LLP); break;
        case 'C': partC(LLP); break;
        case 'D': partD(LLP); break;
        default: printf("Invalid argument to reverse. Please refer to README for list of options and arguments.");
    }
    return(0);
}

//parameter is the head of the list of points
void partA(LinkedListPoints* head)
{
    LinkedListShapes* h = createShape(head, 1); // to return the head of 
    // a new list point
    
    LinkedListShapes *iterator = h;
    int totalLength = 0;
    int numOfLineSegments = 0;
    
    while(iterator != NULL)
    {
        numOfLineSegments++;
        float x1 = (iterator->T).pt1.x;
        float y1 = (iterator->T).pt1.y;
        float x2 = (iterator->T).pt2.x;
        float y2 = (iterator->T).pt2.y;
        float length = (iterator->T).magnitude;
        totalLength += length;
        printf("Segment[%d]: (%f, %f)-->(%f, %f); length = %f", numOfLineSegments, x1, y1, x2, y2, length);
    }
    
    printf("Total tour length = %f\n", totalLength);
    printf("Total line segments = %d\n", numOfLineSegments);
}

void partB(
        



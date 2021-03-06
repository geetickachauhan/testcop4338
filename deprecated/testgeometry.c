#include<stdio.h>
#include<math.h>

// generic typedef to allow for type independent operations, otherwise multiple fns required
// points are merely topologies with one point and magnitude equal to their x dimension
// although distance from origin might be more appropriate
// below is just to store a line segment/rectangle
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

//this creates a linked list of points which is used to create a linked
// list of line segments or rectangles
typedef struct _LinkedListPoints
{
    Point p;
    int size;
    struct _LinkedListPoints *next;
}LinkedListPoints;

//this creates a linked list of shape which can either be a line segment or 
// a rectangle
typedef struct _LinkedListShapes
{
    Topology T;
    int size;
    struct _LinkedListShapes *next;
}LinkedListShapes;

int sizeOfPoints = 0; //store the size of linked list of points
int sizeOfShapes = 0; //store the size of rectangle 

// a function returning the head of the created linked list of points
// this opens up the file and reads in to store the points
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
        (list->size)++;
        //populate the node
        (list->p).x = x;
        (list->p).y = y;
        list->next = prev;
        head = list;
        prev = list;
    }
    return head;
}


//pass the head of the linkedlistpoints
// second parameter to indicate if its a line or a rectangle
// 1 for line, 2 for rectangle
LinkedListShapes* createShape(LinkedListPoints* head, int shape)
{
    //to create the linked list of rectangle or line segments
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
        sizeOfShapes++;
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
    }while(iterator1.next != NULL);
    // no need to make it go to sizeOfPoints/2 because if there are three points
    // they create two line segments
    
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
//the return value is used in partC
LinkedListShapes* partA(LinkedListPoints* head)
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
    
    return h;
}

void partB(LinkedListPoints* head)
{
    //iterates through the linked list of points and then sorts them 
    // the way it is sorted is that there is an array each of whose 
    // element is the pointer to an element of the linked list
    LinkedListPoints *iterator = head;
    int numOfPoints = 0;
    while(iterator!= NULL)
    {
        numOfPoints++;
        iterator = iterator->next;
    }
    LinkedListPoints **array = (LinkedListPoints**)malloc(numOfPoints*sizeof(LinkedListPoints**));
    iterator = head;
    int i = 0;
    while(iterator!= NULL)
    {
        array[i] = iterator;
        i++;
        iterator = iterator->next;
    }
    qsort(array,numOfPoints, sizeof(LinkedListPoints*), cmp);
    
    //now storing the sorted list in a new linked list of points
    LinkedListPoints *list, *h, *prev;
    
    //going all the way up to the size of the array 
    // and in the correct order of elements, storing the linked list 
    // of points 
    int j;
    for(j = 0; j<i ; j++)
    {
        //create a new node
        list = (LinkedListPoints*)malloc(sizeof(LinkedListPoints));
        (list->size)++;
        //populate the node
        (list->p).x = (array[j]->p).x;
        (list->p).y = (array[j]->p).y;
        list->next = prev;
        h = list;
        prev = list;
    }
    
    //now that you have created the linked list of points, 
    // do the same thing that the partA did
    LinkedListShapes* headLines = partA(h); //do the same thing as in partA for
    //the new sorted list
}

//in order to sort the points
// will need a seperate method to sort shapes because in that case we're 
// comparing magnitude
int comp(const void *t1, const void *t2)
{
    LinkedListPoints *A = *((LinkedListPoints**)t1);
    LinkedListPoints *B = *((LinkedListPoints**)t2);
    
    if((A->p).x > (B->p).x) return 1;
    if((A->p).x < (B->p).x) return -1;
    return 0;
}
    /*
	Topology t1 = *((Topology*) t1);
	Topology t2 = *((Topology*) t2);
        //should be t1.magnitude since t1 is not a pointer
	if (t1.magnitude > t2.magnitude) return 1;
	if (t1.magnitude < t2.magnitude) return -1;
	return 0;
        */

        



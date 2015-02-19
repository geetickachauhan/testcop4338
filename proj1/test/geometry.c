#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

//goal of this function is to iterate only once through file to create list
//of topology that can then be printed, sorted, etc
//
//p_step determines when to make Topology to put in list... imod(p_step);
//p_step = 0, 1, 2 for points, lines, and rectangles respectively.
//function pointer is a magnitude function that determines length, area, etc
void parse_shapes(FILE *f, List *list, float (*mag)(Topology*), int p_step)
{
	float x, y;
	Point prev = {0, 0};//prev point encountered
	Point curr = {0, 0};
	int point_flag = 0;//if topologies are to be used as points instead
	if(p_step == 0){point_flag = 1; p_step = 1;}
	int first = 1;
	while((fscanf(f, "%f %f %*[\n]", &x, &y)) != EOF)
	{
		curr.x = x; curr.y = y;
		if(first == 1){prev = curr; first++ ; continue;}
		if(first % p_step == 0)//how many lines to skip before building topology
		{
		Topology tmp = {prev, curr};
		tmp.magnitude = mag(&tmp);
		append(list, tmp);
		}
		prev = curr;
		first++;
	}
	if(point_flag == 1)//needed to add last element that gets leftout
       	{
		Topology tmp = {curr, curr}; 
		tmp.magnitude = mag(&tmp);
	       	append(list, tmp);
	}
}

int main(int argc, const char *argv[])
{
    /* checks if there are more or less than 3 arguments
     * passed to program, if true then prints error
     */
	if(argc != 3)
	{
		printf("geometry only takes 2 arguments, you passed %d.\n", (argc-1));
		exit(0);
	}	
    /* instantiates file pointer and conducts input validation
     * on filename argv[1] that user provides, exits program
     * with error message if fopen fails
     */
	FILE *file;
	if((file = fopen(argv[1], "r")) == NULL){
		perror("FOPEN");
		exit(0);
	}
	
	List list;
	initialize(&list);
	// a switch statement to call the function according to the user's choice
	switch(*argv[2])
	{
		case 'A':   printf("Printing out line segments length from different points. Finally, displaying the total tour length\n");
                            A(&list, file); break;
		case 'B':   printf("Sorting the points according to their X coordinate. Printing out line segments length from different points. Finally, displaying the total tour length\n");
                            B(&list, file); break;
		case 'C':   printf("Sorting the original line segments by length. Printing out line segments length from different points. Finally, displaying the total tour length\n");
                            C(&list, file); break;
		case 'D':   printf("Creating rectangles from the original points. Sorting rectangles by area and printing it out\n");
                            D(&list, file); break;
		default: printf("Invalid argument to geometry. Please refer to README for list of options and arguments.\n");
	}

	free_list(&list);
	fclose(file);

	return 0;
}

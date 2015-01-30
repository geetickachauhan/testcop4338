#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partA.h"
#include "partB.h"
#include "partC.h"

/*
Main method 
Parameters: argc which is an integer to store the number of command line
            arguments   
            argv[] which is an array of pointers for the arguments as characters

This method checks if the desired number of command line arguments are 
entered and then calls the desired method according to which option is 
entered in the third command line argument. 
*/
int main(int argc, const char *argv[])
{
    /* checks if there are more or less than 3 arguments
     * passed to program, if true then prints error
     */
	if(argc != 3){
		printf("reverse only takes 2 arguments, you passed %d.\n", (argc-1));
		exit(0);}
    /* instantiates file pointer and conducts input validation
     * on filename argv[1] that user provides, exits program
     * with error message if fopen fails
     */
	FILE *file;
	if((file = fopen(argv[1], "r")) == NULL){
		perror("FOPEN");
		exit(0);
	}

	// a switch statement to call the function according to the user's choice
	switch(*argv[2]){
		case 'A': partA(file); break;
		case 'B': partB(file); break;
		case 'C': partC(file); break;
		default: printf("Invalid argument to reverse. Please refer to README for list of options and arguments.");
	}

	fclose(file);
}

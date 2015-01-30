#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// required header files

/* partA method
   Parameters: FILE pointer called file that points to a file in memory
   Prints the lines in the reverse order from how they were entered
*/
void partA(FILE * file)
{
    char array[100][81]; // create a char array to store each line as a row
                         // and each character in the line as column
    int numOfLines = 0;  // variable to represent number of lines in the file
    
    printf("\nPrinting lines in reverse order of input\n");
    
    char line[81]; // char array (string) to store the line that will be read
    
    while(fgets(line, sizeof(line), file)) //while you are able to get a string 
    {                                      // called line
        strcpy(array[numOfLines++], line); // copy each line to every row of 
    }                                      // character array
    
    int i; // declare the variable that will run the for loop below
    for(i = numOfLines - 1; i >= 0; i--) // make the loop run from the last line
    {                                    // in the array
        int j; // declare the variable for the for loop below
        for(j = 0; j < strlen(array[i]) - 1; j++) // make the loop run for 
            printf("%c", array[i][j]);            // every character until the 
        printf("\n");                             // second last character
    }                                             // as every last character is 
                                                  // a new line character  
}
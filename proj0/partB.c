#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//required header files

/* partB method
   Parameters: FILE pointer called file that points to a file in memory
   Prints the lines in order but characters of each line in reverse
*/

void partB(FILE * file)
{
    printf("\nPrinting characters of each line in reverse\n");
    
    char line[81]; // char array (string) to store the line that will be read
    while(fgets(line, sizeof(line), file)) //while you are able to get a string 
    {                                      // called line
        int i; // declare the variable that will run the for loop below
        for(i = strlen(line) - 2; i>= 0; i--) // make the loop run from the last        
            printf("%c", line[i]);            // character in every line and 
        printf("\n");                         // print
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void partA(char *);
void partB(char *);
void partC(char *);
/*
int partB(char *);
int partC(char *);
*/

int main(int argc, const char *argv[]){
    /* checks for bad arguments before running program
     * if there are more or less than 3 arguments
     * or either are null or invalid, then program 
     * exits with error message
     */
    if(argc != 3 || argv[1] == NULL || argv[2] == NULL) 
    {
        printf("Please run again.\n");
        exit(0); 
    }
    
    /* instantiates file pointer and conducts input validation
     * on filename argv[1] that user provides, exits program
     *with error message if fopen fails
     */
    FILE *file;
    if((file = fopen(argv[1], "r"))==NULL)
    {
        perror("FOPEN");
       // printf("\n %s failed to OPEN\n", filename);
        exit(0); 
    }

    // call appropriate method refered to by argv[2], print error message otherwise 
    switch (*argv[2]){
	    case 'A': A(file); break;
	    case 'B': B(file); break;
	    case 'C': C(file); break;
	    default: printf("Invalid argument to reverse. Please refer to readme for list of options and arguments.");
    }
    
   // fclose(file);


void A(FILE *file)
{
    char array[100][81];
    int numOfLines = 0;
    
    printf("\nPrinting lines in reverse order of input\n");
    
    char line[81]; // starting to extract lines 
    
    while(fgets(line, sizeof(line), file))
    {
        strcpy(array[numOfLines++], line);
    }
    // will need substring in order to extract the new line character at the end
    int i;
    for( i = numOfLines - 1; i >= 0; i--)
    {
        printf("%s\n", array[i]);
    }
}

void partB(char *filename)
{
    //char array[100][80];
    //int numOfLines = 0;
    
    printf("\nPrinting characters of each line in reverse\n");
    
    char line[81];
    while(fgets(line, sizeof(line), file))
    {
	int i;
        for( i = strlen(line) - 1; i>= 0; i--)
            printf("%c", line[i]);
        printf("\n");
    }
    
}

void partC(FILE *file)
{
    printf("\nPrinting lines in reverse order of input\n");
       
    char line[81];
    //int numOfWords = 0;
    char word[100][81];
    while(fgets(line, sizeof(line), file))
    {
        int charnum = 0; // for the characters in each word
        int wordnum = 0; // i keeps track of which character you are at in line
        int i;
        for(i = 0; i< strlen(line); i++)
        {
            //printf("%d ", i);
            if(line[i] != ' ' && line[i] != '\n')
                word[wordnum][charnum++] = line[i];
            else if(line[i] == ' ' && i!= 0) // i!=0 is for space as first char
            {
                word[wordnum][charnum] = '\0';
                wordnum++;
                charnum = 0;
            }
        }
        
        printf("%d %d", wordnum, charnum);
       // wordnum++;
        //charnum = 0;
        //word[wordnum][charnum++] = line[i];
	int j;
        for( j = wordnum - 1; j >= 0; j--)
        {
            printf("%s ", word[j]);
        }
        printf("\n");
            //
           // if(line[i] == ' ' && i != 0)
           // {
             //   line[i+1] = word[wordnum++]
               
    }
    
}
}

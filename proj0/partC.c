#include <stdio.h>
#include <string.h>

/* partC method
   Parameters: FILE pointer called file that points to a file in memory
   Prints the lines in order but words of each line in reverse
*/
void partC(FILE *f){

	printf("\nPrints each word of a line in the reverse order\n");
	char line[81]; // char array (string) to store the line that will be read
	char* words[81]; // // create a char pointer array to store each word in a line 
	while(fgets(line, sizeof(line), f))
	{
		size_t len = strlen(line);
		line[--len] = '\0';
		char* word;
		int i = 0;
		word = strtok(line, "\n ");
		while((word != NULL)){
			words[i] = word;
			word = strtok(NULL, " ");
			i++;
		}
		for(i = i-1; i >= 0; i--){
			printf("%s ", words[i]);
		}
		printf("\n");
	}
}


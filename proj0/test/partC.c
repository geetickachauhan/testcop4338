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
	/* iterate through the file and tokenize each line
	// place each token into array of words
	// iterate backword through array of words
	*/ 
	while(fgets(line, sizeof(line), f))
	{
		size_t len = strlen(line);
		line[--len] = '\0'; // remove new-line character
		char* word;
		int i = 0;
		word = strtok(line, " ");
		while((word != NULL)){ //continue tokenizing line until tokenizer returns null
			words[i] = word;
			word = strtok(NULL, " ");
			i++;
		}
		for(i = i-1; i >= 0; i--){ //return words in word array from last to first element
			printf("%s ", words[i]);
		}
		printf("\n");
	}
}


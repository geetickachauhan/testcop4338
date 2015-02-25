#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

//parses file to create an array of players
void parse_players(FILE *f, List *list)
{
	char* pname;
	int pid, pvote1, pvote2, pvote3;
	float pPPG, pAPG, pRPG, pSPG, pMPG;
	while((fscanf(f, "%d %s %f %f %f %f %f %d %d %d %*[\n]", 
			&pid, &pname, &pPPG, &pAPG, &pRPG,
			&pSPG, &pMPG, &pvote1, &pvote2, &pvote3)) != EOF)
	{
		//need to order it same way struct is made
		Player tmp = {pname, pid, pvote1, pvote2, pvote3, 
			      pPPG, pAPG, pRPG, pSPG, pMPG};
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
		case 'A':   printf("A");
                            A(&list, file); break;
		case 'B':   printf("B");
                            B(&list, file); break;
		case 'C':   printf("C");
                            C(&list, file); break;
		case 'D':   printf("D");
                            D(&list, file); break;
		default: printf("Invalid argument to geometry. Please refer to README for list of options and arguments.\n");
	}

	free_list(&list);
	fclose(file);

	return 0;
}

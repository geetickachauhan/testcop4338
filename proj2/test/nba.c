#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#define file_name "players.txt"

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
    /* instantiates file pointer and conducts input validation
     * on filename argv[1] that user provides, exits program
     * with error message if fopen fails
     */
	FILE *file;
	if((file = fopen(file_name, "r")) == NULL)
	{
		perror("FOPEN");
		exit(0);
	}
	
	List list;
	initialize(&list);
	parse_players(file, &list); //to create the list 
        
        // a switch statement to call the function according to the user's choice
	switch(*argv[1]) // *argv[1] is function A, B, C, or D
	{
		// argv[2] is option to be passed to function, if the function takes an option
		case 'A':   if(argc != 3) {printf("nba A needs 3 arguments, you passed %d", argc); exit(0);}
		            printf("A");
                            A(&list, argv[2]); break; // pass pointer to argument and dereference in function
		case 'B':   if(argc != 3) {printf("nba B needs 3 arguments, you passed %d", argc); exit(0);}
			    printf("B");
                            B(&list, argv[2]); break; 
		case 'C':   if(argc != 2) {printf("nba C needs 2 arguments, you passed %d", argc); exit(0);}
			    printf("C");
                            C(&list); break;
		case 'D':   if(argc != 2) {printf("nba D needs 2 arguments, you passed %d", argc); exit(0);}
			    printf("D");
                            D(&list); break; 
		default: printf("Invalid argument to nba. Please refer to README for list of options and arguments.\n");
	}

	free_list(&list);
	fclose(file);

	return 0;
}

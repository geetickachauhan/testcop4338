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
        parse_players(file, &list); //to create the list 
	switch(*argv[1]) // Geeticka edit: this time option is mentioned as the second command line var 
	{
		case 'A':   printf("A");
                            // Tyler's code: A(&list, file); break; //Geeticka: let's access the file and create the list in main so that we dont have to pass the file as a parameter
                            A(&list,*argv[2]); break; // Geeticka's code: Added the *argv[2] because it is the name to be searched for in the list
		case 'B':   printf("B");
                            B(&list, file); break; // might need to make the above changes in here as well
		case 'C':   printf("C");
                            //Tyler's code: C(&list, file); break; //Geeticka: same reason as in A
                            C(&list); break;
		case 'D':   printf("D");
                            D(&list, file); break; // might need to make the above changes in here as well
		default: printf("Invalid argument to geometry. Please refer to README for list of options and arguments.\n");
	}

	free_list(&list);
	fclose(file);

	return 0;
}

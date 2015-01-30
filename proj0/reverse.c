#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "B.h"

int main(int argc, const char *argv[])
{
	if(argc != 3){
		printf("reverse only takes 2 arguments, you passed %d.\n", (argc-1));
		exit(0);}

	FILE *file;
	if((file = fopen(argv[1], "r")) == NULL){
		perror("FOPEN");
		//exit(0);
	}

	switch(*argv[2]){
	//	case 'A': A(); break;
		case 'B': B(file); break;
		default: printf("default");
	}

	fclose(file);
}

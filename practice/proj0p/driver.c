#include <stdio.h>

int main(int argc, const char *argv[])
{
	
	if(argc != 3)
		printf("%c only takes 2 arguments: %c <text> <option>", *argv[0], *argv[0]);
	if(argv[1] == NULL || argv[2] == NULL)
		printf("Please ensure your arguments are correct.");
	return 0;
}

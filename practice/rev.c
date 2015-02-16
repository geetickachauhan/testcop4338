#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	int i;
	for(i = 0; i < argc; i++) {
		printf("Argument %d is %s", (1+i), argv[i]);
		printf("\n");
	}
}



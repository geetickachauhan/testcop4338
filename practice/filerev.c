#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	FILE *f = fopen(argv[1], "r");
	char input[81];
	char* last;

	while (fgets(input, 81, f)) {
	      printf("%zu", strlen(input));
              last = (input + (strlen(input)-1));
	     while(last >= input)
	     { 
		putchar( *last);
		last--;	      
	      }
	     // printf("%c", *last);
	     // putchar(*last);

	      //printf("addr of last: %p", last);
	      //printf("addr of input: %p", input);
	      if (last > input) {
	      	printf("true.");
	      }
	    }
	return 0;
}

#include <stdio.h>
#include <string.h>

void B(File *f){
	char input[81];
	char* last;
	while(fgets(input, 81, f)){
		last = (input + (strlen(input)-1));
		while(last >= input){
			putchar( *last);
			last--;
		}
	}
}

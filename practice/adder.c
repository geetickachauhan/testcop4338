#include <stdio.h>

int main(void)
{
	int numbers[10];
	numbers[0] = 10;
	numbers[1] = 20;
	numbers[2] = 30;

	printf("The 3rd number is %d", numbers[2]);
	for(int i = 0; i < 3; i++)
	{
		printf("%d", numbers[i]);}
	return 0;
}

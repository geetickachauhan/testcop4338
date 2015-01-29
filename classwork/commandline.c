#include <stdio.h>

int main(int argc, char *argv []) {
  printf("Number of cmd-lineargs = %d\n", argc);

int i;

for(i = 0; i < argc; i++) {

  printf("Arg %d - %s\n", argc, argv[i]);
}

return 0;

}

#include <stdio.h>
#include <assert.h>

#define MASK 0x80

#define MASK2 0x1

#include "bits.h"

int getset_freeBit(char *c) {
  
  //accepts a character array which basically contains 8 characters to store 
  //the different bits
  int bi;

  // bit index actually returns the index within the character array 
  for(bi=0; bi<sizeof(char)*8; bi++) {
    
    if(getbit(*c,bi)==0) {
      setbit(c,bi); // set bit to 1
      return bi;
    }
    
  }

  // default return value if no zero bit is found
  return -1;

}

void printbitsJean(char c) {

  int i;
  char c2 = (char)1;

  for (i=8*sizeof(c)-1; i>=0; i--) {

    if((c & (c2<<i)) != 0) printf("1");
    else printf("0");

  }
  
}

void printbits(char c) {

  int i;

  for (i=0; i<8*sizeof(c); i++) {

    if(((c<<i) & MASK) != 0) printf("1");
    else printf("0");

  }

}


// Prints the bits in reverse currently
// Homework: fix this 

void printbitsNathan(char c) {

  int i;

  for (i=0; i<8*sizeof(c); i++) {

    printf("%d", (c>>i) & MASK2);

  }

}


/* 
 * 	- get/set/reset bits
 *         - toggle a bit
 */


void setbit(char *c, int pos) {

  assert(pos<8);

  (*c) |= (MASK2<<pos);

  return;

}


void resetbit(char *c, int pos) {

  assert(pos<8);

  (*c) &= ~(MASK2<<pos);

  return;

}

int getbit(char c, int pos) {

  assert(pos<8);

  // this works too 
  // but too complicated
  // return ((MASK2<<pos)&c==0) ? 0:1 ;

  // alternate: more elegant
  return (c>>pos)&MASK2;

}

void togglebit(char *c, int pos) {

  assert(pos<8 && pos>=0);

  // bitwise method using exor
  *c = (*c) ^ (1<<pos) ;

  // alternate method with
  // code reuse
  // if(getbit(c,pos)==0) 
  //   setbit(c,pos);
  // else resetbit(c,pos);

}

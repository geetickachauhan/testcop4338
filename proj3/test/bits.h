#ifndef BITS_H
#define BITS_H

#include <stdio.h>
#include <assert.h>

#define MASK 0x80

#define MASK2 0x1

void printbits(char c);

void setbit(char *c, int pos) ;

void resetbit(char *c, int pos) ;

int getbit(char c, int pos) ;

void togglebit(char *c, int pos) ;


int getset_freeBit(char *c) ;

#endif // BITS_H

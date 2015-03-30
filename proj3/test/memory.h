#ifndef MEMORY_H
#define MEMORY_H


// Caches manage 16, 32, 64, 128, 256, 512, 1024 granularity allocations 

#define PAGE_SIZE 4096
#define SLAB_SIZE sizeof(Slab)
 
#define MIN_SLOT_SIZE 16
#define NUM_CACHES 7


typedef struct __Slab {

  char * bitmap;
  void * addr; // beginning of the slots
  int used; 
  struct __Slab * next;

} Slab;


typedef struct __Cache {

  int slot_size; // size of a single slot
  int max_slots; // maximum number of available slots, occupied or not per slab
  int bm_size;
  Slab * S;

} Cache;


typedef struct __Region {

  void * addr;
  int size; // user-visible bytes allocated
  struct __Region * next;

} Region;


typedef struct {

  Region * R;
  Cache C[NUM_CACHES];

} Memory;

#endif // MEMORY_H

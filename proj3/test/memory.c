#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>


#include "bits.h"
#include "memory.h"

void __attribute__ ((constructor)) init_mallocator(void);
void __attribute__ ((destructor)) finalize_mallocator(void);

Memory M;
int fd;

// allocate for sizes > 1024
void * allocate_region(unsigned int size) {
  
  void *mapped_addr = mmap(NULL, size + sizeof(Region), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  
  if(mapped_addr==MAP_FAILED) {
    perror("Mapping failed during allocate_region");
    exit(0);
  }

  Region * tmp = M.R; // end of the region pointer

  M.R = (Region *)mapped_addr; // make the memory's region pointer point to the new end
  M.R->addr = mapped_addr + sizeof(Region); // the addr points to the actual chunk of memory because region struct was stored in the beginning in the data
  M.R->size = size; // size of the chunk of memory as stored in region pointer is the same as size of chunk of memory 
  M.R->next = tmp; // make the next of new region point to old one
  
  return M.R->addr; // return allocated address

}


  // do this next time; get a free slot within a slab (each element in cache array contains a pointer to a slab
int getset_freeSlot(Slab *S, int max_slots) {

  // compute a conservative bm_size
  int bm_size = max_slots/8 + 1; // size of bitmap in bytes

  int i;
  int bi, si = -1; // bit index and slot index

  // bitmap is defined by the size in bytes (because it is basically 
  // divided as a series of 8 character arrays)
  // getsetfreeBit accepts a character array containing 8 characters
  for(i=0; i< bm_size; i++) 
  {
    if((bi=getset_freeBit(S->bitmap+i))!=-1) 
    {
      // make sure that value returned
      // is smaller than max_slots
      si = i*8+bi; // slot index is bit map size (set of char arrays of size 8) times 8 plus the actual bid index within each array
      if(si>=max_slots) si = -1; // but if slot index exceeds max slots its a problem
      break;
    }
  }

  // no free slot
  return si;
}


//head points to oldest allocation and last element is the newest allocation
// in case a free slot could not be found
// allocate for sizes <= 1024
void * allocate_cache(unsigned int size) {

  // The algorithm

  // 1. Find the cache index to allocate from

  int ci = 0;

  while(size > M.C[ci].slot_size) ci++;
  // as soon as you find a cache array that is just greater than the memory 
  
  int slot_size = M.C[ci].slot_size;

  // 2. Find or create a slab with an empty slot 
  // from that cache

  // iterate through the slabs finding one with an 
  // empty slot
  // getting to a specific cache element which contains pointers to slabs
  Slab *head = M.C[ci].S; // current slab head
  Slab *iterator = head; 
  Slab *prev = head;
  Slab *slab;

  while(iterator != NULL) {
    if(iterator->used!=M.C[ci].max_slots) break;
    // if the number of used slots is not equal to max slots then there 
    // must be a free slot in that particular slab
    prev = iterator;
    iterator = iterator->next;
  } 
  
  // no free slot slab found; so create a new
  if(iterator==NULL) {

    printf("Could not find a slab with a free slot ... Creating a new one!\n");

    void *mapped_addr;

    // No slab with free slot 
    // Need to create a slab
    mapped_addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  
    if(mapped_addr==MAP_FAILED) {
      errno = ENOMEM;
      perror("Mapping failed during allocate_region");
      exit(0);
    }

    // initialize mapped page (including bitmap) to zero
    bzero(mapped_addr, PAGE_SIZE); 

    if(head == NULL) {
      M.C[ci].S = (Slab *)mapped_addr;
      slab = M.C[ci].S;
    } else { 
      prev->next = (Slab *)mapped_addr;
      slab = prev->next;
    }

    slab->next = NULL;
    slab->bitmap = (char *) (mapped_addr + sizeof(Slab)); // cause after the slab stored struct stored in the slab memory, there is bitmap address 
    slab->addr = (void *) (slab->bitmap + M.C[ci].bm_size); // this is after the bitmap address 
       
  } else {
    slab = iterator;
  }
  //slab is basically pointer to the slab where we're going to store data 
    
  // 3. Find a free slot
  // create a placeholder for the slot index within the 
  // slab that has an empty slot
  int si;

  // I have a slab and a free slot in it

  // 4. Update the bitmap for the specific slot

  si = getset_freeSlot(slab, M.C[ci].max_slots); // find a free slot using bitmap and set it to 1 in bitmap
  
  // update number of used slots
  slab->used++;
  
  // 5. Compute the memory address of the slot

  void *retaddr = slab->addr + si*slot_size;

  // 6. return this memory address
  return retaddr;

}



// Allocates memory of size bytes and returns a pointer to it. Other details are set up so that it functions similar to malloc (see the man page).

void *allocate(unsigned int size) {

  if(size>1024) 
    return allocate_region(size);
  else
    return allocate_cache(size);

}

int deallocate_region(void *addr) {

  Region *iterator = M.R; // start from latest memory allocation
  Region *prev = M.R; // the one before latest 

  while(iterator!=NULL) {

    if(addr == iterator->addr) {  
    // region is found!    
    // remove region from the list
    // unmap region 
    
      printf("Found region allocation of size = %d\n", iterator->size);

      if(iterator==M.R) 
      {      
	// head of the region list matched; special case; remove head
	M.R = M.R->next;
      }
      else 
      {
	prev->next = iterator->next;	
      }
 
      munmap(iterator, iterator->size + sizeof(Region)); // unmap whatever is pointed to by iterator
      return 0; // deallocation was possible
    }

    prev = iterator; 
    iterator = iterator->next;    
  }

  printf("Unable to Find region allocation at addr = %p\n", addr);

  return -1;

}


//Geeticka
int deallocate_cache(void *addr) {

  // Homework!
  
  // Steps:

  int ci = 0;

  //while(size > M.C[ci].slot_size) ci++;
  // 1. Find the cache
  // How?
  // Iterate through each cache
  //    Iterate through each slab
  //       check if addr falls within the allocated range
  // if so, you have found the cache
  // if not,
  //goto OUT;
  
  Slab * prevSlab;
  Slab * iteratorSlab;
  int found = 0;
  for(ci = 0; ci< NUM_CACHES; ci++)
  {
    prevSlab = M.C[ci].S;
    iteratorSlab = M.C[ci].S; // remember within each slab is the bitmap and slab struct
    while(iteratorSlab != NULL)
    {
        void* start_addr = iteratorSlab->addr;
        void* end_addr = iteratorSlab->addr + M.C[ci].max_slots * M.C[ci].slot_size; // basically the start slot address to the total slots times the size of each slot
        if(addr >= start_addr && addr <= end_addr)
			found = 1;	
            break; // found the cache and the slab as well
        prevSlab = iteratorSlab;
        iteratorSlab = iteratorSlab->next;
    }
    if(found == 1)
	    break;
  }
  
  if(found==0) // the cache went all the way without finding correct slab or cache
  {
      return -1; // no cache found to deallocate
  }
  
  // 2. Find the slot
  // How?
  // Check Is it a valid slot addr?
  // If not, goto OUT
  // If yes, go to next step

    //iteratorSlab is the slab where the addresses can lie

  int slotIndex = 0;
  void * addrIterator = iteratorSlab->addr; // address where the slots begin
  while(addrIterator <= iteratorSlab->addr + M.C[ci].slot_size * (M.C[ci].max_slots -1)) // while loop should only go up to 1 less max slot because the address can not be valid if it reaches all the way at the end of the slab
  {
      if(addrIterator == addr)
        break;
      slotIndex++;
      addrIterator += M.C[ci].slot_size;
  }
  
  if(addrIterator >= iteratorSlab->addr + M.C[ci].slot_size * M.C[ci].max_slots)
  {
      return -1; // in this case it was not a valid address 
  }

  /*  
  void * addrIterator = iteratorSlab->addr; // address where the slots begin
  while(addrIterator <= iteratorSlab->addr + M.C[ci].slot_size * (M.C[ci].max_slots -1)) // while loop should only go up to 1 less max slot because the address can not be valid if it reaches all the way at the end of the slab
  {
      if(addrIterator == addr)
        break;
      addrIterator += M.C[ci].slot_size;
  }
  
  if(addrIterator >= iteratorSlab->addr + M.C[ci].slot_size * M.C[ci].max_slots)
  {
      return -1; // in this case it was not a valid address 
  }
  */
  
  //iteratorSlab is the correct slab 
  
  
  // fix step 2 and 3 where you just find the slot in step 2 and then work with step 3
  
  // 3. Check bit corresponding to
  // above slot in bitmap
  // IF bit is zero, then goto OUT
  
  
  int bitIndex = slotIndex/8; 
  // the specific bit position is determined by slotIndex%8 
  int pos = slotIndex%8;
  if(getbit(*(iteratorSlab->bitmap+bitIndex), pos) == 0)
    return -1;
  
  /*
  int bm_size = max_slots/8 + 1; // size of bitmap in bytes

  int i;
  int j; // index for each slot within the bitmap
  int bi, si = -1; // bit index and slot index
  addrIterator = iteratorSlab->addr;
  int bitIndex; // index of the bit within each character array in the bitmap
  char *c; // pointer to the bitmap index character array and a position

  // bitmap is defined by the size in bytes (because it is basically 
  // divided as a series of 8 character arrays)
  // getsetfreeBit accepts a character array containing 8 characters
  for(i=0; i< bm_size; i++) 
  {
      bi=S->bitmap+i; // bit index, go through the bitmap
      // each bitmap index is a pointer to a character array of size 8
      for(j = 0; j< sizeof(char)*8; j++)
      {
            if(addrIterator == addr)
            {
               if(getbit(S->bitmap+i,j)== 0)
                    return -1;
               else if(getbit(S->bitmap+i, j)==1)
                    break;  // get out of the looop as soon as you've found your slot
            }
            addrIterator += M.C[ci].slot_size;
      }
      si = i*8+bi; // slot index is bit map size (set of char arrays of size 8) times 8 plus the actual bid index within each array
    
      if(si>=max_slots) si = -1; // but if slot index exceeds max slots its a problem; this problem should not arise here
    }
  }
  */

  // 4. We have found a valid bit
  // Reset/clear the bit
  resetbit(iteratorSlab->bitmap+bitIndex, pos);
  //resetbit(S->bitmap+i, j);
  

  // 5. Decrease slots used
  (iteratorSlab->used)--;

  // 6. If (slots_used == 0)
  // Remove slab from list of slabs
  // And unmap slab using slab starting address
  if(iteratorSlab->used == 0)
  {
      if(iteratorSlab == M.C[ci].S)
      {
          M.C[ci].S = M.C[ci].S->next;
      }
      else
      {
          prevSlab->next = iteratorSlab->next; // include special case where you remove the head
      }
	munmap(iteratorSlab, PAGE_SIZE);
   }
   
   
  // 7. return 0
  return 0;

}


// Frees the allocated memory, checking for appropriate error conditions. Other details are set up so that it functions similarly to free (see the man page)

void deallocate(void * addr) {

  if(deallocate_region(addr)==-1) {
    if(deallocate_cache(addr)==-1) {
      printf("Deallocation failed: %p\n", addr);
    }
  }

  return;

}




void init_mallocator() {

  fd = open("../ZEROES", O_RDWR);

  if(fd<0) {
    perror("opening the ZEROES file failed!");
    exit(0);
  }

  // initialize the region list
  M.R = NULL;

  // initilizalize the caches
  int i;
  for(i=0; i<NUM_CACHES; i++) {
    M.C[i].slot_size = MIN_SLOT_SIZE << i;
    M.C[i].max_slots = 8*(PAGE_SIZE - SLAB_SIZE - 1) / (M.C[i].slot_size*8 + 1);
    M.C[i].bm_size = M.C[i].max_slots/8 + 1; // a conservative bm_size
    M.C[i].S = NULL;
  }

  return;

}

void finalize_mallocator() {

  // Homework!
  Region *iteratorRegion = M.R;
  int i; // to iterate through cache
  Slab *s; // to iterate through slab

  // Steps:

  // 1. Iterate through region list 
  //    unmap each region
  while(iteratorRegion != NULL)
  {
      M.R = M.R->next;
      munmap(iteratorRegion, iteratorRegion->size + sizeof(Region));
      iteratorRegion = iteratorRegion->next;
  }

  // 2. Iterate through each cache
  //      Iterate through each slab
  //         Unmap each slab
  for(i = 0; i<NUM_CACHES; i++)
  {
      s = M.C[i].S;
      while(s != NULL)
      {
          M.C[i].S = M.C[i].S->next;
          munmap(s, PAGE_SIZE);
          s = s->next;
      }
  }
 
}

void test_region_allocator() {


  void *p;
  
  p = allocate(2000);

  printf("Allocated 2000 bytes at %p\n",p);

  strcpy((char *)(p+1900), "hello, world!");
  
  printf("@ (p+1900): %s\n", (char *)(p+1900));

  // Test deallocate
  deallocate(p);

  deallocate(p);

  // Cannot do this since p just got deallocated
  // printf("@ (p+1900): %s\n", (char *)(p+1900));

  p = allocate(1500);

  printf("Allocated 1500 bytes at %p\n",p);

  // this doesn't work
  // strcpy((char *)(p+10000), "hello, world!");
  
  strcpy((char *)(p+1400), "hello, world!");
  
  printf("@ (p+1400): %s\n", (char *)(p+1400));

  // Homework: check if you can write to p+3500

  return;
}



void test_slab_allocator() {

  void *p1;
  int i;

  p1 = allocate(19);


  printf("Allocated 19 bytes at %p\n",p1);

  for(i =0; i<1000; i++) {

    p1 = allocate(23);
    printf("Allocated 23 bytes at %p\n",p1);

  }

  for(i =0; i<50; i++) {

    p1 = allocate(231);
    printf("Allocated 231 bytes at %p\n",p1);

  }

  for(i =0; i<10; i++) {

    p1 = allocate(1024);
    printf("Allocated 1024 bytes at %p\n",p1);

  }

  return;

}

/*
int main (int argc, char *argv []) {

  //init_mallocator();

  // test_region_allocator();

  test_slab_allocator();

  //finalize_mallocator();

  return 0;
  
}
*/


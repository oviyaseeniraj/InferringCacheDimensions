/*
Oviya Seeniraj
Aneesh Garg
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/6/24, 11:59 pm

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 4194304 bytes (4 MB)
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4096 bytes (4 KB)
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4096 bytes (4 KB)
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  int cache_size = 0;
  int prev_cache = block_size;
  flush_cache();

  access_cache(0);
  while (access_cache(0))
  {
    cache_size = block_size;
    while (cache_size <= prev_cache)
    {
      cache_size += block_size;
      if (!access_cache(cache_size))
      {
        return prev_cache;
      }
    }
    prev_cache += block_size;
  }
  return prev_cache;

  /*flush_cache();
  int cache_size = 0;
  int z = cache_size;
  int x = 1;
  while(1) {
	  for(int k = z; k < cache_size + block_size; k += block_size) {
		 access_cache(k);
	  } 
	  for(int c = 0; c < cache_size + block_size; c+= block_size) {
		if(!access_cache(c)) {
		  	x = 0;
		  	break;
		}
	  }
		if(!x)
			break;
		z = cache_size;
	  i *= 2;
	  if(i == 0)
		  i+=cache_size;
  }
  return cache_size;*/
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /*int assoc = 0;
  flush_cache();

  int numBlocks = size/get_block_size();

  access_cache(0);
  while (access_cache(0))
  {
    for (int i = 0; i <= assoc; i++)
    {
        access_cache(i * size);
    }
    assoc++;
    //flush_cache();
  }
  return assoc;*/

  int set_size = 0;
  int set_check = 1;
  int assoc = 0;
  flush_cache();

  access_cache(0);
  while (access_cache(0)) {
    set_size = size;
    assoc = 0;
    while (set_size <= set_check) {
      set_size += size;
      assoc++;
      access_cache(set_size);
    }
    set_check += size;
  }
  return assoc;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  int addr = 0;
  access_cache(addr);
  while (access_cache(addr)) {
    addr = addr + 4;
  }
  return addr;
}

int main(void) {
  int size; // CAPACITY C
  int assoc; // N AKA NUMBER OF BLOCKS PER SET
  int block_size; // BLOCK SIZE B
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(64,16);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}

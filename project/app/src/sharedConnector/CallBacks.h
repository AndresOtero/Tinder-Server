#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SendStruct {
  const char *memory;
  size_t size;
};
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct MemoryStruct *pooh = (struct MemoryStruct *)userp;
 
  if(size*nmemb < 1)
    return 0;
 
  if(pooh->size) {
    *(char *)ptr = pooh->memory[0]; /* copy one single byte */ 
    pooh->memory++;                 /* advance pointer */ 
    pooh->size--;                /* less data left */ 
    return 1;                        /* we return 1 byte at a time! */ 
  }
 
  return 0;                          /* no more data left to deliver */ 
}
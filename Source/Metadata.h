#ifndef HEAPDATA_H
#define HEAPDATA_H



#define NULL 0
#define null 0
#define VOID 0

#include <stdint.h>
#include <stdbool.h>



struct heap_chunck_t{
  unsigned int size;
  bool is_being_used;

  struct heap_chunck_t *next;
  struct heap_chunck_t *prev;

};

struct heap_info_t {
  struct heap_chunck_t *chunk;
};

extern struct heap_info_t global;


typedef struct heap_chunck_t chunk_t;
typedef struct heap_info_t info_t;





void add(chunk_t *ptr);



#endif

#ifndef _CIRBUFF_H_
#define _CIRBUFF_H_


#include <stddef.h>
#include <stdbool.h>
#include <alloc/alloc.h>


typedef struct cirbuff cirbuff;


cirbuff * cirbuff_new(Alloc * alloc, size_t dtype, size_t size);

cirbuff * cirbuff_from_array(Alloc * alloc, size_t dtype, size_t size, void * array);


size_t cirbuff_alloc_size(cirbuff * self);


size_t cirbuff_size(cirbuff * self);


bool cirbuff_empty(cirbuff * self);


bool cirbuff_full(cirbuff * self);


size_t cirbuff_allocated_size(cirbuff * self);



#endif

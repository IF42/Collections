#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>
#include <alloc/alloc.h>

typedef struct vector vector;


vector * vector_default_new(Alloc * alloc, size_t dtype, size_t capacity);


vector * vector_new(Alloc * alloc, size_t dtype);


void vector_push_back(vector * self, void * value);


void vector_push_front(vector * self, void * value);


void * vector_begin(vector * self);


void * vector_end(vector * self);


void vector_finalize(vector * self);


#endif




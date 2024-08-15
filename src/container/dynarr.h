/** 
 * @file dynarr.h
 * @brief
 */

#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <vector/vector.h>
#include <stdbool.h>

typedef struct dynarr dynarr;


dynarr * dynarr_default_new(Alloc * alloc, size_t dtype, size_t capacity);


#define dynarr_new(alloc, dtype) \
    dynarr_default_new((alloc), (dtype), 0)


#define dynarr_to_vector(T) ((const vector *) (T))


bool dynarr_push_back(dynarr * self, void * value);


bool dynarr_push_front(dynarr * self, void * value);


void * dynarr_begin(dynarr * self);


void * dynarr_end(dynarr * self);


void dynarr_finalize(dynarr * self);


#endif




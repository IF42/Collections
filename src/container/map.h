/**
 * @file map.h
 * @brief
 */
#ifndef _MAP_H_
#define _MAP_H_

#include <stddef.h>
#include <stdbool.h>
#include <alloc/alloc.h>
#include <vector/vector.h>


typedef struct map map;


#define map_to_vector(T) _Generic((T), map*: ((const vector*)(T)))


map * map_new(Alloc * alloc, size_t memsize);


size_t map_size(map * self);


bool map_empty(map * self);


void map_finalize(map * self);


#endif




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


typedef struct {
    vector vector;
    Alloc * alloc;

    size_t dtype;
    size_t size;
} Map;


#define map_to_vector(T) _Generic((T), map*: ((const vector*)(T)))


Map map(Alloc * alloc, size_t dtype);


size_t map_size(Map * self);


bool map_empty(Map * self);


void map_finalize(Map * self);


#endif




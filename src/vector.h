/** 
 * @file vector.h
 *
 */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdbool.h>
#include <stddef.h>


typedef struct vector vector;


/**
 * @brief
 */
vector * vector_new(size_t dtype);


/*
 * @brief
 */
vector * vector_new_from_array(size_t dtype, size_t size, void * array);


/**
 * @brief
 */
void * vector_at(vector * self, size_t index);


/**
 * @brief
 */
bool vector_set(vector * self, size_t index, void * value);


/**
 * @brief
 */
void vector_append(vector * self, void * value);


/*
 * @brief
 */
size_t vector_size(vector * self);


/*
 *
 */
size_t vector_dtype(vector * self);


/**
 * @brief
 */
void vector_delete(vector * self);


#endif

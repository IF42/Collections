/** 
 * @file dynarr.h
 * @brief
 */

#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <vector/vector.h>
#include <stdbool.h>
#include <alloc/alloc.h>

/**
 * @brief
 */
typedef struct dynarr dynarr;


/**
 * @brief
 */
dynarr * dynarr_default_new(Alloc * alloc, size_t dtype, size_t capacity);


/**
 * @brief
 */
#define dynarr_new(alloc, dtype) \
    dynarr_default_new((alloc), (dtype), 0)


/**
 * @brief
 */
#define dynarr_to_vector(T) _Generic((T), dynarr*: ((const vector *) (T)))


/**
 * @brief
 */
bool dynarr_push_back(dynarr * self, void * value);


/**
 * @brief
 */
bool dynarr_push_front(dynarr * self, void * value);


/**
 * @brief
 */
void * dynarr_begin(dynarr * self);


/**
 * @brief
 */
void * dynarr_back(dynarr * self);


/**
 * @brief
 */
void dynarr_remove(dynarr * self, size_t index);


/**
 * @brief
 */
void dynarr_remove_front(dynarr * self);


/**
 * @brief
 */
void dynarr_remove_back(dynarr * self);


/**
 * @brief
 */
size_t dynarr_size(dynarr * self);


/**
 * @brief
 */
bool dynarr_empty(dynarr * self);


/**
 * @brief
 */
void dynarr_finalize(dynarr * self);


#endif




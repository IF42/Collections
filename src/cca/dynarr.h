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

typedef struct {
    vector vector;

    Alloc * alloc;
    size_t dtype;
    size_t capacity;
    size_t size;
    char * front;

    size_t iter;
}DynArr;



/**
 * @brief
 */
DynArr dynarr_default(Alloc * alloc, size_t dtype, size_t capacity);


/**
 * @brief
 */
#define dynarr(alloc, dtype) \
    dynarr_default_new((alloc), (dtype), 0)


/**
 * @brief
 */
#define dynarr_to_vector(T) _Generic((T), DynArr*: ((const vector *) (T)))


/**
 * @brief
 */
bool dynarr_push_back(DynArr * self, void * value);


/**
 * @brief
 */
bool dynarr_push_front(DynArr * self, void * value);


/**
 * @brief
 */
void * dynarr_begin(DynArr * self);


/**
 * @brief
 */
void * dynarr_back(DynArr * self);


/**
 * @brief
 */
void dynarr_remove(DynArr * self, size_t index);


/**
 * @brief
 */
void dynarr_remove_front(DynArr * self);


/**
 * @brief
 */
void dynarr_remove_back(DynArr * self);


/**
 * @brief
 */
size_t dynarr_size(DynArr * self);


/**
 * @brief
 */
bool dynarr_empty(DynArr * self);


/**
 * @brief
 */
void dynarr_finalize(DynArr * self);


#endif




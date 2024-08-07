/** 
 * @file dynarr.h
 * @brief
 */

#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h>
#include <stddef.h>

#include "vector.h"


/**
 * @brief
 */
vector * dynarr_new(Alloc * alloc, size_t dtype);


/** 
 * @brief
 */
vector * dynarr_empty_new(Alloc * alloc, size_t dtype, size_t size);


/*
 * @brief
 */
vector * dynarr_from_array(Alloc * alloc, size_t dtype, size_t size, void * array);


/*
 * @brief
 */
typedef struct dynarr dynarr;


/*
 * @brief
 */
#define DYNARR(T) ((dynarr*) (T))


/**
 * @brief
 */
void * dynarr_at(dynarr * self, size_t index);


/**
 * @brief
 */
bool dynarr_set(dynarr * self, size_t index, void * value);


/**
 * @brief
 */
void dynarr_push_front(dynarr * self, void * value);


/**
 * @brief
 */
void dynarr_push_back(dynarr * self, void * value);


/**
 * @brief
 */
bool dynarr_insert(dynarr * self, size_t index, void * value);


/**
 * @brief
 */
void dynarr_delete(dynarr * self, size_t index);


/**
 * @brief
 */
size_t dynarr_size(dynarr * self);


/**
 * @brief
 */
bool dynarr_empty(dynarr * self);


/**
 *  @brief
 */
void dynarr_clear(dynarr * self);


#endif




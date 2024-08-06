/**
 * @file queue.h
 * @brief
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_


#include <stddef.h>
#include <stdbool.h>
#include <alloc/alloc.h>


/**
 * @brief
 */
typedef struct queue queue;


/**
 * @brief
 */
queue * queue_new(Alloc * alloc, size_t dtype);


/**
 * @brief
 */
void * queue_front(queue * self);


/**
 * @brief
 */
void * queue_back(queue * self);


/**
 * @brief
 */
void * queue_pop_front(queue * self);


/**
 * @brief
 */
void * queue_pop_back(queue * self);


/**
 * @brief
 */
bool queue_push_front(queue * self, void * data);


/**
 * @brief
 */
bool queue_push_back(queue * self, void * data);


/**
 * @brief
 */
bool queue_empty(queue * self);


/**
 * @brief
 */
size_t queue_size(queue * self);


/**
 * @brief
 */
size_t queue_dtype(queue * self);


/**
 * @brief
 */
void queue_finalize(queue * self);


#endif




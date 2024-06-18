#ifndef _LIST_H_
#define _LIST_H_ 

#include <stddef.h>
#include <alloc/alloc.h>


typedef struct list list;


/**
 * @brief
 */
list * list_new(Alloc * alloc, size_t dtype);


/**
 * @brief
 */
void list_push_front(list * self, void * value);


/**
 * @brief
 */
void list_push_back(list * self, void * value);


/**
 * @brief
 */
void * list_get(list * self, size_t index);


/**
 * @brief
 */
void list_remove(list * self, size_t index);


#include "iter.h"


/**
 * @brief
 */
typedef struct {
    iterator iter;
    void * head;
}list_iter;


/**
 * @brief
 */
list_iter list_iterator(list * self);


/**
 * @brief
 */
size_t list_size(list * self);


/**
 *@brief
 */
void list_finalize(list * self);


#endif



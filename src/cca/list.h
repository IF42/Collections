/**
 * @file list.h
 * @brief
 */

#ifndef _LIST_H_
#define _LIST_H_ 

#include <stddef.h>
#include <stdbool.h>
#include <alloc/alloc.h>
#include <vector/vector.h>


/**
 * @brief
 */
typedef struct Node {
    struct Node * next;
    struct Node * prev;
} Node;


typedef struct {
    vector vector;
    Alloc * alloc;

    size_t dtype;
    size_t size;
    Node * front;
    Node * back;
    Node * iter;
} List;


/**
 * @brief
 */
List list(Alloc * alloc, size_t dtype);


/**
 * @brief
 */
#define list_to_vector(T) _Generic((T), List*: ((const vector*)(T)))


/**
 * @brief
 */
bool list_push_front(List * self, void * value);


/**
 * @brief
 */
bool list_push_back(List * self, void * value);


/**
 * @brief
 */
void * list_front(List * self);


/**
 * @brief
 */
void * list_back(List * self);


/**
 * @brief
 */
void * list_get(List * self, size_t index);


/**
 * @brief
 */
void list_remove(List * self, size_t index);


/**
 * @brief
 */
void list_remove_front(List * self);


/**
 * @brief
 */
void list_remove_back(List * self);


/**
 * @brief
 */
size_t list_size(List * self);


/**
 * @brief
 */
size_t list_dtype(List * self);


/**
 * @brief
 */
bool list_empty(List * self);


/**
 *@brief
 */
void list_finalize(List * self);


#endif



#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>
#include <alloc/alloc.h>


typedef struct vector vector;


typedef struct {
    void * (*iter)(vector *);
    void * (*next)(vector*);
} vector_vtab;


struct vector {
    Alloc * alloc;
    size_t dtype;

    vector_vtab * vtab;
};


#define vector_next(T) (T)->vtab->next((T))


#define vector_iter(T) (T)->vtab->iter((T))


#define foreach(item, iter) \
    vector_iter(iter); \
    for(void * item = vector_next((iter)); item != NULL; item = vector_next((iter)))


void vector_finalize(vector * self);


#endif




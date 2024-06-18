#ifndef _ITER_H_
#define _ITER_H_

typedef struct iterator {
    void * (*next)(struct iterator*);
}iterator;


#define ITERATOR(T) ((iterator*) (T))


#define iterator_next(T) (T)->next((T))


#define foreach(item, iter) \
    for(void* item = iterator_next((iter)); item != NULL; item = iterator_next((iter)))


#endif



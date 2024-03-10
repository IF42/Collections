#ifndef _LIST_H_
#define _LIST_H_ 

#include <stddef.h>


typedef struct list list;


list * list_append(list * self, size_t dtype, void * value);


void * list_peek(list * self);


list * list_next(list * self);


size_t list_size(list * self);


void list_delete(list * self);


#endif

#include "list.h"

#include <string.h>
#include <stdlib.h>


struct list {
    void * value;
    list * next;  
};


list * list_append(list * self, size_t dtype, void * value) {
    list * node = malloc(sizeof(list));

    *node = (list) {
        .value =  memcpy(malloc(dtype), value, dtype)
        , .next = self
    };

    return node;    
}


void * list_peek(list * self) {
    return self->value;
}


list * list_next(list * self) {
    return self->next;
}


size_t list_size(list * self) {
    size_t size = 0; 

    while(self != NULL) {
        size++;
        self = self->next;
    }

    return size;
}


void list_delete(list * self) {
    while(self != NULL) {
        list * next = self->next;

        if(self->value != NULL)
            free(self->value);

        free(self);
        self = next;
    }    
}




#include "container/list.h"

#include <string.h>
#include <stdlib.h>


typedef struct node {
    struct node * tail;
}node;


struct list {
    Alloc * alloc;
    size_t dtype;

    size_t size;
    node * front;
    node * back;
};


list * list_new(Alloc * alloc, size_t dtype) {
    list * self = new(alloc, sizeof(list));

    *self = (list) {
        .alloc = alloc
        , .dtype = dtype
    };

    return self;
}


void list_push_front(list * self, void * value) {
    node * list_node = new(self->alloc, sizeof(node) + self->dtype);
    memcpy((list_node + 1), value, self->dtype);

    list_node->tail = self->front;
    self->front = list_node;

    self->size++;

    if(self->back == NULL) {
        self->back = list_node;
    } 
}


void list_push_back(list * self, void * value) {
    node * list_node = new(self->alloc, sizeof(node) + self->dtype);
    memcpy((list_node + 1), value, self->dtype);

    if(self->back != NULL) {
        self->back->tail = list_node;
    }

    self->back = list_node;

    self->size++;

    if(self->front == NULL) {
        self->front = list_node;
    }
}


void * list_get(list * self, size_t index) {
    if(index < self->size) {
        node * list_node = self->front;

        for(size_t i = 0; i < index; i++) {
            if(list_node != NULL) {
                list_node = list_node->tail;
            } else {
                break;
            }
        }

        return (list_node + 1);
    } else {
        return NULL;
    }
}


static void * list_iterator_next(list_iter * iterator) {
    if(iterator->head != NULL) {
        void * data = (void*) (((node*) iterator->head) + 1); 
        iterator->head = ((node*) iterator->head)->tail;
        return data;
    } else {
        return NULL;
    }
}


list_iter list_iterator(list * self) {
    return (list_iter) {
        .iter.next = (void*(*)(iterator *)) list_iterator_next 
        , .head = self->front
    };
}


size_t list_size(list * self) {
    return self->size;
}




void list_finalize(list * self) {
    if(self != NULL) {
        finalize(self->alloc);
    }
}


#include "container/queue.h"
#include "container/list.h"

#include <string.h>
#include <stdint.h>


struct queue {
    Alloc * alloc;
    list * container;
    void * pop_buffer;
};


queue * queue_new(Alloc * alloc, size_t dtype) {
    queue * self = new(alloc, sizeof(queue));

    *self = (queue) {
        .alloc = alloc
        , .container = list_new(alloc, dtype)
        , .pop_buffer = new(alloc, dtype)
    };

    return self;
}


void * queue_front(queue * self) {
    return list_front(self->container);
}


void * queue_back(queue * self) {
    return list_back(self->container);
}


void * queue_pop_front(queue * self) {
    size_t dtype = list_dtype(self->container);
    void * data = list_front(self->container);

    if(data != NULL) {
        switch(dtype) {
            case 1:
                *(uint8_t*)self->pop_buffer = *(uint8_t*) data;
                break;
            case 2:
                *(uint16_t*)self->pop_buffer = *(uint16_t*) data;
                break;
            case 4:
                *(uint32_t*)self->pop_buffer = *(uint32_t*) data;
                break;
            case 8:
                *(uint64_t*)self->pop_buffer = *(uint64_t*) data;
                break;
            default:
                memcpy(self->pop_buffer, data, dtype);
        }

        list_remove_front(self->container);

        return self->pop_buffer;
    } else {
        return NULL;
    }
}


void * queue_pop_back(queue * self) {
    size_t dtype = list_dtype(self->container);
    void * data = list_back(self->container);

    if(data != NULL) {
        switch(dtype) {
            case 1:
                *(uint8_t*)self->pop_buffer = *(uint8_t*) data;
                break;
            case 2:
                *(uint16_t*)self->pop_buffer = *(uint16_t*) data;
                break;
            case 4:
                *(uint32_t*)self->pop_buffer = *(uint32_t*) data;
                break;
            case 8:
                *(uint64_t*)self->pop_buffer = *(uint64_t*) data;
                break;
            default:
                memcpy(self->pop_buffer, data, dtype);
        }

        list_remove_back(self->container);

        return self->pop_buffer;
    } else {
        return NULL;
    }
}


bool queue_push_front(queue * self, void * data) {
    return list_push_front(self->container, data);
}


bool queue_push_back(queue * self, void * data) {
    return list_push_back(self->container, data);
}


bool queue_empty(queue * self) {
    return list_empty(self->container);
}


size_t queue_size(queue * self) {
    return list_size(self->container);
}


size_t queue_dtype(queue * self) {
    return list_dtype(self->container);
}


void queue_finalize(queue * self) {
    if(self != NULL) {
        finalize(self->alloc);
    }
}




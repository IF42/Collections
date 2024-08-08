#include "container/vector.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>


struct vector {
    Alloc * alloc;
    size_t dtype;
    size_t size;
    size_t capacity;
    char * array;
};


vector * vector_new(Alloc * alloc, size_t dtype) {
    vector * self = new(alloc, sizeof(vector));
    *self = (vector) {
        .alloc = alloc
        , .dtype = dtype
    };

    return self;
}


vector * vector_default_new(Alloc * alloc, size_t dtype, size_t capacity) {
    vector * self = new(alloc, sizeof(vector));
    char * array = new(alloc, dtype * capacity);

    *self = (vector) {
        .alloc = alloc
        , .dtype = dtype
        , .capacity = capacity
        , .array = array
    };

    return self;
}


static void vector_realloc(vector * self) {
    if(self->capacity == 0) {
        self->capacity = 2;
        self->array = new(self->alloc, self->dtype * self->capacity);
    } else {
        self->capacity *= self->capacity * 2;

        void * array = new(self->alloc, self->dtype * self->capacity);

        memcpy(array, self->array, self->size * self->dtype);
        delete(self->alloc, self->array);

        self->array = array;
    }
}


void vector_push_back(vector * self, void * value) {
    if(self->size >= self->capacity) {
        vector_realloc(self);
    } 

    switch(self->dtype) {
        case 1:
            ((uint8_t*) self->array)[self->size] = *(uint8_t*) value;
            break;
        case 2:
            ((uint16_t*) self->array)[self->size] = *(uint16_t*) value;
            break;
        case 4:
            ((uint32_t*) self->array)[self->size] = *(uint32_t*) value;
            break;
        case 8:
            ((uint64_t*) self->array)[self->size] = *(uint64_t*) value;
            break;
        default:
            memcpy(self->array + (self->size * self->dtype), value, self->dtype);
    }

    self->size ++;
}


void vector_push_front(vector * self, void * value) {
    if(self->size >= self->capacity) {
        vector_realloc(self);
    }

    memcpy(self->array + self->dtype, self->array, self->size * self->dtype);
    memcpy(self->array, value, self->dtype);
    self->size++;
}


void * vector_begin(vector * self) {
    return self->array;
}


void * vector_end(vector * self) {
    return self->array + (self->size * self->dtype);
}


void vector_finalize(vector * self) {
    if(self->alloc != NULL) {
        finalize(self->alloc);
    }
}





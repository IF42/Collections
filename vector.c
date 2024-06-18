#include "vector.h"

#include <stdlib.h>
#include <string.h>


struct vector {
    size_t dtype;
    size_t size;
    size_t capacity;
    void * array;
};


#define DEFAULT_SIZE 10


vector * vector_new(size_t dtype) {
    vector * self = malloc(sizeof(vector));

    *self = (vector) {
        .dtype = dtype
        , .size = 0
        , .capacity = DEFAULT_SIZE
        , .array = malloc(dtype * DEFAULT_SIZE)
    };

    return self;
}


vector * vector_new_from_array(size_t dtype, size_t size, void * array) {
    vector * self = malloc(sizeof(vector));

    *self = (vector) {
        .dtype = dtype
        , .size = size
        , .capacity = size
        , .array = memcpy(malloc(size * dtype), array, size * dtype)
    };

    return self;
}


void * vector_at(vector * self, size_t index) {
    if(index < self->size)
        return (char*) self->array + (index*self->dtype);

    return NULL;
}


bool vector_set(vector * self, size_t index, void * value) {
    if(index < self->size) {
        memcpy((char*) self->array + (index*self->dtype), value, self->dtype);
        return true;
    }

    return false;
}


void vector_append(vector * self, void * value) {
    if(self->size >= self->capacity) {
        self->array     = realloc(self->array, self->capacity * self->dtype * 2);
        self->capacity *= 2;
    }

    memcpy((char*) self->array + (self->size * self->dtype), value, self->dtype);
    self->size++;
}


size_t vector_size(vector * self) {
    return self->size;
}


size_t vector_dtype(vector * self) {
    return self->dtype;
}


void vector_delete(vector * self) {
    if(self != NULL) {
        if(self->array != NULL)
            free(self->array);

        free(self);
    }
}




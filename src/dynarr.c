#include "container/dynarr.h"

#include <string.h>


struct dynarr {
    Alloc * alloc;
    size_t dtype;
    size_t size;
    size_t capacity;
    void * array;
};


#define DEFAULT_SIZE 10


dynarr * dynarr_new(Alloc * alloc, size_t dtype) {
    dynarr * self = new(alloc, sizeof(dynarr));

    *self = (dynarr) {
        .dtype = dtype
        , .size = 0
        , .capacity = DEFAULT_SIZE
        , .array = new(alloc, dtype * DEFAULT_SIZE)
    };

    return self;
}


dynarr * dynarr_new_empty(Alloc * alloc, size_t dtype, size_t size) {
    dynarr * self = new(alloc, sizeof(dynarr));

    *self = (dynarr) {
        .alloc = alloc
        , .dtype = dtype
        , .size = size
        , .capacity = size
        , .array = new(alloc, size * dtype)
    };

    return self;
}


dynarr * dynarr_new_from_array(Alloc * alloc, size_t dtype, size_t size, void * array) {
    dynarr * self = dynarr_new_empty(alloc, dtype, size);
    memcpy(self->array, array, size * dtype);
    return self;
}


static void * dynarr_next(dynarr_iter * iter) {
    if(iter->index < iter->size) {
        void * memptr = iter->head;
        iter->head = ((char*)iter->head) + iter->dtype;
        iter->index ++;
        return memptr;
    } else {
        return NULL;
    }
}


dynarr_iter dynarr_iterator(dynarr * self) {
    return (dynarr_iter) {
        .iter.next = (void*(*)(iterator*)) dynarr_next
        , .dtype = self->dtype
        , .size = self->size
        , .index = 0
        , .head = self->array
    };
}


void * dynarr_at(dynarr * self, size_t index) {
    if(index < self->size) {
        return (char*) self->array + (index*self->dtype);
    } else {
        return NULL;
    }
}


bool dynarr_set(dynarr * self, size_t index, void * value) {
    if(index < self->size) {
        memcpy((char*) self->array + (index*self->dtype), value, self->dtype);
        return true;
    } else {
        return false;
    }
}


static void dynarr_realloc(dynarr * self, size_t capacity) {
    void * array = new(self->alloc, self->dtype); 
    memcpy(array, self->array, self->dtype * sizeof(self->size));
    delete(self->alloc, self->array);

    self->array = array;
    self->capacity = capacity;
}


void dynarr_push(dynarr * self, void * value) {
    if(self->size >= self->capacity) {
        dynarr_realloc(self, self->capacity * 2);
    }

    memcpy((char*) self->array + (self->size * self->dtype), value, self->dtype);
    self->size++;
}


bool dynarr_insert(dynarr * self, size_t index, void * value) {
    if(index < self->size) {
        if(self->size >= self->capacity) {
            dynarr_realloc(self, self->capacity * 2);
        }

        char * mem_ptr = ((char*)self->array) + (self->dtype * (index + 1));

        memcpy(mem_ptr, mem_ptr + (self->dtype * index), self->dtype * (self->size - index));
        memcpy(mem_ptr, value, self->dtype);

        return true;
    } else {
        return false;
    }
}


void dynarr_round(dynarr * self) {
    dynarr_realloc(self, self->size);
}


size_t dynarr_size(dynarr * self) {
    return self->size;
}


const void * dynarr_array(dynarr * self) {
    return self->array;
}


#include <stdlib.h>


void * dynarr_to_array(dynarr * self) {
    void * array = malloc(self->dtype * self->size);
    memcpy(array, self->array, self->dtype * self->size);
    return array;
}


size_t dynarr_dtype(dynarr * self) {
    return self->dtype;
}


void dynarr_finalize(dynarr * self) {
    if(self != NULL) {
        finalize(self->alloc);
    }
}




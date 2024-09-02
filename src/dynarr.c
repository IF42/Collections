#include "cca/dynarr.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>


static void dynarr_reset_iterator(DynArr * self) {
    self->iter = 0;
}


static void * dynarr_next(DynArr * self) {
    if(self->iter < self->size) {
        return self->front + ((self->iter++) * self->dtype);
    } else {
        return NULL;
    }
}


DynArr dynarr_default(Alloc * alloc, size_t dtype, size_t capacity) {
    return (DynArr) {
        . vector = {
            .next = (void*(*)(const vector*)) dynarr_next
            , .reset_iterator = (void(*)(const vector*)) dynarr_reset_iterator
        }
        , .alloc = alloc
        , .dtype = dtype
        , .capacity = capacity
        , .front = capacity > 0 ? new(alloc, dtype * capacity) : NULL
    };
}


static inline bool dynarr_realloc(DynArr * self) {
    size_t capacity = (self->capacity * 2) + 1;
    char * array = new(self->alloc, capacity * self->dtype);

    if(array != NULL) {
		if(self->size > 0) {
			memcpy(array, self->front, self->dtype * self->size);
			delete(self->alloc, self->front);
		}

        self->front = array;
        self->iter = 0;
        self->capacity = capacity;

        return true;
    } else {
        return false;
    }
}


bool dynarr_push_back(DynArr * self, void * value) {
    if(self->size >= self->capacity) {
        if(dynarr_realloc(self) == false) {
            return false;
        }
    } 

    switch(self->dtype) {
        case 1:
            *((uint8_t*) self->front + self->size)  = *(uint8_t*) value;
            break;
        case 2:
            *((uint16_t*) self->front + self->size) = *(uint16_t*) value;
            break;
        case 4:
            *((uint32_t*) self->front + self->size) = *(uint32_t*) value;
            break;
        case 8:
            *((uint64_t*) self->front + self->size) = *(uint64_t*) value;
            break;
        default:
            memcpy(self->front + (self->size*self->dtype), value, self->dtype);
    }

	self->size++;

    return true;
}


bool dynarr_push_front(DynArr * self, void * value) {
    if(self->size >= self->capacity) {
        if(dynarr_realloc(self) == false) {
            return false;
        }
    }

    memcpy(self->front + self->dtype, self->front, self->size * self->dtype);
    memcpy(self->front, value, self->dtype);

    self->size ++;

    return true;
}


void * dynarr_begin(DynArr * self) {
    return self->front;
}


void * dynarr_back(DynArr * self) {
    return self->front + (self->size * self->dtype);
}


void dynarr_remove(DynArr * self, size_t index) {
    if(self->size > 0 && index < self->size) {
        char * ptr = self->front + (index * self->dtype);
        memcpy(ptr, ptr+self->dtype, (self->size - index - 1) * self->dtype);
        self->size--;
    }
}


void dynarr_remove_front(DynArr * self) {
    if(self->size > 0) {
        memcpy(self->front, self->front + self->dtype, (self->size-1) * self->dtype);
        self->size--;
    }
}


void dynarr_remove_back(DynArr * self) {
    if(self->size > 0) {
        self->size --;
    }
}


size_t dynarr_size(DynArr * self) {
    return self->size;
}


bool dynarr_empty(DynArr * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    }
}


void dynarr_finalize(DynArr * self) {
    if(self->front != NULL) {
        delete(self->alloc, self->front);
    }
}




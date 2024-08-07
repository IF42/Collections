#include "container/dynarr.h"

#include <stdio.h>
#include <string.h>


typedef struct segment {
    struct segment * next;
    struct segment * prev;
    char mem[];
} segment;


struct dynarr {
    vector vector;

    size_t size;
    size_t capacity;
    segment * front;
    segment * back;

    struct {
        size_t index;
        segment * front;  
    } iterator;
};


static void * dynarr_iter(dynarr * self) {
    self->iterator.index = 0;
    self->iterator.front = self->front;
    return NULL;
}


static void * dynarr_next(dynarr * self) {
    if(self->iterator.front != NULL && self->iterator.index < self->size) {
        if((self->iterator.index % self->capacity) == 0 && self->iterator.index > 0) {
            self->iterator.front = self->iterator.front->next;
        }

        void * memptr = self->iterator.front->mem + (self->vector.dtype * (self->iterator.index % self->capacity));

        self->iterator.index ++;

        return memptr;
    } else {
        return NULL;
    }
}


vector * dynarr_empty_new(Alloc * alloc, size_t dtype, size_t capacity) {
    static vector_vtab vtab = {.iter = (void*(*)(vector*)) dynarr_iter, .next = (void*(*)(vector*)) dynarr_next};
    dynarr * self = new(alloc, sizeof(dynarr));

    segment * mem_segment = new(alloc, sizeof(segment) + (capacity * dtype));
    mem_segment->next = NULL;
    mem_segment->prev = NULL;

    if(self != NULL && mem_segment != NULL) {
        *self = (dynarr) {
                .vector = {.alloc = alloc
                , .dtype = dtype
                , .vtab = &vtab 
            }
            , .capacity = capacity
            , .front = mem_segment
            , .back = mem_segment
        };

        return (vector*) self;
    } else {
        return NULL;
    }
}


#define DEFAULT_SIZE 10


vector * dynarr_new(Alloc * alloc, size_t dtype) {
    return dynarr_empty_new(alloc, dtype, DEFAULT_SIZE);
}


vector * dynarr_from_array(Alloc * alloc, size_t dtype, size_t size, void * array) {
    vector * self = dynarr_empty_new(alloc, dtype, size);

    if(self != NULL) {
        memcpy(DYNARR(self)->front->mem, array, size * dtype);
        DYNARR(self)->size = size;
        return self;
    } else {
        return NULL;
    }
}


static segment * dynarr_get_segment(dynarr * self, size_t index) {
    size_t back_index = self->size / self->capacity;
    segment * mem_segment;

    index /= self->capacity;

    if(index > back_index / 2) {
        // index is closer to back segment
        mem_segment = self->back;

        for(size_t i = back_index; i > index; i--) {
            if(mem_segment == NULL) {
                return NULL;
            } else {
                mem_segment = mem_segment->prev;
            }
        }
    } else {
        // index is closer to front segment
        mem_segment = self->front;

        for(size_t i = 0; i < index; i++) {
            if(mem_segment == NULL) {
                return NULL;
            } else {
                mem_segment = mem_segment->next;
            }
        }
    }

    return mem_segment;
}


void * dynarr_at(dynarr * self, size_t index) {
    if(index < self->size) {
        segment * front = dynarr_get_segment(self, index);

        if(front != NULL) {
            return front->mem + ((index % self->capacity) * self->vector.dtype);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}


bool dynarr_set(dynarr * self, size_t index, void * value) {
    if(index < self->size) {
        segment * front = dynarr_get_segment(self, index);

        if(front != NULL) {
            memcpy(front->mem + ((index % self->capacity) * self->vector.dtype), value, self->vector.dtype);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


static void dynarr_realloc(dynarr * self) {
    segment * mem_seg = new(self->vector.alloc, sizeof(segment) + (self->vector.dtype * self->capacity));
    
    mem_seg->next = NULL;
    mem_seg->prev = self->back;

    self->back->next = mem_seg;
    self->back = mem_seg;
}


static void dynarr_shift_left(dynarr * self, segment * mem_seg, size_t index, void * value) {
    if(mem_seg->next != NULL) {
        /*
         * recursive shifting of values in each segment
         */
        size_t next_index = index + self->capacity - (index % self->capacity);
        void * last_value = mem_seg->mem + ((self->capacity - 1) * self->vector.dtype);

        dynarr_shift_left(self, mem_seg->next, next_index, last_value);
    }

    /*
     * memory shifting
     */
    char * mem = mem_seg->mem + ((index % self->capacity) * self->vector.dtype);
    size_t shift_size = ((self->size % self->capacity));

    memcpy(mem + self->vector.dtype, mem,  shift_size * self->vector.dtype);

    /*
     * copy of input value into given index
     */
    memcpy(mem, value, self->vector.dtype);
}


/*
 * TODO: I don't like the way how is managed reallocation of new block and insertion of new value
 * but the way how is the memory shifted is good. I would like to separate or rename the dynarr_shift_left function from
 * copying of new value and way of indication reallocation reallocation
 * it is maybe point to improve, but it works at all
 */
bool dynarr_insert(dynarr * self, size_t index, void * value) {
    if(index <= self->size) {
        /*
         * realloc memory segments if needed
         */
        if((self->size % self->capacity) == 0 && self->size > 0) {
            dynarr_realloc(self);
        }
        
        /*
         * find segmet where will be new value inserted
         */
        segment * mem_seg = dynarr_get_segment(self, index);

        dynarr_shift_left(self, mem_seg, index, value);
        self->size++;

        return true;
    } else {
        return false;
    }
}


void dynarr_push_back(dynarr * self, void * value) {
    if((self->size % self->capacity) == 0 && self->size > 0) {
        dynarr_realloc(self);
    }

    char * mem = self->back->mem + ((self->size % self->capacity) * self->vector.dtype);

    memcpy(mem, value, self->vector.dtype);
    self->size++;
}


void dynarr_push_front(dynarr * self, void * value) {
    dynarr_insert(self, 0, value);
}


static void dynarr_shift_right(dynarr * self, segment * mem_seg, size_t index) {
    if(mem_seg->next != NULL) {
        /*
         * recursive shifting of values in each segment
         */
        size_t next_index = index + self->capacity - (index % self->capacity);

        dynarr_shift_right(self, mem_seg->next, next_index);
    }

    /*
     * memory shifting
     */
    char * mem = mem_seg->mem + ((index % self->capacity) * self->vector.dtype);
    size_t shift_size = ((self->size % self->capacity));

    memcpy(mem, mem + self->vector.dtype, shift_size * self->vector.dtype);
}


void dynarr_delete(dynarr * self, size_t index) {
    if(index < self->size) {
        segment * mem_seg = dynarr_get_segment(self, index);
        dynarr_shift_right(self, mem_seg, index);

        // TODO: remove unused empty block
        self->size --;
    }
}


size_t dynarr_size(dynarr * self) {
    return self->size;
}


bool dynarr_empty(dynarr * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    }
}


void dynarr_clear(dynarr * self) {
    /*
     * release allocated memory
     */
    while(self->front != NULL) {
        segment * front = self->front->next;
        delete(self->vector.alloc, self->front);
        self->front = front;
    }

    /*
     * allocate new segment
     */
    segment * mem_segment = new(self->vector.alloc, sizeof(segment) + (self->capacity * self->vector.dtype));
    mem_segment->next = NULL;
    mem_segment->prev = NULL;

    /*
     * initialize dynarr instance
     */
    self->front = mem_segment;
    self->back = mem_segment;
    self->size = 0;
}




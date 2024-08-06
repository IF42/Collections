#include "container/dynarr.h"

#include <stdio.h>
#include <string.h>


typedef struct segment {
    struct segment * next;
    struct segment * prev;
    char mem[];
} segment;


struct dynarr {
    Alloc * alloc;

    size_t dtype;
    size_t size;
    size_t capacity;
    segment * head;
    segment * tail;
};


dynarr * dynarr_empty_new(Alloc * alloc, size_t dtype, size_t size) {
    dynarr * self = new(alloc, sizeof(dynarr));

    segment * mem_segment = new(alloc, sizeof(segment) + (size * dtype));
    mem_segment->next = NULL;
    mem_segment->prev = NULL;

    if(self != NULL && mem_segment != NULL) {
        *self = (dynarr) {
            .alloc = alloc
            , .dtype = dtype
            , .size = size
            , .capacity = size
            , .head = mem_segment
            , .tail = mem_segment
        };

        return self;
    } else {
        return NULL;
    }
}


#define DEFAULT_SIZE 10


dynarr * dynarr_new(Alloc * alloc, size_t dtype) {
    dynarr * self = new(alloc, sizeof(dynarr));

    segment * mem_segment = new(alloc, sizeof(segment) + (DEFAULT_SIZE * dtype));
    mem_segment->next = NULL;
    mem_segment->prev = NULL;

    if(self != NULL && mem_segment != NULL) {
        *self = (dynarr) {
            .alloc = alloc
            , .dtype = dtype
            , .size = 0
            , .capacity = DEFAULT_SIZE
            , .head = mem_segment
            , .tail = mem_segment
        };

        return self;
    } else {
        return NULL;
    }
}


dynarr * dynarr_from_array(Alloc * alloc, size_t dtype, size_t size, void * array) {
    dynarr * self = dynarr_empty_new(alloc, dtype, size);

    if(self != NULL) {
        memcpy(self->head->mem, array, size * dtype);
        return self;
    } else {
        return NULL;
    }
}


static segment * dynarr_get_segment(dynarr * self, size_t index) {
    size_t tail_index = self->size / self->capacity;
    segment * mem_segment;

    index /= self->capacity;

    if(index > tail_index / 2) {
        // index is closer to tail segment
        mem_segment = self->tail;

        for(size_t i = tail_index; i > index; i--) {
            if(mem_segment == NULL) {
                return NULL;
            } else {
                mem_segment = mem_segment->prev;
            }
        }
    } else {
        // index is closer to head segment
        mem_segment = self->head;

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


static void * dynarr_next(dynarr_iter * iter) {
    if(iter->head != NULL && iter->index < iter->size) {
        if((iter->index % iter->capacity) == 0 && iter->index > 0) {
            iter->head = ((segment*) iter->head)->next;
        }

        void * memptr = ((segment*) iter->head)->mem + (iter->dtype * (iter->index % iter->capacity));

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
        , .capacity = self->capacity
        , .index = 0
        , .head = self->head
    };
}


void * dynarr_at(dynarr * self, size_t index) {
    if(index < self->size) {
        segment * head = dynarr_get_segment(self, index);

        if(head != NULL) {
            return head->mem + ((index % self->capacity) * self->dtype);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}


bool dynarr_set(dynarr * self, size_t index, void * value) {
    if(index < self->size) {
        segment * head = dynarr_get_segment(self, index);

        if(head != NULL) {
            memcpy(head->mem + ((index % self->capacity) * self->dtype), value, self->dtype);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


static void dynarr_realloc(dynarr * self) {
    segment * mem_seg = new(self->alloc, sizeof(segment) + (self->dtype * self->capacity));
    
    mem_seg->next = NULL;
    mem_seg->prev = self->tail;

    self->tail->next = mem_seg;
    self->tail = mem_seg;
}


static void dynarr_shift_left(dynarr * self, segment * mem_seg, size_t index, void * value) {
    if(mem_seg->next != NULL) {
        /*
         * recursive shifting of values in each segment
         */
        size_t next_index = index + self->capacity - (index % self->capacity);
        void * last_value = mem_seg->mem + ((self->capacity - 1) * self->dtype);

        dynarr_shift_left(self, mem_seg->next, next_index, last_value);
    }

    /*
     * memory shifting
     */
    char * mem = mem_seg->mem + ((index % self->capacity) * self->dtype);
    size_t shift_size = ((self->size % self->capacity));

    memcpy(mem + self->dtype, mem,  shift_size * self->dtype);

    /*
     * copy of input value into given index
     */
    memcpy(mem, value, self->dtype);
}


/*
 * TODO: I don't like the way how is managed reallocation of new block and insertion of new value
 * but the way how is the memory shifted is good. I would like to separate or rename the dynarr_shift_left function from
 * copying of new value and way of indication reallocation reallocation
 * it is maybe point to improve, but it works at all
 */
bool dynarr_insert(dynarr * self, size_t index, void * value) {
    if(index < self->size) {
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


void dynarr_push_front(dynarr * self, void * value) {
    if((self->size % self->capacity) == 0 && self->size > 0) {
        dynarr_realloc(self);
    }

    char * mem = self->tail->mem + ((self->size % self->capacity) * self->dtype);

    memcpy(mem, value, self->dtype);
    self->size++;
}


void dynarr_push_back(dynarr * self, void * value) {
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
    char * mem = mem_seg->mem + ((index % self->capacity) * self->dtype);
    size_t shift_size = ((self->size % self->capacity));

    memcpy(mem, mem + self->dtype, shift_size * self->dtype);
}


void dynarr_delete(dynarr * self, size_t index) {
    if(index < self->size) {
        segment * mem_seg = dynarr_get_segment(self, index);
        dynarr_shift_right(self, mem_seg, index);

        // TODO: remove unused empty block
        self->size --;
    }
}


size_t dynarr_dtype(dynarr * self) {
    return self->dtype;
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
    while(self->head != NULL) {
        segment * head = self->head->next;
        delete(self->alloc, self->head);
        self->head = head;
    }

    /*
     * allocate new segment
     */
    segment * mem_segment = new(self->alloc, sizeof(segment) + (self->capacity * self->dtype));
    mem_segment->next = NULL;
    mem_segment->prev = NULL;

    /*
     * initialize dynarr instance
     */
    self->head = mem_segment;
    self->tail = mem_segment;
    self->size = 0;
}


void dynarr_finalize(dynarr * self) {
    if(self != NULL) {
        finalize(self->alloc);
    }
}




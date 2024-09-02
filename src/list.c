#include "cca/list.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>


static void list_reset_iterator(List * self) {
    self->iter = self->front;
}


static void * list_next(List * self) {
    if(self->iter != NULL) {
        void * value = self->iter + 1;
        self->iter = self->iter->next;
        return value;
    } else {
        return NULL;
    }
}


List list(Alloc * alloc, size_t dtype) {
    return (List) {
        .vector = {
            .next = (void*(*)(const vector*)) list_next
            , .reset_iterator = (void(*)(const vector*)) list_reset_iterator
        }
        , .alloc = alloc
        , .dtype = dtype
    };
}


bool list_push_front(List * self, void * value) {
    Node * node = new(self->alloc, sizeof(Node) + self->dtype);

    if(node != NULL) {
        switch(self->dtype) {
            case 1:
                *(uint8_t*)(node+1) = *(uint8_t*) value;
                break;
            case 2:
                *(uint16_t*) (node+1) = *(uint16_t*) value;
                break;
            case 4:
                *(uint32_t*) (node+1) = *(uint32_t*) value;
                break;
            case 8:
                *(uint64_t*) (node+1) = *(uint64_t*) value;
                break;
            default:
                memcpy((node+1), value, self->dtype);
        }

        node->next = self->front;
        node->prev = NULL;

        if(self->front != NULL) {
            self->front->prev = node;
        }

        self->front = node;

        if(self->back == NULL) {
            self->back = node;
        }   

        self->size++;

        return true;
    } else {
        return false;
    }
}


bool list_push_back(List * self, void * value) {
    Node * node = new(self->alloc, sizeof(Node) + self->dtype);

    if(node != NULL) {
        switch(self->dtype) {
            case 1:
                *(uint8_t*)(node+1) = *(uint8_t*) value;
                break;
            case 2:
                *(uint16_t*) (node+1) = *(uint16_t*) value;
                break;
            case 4:
                *(uint32_t*) (node+1) = *(uint32_t*) value;
                break;
            case 8:
                *(uint64_t*) (node+1) = *(uint64_t*) value;
                break;
            default:
                memcpy((node+1), value, self->dtype);
        }

        node->next = NULL;
        node->prev = self->back;

        if(self->back != NULL) {
            self->back->next= node;
        }

        self->back = node;

        if(self->front == NULL) {
            self->front = node;
            self->iter = node;
        }

        self->size++;

        return true;
    } else {
        return false;
    }
}


void * list_front(List * self) {
    return self->front + 1;
}


void * list_back(List * self) {
    return self->back + 1;
}


/*
 * TODO: improve searching of node on given index by starting at the nearest edge (index > size/2 ? back : front )
 */
static Node * list_find_node(List * self, size_t index) {
    if(index < self->size) {
        Node * node = self->front;

        for(size_t i = 0; i < index; i++) {
            if(node != NULL) {
                node = node->next;
            } else {
                return NULL;
            }
        }

        return node;
    } else {
        return NULL;
    }
}


void * list_get(List * self, size_t index) {
    Node * node = list_find_node(self, index);

    if(node != NULL) {
        return node + 1;
    } else {
        return NULL;
    }
}


void list_remove(List * self, size_t index) {
    Node * node = list_find_node(self, index);

    if(node != NULL) {
        if(node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            self->front = node->next;
            self->iter = node->next;
        }

        if(node->next != NULL) {
            node->next->prev = node->prev;
        } else {
            self->back = node->prev;
        }

        /*
         * delete memory
         */
        delete(self->alloc, node);

        self->size --;
    } 
}


void list_remove_front(List * self) {
    if(self->front != NULL) {
        if(self->front == self->back) {
            delete(self->alloc, self->front);
            self->front = NULL;
            self->back = NULL;
        } else {
            Node * node = self->front;
            self->front = node->next;
            self->front->prev = NULL;
            delete(self->alloc, node);
        }

        self->size --;
    }
}


void list_remove_back(List * self) {
    if(self->back != NULL) {
        if(self->back == self->front) {
            delete(self->alloc, self->front);
            self->front = NULL;
            self->back = NULL;
        } else {
            Node * node = self->back;
            self->back = node->prev;
            self->back->next = NULL;
            delete(self->alloc, node);
        }

        self->size --;
    }
}


bool list_empty(List * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    } 
}


size_t list_size(List * self) {
    return self->size;
}


size_t list_dtype(List * self) {
    return self->dtype;
}


void list_finalize(List * self) {
    if(self->alloc != NULL) {
        while(self->front != self->back) {
           Node * memnode = self->front;
           self->front = memnode->next;
           delete(self->alloc, memnode);
        }
    }
}


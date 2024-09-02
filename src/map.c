#include "cca/map.h"


Map map(Alloc * alloc, size_t dtype) {
    return (Map) {
        .alloc = alloc
        , .dtype = dtype   
    };
}


size_t map_size(Map * self) {
    return self->size;
}


bool map_empty(Map * self) {
    if(self->size == 0) {
        return true;
    } else {
        return false;
    }
}


void map_finalize(Map * self) {
    if(self->alloc != NULL) {
    }
}





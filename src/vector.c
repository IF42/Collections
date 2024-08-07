#include "container/vector.h"


void vector_finalize(vector * self) {
    if(self->alloc != NULL) {
        finalize(self->alloc);
    }
}

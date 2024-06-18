#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stddef.h>


typedef struct {
    size_t dtype;
    size_t size;
    void * array;   
}vector;


#define vector(dtype, size, array) (vector){dtype, size, (void*) array}



#endif

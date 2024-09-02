#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>
#include <alloc/sys_alloc.h>

#include "../src/cca/dynarr.h"
#include "../src/cca/list.h"


//#define DEFAULT_TEST
#define DYNARR_TEST
//#define LIST_TEST 


#define TEST_SIZE 100000000


size_t vector_sum(const vector * vec) {
    size_t sum = 0;

    foreach(vec, num) {
        sum += *(int*) num;
    };

    return sum;
}


#if defined(DEFAULT_TEST)
void default_test(void) {
    size_t * mem = malloc(sizeof(size_t) * TEST_SIZE);

    for(size_t i = 0; i < TEST_SIZE; i++) {
        mem[i] = i;
    }

    size_t sum = 0;

    for(size_t i = 0; i < TEST_SIZE; i++) {
        sum += mem[i];
    }

    printf("%ld\n", sum);

    free(mem);
}
#elif defined(DYNARR_TEST) 
void dynarr_test(void) {
    Alloc * alloc = sys_alloc_new();
    DynArr arr = dynarr_default(alloc, sizeof(int), 100);
    
    for(int i = 0; i < TEST_SIZE; i++) {
        if(dynarr_push_back(&arr, &i) == false) {
            printf("alloc error %d\n", i);
            return;
        }
    }  

    size_t sum = vector_sum(dynarr_to_vector(&arr));

    printf("%ld\n", sum);
    dynarr_finalize(&arr);
}
#elif defined(LIST_TEST)
void list_test(void) {
    Alloc * alloc = stack_alloc_new(((size_t)TEST_SIZE)*21); //sys_alloc_new();
    List lst = list(alloc, sizeof(int));
    
    for(int i = 0; i < TEST_SIZE; i++) {
        if(list_push_back(&lst, &i) == false) {
            printf("alloc error %d\n", i);
            return;
        }
    }  

    size_t sum = vector_sum(list_to_vector(&lst));

    printf("%ld\n", sum);
    list_finalize(&lst);
}
#endif

int main(void) {
#if defined(DEFAULT_TEST) 
    printf("default test:\n");
    default_test();
#elif defined(DYNARR_TEST)
    printf("dynarr test:\n");
    dynarr_test();
#elif defined(LIST_TEST)
    printf("list test: \n");
    list_test();
#endif
    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




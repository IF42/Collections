#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>
#include <alloc/sys_alloc.h>

#include "../src/container/dynarr.h"
#include "../src/container/list.h"


//#define DEFAULT_TEST
//#define DYNARR_TEST
#define LIST_TEST 


#define TEST_SIZE 100000000


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
void dynar_test(void) {
    Alloc * alloc = sys_alloc_new();
    dynarr * arr = dynarr_default_new(alloc, sizeof(int), 100);
    
    for(int i = 0; i < TEST_SIZE; i++) {
        if(dynarr_push_back(arr, &i) == false) {
            printf("alloc error %d\n", i);
            return;
        }
    }  

    size_t sum = fold(dynarr_to_vector(arr), num, 0, sum += *(int*) num);
   
    printf("%ld\n", sum);
    dynarr_finalize(arr);
}
#elif defined(LIST_TEST)
void list_test(void) {
    Alloc * alloc = stack_alloc_new(((size_t)TEST_SIZE)*21); //sys_alloc_new();
    list * lst = list_new(alloc, sizeof(int));
    
    for(int i = 0; i < TEST_SIZE; i++) {
        if(list_push_back(lst, &i) == false) {
            printf("alloc error %d\n", i);
            return;
        }
    }  

    size_t sum = 0;

    foreach(list_to_vector(lst), num) {
        sum += *(int*) num;
    };
   
    printf("%ld\n", sum);
    list_finalize(lst);
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




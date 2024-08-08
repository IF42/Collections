#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>

#include "../src/container/dynarr.h"
#include "../src/container/list.h"


#define TEST_SIZE 100000000
/*
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
*/

void test(void) {
    Alloc * alloc = sys_alloc_new();
    vector * vec = vector_default_new(alloc, sizeof(int), 100);
    
    for(int i = 0; i < TEST_SIZE; i++) {
        vector_push_back(vec, &i);
    }  

    size_t sum = 0;

    for (int *i = vector_begin(vec), *end = vector_end(vec); i != end; ++i) {
        sum += *i;
    }

    printf("%ld\n", sum);
    
    vector_finalize(vec);
}


void list_test(void) {
    Alloc * alloc = stack_alloc_new(TEST_SIZE*20);//sys_alloc_new();//
    list * l = list_new(alloc, sizeof(int));
  
    for(int i = 0; i < TEST_SIZE; i++) {
        list_push_back(l, &i);
    }

    size_t sum = 0;

    for(int * i = list_front(l); i != NULL; i = list_next(i)) {
        sum += *i;
    }

    printf("%ld\n", sum);

    /*
    list_remove_back(list);

    list_iter iter = list_iterator(list);

    foreach(num, ITERATOR(&iter)) {
        printf("%d\n", *(int*)num);
    }
   
    
    printf("empty: %s\n", list_empty(list) ? "true" : "false");
    */
    list_finalize(l);
}


#if 0

void list_test(void) {
    Alloc * alloc = sys_alloc_new();
    list * list = list_new(alloc, sizeof(int));
  
    for(size_t i = 0; i < TEST_SIZE; i++) {
        list_push_back(list, &i);
    }

    printf("size: %ld\n", list_size(list));
   
    /*
    list_remove_back(list);

    list_iter iter = list_iterator(list);

    foreach(num, ITERATOR(&iter)) {
        printf("%d\n", *(int*)num);
    }
   
    
    printf("empty: %s\n", list_empty(list) ? "true" : "false");
    */
    list_finalize(list);
}


void dynarr_test(void) {
#if 0
    Alloc * alloc = sys_alloc_new();
    vector * arr = dynarr_empty_new(alloc, sizeof(size_t), TEST_SIZE);
  
    for(size_t i = 0; i < TEST_SIZE; i++) {
        dynarr_push_back(DYNARR(arr), &i);
    }

    printf("size: %ld\n", dynarr_size(DYNARR(arr)));

    printf("%ld\n", *(size_t*)dynarr_at(DYNARR(arr), 2));
    
    size_t i = 0;
    foreach(num, arr) {
        i += *(size_t*)num;
    }

    printf("%ld\n", i);

    /*
    dynarr_insert(arr, 20, (int[]){42});
    dynarr_delete(arr, 23);

    dynarr_iter iter = dynarr_iterator(arr);

    size_t i = 0;
    foreach(num, ITERATOR(&iter)) {
        printf("%ld: %d\n",i, *(int*)num);
        i++;
    }
*/
    /*
    dynarr_clear(arr);

    for(size_t i = 0; i < 15; i++) {
        int k = i + 3;
        dynarr_push_front(arr, &k);
    }

    ter = dynarr_iterator(arr);

    foreach(num, ITERATOR(&iter)) {
        printf("%d\n", *(int*)num);
    }
    */
    vector_finalize(arr);
#endif
}
#endif


int main(void) {
    list_test();
    //dynarr_test();
    //test();
    //default_test();
    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




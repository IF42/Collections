#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>

#include "../src/container/dynarr.h"
//#include "../src/container/list.h"


#define TEST_SIZE 100000000

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


void list_test(void) {
#if 0
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
#endif
}


void dynarr_test(void) {
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
}


int main(void) {
    //list_test();
    dynarr_test();
    //default_test();
    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




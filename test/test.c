#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>

#include "../src/container/dynarr.h"
#include "../src/container/list.h"


#define TEST_SIZE 1000000


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
    Alloc * alloc = sys_alloc_new();
    dynarr * arr = dynarr_new(alloc, sizeof(int));
  
    for(size_t i = 0; i < TEST_SIZE; i++) {
        dynarr_push_front(arr, &i);
    }

    printf("size: %ld\n", dynarr_size(arr));

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
    dynarr_finalize(arr);
}


int main(void) {
    //list_test();
    dynarr_test();

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




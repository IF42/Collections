#include <stdio.h>
#include <stdlib.h>
#include <alloc/free_list_alloc.h>

#include "../src/container/dynarr.h"
#include "../src/container/list.h"


void list_test(void) {
    Alloc * alloc = sys_alloc_new();
    list * list = list_new(alloc, sizeof(int));
  
    for(size_t i = 0; i < 10; i++) {
        list_push_back(list, &i);
    }

    printf("size: %ld\n", list_size(list));

    list_iter iter = list_iterator(list);

    foreach(num, ITERATOR(&iter)) {
        printf("%d\n", *(int*)num);
    }

    list_finalize(list);
}


void dynarr_test(void) {
    Alloc * alloc = sys_alloc_new();
    dynarr * arr = dynarr_new(alloc, sizeof(int));
  
    for(size_t i = 0; i < 10; i++) {
        dynarr_push(arr, &i);
    }

    printf("size: %ld\n", dynarr_size(arr));

    dynarr_iter iter = dynarr_iterator(arr);

    foreach(num, ITERATOR(&iter)) {
        printf("%d\n", *(int*)num);
    }

    dynarr_finalize(arr);
}


int main(void) {
    list_test();
    dynarr_test();

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}

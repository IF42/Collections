#include <stdio.h>
#include <stdlib.h>

#include "../src/vector.h"
#include "../src/list.h"


void vector_test(void) {
    vector * arr = vector_new_from_array(sizeof(int), 5, (int[]) {1,2,3,4,5});

    for(size_t i = 0; i < vector_size(arr); i++)
        printf(i == 0 ? "%d" : ", %d", *(int*)vector_at(arr, i));

    printf("\n");

    vector_delete(arr);
}


void list_test(void) {
    list * l = NULL;

    for(size_t i = 0; i < 10; i++)
        l = list_append(l, sizeof(int), (int[]){2*i});   

    for(list * node = l; node != NULL; node = list_next(node)) 
        printf("%d ", *(int*)list_peek(node));
    
    printf("\n");

    list_delete(l);
}


int main(void) {
    vector_test();
    list_test();

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}

#include <iostream>
#include <vector>
#include <list>

#define TEST_SIZE 100000000


void vector_test() {
    std::vector<int> vec(0);

    for(int i = 0; i < TEST_SIZE; i++) {
        vec.push_back(i);
    }  

    size_t sum = 0;

    for (auto i = vec.begin(); i != vec.end(); ++i) {
        sum += *i;
    }

    std::cout << sum << std::endl;
}

void list_test() {
    std::list<int> l;

    for(int i = 0; i < TEST_SIZE; i++) {
        l.push_back(i);
    }  

    size_t sum = 0;

    for (auto i = l.begin(); i != l.end(); ++i) {
        sum += *i;
    }

    std::cout << sum << std::endl;
}


int main(void) {
    vector_test();
    //list_test();
    std::cout << "Program exit.." << std::endl;
    return 0;
}

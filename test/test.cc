#include <iostream>
#include <vector>

#define TEST_SIZE 100000000


void test() {
    std::vector<size_t> vec;

    for(size_t i = 0; i < TEST_SIZE; i++) {
        vec.push_back(i);
    }  

    size_t sum = 0;

    for (auto i = vec.begin(); i != vec.end(); ++i) {
        sum += *i;
    }

    printf("%ld\n", sum);
}


int main(void) {
    test();
    std::cout << "Program exit.." << std::endl;
    return 0;
}

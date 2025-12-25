#include <iostream>
#include <unistd.h>
#include "shared_array.h"

int main() {
    shared_array arr("shared_array_name", 10);  

    int index = 0;
    while (true) {
        arr.lock();

        std::cout << "First Process: Writing to index " << index << std::endl;
        arr[index] = index * 2;  
        index = (index + 1) % 10;  

        arr.unlock();

        sleep(1);  
    }

    return 0;
}

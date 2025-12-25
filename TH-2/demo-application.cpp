#include "parallel_scheduler.hpp"
#include <iostream>
#include <unistd.h>


void task1(void* arg) {
    int id = *(int*)arg;
    sleep(1);
    std::cout << "Task " << id << " completed by thread\n";
}

void task2(void* arg) {
    int id = *(int*)arg;
    std::cout << "Quick task " << id << " completed\n";
}

void calculate_sum(void* arg) {
    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += i;
    }
    std::cout << "Sum calculated: " << sum << "\n";
}

int main() {
    std::cout << "=== Thread Pool Demo ===\n";
    
    parallel_scheduler pool(3);
    
    std::cout << "Created thread pool with capacity 3\n";
    std::cout << "Adding 10 tasks to queue...\n";
    
    int task_ids[10];
    
    for (int i = 0; i < 10; i++) {
        task_ids[i] = i + 1;
        
        if (i % 3 == 0) {
            pool.run(task1, &task_ids[i]);
            std::cout << "Added slow task " << (i+1) << "\n";
        } else if (i % 3 == 1) {
            pool.run(task2, &task_ids[i]);
            std::cout << "Added quick task " << (i+1) << "\n";
        } else {
            pool.run(calculate_sum, NULL);
            std::cout << "Added calculation task " << (i+1) << "\n";
        }
    }
    
    std::cout << "\nAll tasks added to queue.\n";
    std::cout << "Pool will execute them using 3 threads.\n";
    std::cout << "Main thread will wait 5 sec\n";
    
     sleep(5);
    
    std::cout << "END ";
    return 0;
}

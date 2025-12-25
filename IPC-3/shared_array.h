#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <cstring>
#include <unistd.h>
#include <stdexcept>

class shared_array {
public:
    shared_array(const std::string& name, size_t size);
    ~shared_array();

    int& operator[](size_t i);
    void lock();
    void unlock();

private:
    std::string name_;
    size_t size_;
    int shmid_;
    int semid_;
    int* array_;
    key_t shmkey_;
    key_t semkey_;

    void init_semaphore();
    void cleanup_semaphore();
};

#endif // SHARED_ARRAY_H

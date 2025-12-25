#include "shared_array.h"

shared_array::shared_array(const std::string& name, size_t size)
    : name_(name), size_(size) {
    shmkey_ = ftok(name_.c_str(), 1);
    semkey_ = ftok(name_.c_str(), 2);

    shmid_ = shmget(shmkey_, size_ * sizeof(int), IPC_CREAT | 0666);
    if (shmid_ == -1) {
        throw std::runtime_error("Failed to create shared memory segment.");
    }

    array_ = static_cast<int*>(shmat(shmid_, nullptr, 0));
    if (array_ == (int*)-1) {
        throw std::runtime_error("Failed to attach shared memory.");
    }

    
    init_semaphore();
}

shared_array::~shared_array() {
    if (shmdt(array_) == -1) {
        std::cerr << "Failed to detach shared memory." << std::endl;
    }

    
    cleanup_semaphore();
}

int& shared_array::operator[](size_t i) {
    if (i >= size_) {
        throw std::out_of_range("Index out of bounds.");
    }
    return array_[i];
}

void shared_array::lock() {
    struct sembuf sb = {0, -1, 0};
    if (semop(semid_, &sb, 1) == -1) {
        std::cerr << "Failed to lock semaphore." << std::endl;
        exit(1);
    }
}

void shared_array::unlock() {
    struct sembuf sb = {0, 1, 0};
    if (semop(semid_, &sb, 1) == -1) {
        std::cerr << "Failed to unlock semaphore." << std::endl;
        exit(1);
    }
}

void shared_array::init_semaphore() {
    semid_ = semget(semkey_, 1, IPC_CREAT | 0666);
    if (semid_ == -1) {
        throw std::runtime_error("Failed to create semaphore.");
    }

    if (semctl(semid_, 0, SETVAL, 1) == -1) {
        throw std::runtime_error("Failed to initialize semaphore.");
    }
}

void shared_array::cleanup_semaphore() {
    if (semctl(semid_, 0, IPC_RMID) == -1) {
        std::cerr << "Failed to remove semaphore." << std::endl;
    }
}

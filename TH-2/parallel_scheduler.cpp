#include "parallel_scheduler.hpp"
#include <queue>
#include <pthread.h>

struct Task {
    FunctionPtr func;
    void* arg;
};


struct ThreadData {
    std::queue<Task>* task_queue;
    pthread_mutex_t* queue_mutex;
    pthread_cond_t* queue_cond;
    bool* stop;
    int id;
};


void* worker_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    while (true) {
        pthread_mutex_lock(data->queue_mutex);

        while (data->task_queue->empty() && !(*data->stop)) {
            pthread_cond_wait(data->queue_cond, data->queue_mutex);
        }
        
        if (*data->stop && data->task_queue->empty()) {
            pthread_mutex_unlock(data->queue_mutex);
            break;
        }
        
        Task task = data->task_queue->front();
        data->task_queue->pop();
        pthread_mutex_unlock(data->queue_mutex);
        task.func(task.arg);
    }
    
    delete data;
    return NULL;
}

class parallel_scheduler_impl {
private:
    int capacity;
    std::queue<Task> task_queue;
    pthread_t* threads;
    pthread_mutex_t queue_mutex;
    pthread_cond_t queue_cond;
    bool stop;
    ThreadData** thread_data;

public:
    parallel_scheduler_impl(int cap) : capacity(cap), stop(false) {
        pthread_mutex_init(&queue_mutex, NULL);
        pthread_cond_init(&queue_cond, NULL);
        
        threads = new pthread_t[capacity];
        thread_data = new ThreadData*[capacity];
        
        
        for (int i = 0; i < capacity; i++) {
            thread_data[i] = new ThreadData{
                &task_queue,
                &queue_mutex,
                &queue_cond,
                &stop,
                i
            };
            pthread_create(&threads[i], NULL, worker_thread, thread_data[i]);
        }
    }
    
    ~parallel_scheduler_impl() {
         pthread_mutex_lock(&queue_mutex);
        stop = true;
        pthread_cond_broadcast(&queue_cond);
        pthread_mutex_unlock(&queue_mutex);
        
        for (int i = 0; i < capacity; i++) {
            pthread_join(threads[i], NULL);
            delete thread_data[i];
        }
        
        delete[] threads;
        delete[] thread_data;
        
        pthread_mutex_destroy(&queue_mutex);
        pthread_cond_destroy(&queue_cond);
    }
    
    void run(FunctionPtr func, void* arg) {
        pthread_mutex_lock(&queue_mutex);
        
        Task task;
        task.func = func;
        task.arg = arg;
        task_queue.push(task);
        
        pthread_cond_signal(&queue_cond);
        pthread_mutex_unlock(&queue_mutex);
    }
};

parallel_scheduler::parallel_scheduler(int capacity) {
    impl = new parallel_scheduler_impl(capacity);
}

parallel_scheduler::~parallel_scheduler() {
    delete (parallel_scheduler_impl*)impl;
}

void parallel_scheduler::run(FunctionPtr func, void* arg) {
    ((parallel_scheduler_impl*)impl)->run(func, arg);
}



#ifndef PARALLEL_SCHEDULER_HPP
#define PARALLEL_SCHEDULER_HPP

typedef void (*FunctionPtr)(void*);

class parallel_scheduler {
private:
    void* impl;  
    
public:
    parallel_scheduler(int capacity);
    ~parallel_scheduler();
    
    void run(FunctionPtr func, void* arg);
};

#endif

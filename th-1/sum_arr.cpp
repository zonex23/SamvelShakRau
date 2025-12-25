#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <sys/time.h>

int* arr;
long long total_sum = 0;
pthread_mutex_t lock;

void* sum_part(void* args) {
    long long start = ((long long*)args)[0];
    long long end = ((long long*)args)[1];
    long long my_sum = 0;
    
    for (long long i = start; i < end; i++) {
        my_sum += arr[i];
    }
    
    pthread_mutex_lock(&lock);
    total_sum += my_sum;
    pthread_mutex_unlock(&lock);
    
    delete[] (long long*)args;
    return NULL;
}

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <array_size> <thread_count>\n";
        return 1;
    }
    
    long long N = atoll(argv[1]);
    int M = atoi(argv[2]);
    
    if (N <= 1000000) {
        std::cout << "Array size must be > 1,000,000\n";
        return 1;
    }
    
    
    arr = new int[N];
    
    srand(time(NULL));
    for (long long i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }
    
    double start1 = get_time();
    
    long long sum1 = 0;
    for (long long i = 0; i < N; i++) {
        sum1 += arr[i];
    }
    
    double end1 = get_time();
    double time1 = end1 - start1;
    
    std::cout << "Time spent without threads: " << time1 << " seconds\n";
    
    double start2 = get_time();
    
    total_sum = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_t threads[M];
    long long chunk = N / M;
    
    for (int i = 0; i < M; i++) {
        long long* range = new long long[2];
        range[0] = i * chunk;
        range[1] = (i == M-1) ? N : range[0] + chunk;
        pthread_create(&threads[i], NULL, sum_part, range);
    }
    
    for (int i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }
    
    double end2 = get_time();
    double time2 = end2 - start2;
    
    pthread_mutex_destroy(&lock);
    
    std::cout << "Time spent with " << M << " threads: " << time2 << " seconds\n";
    
    if (sum1 == total_sum) {
        std::cout << "Sum: " << total_sum << " (correct)\n";
    } else {
        std::cout << "Error: sums don't match!\n";
    }
    
    delete[] arr;
    return 0;
}


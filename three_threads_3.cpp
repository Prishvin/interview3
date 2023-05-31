#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

const int PRINT_TIMES = 5;

#define N_THREADS 3
sem_t semaphores[N_THREADS];

void* print(void* arg) {
    int id = *((int*) arg);
    for (int i = 0; i < PRINT_TIMES; ++i) {
        sem_wait(&semaphores[id]);
        cout << id + 1 << endl;
        sem_post(&semaphores[(id + 1) % N_THREADS]);
    }
    return nullptr;
}

int main() {
    pthread_t threads[N_THREADS];
    int thread_ids[N_THREADS];


    for (int i = 0; i < N_THREADS; ++i) {
        if (i == 0) {
            sem_init(&semaphores[i], 0, 1);  
        } else {
            sem_init(&semaphores[i], 0, 0);  
        }
    }

    for (int i = 0; i < N_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, print, &thread_ids[i]);
    }

    for (int i = 0; i < N_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N_THREADS; ++i) {
        sem_destroy(&semaphores[i]);
    }

    return 0;
}

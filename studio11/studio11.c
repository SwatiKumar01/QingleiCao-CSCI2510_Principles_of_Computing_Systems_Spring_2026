#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long shared = 0;
int iterations = 20000000;

pthread_mutex_t mutex;

void* adder(void* arg) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < iterations; i++) {
        shared++;
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* subtractor(void* arg) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < iterations; i++) {
        shared--;
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, adder, NULL);
    pthread_create(&t2, NULL, subtractor, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value: %ld\n", shared);

    pthread_mutex_destroy(&mutex);

    return 0;
}
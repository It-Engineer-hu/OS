#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 3

// Shared resource
int shared_resource = 0;

// Semaphores and mutex
pthread_mutex_t mutex;     // Protects shared resource
pthread_mutex_t rw_mutex;  // Protects the number of readers
sem_t write_sem;           // Semaphore to control writing

int read_count = 0;        // Number of readers currently reading

// Reader thread function
void *reader(void *param) {
    pthread_mutex_lock(&rw_mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_sem);  // First reader locks the write semaphore
    }
    pthread_mutex_unlock(&rw_mutex);

    // Read the shared resource
    printf("Reader %ld reading value: %d\n", (long)param, shared_resource);

    pthread_mutex_lock(&rw_mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&write_sem);  // Last reader unlocks the write semaphore
    }
    pthread_mutex_unlock(&rw_mutex);

    return NULL;
}

// Writer thread function
void *writer(void *param) {
    // Wait for the write semaphore (exclusive access)
    sem_wait(&write_sem);

    // Write to the shared resource
    shared_resource++;
    printf("Writer %ld wrote value: %d\n", (long)param, shared_resource);

    // Signal that the writer is done
    sem_post(&write_sem);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    // Initialize mutexes and semaphores
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&rw_mutex, NULL);
    sem_init(&write_sem, 0, 1);  // Initially, only one writer can write

    // Create reader and writer threads
    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
    }
    for (long i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);
    sem_destroy(&write_sem);

    return 0;
}


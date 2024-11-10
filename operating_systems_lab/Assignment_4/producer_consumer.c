#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5 // Size of the buffer
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

// Buffer and associated indices
int buffer[BUFFER_SIZE];
int in = 0, out = 0; // Indices to add and remove items

// Semaphores
sem_t empty;  // Semaphore to track empty slots
sem_t full;   // Semaphore to track filled slots
pthread_mutex_t mutex;  // Mutex for mutual exclusion

// Producer thread function
void *producer(void *param) {
    int item, i;
    for (i = 0; i < 5; i++) {
        item = rand() % 100; // Produce an item

        // Wait until there is space in the buffer
        sem_wait(&empty);

        // Lock the mutex for mutual exclusion
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        buffer[in] = item;
        printf("Producer %ld produced item: %d at index %d\n", (long)param, item, in);
        in = (in + 1) % BUFFER_SIZE;

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal that the buffer has a new item
        sem_post(&full);

        // Simulate production time
        sleep(rand() % 2);
    }
    return NULL;
}

// Consumer thread function
void *consumer(void *param) {
    int item, i;
    for (i = 0; i < 5; i++) {
        // Wait until there is an item in the buffer
        sem_wait(&full);

        // Lock the mutex for mutual exclusion
        pthread_mutex_lock(&mutex);

        // Consume an item from the buffer
        item = buffer[out];
        printf("Consumer %ld consumed item: %d from index %d\n", (long)param, item, out);
        out = (out + 1) % BUFFER_SIZE;

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Signal that there is an empty slot in the buffer
        sem_post(&empty);

        // Simulate consumption time
        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no slots are filled
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    // Create producer and consumer threads
    for (long i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)i);
    }
    for (long i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}


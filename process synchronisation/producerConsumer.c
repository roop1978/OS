#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 5 // Maximum size of the buffer

int buffer[MAX_BUFFER_SIZE];
int in = 0, out = 0;      // Indices for producing and consuming
sem_t empty, full, mutex; // Semaphores

// Producer function
void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100; // Produce an item (random number)
        sem_wait(&empty);    // Wait for space in the buffer
        sem_wait(&mutex);    // Lock the buffer for producing
        buffer[in] = item;
        printf("Producer produced: %d at index %d\n", item, in);
        in = (in + 1) % MAX_BUFFER_SIZE; // Circular buffer
        sem_post(&mutex);                // Unlock the buffer
        sem_post(&full);                 // Signal that the buffer has an item
        sleep(1);                        // Simulate time taken to produce an item
    }
}

// Consumer function
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);  // Wait for items in the buffer
        sem_wait(&mutex); // Lock the buffer for consuming
        item = buffer[out];
        printf("Consumer consumed: %d from index %d\n", item, out);
        out = (out + 1) % MAX_BUFFER_SIZE; // Circular buffer
        sem_post(&mutex);                  // Unlock the buffer
        sem_post(&empty);                  // Signal that there is space in the buffer
        sleep(1);                          // Simulate time taken to consume an item
    }
}

int main()
{
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, MAX_BUFFER_SIZE); // Buffer has MAX_BUFFER_SIZE empty spaces
    sem_init(&full, 0, 0);                // No items in buffer initially
    sem_init(&mutex, 0, 1);               // Mutex for critical section, initially unlocked

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish (which they won't in this infinite loop)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores (will never reach here in this code)
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

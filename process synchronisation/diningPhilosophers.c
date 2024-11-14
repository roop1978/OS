#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t mutex;                   // Mutex for critical section
sem_t forks[NUM_PHILOSOPHERS]; // Semaphore for each fork

// Function to simulate philosopher's actions
void *philosopher(void *num)
{
    int phil = *((int *)num);
    int left = phil;
    int right = (phil + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Think for a while
        printf("Philosopher %d is thinking...\n", phil);
        sleep(rand() % 3);

        // Pick up forks (left and right)
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        // Eating
        printf("Philosopher %d is eating using forks %d and %d\n", phil, left, right);
        sleep(rand() % 3); // Simulate time taken to eat

        // Put down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);

        // Go back to thinking
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int phil_nums[NUM_PHILOSOPHERS];

    // Initialize the semaphores
    sem_init(&mutex, 0, 1); // Initialize mutex for mutual exclusion
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1); // Each fork starts as available
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        phil_nums[i] = i; // Assign philosopher numbers
        pthread_create(&philosophers[i], NULL, philosopher, &phil_nums[i]);
    }

    // Wait for all philosopher threads to finish (they won’t in this case)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (this part will never be reached due to infinite loop)
    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex;        // To protect the critical section of reader count
sem_t wrt;          // To give writers exclusive access
int read_count = 0; // Number of readers currently reading

// Reader function
void *reader(void *arg)
{
    int reader_id = *((int *)arg);
    while (1)
    {
        // Reader waits for writers to finish (not interrupting any writers)
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
        {
            // If this is the first reader, block writers
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Read the shared resource (simulated by printing)
        printf("Reader %d is reading.\n", reader_id);
        sleep(1); // Simulate reading

        // Done reading, decrement read_count
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0)
        {
            // If this is the last reader, allow writers
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(1); // Simulate time between reading
    }
}

// Writer function
void *writer(void *arg)
{
    int writer_id = *((int *)arg);
    while (1)
    {
        // Writer needs exclusive access
        sem_wait(&wrt);

        // Write to the shared resource (simulated by printing)
        printf("Writer %d is writing.\n", writer_id);
        sleep(2); // Simulate writing

        // Done writing
        sem_post(&wrt);

        sleep(1); // Simulate time between writing
    }
}

int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Protect reader count
    sem_init(&wrt, 0, 1);   // Control access to the resource (writers exclusive)

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish (in a real program, you'd have to add a way to terminate threads)
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores (although the program won't reach this point)
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

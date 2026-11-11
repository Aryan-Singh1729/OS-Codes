#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    for (int i = 1; i <= 5; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 1; i <= 5; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// 1. Theory: Thread synchronization is a technique used in operating systems to coordinate the execution of multiple threads when they share common resources. A thread is the smallest unit of execution within a process, and multiple threads can execute concurrently. When two or more threads access and modify shared data simultaneously without proper synchronization, a race condition may occur, producing incorrect or unpredictable results. To prevent this, synchronization mechanisms such as semaphores and mutexes are used. A semaphore is a synchronization variable that controls access to shared resources through two operations: sem_wait(), which decreases the semaphore count when a permit is available or blocks the thread when the count is zero, and sem_post(), which increases the semaphore count and may wake a waiting thread. A counting semaphore can maintain values greater than one and is used to manage multiple available resources. A mutex (Mutual Exclusion) is a locking mechanism that allows only one thread to access a critical section at a time. A critical section is the portion of a program where shared resources are accessed or modified. The Producer-Consumer Problem is a classical synchronization problem involving two types of threads: a producer and a consumer. The producer generates items and places them into a shared buffer, while the consumer removes and processes those items. The buffer has a limited capacity, so the producer cannot insert new items when the buffer is full, and the consumer cannot remove items when the buffer is empty. For example, consider a buffer containing five slots. Initially, all five slots are empty. The producer starts generating items and placing them into the buffer. If all five slots become occupied, the producer must wait until the consumer removes an item and creates an empty slot. Similarly, if the consumer tries to remove an item when the buffer is empty, it must wait until the producer inserts a new item. Without synchronization, both threads might access the same buffer position simultaneously, leading to incorrect data or inconsistent buffer management. To solve this problem, two counting semaphores, named empty and full, are used. The empty semaphore keeps track of the number of available empty slots and is initially set to five, while the full semaphore keeps track of occupied slots and is initially set to zero. Before producing an item, the producer decreases empty, and after inserting the item, it increases full. Similarly, before consuming an item, the consumer decreases full, and after removing the item, it increases empty. A mutex is used to ensure that only one thread accesses the shared buffer at a time, preventing race conditions. The buffer is implemented as a circular buffer, meaning that after reaching the last position, the insertion or removal index returns to the first position using the modulo operator %. This allows the same buffer positions to be reused efficiently. Therefore, the Producer-Consumer Problem demonstrates how counting semaphores manage resource availability and how mutex locks provide mutual exclusion, ensuring safe communication and coordination between concurrent threads.

// 2. Code Explanation: The program begins by including four header files: stdio.h, pthread.h, semaphore.h, and unistd.h. The stdio.h header provides the printf() function for displaying output, pthread.h provides functions for creating and managing threads, and semaphore.h provides semaphore operations. The unistd.h header provides functions such as sleep(), although it is not directly used in this program. The statement #define SIZE 5 defines the maximum capacity of the shared buffer as five elements. The array int buffer[SIZE] stores the items produced by the producer, while the variables in and out, initially set to zero, represent the positions where items are inserted and removed. The statement sem_t empty, full declares two counting semaphores used to manage empty and occupied buffer slots. The statement pthread_mutex_t mutex declares a mutex that protects the shared buffer from simultaneous access. The producer function void *producer(void *arg) generates five items using a for loop that runs from 1 to 5. Before inserting an item, sem_wait(&empty) checks whether an empty slot is available and decreases the number of available slots. If the buffer is full, the producer waits until the consumer removes an item. The statement pthread_mutex_lock(&mutex) locks the critical section so that the consumer cannot access the shared buffer simultaneously. The statement buffer[in] = i inserts the current item into the buffer at index in, and printf("Produced: %d\n", i) displays the produced item. The expression in = (in + 1) % SIZE updates the insertion position circularly, ensuring that the index returns to zero after reaching the last position. After inserting the item, pthread_mutex_unlock(&mutex) releases the mutex, allowing the consumer to access the buffer. The statement sem_post(&full) increases the number of occupied slots and allows a waiting consumer to proceed. The consumer function void *consumer(void *arg) also executes a loop five times to remove the items produced by the producer. The statement sem_wait(&full) checks whether an item is available and decreases the count of occupied slots. If the buffer is empty, the consumer waits until the producer inserts an item. The statement pthread_mutex_lock(&mutex) locks the critical section before accessing the buffer. The statement int item = buffer[out] retrieves an item from the current removal position, while printf("Consumed: %d\n", item) displays the consumed item. The expression out = (out + 1) % SIZE updates the removal position circularly. After consuming the item, pthread_mutex_unlock(&mutex) releases the mutex, and sem_post(&empty) increases the number of available empty slots so that the producer can insert another item. Both functions return NULL after completing their execution. In the main function, pthread_t p, c declares two thread identifiers representing the producer and consumer threads. The statement sem_init(&empty, 0, SIZE) initializes the empty semaphore to five because all buffer slots are initially available, while sem_init(&full, 0, 0) initializes the full semaphore to zero because the buffer initially contains no items. The second argument 0 specifies that the semaphores are shared between threads of the same process. The statement pthread_mutex_init(&mutex, NULL) initializes the mutex using default attributes. The function pthread_create(&p, NULL, producer, NULL) creates the producer thread, while pthread_create(&c, NULL, consumer, NULL) creates the consumer thread. Both threads execute concurrently and communicate through the shared buffer. The statements pthread_join(p, NULL) and pthread_join(c, NULL) make the main thread wait until both threads complete their execution. Finally, sem_destroy(&empty) and sem_destroy(&full) release the semaphore resources, while pthread_mutex_destroy(&mutex) destroys the mutex. The statement return 0 indicates successful program execution. Thus, the program demonstrates how counting semaphores prevent buffer overflow and underflow, while a mutex ensures mutual exclusion and prevents race conditions during shared buffer access.
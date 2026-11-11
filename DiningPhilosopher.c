#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t ch[5];

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    int left, right;

    printf("\n%d philosopher is created\n", i);

    left = i;
    right = (i + 1) % 5;

    printf("\n%d philosopher is hungry\n", i);

    sem_wait(&ch[left]);
    sem_wait(&ch[right]);

    printf("\n%d philosopher is eating\n", i);

    sleep(5);

    sem_post(&ch[right]);
    sem_post(&ch[left]);

    printf("\n%d philosopher is complete\n", i);

    return NULL;
}

int main()
{
    int i;
    int id[5];
    pthread_t pid[5];

    for(i = 0; i < 5; i++)
        sem_init(&ch[i], 0, 1);

    for(i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&pid[i], NULL, philosopher, &id[i]);
        sleep(i);
    }

    for(i = 0; i < 5; i++)
        pthread_join(pid[i], NULL);

    return 0;
}


/*
Sample Output
Philosopher 1 is thinking
Philosopher 2 is thinking
Philosopher 3 is thinking
Philosopher 4 is thinking
Philosopher 5 is thinking

Philosopher 1 is eating
Philosopher 3 is eating
Philosopher 1 finished eating
Philosopher 3 finished eating

Philosopher 2 is eating
Philosopher 4 is eating
Philosopher 2 finished eating
Philosopher 4 finished eating

Philosopher 5 is eating
Philosopher 5 finished eating

The sample output shows how 5 philosophers share 5 forks without deadlock.

1. Thinking: Initially, all five philosophers are thinking and waiting for their turn to eat.
2. Eating: Philosophers 1 and 3 start eating simultaneously because they use different forks.
3. Finished Eating: Philosophers 1 and 3 finish eating and release their forks using sem_post().
4. Next Turn: Philosophers 2 and 4 acquire the available forks and start eating.
5. Last Philosopher: Philosopher 5 gets the required forks and finishes eating.
Conclusion: All five philosophers successfully finish eating without deadlock. Multiple philosophers can eat simultaneously if their required forks are available.
Note: The order of execution may change because threads run concurrently.
*/


// 1. Theory: Thread synchronization is a technique used in operating systems to coordinate multiple threads when they share common resources. When multiple threads try to access the same resource simultaneously, problems such as race conditions, deadlock, and starvation may occur. A deadlock is a situation where two or more threads wait indefinitely for resources held by one another, preventing further execution. Starvation occurs when a thread keeps waiting for a resource because other threads repeatedly obtain access to it. The Dining Philosophers Problem is a classical synchronization problem that demonstrates how deadlock can occur when multiple threads compete for limited resources. In this problem, five philosophers sit around a circular table, with five forks placed between them. Each philosopher performs two activities: thinking and eating. A philosopher does not need any forks while thinking, but to eat, they must acquire two forks, one from their left side and one from their right side. Since each fork is shared between two neighboring philosophers, only one philosopher can use a particular fork at a time. The problem occurs when all five philosophers become hungry simultaneously and each picks up their left fork. Now every philosopher holds one fork and waits for their right fork, which is already held by the neighboring philosopher. Consequently, none of the philosophers can eat or release their forks, resulting in deadlock. Deadlock occurs when four conditions exist simultaneously: mutual exclusion, where only one thread can use a resource at a time; hold and wait, where a thread holds one resource while waiting for another; no preemption, where a resource cannot be forcibly taken away; and circular wait, where each thread waits for a resource held by another thread in a circular chain. To manage access to shared resources, we use semaphores, which are synchronization variables that control resource availability. Semaphores use two main operations: sem_wait(), which acquires a resource or blocks the thread if it is unavailable, and sem_post(), which releases a resource and may wake a waiting thread. A binary semaphore is initialized to one and can be used to ensure that only one philosopher accesses a particular fork at a time. In this program, five binary semaphores represent the five forks, and each philosopher must successfully acquire both forks before eating. Once eating is completed, the philosopher releases both forks, allowing other philosophers to use them. The program also uses the sleep() function to introduce delays, which helps demonstrate concurrent execution and resource competition. However, the given implementation does not guarantee deadlock prevention, because every philosopher attempts to acquire the left fork before the right fork. If all philosophers acquire their left forks simultaneously, circular waiting can still occur. The delays between thread creation reduce the likelihood of this situation during typical execution but do not provide a guaranteed deadlock-free solution. Thus, the Dining Philosophers Problem demonstrates the importance of thread synchronization, mutual exclusion, semaphores, resource sharing, and deadlock handling in operating systems.

// 2. Code Explanation: The program begins by including four header files: unistd.h, pthread.h, stdio.h, and semaphore.h. The unistd.h header provides the sleep() function, pthread.h provides functions for creating and managing threads, stdio.h provides the printf() function, and semaphore.h provides semaphore operations. The statement sem_t ch[5] declares an array of five semaphores, where each semaphore represents one fork shared between neighboring philosophers. The function void *philosopher(void *arg) defines the actions performed by each philosopher thread. Inside this function, int i = *(int *)arg retrieves the philosopher's identification number from the argument passed during thread creation. Two integer variables, left and right, are declared to store the indices of the forks required by the philosopher. The statement printf("\n%d philosopher is created\n", i) displays a message indicating that the philosopher thread has started execution. The statement left = i assigns the philosopher's own index as the left fork, while right = (i + 1) % 5 calculates the right fork's index. The modulo operator % ensures circular indexing so that philosopher 4 uses fork 0 as the right fork instead of accessing an invalid index. The next printf() statement displays that the philosopher is hungry and wants to eat. The statement sem_wait(&ch[left]) attempts to acquire the left fork, while sem_wait(&ch[right]) attempts to acquire the right fork. If a fork is already being used by another philosopher, the thread waits until it becomes available. Once both forks are acquired, the program displays that the philosopher is eating using printf(). The statement sleep(5) introduces a five-second delay to simulate the time taken by the philosopher to eat. After eating, sem_post(&ch[right]) releases the right fork, and sem_post(&ch[left]) releases the left fork, allowing neighboring philosophers to acquire them. The program then displays that the philosopher has completed eating and returns NULL, indicating the completion of that thread. In the main function, the variable int i is used as a loop counter, int id[5] stores the identification numbers of all five philosophers, and pthread_t pid[5] declares an array of five thread identifiers. The first for loop initializes all five semaphores using sem_init(&ch[i], 0, 1). Here, the first argument specifies the semaphore, the second argument 0 indicates that it is shared between threads of the same process, and the third argument 1 indicates that each fork is initially available. The second for loop creates five philosopher threads. The statement id[i] = i assigns a unique identification number to each philosopher, while pthread_create(&pid[i], NULL, philosopher, &id[i]) creates a new thread that executes the philosopher() function. The arguments specify the thread identifier, default thread attributes, function to execute, and argument passed to that function. The statement sleep(i) introduces a delay after creating each thread, with delay values of 0, 1, 2, 3, and 4 seconds. This separates thread creation times and reduces the chances of all philosophers attempting to acquire forks simultaneously, although it does not guarantee deadlock prevention. The final for loop uses pthread_join(pid[i], NULL) to make the main thread wait until every philosopher thread finishes execution. Finally, the program returns 0 to indicate successful completion. Therefore, this program demonstrates how multiple philosopher threads compete for shared forks and how semaphores provide mutual exclusion by allowing only one philosopher to use a particular fork at a time. However, a guaranteed deadlock-free implementation would require an additional mechanism, such as limiting the number of philosophers attempting to acquire forks to four or enforcing a consistent order of fork acquisition.
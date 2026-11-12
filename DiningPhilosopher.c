#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t forks[5],room;

void *philosopher(void *arg){
  int id = *(int *)arg;
  for(int i=0;i<3;i++){
    printf("Philosopher %d is thinking.\n",id);
    sleep(1);
    sem_wait(&room);
    sem_wait(&forks[i]);
    sem_wait(&forks[(i+1)%5]);
    printf("Philosopher %d is eating.\n",id);
    sleep(2);
    printf("Philosopher %d has finished.\n",id);
    sem_post(&forks[(i+1)%5]);
    sem_post(&forks[i]);
    sem_post(&room);
  }
  return NULL;
}

int main(){
  pthread_t t[5];
  int id[5];
  sem_init(&room,0,4);
  for(int i=0;i<5;i++){ sem_init(&forks[i],0,1); }
  for(int i=0;i<5;i++){
    id[i] = i;
    pthread_create(&t[i],NULL,philosopher,&id[i]);
  }
  for(int i=0;i<5;i++){ pthread_join(t[i],NULL); }
  return 0;
}




// 1. Theory: Thread synchronization is a technique used in operating systems to coordinate multiple threads when they share common resources. When several threads try to access the same resource simultaneously, problems such as race conditions, deadlock, and starvation may occur. A deadlock is a situation where two or more threads wait indefinitely for resources held by one another, preventing them from completing their execution. Starvation occurs when a thread keeps waiting for a resource because other threads repeatedly get access to it. The Dining Philosophers Problem is a classical synchronization problem used to demonstrate how deadlock can occur when multiple threads compete for limited resources. In this problem, five philosophers sit around a circular table with five forks placed between them. Each philosopher performs two activities: thinking and eating. While thinking, a philosopher does not require any forks, but to eat, they must acquire two forks, one from their left side and one from their right side. Since each fork is shared between two neighboring philosophers, only one philosopher can use a particular fork at a time. The problem occurs when all five philosophers become hungry simultaneously and each picks up one fork. Now every philosopher holds one fork and waits for the second fork, which is already held by a neighboring philosopher. Consequently, none of them can eat or release their forks, resulting in deadlock. Deadlock occurs when four conditions exist simultaneously: mutual exclusion, where only one thread can use a resource at a time; hold and wait, where a thread holds one resource while waiting for another; no preemption, where a resource cannot be forcibly taken away; and circular wait, where threads wait for resources held by one another in a circular chain. To prevent this problem, the program uses semaphores, which are synchronization variables that control access to shared resources. The sem_wait() operation acquires an available permit or blocks the thread if none is available, while sem_post() releases a permit and may wake a waiting thread. A binary semaphore is initialized to one and allows only one philosopher to access a particular fork at a time. A counting semaphore can maintain multiple permits and control how many threads are allowed to proceed simultaneously. In this program, five binary semaphores represent the five forks, while an additional counting semaphore named room is initialized to four. This allows at most four philosophers to attempt to acquire forks simultaneously, preventing the situation where all five philosophers hold one fork each and wait for another. In the standard Dining Philosophers solution, this restriction prevents circular waiting and guarantees freedom from deadlock. After eating, each philosopher releases both forks and the room permit, allowing other philosophers to proceed. Each philosopher repeats the thinking and eating cycle three times. However, starvation may still occur in general because semaphores do not necessarily guarantee fair scheduling. An important detail in the given code is that the forks are selected using the loop variable i instead of the philosopher's id. Therefore, the code does not correctly assign a fixed pair of neighboring forks to each philosopher, although its semaphore operations still protect the forks from simultaneous use. Thus, the Dining Philosophers Problem demonstrates thread synchronization, mutual exclusion, resource sharing, and deadlock prevention using semaphores.

// 2. Code Explanation: The program begins by including four header files: stdio.h, semaphore.h, pthread.h, and unistd.h. The stdio.h header provides the printf() function for displaying messages, semaphore.h provides semaphore functions, pthread.h provides functions for creating and managing threads, and unistd.h provides the sleep() function. The statement sem_t forks[5], room declares five semaphores representing the forks and one additional semaphore named room to limit the number of philosophers attempting to eat simultaneously. The function void *philosopher(void *arg) defines the activities performed by each philosopher thread. Inside this function, int id = *(int *)arg retrieves the philosopher's identification number from the argument passed during thread creation. The for(int i=0; i<3; i++) loop makes each philosopher repeat the thinking and eating process three times. The statement printf("Philosopher %d is thinking.\n", id) displays that the philosopher is thinking, while sleep(1) introduces a one-second delay to simulate thinking. The statement sem_wait(&room) checks whether a room permit is available. Since room is initialized to four, at most four philosophers can enter the fork-acquisition section simultaneously. The statements sem_wait(&forks[i]) and sem_wait(&forks[(i+1)%5]) attempt to acquire two forks. If a fork is already being used by another philosopher, the thread waits until it becomes available. The modulo operator % ensures circular indexing, meaning that after fork 4, the next fork is fork 0. However, in this code, i represents the loop iteration rather than the philosopher's identification number. Therefore, during the first iteration, every philosopher attempts to acquire forks 0 and 1; during the second iteration, forks 1 and 2; and during the third iteration, forks 2 and 3. For the correct Dining Philosophers implementation, these statements should use forks[id] and forks[(id+1)%5], so each philosopher acquires their own two neighboring forks. Once both forks have been acquired, printf("Philosopher %d is eating.\n", id) displays that the philosopher is eating, and sleep(2) introduces a two-second delay to simulate eating. The next printf() statement displays that the philosopher has finished eating. The statements sem_post(&forks[(i+1)%5]) and sem_post(&forks[i]) release both acquired forks, making them available to other philosophers. The statement sem_post(&room) releases the room permit, allowing another philosopher to attempt eating. After completing three iterations, the function returns NULL, indicating that the thread has finished execution. In the main function, pthread_t t[5] declares an array of five thread identifiers, while int id[5] stores the identification numbers of the philosophers. The statement sem_init(&room, 0, 4) initializes the counting semaphore with four permits. Here, 0 indicates that the semaphore is shared between threads of the same process, and 4 specifies the maximum number of available room permits. The first for loop initializes all five fork semaphores using sem_init(&forks[i], 0, 1), where the value 1 indicates that each fork is initially available. The second for loop assigns a unique identification number to each philosopher using id[i] = i and creates the philosopher threads using pthread_create(&t[i], NULL, philosopher, &id[i]). This function creates a new thread, uses default thread attributes, executes the philosopher() function, and passes the philosopher's identification number as an argument. All five threads execute concurrently and compete for the available forks. The final for loop uses pthread_join(t[i], NULL) to make the main thread wait until all five philosopher threads complete their execution. Finally, return 0 terminates the program successfully. Thus, the program demonstrates how binary semaphores control access to individual forks and how a counting semaphore limits the number of philosophers competing for resources. With the fork-index correction mentioned above, it implements the standard deadlock-free Dining Philosophers solution using semaphores./

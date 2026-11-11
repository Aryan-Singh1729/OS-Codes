
#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10];
    int count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    while (count < n) {
        found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                        break;

                if (j == m) {
                    for (k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    if (count == n) {
        printf("\nSystem is in Safe State.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else {
        printf("\nSystem is in Unsafe State.");
    }

    return 0;
}



/*
Sample Input:-
Number of processes: 5
Number of resources: 3

Allocation Matrix
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Maximum Matrix
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Available Resources
3 3 2

Sample Output
System is in Safe State.
Safe Sequence: P1 P3 P4 P0 P2
*/




// 1. Theory: Deadlock avoidance is a technique used in operating systems to prevent situations where processes get stuck while waiting for resources. A deadlock occurs when two or more processes keep waiting for resources held by one another, and none of them can continue execution. For example, suppose Process P1 is holding a printer and waiting for a scanner, while Process P2 is holding the scanner and waiting for the printer. Both processes keep waiting for each other, resulting in deadlock. To avoid such situations, operating systems can use the Banker's Algorithm, which is a deadlock avoidance algorithm developed by Edsger Dijkstra. The algorithm is called the Banker's Algorithm because it works similarly to how a bank gives loans to customers. A bank has a limited amount of money, and several customers may request loans. Before giving a loan, the bank checks whether it will still have enough money to eventually satisfy all its customers. Similarly, an operating system has limited resources, such as memory, printers, and other devices, that must be shared among different processes. The Banker's Algorithm helps the operating system decide whether resources can be allocated safely without creating a possible deadlock situation. The main concept of this algorithm is the safe state. A safe state means that there is at least one possible order in which all processes can obtain their required resources, finish their work, and release their resources. This order is called a safe sequence. An unsafe state means that the system cannot find any sequence that guarantees the completion of all processes. However, an unsafe state does not always mean that deadlock has already occurred; it means that deadlock may occur in the future. The Banker's Algorithm uses four important data structures. The Allocation Matrix shows how many resources are currently given to each process. The Maximum Matrix shows the maximum number of resources that each process may require to complete its execution. The Need Matrix shows how many additional resources each process still requires to finish its work. It is calculated using the formula Need = Maximum − Allocation. The Available Vector shows how many resources are currently free and can be given to processes. The algorithm also uses a Finish Array to keep track of which processes have completed and a Safe Sequence Array to store the order in which processes can safely finish. The working of the algorithm is simple. First, it takes the number of processes, resource types, allocated resources, maximum required resources, and available resources as input. It then calculates the Need Matrix for every process. After that, it searches for a process whose remaining resource requirements are less than or equal to the available resources. If such a process is found, the algorithm assumes that the process gets the resources it needs, completes its execution, and releases all the resources it was holding. These released resources are added to the available resources, allowing other processes to execute. The same procedure is repeated until all processes finish or no further process can complete. For example, suppose there are five processes named P0, P1, P2, P3, and P4. Initially, some resources are already allocated to these processes, and the system has a limited number of free resources. If the available resources are sufficient for P1, the algorithm allows P1 to complete first. After P1 finishes, it releases its resources, which may now be enough for P3 to complete. Similarly, P3 releases its resources, allowing P4 to complete, followed by P0 and P2. Therefore, P1 → P3 → P4 → P0 → P2 becomes a safe sequence. Since all processes can complete successfully in this order, the system is considered to be in a safe state. However, if some processes are still incomplete and none of them can get enough resources to finish, the algorithm stops and declares the system to be in an unsafe state. In the complete Banker's Algorithm, whenever a process requests additional resources, the operating system temporarily checks what would happen if those resources were allocated. If the system remains safe, the request can be accepted; otherwise, the process must wait. The given C program implements the safety-checking part of the Banker's Algorithm, which checks whether the current allocation of resources is safe and displays a possible safe sequence. The main advantage of the Banker's Algorithm is that it helps avoid deadlock by carefully managing limited resources. However, it requires the maximum resource requirements of every process to be known in advance. Thus, the Banker's Algorithm helps operating systems manage resources safely and ensures that processes can complete their work in a suitable order without getting stuck due to deadlock.

// 2. Code Explanation: The program begins by including the header file stdio.h, which provides functions like printf() and scanf() for input and output operations. Inside the main function, the variables n and m store the number of processes and resource types, while i, j, and k are used as loop counters. Three two-dimensional arrays are declared: alloc[10][10], max[10][10], and need[10][10]. The Allocation Matrix (alloc) stores the resources currently allocated to each process, the Maximum Matrix (max) stores the maximum resources each process may require, and the Need Matrix (need) stores the additional resources required by each process to complete its execution. The array avail[10] stores the currently available resources, while finish[10] = {0} keeps track of completed processes. Initially, all values in finish are zero, indicating that no process has completed. The array safe[10] stores the safe sequence of processes. The variable count is initialized to zero and counts the number of completed processes, while found indicates whether at least one process can complete during the current round. The program first accepts the number of processes and resource types using scanf(). It then uses nested for loops to accept the Allocation Matrix and Maximum Matrix, followed by the Available Vector. After taking the inputs, the program calculates the Need Matrix using the formula need[i][j] = max[i][j] - alloc[i][j]. This determines how many more resources each process needs to complete. For example, if a process requires a maximum of 7 resources and already has 3, its remaining need is 4. The program then begins the Banker's safety algorithm using the while (count < n) loop, which continues until all processes complete or no further process can execute safely. At the beginning of each round, found = 0 indicates that no suitable process has been found yet. The program checks every process using a for loop, and the condition if (finish[i] == 0) ensures that only incomplete processes are considered. For each incomplete process, another loop compares its remaining requirements with the available resources. The condition if (need[i][j] > avail[j]) checks whether the process requires more resources than are currently available. If any required resource is insufficient, the break statement stops checking that process. However, if all required resources are available, the condition if (j == m) becomes true, meaning the process can complete its execution. The statement avail[k] += alloc[i][k] then adds the resources held by the completed process back to the available resources. These released resources can be used by other processes. The statement safe[count++] = i stores the completed process in the safe sequence and increases the completed process count. The statement finish[i] = 1 marks the process as completed, while found = 1 indicates that at least one process completed during the current round. The algorithm continues checking the remaining processes and repeats the procedure until all processes finish or no further process can complete. The condition if (found == 0) stops the loop when no process can be completed using the available resources. After the loop, if (count == n) checks whether all processes have completed. If true, the program displays "System is in Safe State" and prints the safe sequence. Otherwise, it displays "System is in Unsafe State", indicating that no complete safe sequence could be found. For the given sample input, the algorithm finds the safe sequence P1 → P3 → P4 → P0 → P2, showing that all five processes can finish successfully. Finally, return 0 terminates the program. Thus, the program demonstrates how the Banker's Algorithm calculates resource requirements, checks resource availability, identifies a safe sequence, and determines whether the system is in a safe or unsafe state.
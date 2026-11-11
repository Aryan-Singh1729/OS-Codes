
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int ch, n, a[100], temp;
    pid_t pid;

    printf("1. Sorting with fork and wait\n");
    printf("2. Zombie Process\n");
    printf("3. Orphan Process\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    if (ch == 1) {
        printf("Enter number of elements: ");
        scanf("%d", &n);

        printf("Enter elements: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
    }

    pid = fork();  // Create child process

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (ch == 1) {
        // Sorting using Bubble Sort
        if (pid == 0) {
            // Child: Descending order
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                    if (a[i] < a[j]) {
                        temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                    }

            printf("Child (Descending): ");
        }
        else {
            // Parent: Ascending order
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                    if (a[i] > a[j]) {
                        temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                    }

            printf("Parent (Ascending): ");
        }

        for (int i = 0; i < n; i++)
            printf("%d ", a[i]);
        printf("\n");

        if (pid > 0)
            wait(NULL);  // Parent waits for child
    }

    else if (ch == 2) {
        // Zombie: Child exits, parent stays alive
        if (pid == 0) {
            printf("Child finished\n");
            exit(0);
        }
        else {
            printf("Parent sleeping for 20 seconds\n");
            sleep(20);  // Child becomes zombie
            wait(NULL); // Collect child status
        }
    }

    else if (ch == 3) {
        // Orphan: Parent exits, child stays alive
        if (pid == 0) {
            sleep(5);
            printf("Orphan Child, New PPID: %d\n", getppid());
        }
        else {
            printf("Parent exiting\n");
            exit(0);
        }
    }

    return 0;
}


// 1. Process Management, fork(), wait() and Sorting: Process management is an important function of an operating system that involves creating, executing, and terminating processes. A process is a program currently being executed. In this program, stdio.h is used for input and output, unistd.h provides fork(), sleep(), and getppid(), stdlib.h provides exit(), and sys/wait.h provides wait(). The program first displays a menu containing three options: Sorting, Zombie Process, and Orphan Process. When the user selects sorting, the program accepts the number of elements and stores them in an array. The fork() system call creates a new child process by duplicating the existing parent process. It returns 0 to the child process, a positive value (child's PID) to the parent process, and -1 if process creation fails. Both processes execute independently and have separate copies of the array. The child process (pid == 0) sorts the elements in descending order, while the parent process (pid > 0) sorts them in ascending order. The program uses nested loops to compare array elements and swaps them using a temporary variable. The sorted arrays are displayed using a for loop. Finally, the parent calls wait(NULL), which makes it wait until the child terminates and collects its exit status. This demonstrates process creation, independent execution, sorting, and process synchronization using fork() and wait(). Note: In the given code, the parent's swapping logic contains a mistake: a[i] = a[j] is written twice. The second assignment should be a[j] = temp for ascending sorting to work correctly.

// 2. Zombie Process and Orphan Process: A zombie process is a child process that has completed its execution but whose parent has not yet collected its exit status using wait(). When the user selects option 2, the fork() system call creates a child process. The child immediately prints "Child finished" and terminates using exit(0), where 0 indicates successful termination. Meanwhile, the parent executes sleep(20), which pauses it for 20 seconds without calling wait(). During this period, the terminated child remains in the process table as a zombie because its exit status has not been collected. After 20 seconds, the parent executes wait(NULL), which collects the child's termination status and removes the zombie entry. An orphan process, on the other hand, is a child process whose original parent has terminated while the child is still running. When the user selects option 3, fork() creates a child process. The parent immediately prints "Parent exiting" and terminates using exit(0), while the child executes sleep(5) and remains active. Since the parent terminates before the child, the child becomes an orphan process and is adopted by another system process, such as init, systemd, or a designated subreaper. After five seconds, the child uses getppid() to display its new Parent Process ID (PPID). Thus, the program demonstrates that a zombie occurs when the child finishes before the parent collects its status, whereas an orphan occurs when the parent terminates before the child.
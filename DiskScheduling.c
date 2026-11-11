
#include <stdio.h>
#include <stdlib.h>

int head, total;

void move(int x) {
    total += abs(head - x);
    head = x;
    printf(" -> %d", x);
}

int main() {
    int n, start, size, a[100], b[100], done[100] = {0};
    int i, j, k, best, temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) return 1;

    printf("Enter requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    printf("Enter initial head position: ");
    scanf("%d", &start);

    printf("Enter disk size: ");
    scanf("%d", &size);

    if (size <= 0 || start < 0 || start >= size)
        return 1;

    for (i = 0; i < n; i++)
        if (a[i] < 0 || a[i] >= size)
            return 1;

    // SSTF
    head = start;
    total = 0;
    printf("\nSSTF: %d", head);

    for (i = 0; i < n; i++) {
        best = -1;

        for (j = 0; j < n; j++)
            if (!done[j] && (best == -1 ||
                abs(a[j] - head) < abs(a[best] - head)))
                best = j;

        move(a[best]);
        done[best] = 1;
    }

    printf("\nTotal Movement: %d\n", total);

    // Sort requests
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (b[i] > b[j]) {
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }

    // Find first request >= head
    k = 0;
    while (k < n && b[k] < start)
        k++;

    // SCAN
    head = start;
    total = 0;
    printf("\nSCAN: %d", head);

    for (i = k; i < n; i++)
        move(b[i]);

    move(size - 1);

    for (i = k - 1; i >= 0; i--)
        move(b[i]);

    printf("\nTotal Movement: %d\n", total);

    // C-LOOK
    head = start;
    total = 0;
    printf("\nC-LOOK: %d", head);

    for (i = k; i < n; i++)
        move(b[i]);

    for (i = 0; i < k; i++)
        move(b[i]);

    printf("\nTotal Movement: %d\n", total);

    return 0;
}



/*
Sample Input
Enter number of requests: 8
Enter requests: 98 183 37 122 14 124 65 67
Enter initial head position: 53
Enter disk size: 200


Sample Output
SSTF: 53 -> 65 -> 67 -> 37 -> 14 -> 98 -> 122 -> 124 -> 183
Total Movement: 236

SCAN: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 199 -> 37 -> 14
Total Movement: 331

C-LOOK: 53 -> 65 -> 67 -> 98 -> 122 -> 124 -> 183 -> 14 -> 37
Total Movement: 322
*/




// 1. Theory: Disk scheduling is a technique used in operating systems to decide the order in which disk read and write requests should be processed. In a traditional Hard Disk Drive (HDD), data is stored on rotating magnetic disks called platters, which are divided into tracks and sectors. A disk head is used to read and write data, and it moves across different tracks to access the requested information. When multiple processes request data from different disk locations, the operating system must decide which request should be completed first. This is called Disk Scheduling. The main objective of disk scheduling is to reduce the total movement of the disk head, minimize waiting time, and improve disk performance. The time required to move the disk head to the required track is called seek time, and the total distance travelled by the disk head is called total head movement. Generally, reducing head movement helps reduce seek time and improves performance. There are several disk scheduling algorithms, including FCFS, SSTF, SCAN, C-SCAN, LOOK, and C-LOOK. In this assignment, three algorithms are implemented: SSTF, SCAN, and C-LOOK. The SSTF (Shortest Seek Time First) algorithm selects the disk request that is closest to the current head position. For example, if the disk head is at position 53 and requests are present at positions 65, 98, and 14, SSTF selects 65 because it is the nearest request. After completing that request, it again searches for the nearest remaining request. This process continues until all requests are completed. The main advantage of SSTF is that it generally reduces unnecessary head movement compared to FCFS. However, it may cause starvation, where requests located far from the current head position keep waiting because new nearby requests are repeatedly selected. The SCAN Algorithm, also known as the Elevator Algorithm, works similarly to an elevator moving between floors. The disk head moves in one direction and services all requests encountered along its path. When it reaches the end of the disk, it reverses direction and services the remaining requests. In this assignment, the disk head initially moves towards higher-numbered tracks, as specified by the question. For example, if the head starts at position 53, it first services requests at positions 65, 67, 98, 122, 124, and 183. It then continues to the last disk position, 199, before reversing direction to service requests at 37 and 14. SCAN provides more predictable waiting times than SSTF because requests are serviced according to the movement direction of the disk head. The C-LOOK (Circular LOOK) algorithm is another disk scheduling technique in which the disk head moves in only one servicing direction. It first services all requests in the increasing direction, but unlike SCAN, it does not continue to the physical end of the disk if there are no more requests. After servicing the highest requested track, the head jumps directly to the lowest pending request and continues moving in the increasing direction. For example, starting from position 53, the head services 65, 67, 98, 122, 124, and 183. After reaching 183, it jumps to 14 and then services 37. The movement during this jump is also counted in the total head movement. C-LOOK avoids unnecessary movement to the physical disk boundaries and provides a more uniform direction of service. The total head movement for all three algorithms is calculated by adding the absolute differences between consecutive head positions using the formula Total Head Movement = Σ |Current Head Position − Next Head Position|. For the given sample input, SSTF produces a total head movement of 236 tracks, SCAN produces 331 tracks, and C-LOOK produces 322 tracks. Thus, disk scheduling algorithms help operating systems manage disk requests efficiently by selecting suitable head movement paths, reducing seek time, and improving the overall performance of traditional hard disk drives.

// 2. Code Explanation: The program begins by including two header files: stdio.h, which provides functions such as printf() and scanf() for input and output, and stdlib.h, which provides the abs() function to calculate the absolute value of a number. Two global variables, head and total, are declared to store the current disk head position and the total head movement. The function void move(int x) is created to move the disk head to a new position. Inside this function, total += abs(head - x) calculates the distance between the current head position and the requested position and adds it to the total movement. The statement head = x updates the current head position, while printf(" -> %d", x) displays the movement sequence. Inside the main function, the variables n, start, and size store the number of disk requests, initial head position, and total disk size. The arrays a[100] and b[100] store the disk requests, while done[100] = {0} keeps track of requests completed by the SSTF algorithm. Initially, all values in done are zero, indicating that no request has been processed. The variables i, j, and k are used as loop counters, best stores the index of the nearest request, and temp is used while sorting the requests. The program first accepts the number of requests using scanf(). The condition if (n < 1 || n > 100) checks whether the number of requests is between 1 and 100. It then accepts all disk requests and stores them in array a, while copying the same values into array b for sorting. Next, the program accepts the initial head position and disk size. The conditions if (size <= 0 || start < 0 || start >= size) and if (a[i] < 0 || a[i] >= size) check whether the entered values are valid. If any value is invalid, the program terminates using return 1. The program then begins implementing the SSTF Algorithm by setting head = start and total = 0. A for loop runs once for every disk request. Inside the loop, best = -1 indicates that no request has been selected yet. Another loop examines all requests and checks whether they have already been completed using !done[j]. The expression abs(a[j] - head) < abs(a[best] - head) compares the distance of the current request with the nearest request found so far. The request with the shortest distance is selected, and move(a[best]) moves the disk head to that position. The statement done[best] = 1 marks the selected request as completed. This procedure repeats until every request is processed, after which the total head movement is displayed. Next, the program sorts the requests stored in array b in ascending order using nested for loops. If b[i] > b[j], their values are exchanged using the temporary variable temp. After sorting, the statement k = 0 initializes an index, and the while (k < n && b[k] < start) loop finds the first request whose position is greater than or equal to the initial head position. The program then implements the SCAN Algorithm by resetting head = start and total = 0. The loop for (i = k; i < n; i++) processes all requests greater than or equal to the initial head position in increasing order. The statement move(size - 1) then moves the disk head to the last disk position. After reaching the end, the loop for (i = k - 1; i >= 0; i--) processes the remaining requests in decreasing order, representing the disk head moving back in the opposite direction. The program then displays the total head movement for SCAN. Finally, the program implements the C-LOOK Algorithm by again resetting head = start and total = 0. The first loop for (i = k; i < n; i++) processes all requests greater than or equal to the initial head position in increasing order. After completing these requests, the second loop for (i = 0; i < k; i++) moves the head directly to the lowest pending request and continues processing the remaining requests in increasing order. Unlike SCAN, C-LOOK does not move to the last physical disk position unless a request exists there. The program calculates the movement during the jump and includes it in the total. After completing all requests, it displays the total head movement for C-LOOK. Finally, return 0 indicates successful program execution. For the given sample input, the program calculates 236 tracks for SSTF, 331 tracks for SCAN, and 322 tracks for C-LOOK. Therefore, the program demonstrates how different disk scheduling algorithms determine the order of disk requests and calculate the total movement of the disk head. In this particular example, SSTF produces the least head movement, although the best-performing algorithm can change depending on the request sequence and initial head position.
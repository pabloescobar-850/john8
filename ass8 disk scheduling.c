//8. Disk Scheduling (CO5)
//Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, C-Look considering the
//initial head position moving away from the spindle.



#include <stdio.h>
#include <stdlib.h>

// Function to sort disk requests in ascending order
void sort(int a[], int n) {

    int i, j, temp;

    // Bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {

            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {

    int n, head, cylinders;
    int req[100], a[100];       // Disk requests and sorted requests
    int i, j, pos;
    int current, total;         // Current head position and total movement
    int left[100], right[100];  // Requests on left and right of head
    int l = 0, r = 0;           // Count of left and right requests

    // Input number of disk requests
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    // Check valid number of requests
    if (n < 1 || n > 100) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    // Input disk requests
    printf("Enter disk requests:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Input total number of cylinders
    printf("Enter total number of cylinders: ");
    scanf("%d", &cylinders);

    // Check valid disk size and head position
    if (cylinders < 1 || head < 0 || head >= cylinders) {
        printf("Invalid disk size or head position.\n");
        return 1;
    }

    // Check each disk request
    for (i = 0; i < n; i++) {

        if (req[i] < 0 || req[i] >= cylinders) {
            printf("Invalid request: %d\n", req[i]);
            return 1;
        }

        // Copy requests into another array
        a[i] = req[i];
    }

    // Sort disk requests
    sort(a, n);

    // Divide requests into left and right of head
    // Initial direction is toward cylinder 0
    for (i = 0; i < n; i++) {

        if (a[i] <= head)
            left[l++] = a[i];
        else
            right[r++] = a[i];
    }

    // ---------------- SSTF ----------------

    // SSTF = Shortest Seek Time First
    // Select the request closest to current head

    printf("\nSSTF:\n");

    int visited[100] = {0};  // Tracks completed requests

    current = head;
    total = 0;

    printf("Service order: ");

    // Service all disk requests
    for (i = 0; i < n; i++) {

        int best = -1;
        int distance = 1000000000;

        // Find nearest unvisited request
        for (j = 0; j < n; j++) {

            if (!visited[j]) {

                // Calculate distance from current head
                int d = abs(req[j] - current);

                // Select request with minimum distance
                if (d < distance) {
                    distance = d;
                    best = j;
                }
            }
        }

        // Mark selected request as completed
        visited[best] = 1;

        // Add head movement
        total += abs(req[best] - current);

        // Move head to selected request
        current = req[best];

        printf("%d ", current);
    }

    // Display total movement for SSTF
    printf("\nTotal head movement = %d\n", total);

    // ---------------- SCAN ----------------

    // SCAN = Elevator Algorithm
    // Head moves toward cylinder 0 first
    // Then reverses direction

    printf("\nSCAN (moving toward cylinder 0 first):\n");

    current = head;
    total = 0;

    printf("Service order: ");

    // Service left requests in descending order
    for (i = l - 1; i >= 0; i--) {

        // Calculate movement
        total += abs(current - left[i]);

        // Update current head
        current = left[i];

        printf("%d ", current);
    }

    // Move head to cylinder 0
    total += current;
    current = 0;

    // Reverse direction and service right requests
    for (i = 0; i < r; i++) {

        // Calculate movement
        total += abs(right[i] - current);

        // Update current head
        current = right[i];

        printf("%d ", current);
    }

    // Display total movement for SCAN
    printf("\nTotal head movement = %d\n", total);

    // ---------------- C-LOOK ----------------

    // C-LOOK = Circular LOOK Algorithm
    // Head moves left first
    // Then jumps to highest pending request

    printf("\nC-LOOK (moving toward cylinder 0 first):\n");

    current = head;
    total = 0;

    printf("Service order: ");

    // Service left requests in descending order
    for (i = l - 1; i >= 0; i--) {

        // Calculate movement
        total += abs(current - left[i]);

        // Update head position
        current = left[i];

        printf("%d ", current);
    }

    // Check if right-side requests are present
    if (r > 0) {

        // Jump to highest request on right
        total += abs(current - right[r - 1]);

        // Update head position
        current = right[r - 1];

        printf("%d ", current);

        // Service remaining right requests in descending order
        for (i = r - 2; i >= 0; i--) {

            // Calculate movement
            total += abs(current - right[i]);

            // Update current head
            current = right[i];

            printf("%d ", current);
        }
    }

    // Display total movement for C-LOOK
    printf("\nTotal head movement = %d\n", total);

    return 0;
}


// gcc disk.c -o disk
// ./disk

//inputs
8
//   
98 183 37 122 14 124 65 67
//
53
//
200
//

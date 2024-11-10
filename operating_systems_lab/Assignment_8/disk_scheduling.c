#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 500  // Maximum number of cylinders in the disk

// Function to calculate the absolute difference
int absolute(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// Comparison function for sorting
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to implement SSTF (Shortest Seek Time First)
void sstf(int requests[], int n, int head) {
    int visited[n];
    int seek_count = 0, i, j;
    int distance, min_distance, next_head;

    for (i = 0; i < n; i++) {
        visited[i] = 0;  // Mark all requests as not visited
    }

    for (i = 0; i < n; i++) {
        min_distance = MAX_CYLINDERS;
        next_head = -1;

        // Find the closest request
        for (j = 0; j < n; j++) {
            if (!visited[j]) {
                distance = absolute(head, requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    next_head = j;
                }
            }
        }

        visited[next_head] = 1;  // Mark the next request as visited
        seek_count += min_distance;  // Add the seek time to the total
        head = requests[next_head];  // Move head to the next request
    }

    printf("Total Seek Time for SSTF: %d\n", seek_count);
}

// Function to implement SCAN
void scan(int requests[], int n, int head, int direction) {
    int seek_count = 0;
    int i, j;
    int left[MAX_CYLINDERS], right[MAX_CYLINDERS];
    int left_index = 0, right_index = 0;

    // Divide requests into left and right of the head
    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_index++] = requests[i];
        else
            right[right_index++] = requests[i];
    }

    // Sort both arrays
    qsort(left, left_index, sizeof(int), compare);
    qsort(right, right_index, sizeof(int), compare);

    // Move the head in the specified direction
    if (direction == 0) {  // Moving to the left first
        // Move to the leftmost
        for (i = left_index - 1; i >= 0; i--) {
            seek_count += absolute(head, left[i]);
            head = left[i];
        }
        // Reverse direction and move to the right
        for (i = 0; i < right_index; i++) {
            seek_count += absolute(head, right[i]);
            head = right[i];
        }
    } else {  // Moving to the right first
        // Move to the rightmost
        for (i = 0; i < right_index; i++) {
            seek_count += absolute(head, right[i]);
            head = right[i];
        }
        // Reverse direction and move to the left
        for (i = left_index - 1; i >= 0; i--) {
            seek_count += absolute(head, left[i]);
            head = left[i];
        }
    }

    printf("Total Seek Time for SCAN: %d\n", seek_count);
}

// Function to implement C-Look
void clook(int requests[], int n, int head) {
    int seek_count = 0;
    int i, j;
    int left[MAX_CYLINDERS], right[MAX_CYLINDERS];
    int left_index = 0, right_index = 0;

    // Divide requests into left and right of the head
    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_index++] = requests[i];
        else
            right[right_index++] = requests[i];
    }

    // Sort both arrays
    qsort(left, left_index, sizeof(int), compare);
    qsort(right, right_index, sizeof(int), compare);

    // Move the head in one direction (right)
    for (i = 0; i < right_index; i++) {
        seek_count += absolute(head, right[i]);
        head = right[i];
    }

    // Once done with right side, jump to the leftmost and service the requests
    head = left[left_index - 1];
    for (i = left_index - 1; i >= 0; i--) {
        seek_count += absolute(head, left[i]);
        head = left[i];
    }

    printf("Total Seek Time for C-Look: %d\n", seek_count);
}

// Main function to execute the disk scheduling algorithms
int main() {
    int n, head, i, choice;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk requests (space-separated): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &choice);

    printf("\nChoose Disk Scheduling Algorithm:\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. C-Look\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sstf(requests, n, head);
            break;
        case 2:
            scan(requests, n, head, choice);
            break;
        case 3:
            clook(requests, n, head);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }

    return 0;
}


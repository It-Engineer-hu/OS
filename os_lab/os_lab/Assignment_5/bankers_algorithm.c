#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Declare arrays for the Banker's Algorithm
    int alloc[n][m];      // Allocation matrix
    int max[n][m];        // Maximum demand matrix
    int avail[m];         // Available resources
    int need[n][m];       // Need matrix
    bool finish[n];       // Finish array to track completion of processes
    int safeSeq[n];       // To store the safe sequence

    // Input allocation matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the Available Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the Need matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish array to false
    for (i = 0; i < n; i++) {
        finish[i] = false;
    }

    int count = 0;  // Count of processes in safe sequence

    // Safety Algorithm
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (finish[i] == false) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Add allocated resources of process i to available resources
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    // Add this process to safe sequence and mark it finished
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process was found in this iteration, then the system is in an unsafe state
        if (found == false) {
            printf("The system is in an unsafe state.\n");
            return -1;
        }
    }

    // If the system is in a safe state, print the safe sequence
    printf("The system is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}

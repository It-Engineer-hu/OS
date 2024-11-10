#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

// Function to calculate the Need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Function to find if the system is in a safe state
bool isSafeState(int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {0};  // To keep track of processes that are finished
    int safeSeq[P];  // To store safe sequence
    int work[R];  // To store available resources during execution

    // Initialize work array as available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        
        // Try to find a process whose needs can be satisfied by available resources
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                
                // If all needs can be satisfied
                if (j == R) {
                    // Add allocated resources to work
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }

                    // Add the process to safe sequence and mark it as finished
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                    break;
                }
            }
        }

        // If no process can be found, then system is not in a safe state
        if (!found) {
            printf("System is in an unsafe state\n");
            return false;
        }
    }

    // If we found a safe sequence
    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

// Function to request resources from the system
bool requestResources(int processID, int request[], int avail[], int max[][R], int allot[][R]) {
    // Check if request is less than or equal to need
    for (int i = 0; i < R; i++) {
        if (request[i] > max[processID][i] || request[i] > avail[i]) {
            printf("Error: Process has exceeded maximum claim or resources are not available.\n");
            return false;
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < R; i++) {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
    }

    // Check if the system is still in a safe state
    if (isSafeState(avail, max, allot)) {
        printf("Request granted.\n");
        return true;
    } else {
        // Rollback if not safe
        for (int i = 0; i < R; i++) {
            avail[i] += request[i];
            allot[processID][i] -= request[i];
        }
        printf("Request cannot be granted. System is in an unsafe state.\n");
        return false;
    }
}

// Function to release resources
void releaseResources(int processID, int release[], int avail[], int allot[][R]) {
    // Release the resources and update allocation and available matrices
    for (int i = 0; i < R; i++) {
        avail[i] += release[i];
        allot[processID][i] -= release[i];
    }

    printf("Resources released by process P%d.\n", processID);
}

int main() {
    int avail[] = {3, 3, 2};  // Available resources
    int max[][R] = {
        {7, 5, 3},  // Max resources for P0
        {3, 2, 2},  // Max resources for P1
        {9, 0, 2},  // Max resources for P2
        {2, 2, 2},  // Max resources for P3
        {4, 3, 3}   // Max resources for P4
    };
    int allot[][R] = {
        {0, 1, 0},  // Allocated resources for P0
        {2, 0, 0},  // Allocated resources for P1
        {3, 0, 2},  // Allocated resources for P2
        {2, 1, 1},  // Allocated resources for P3
        {0, 0, 2}   // Allocated resources for P4
    };

    // Check system safety
    isSafeState(avail, max, allot);

    // Request resources for process P1
    int request1[] = {1, 0, 2};  // Request for process P1
    requestResources(1, request1, avail, max, allot);

    // Release resources for process P2
    int release2[] = {2, 1, 1};  // Release for process P2
    releaseResources(2, release2, avail, allot);

    // Check system safety again
    isSafeState(avail, max, allot);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Bubble sort for parent process
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    // Accepting input from the user
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();  // Creating a child process

    if (pid < 0) {
        // If fork fails
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child Process: Exec a new program to display the array in reverse order
        char *args[n + 1];  // Array to hold command-line arguments for EXECVP
        for (int i = 0; i < n; i++) {
            args[i] = malloc(10 * sizeof(char));  // Allocate space for each integer
            sprintf(args[i], "%d", arr[i]);
        }
        args[n] = NULL;  // Null-terminate the arguments

        // Exec a new program (which will print the array in reverse)
        execvp("./display_reverse", args);  // Execute the display_reverse program
    } else {
        // Parent Process: Sort using bubble sort and pass to child
        bubble_sort(arr, n);
        printf("Parent Process: Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Wait for the child process to finish
        wait(NULL);
        printf("Parent Process: Child has finished.\n");
    }

    return 0;
}


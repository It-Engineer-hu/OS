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

    // Parent Process: Sort the array using bubble sort first
    bubble_sort(arr, n);
    printf("Parent Process: Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pid_t pid = fork();  // Creating a child process

    if (pid < 0) {
        // If fork fails
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child Process: Use EXECVE to load a new program to display the array in reverse order
        char *args[n + 2];  // Array to hold command-line arguments for execve
        args[0] = "./display_reverse";  // Name of the program to execute (path to display_reverse)
        
        // Convert the sorted array to strings and pass them as arguments
        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(10 * sizeof(char));  // Allocate space for each integer
            sprintf(args[i + 1], "%d", arr[i]);
        }
        
        args[n + 1] = NULL;  // Null-terminate the arguments

        // Execve a new program to display the array in reverse
        execve(args[0], args, NULL);  // Executes the display_reverse program

        // If execve fails
        perror("execve failed");
        exit(1);
    } else {
        // Parent Process: Wait for the child process to finish
        wait(NULL);
        printf("Parent Process: Child has finished.\n");
    }

    return 0;
}


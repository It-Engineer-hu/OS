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

// Selection sort for child process
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
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
        // Child Process
        printf("Child Process: Sorting using selection sort...\n");
        selection_sort(arr, n);
        printf("Child Process: Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Exit child process
        exit(0);  // Child exits after completing its task
    } else {
        // Parent Process
        printf("Parent Process: Sorting using bubble sort...\n");
        bubble_sort(arr, n);
        printf("Parent Process: Sorted array: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // We deliberately omit wait() here to show Zombie process behavior
        //wait(NULL); // If this is commented out, the child will remain in Zombie state

        // Simulate **Orphan** process behavior by terminating parent early
        // In this case, the parent process will exit before the child finishes.
        sleep(2);  // Parent sleeps for 2 seconds before terminating
        printf("Parent Process: Parent is now exiting, child will become orphaned.\n");

        // Parent process exits, making child an orphan (init process will adopt the child)
        exit(0);
    }

    return 0;
}


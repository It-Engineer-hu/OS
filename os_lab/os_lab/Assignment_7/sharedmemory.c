#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    int x, y, ret, ret_v;
    long int add;
    int shmid;
    int *shmptr;
    key_t key;
    pid_t pid;

    // Take input from the user
    printf("\nEnter a number: ");
    scanf("%d", &x);

    // Generate a key for shared memory
    key = ftok(".", 'M');
    if (key == -1) {
        printf("\nError in ftok()\n");
        return -1;
    }

    // Create shared memory
    shmid = shmget(key, sizeof(x), IPC_CREAT | 0666);
    if (shmid < 0) {
        printf("\nShared memory creation error!\n");
        return -1;
    }

    printf("\nShared Memory is Created.");
    printf("\nShmid is: %d", shmid);

    // Attach to the shared memory
    shmptr = (int *)shmat(shmid, 0, 0);
    if (shmptr == (void *)-1) {
        printf("\nShared Memory not attached!\n");
        return -1;
    }

    printf("\nShared Memory is attached at address: %p", shmptr);

    // Write the value to shared memory
    *shmptr = x;

    // Detach from the shared memory
    ret = shmdt((void *)shmptr);
    if (ret == 0)
        printf("\nShared Memory detached successfully.\n");

    // Create a child process
    pid = fork();
    if (pid == 0) {
        // This block runs in the child process
        printf("\n-----------------------------------------------\n");
        printf("This is the Child Process\n");
        printf("-----------------------------------------------\n");

        // Attach to the shared memory
        shmptr = (int *)shmat(shmid, 0, 0);
        if (shmptr == (void *)-1) {
            printf("\nShared Memory not attached!\n");
            return -1;
        }

        printf("\nShared Memory is attached at address: %p", shmptr);

        // Read the data from shared memory
        y = *shmptr;
        printf("\nThe data read is: %d", y);

        // Detach from shared memory
        ret = shmdt((void *)shmptr);
        if (ret == 0)
            printf("\nShared Memory detached successfully.\n");

        // Remove the shared memory segment
        ret_v = shmctl(shmid, IPC_RMID, 0);
        if (ret_v == 0)
            printf("\nShared Memory removed successfully!\n");

        printf("-----------------------------------------------\n");
    } else {
        // Parent process waits for the child to finish
        wait(0);
    }

    return 0;
}


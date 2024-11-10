#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    key_t key = 1234;  // Shared memory key
    int shm_id;
    char *shm_ptr;

    // Create shared memory segment
    shm_id = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach to the shared memory
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to shared memory
    strcpy(shm_ptr, "Hello from the server!");

    printf("Server: Message written to shared memory\n");

    // Detach from shared memory
    shmdt(shm_ptr);

    return 0;
}


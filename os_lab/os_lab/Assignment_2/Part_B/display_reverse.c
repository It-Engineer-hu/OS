#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Child Process: Displaying array in reverse order:\n");
    
    // Start from argc - 1 (the last argument) and print in reverse order
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}


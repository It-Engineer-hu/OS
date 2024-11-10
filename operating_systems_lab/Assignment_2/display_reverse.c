#include <stdio.h>

void display_reverse(int argc, char *argv[]) {
    printf("Child Process: Displaying array in reverse order:\n");
    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    display_reverse(argc, argv);
    return 0;
}


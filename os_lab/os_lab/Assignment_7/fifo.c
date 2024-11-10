#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_BUF 1024

int main() {
    int fd, c = 0;
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    int fd1;
    int words = 1, lines = 1, chars = 0;
    char buf1[MAX_BUF];
    char str;

    // Create the first FIFO
    mkfifo(fifo1, 0666);

    // Open the FIFO for writing
    fd = open(fifo1, O_RDWR);

    // Prompt user for input
    printf("\nEnter the String (end input with '#'):");
    
    // Read input character by character until '#' is entered
    while ((str = getchar()) != '#') {
        buf1[c++] = str;
    }
    buf1[c] = '\0'; // Null-terminate the string

    // Write the input string to the FIFO
    write(fd, buf1, sizeof(buf1));
    
    // Close the FIFO after writing
    close(fd);
    
    // Unlink the FIFO to remove it
    unlink(fifo1);

    // Open the second FIFO for reading
    fd1 = open(fifo2, O_RDWR);

    // Read the data from the second FIFO
    read(fd1, buf1, sizeof(buf1));
    
    // Print the received string
    printf("\nThe contents of the FIFO are: %s", buf1);

    // Count words, characters, and lines
    int i = 0;
    while (buf1[i] != '\0') {
        if (buf1[i] == ' ' || buf1[i] == '\n') {
            words++; // Increment word count when space or newline is encountered
        } else {
            chars++; // Increment character count for each non-space character
        }
        if (buf1[i] == '\n') {
            lines++; // Increment line count when newline is encountered
        }
        i++;
    }

    // Print the word, character, and line counts
    printf("\nNo of Words: %d", words);
    printf("\nNo of Characters: %d", chars);
    printf("\nNo of Lines: %d\n", lines);

    // Close the FIFO after reading
    close(fd1);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 1024

int main() {
    int fd1, fd2;
    char sentence[MAX_LEN];
    char fileContent[MAX_LEN];
    
    // Create the first FIFO (for sending sentence to process2)
    mkfifo("/tmp/fifo1", 0666);
    // Create the second FIFO (for receiving results from process2)
    mkfifo("/tmp/fifo2", 0666);
    
    while (1) {
        printf("Enter a sentence (or 'exit' to quit): ");
        fgets(sentence, MAX_LEN, stdin);
        
        if (strcmp(sentence, "exit\n") == 0) {
            break;
        }
        
        // Open the first FIFO for writing the sentence to process2
        fd1 = open("/tmp/fifo1", O_WRONLY);
        write(fd1, sentence, strlen(sentence) + 1);  // Write to fifo1
        close(fd1);
        
        // Open the second FIFO for reading the result from process2
        fd2 = open("/tmp/fifo2", O_RDONLY);
        read(fd2, fileContent, sizeof(fileContent));  // Read result from fifo2
        close(fd2);
        
        // Display the content received from process2
        printf("Result from Process 2:\n%s\n", fileContent);
    }
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 1024

int count_words(char *sentence) {
    int count = 0;
    char *token = strtok(sentence, " \t\n");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " \t\n");
    }
    return count;
}

int count_lines(char *sentence) {
    int count = 0;
    char *ptr = sentence;
    while (*ptr) {
        if (*ptr == '\n') {
            count++;
        }
        ptr++;
    }
    return count + 1;  // Including the last line
}

int main() {
    int fd1, fd2;
    char sentence[MAX_LEN];
    char result[MAX_LEN];
    FILE *file;
    
    // Open the first FIFO for reading sentences from process1
    fd1 = open("/tmp/fifo1", O_RDONLY);
    // Open the second FIFO for writing the results to process1
    fd2 = open("/tmp/fifo2", O_WRONLY);
    
    while (1) {
        // Read the sentence from fifo1
        read(fd1, sentence, sizeof(sentence));
        
        if (strlen(sentence) == 0) {
            break;
        }o
        
        // Process the sentence (count words, lines, and characters)
        int num_chars = strlen(sentence);
        int num_words = count_words(sentence);
        int num_lines = count_lines(sentence);
        
        // Format the result
        snprintf(result, sizeof(result), 
                 "Number of Characters: %d\nNumber of Words: %d\nNumber of Lines: %d\n",
                 num_chars, num_words, num_lines);
        
        // Write the result to a file
        file = fopen("result.txt", "w");
        if (file == NULL) {
            perror("Error opening file");
            exit(1);
        }
        fprintf(file, "%s", result);
        fclose(file);
        
        // Read the content of the file
        file = fopen("result.txt", "r");
        if (file == NULL) {
            perror("Error reading file");
            exit(1);
        }
        fread(result, sizeof(char), MAX_LEN, file);
        fclose(file);
        
        // Send the file content back to process1 through fifo2
        write(fd2, result, strlen(result) + 1);  // Send to fifo2
    }
    
    return 0;
}


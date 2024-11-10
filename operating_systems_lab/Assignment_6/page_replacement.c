#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// FCFS Page Replacement Algorithm
int FCFS(int pages[], int pageCount, int frames) {
    int pageFaults = 0;
    int memory[frames];
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;  // Initialize the frames to -1 (empty)
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!found) {
            memory[pageFaults % frames] = page;  // Replace the first frame (FCFS)
            pageFaults++;
        }
    }

    return pageFaults;
}

// LRU Page Replacement Algorithm
int LRU(int pages[], int pageCount, int frames) {
    int pageFaults = 0;
    int memory[frames];
    int lastUsed[frames];
    
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;  // Initialize the frames to -1 (empty)
        lastUsed[i] = -1;  // Initialize last used times to -1
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;
        int leastRecent = -1;
        int leastRecentIndex = -1;

        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!found) {
            // Find the least recently used page
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    leastRecentIndex = j;
                    break;
                }
            }

            if (leastRecentIndex == -1) {  // All frames are full, replace the LRU page
                int minTime = i;
                for (int j = 0; j < frames; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        leastRecentIndex = j;
                    }
                }
            }

            memory[leastRecentIndex] = page;
            lastUsed[leastRecentIndex] = i;
            pageFaults++;
        } else {
            lastUsed[found] = i;  // Update the last used time for the page
        }
    }

    return pageFaults;
}

// Optimal Page Replacement Algorithm
int Optimal(int pages[], int pageCount, int frames) {
    int pageFaults = 0;
    int memory[frames];
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;  // Initialize the frames to -1 (empty)
    }

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!found) {
            // Find the page to replace (the one which will be used farthest in the future)
            int farthest = -1;
            int replaceIndex = -1;
            for (int j = 0; j < frames; j++) {
                int nextUse = -1;
                for (int k = i + 1; k < pageCount; k++) {
                    if (memory[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if (nextUse == -1) {  // If the page is not used again, replace it
                    replaceIndex = j;
                    break;
                }

                if (nextUse > farthest) {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }

            memory[replaceIndex] = page;
            pageFaults++;
        }
    }

    return pageFaults;
}

// Helper function to print the page reference string
void printPageReferences(int pages[], int pageCount) {
    printf("Page Reference String: ");
    for (int i = 0; i < pageCount; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};  // Example page reference string
    int pageCount = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;  // Minimum 3 frames

    printPageReferences(pages, pageCount);

    // FCFS Algorithm
    int fcfsFaults = FCFS(pages, pageCount, frames);
    printf("FCFS Page Faults: %d\n", fcfsFaults);

    // LRU Algorithm
    int lruFaults = LRU(pages, pageCount, frames);
    printf("LRU Page Faults: %d\n", lruFaults);

    // Optimal Algorithm
    int optimalFaults = Optimal(pages, pageCount, frames);
    printf("Optimal Page Faults: %d\n", optimalFaults);

    return 0;
}


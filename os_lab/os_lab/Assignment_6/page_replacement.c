#include <stdio.h>
#include <stdlib.h>

void pageReplacementFCFS(char referenceString[], int stringLength, int numFrames);
void pageReplacementLRU(char referenceString[], int stringLength, int numFrames);
void pageReplacementOptimal(char referenceString[], int stringLength, int numFrames);

int main() {
    int choice, continueFlag = 1, numFrames, stringLength;
    char referenceString[25];

    // Input number of frames (minimum 3)
    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &numFrames);
    if (numFrames < 3) {
        printf("Number of frames should be at least 3.\n");
        return 0;
    }

    // Input the reference string
    printf("Enter the length of the reference string: ");
    scanf("%d", &stringLength);

    printf("Enter the reference string: ");
    scanf("%s", referenceString);

    do {
        // Display menu for algorithm selection
        printf("\n*********** MENU ***********\n");
        printf("1. First-Come-First-Serve (FCFS)\n");
        printf("2. Least Recently Used (LRU)\n");
        printf("3. Optimal Page Replacement\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // No terminal clearing here
        switch (choice) {
            case 1:
                pageReplacementFCFS(referenceString, stringLength, numFrames);
                break;
            case 2:
                pageReplacementLRU(referenceString, stringLength, numFrames);
                break;
            case 3:
                pageReplacementOptimal(referenceString, stringLength, numFrames);
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Ask if user wants to continue
        printf("\nDo you want to continue? (1 for YES / 0 for NO): ");
        scanf("%d", &continueFlag);

    } while (continueFlag == 1);

    return 0;
}

// FCFS Page Replacement Algorithm
void pageReplacementFCFS(char referenceString[], int stringLength, int numFrames) {
    int frames[10], i, j = 0, k, isPageFound, pageFaultCount = 0;

    // Initialize frames with -1 (empty)
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    printf("\nPAGE\t\tFRAMES\t\tFAULTS");

    // Iterate over the reference string
    for (i = 0; i < stringLength; i++) {
        isPageFound = 0;

        // Check if the page is already in the frames
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == referenceString[i]) {
                isPageFound = 1;
                break;
            }
        }

        // If the page is not found in frames, replace a page
        if (isPageFound == 0) {
            frames[j] = referenceString[i];  // Insert the new page in the current frame
            j = (j + 1) % numFrames;  // Move to the next frame (circular)
            pageFaultCount++;  // Increment page fault count
        }

        // Print the current page and frames status
        printf("\n%c\t\t", referenceString[i]);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] != -1) {
                printf("%c ", frames[k]);
            } else {
                printf("- ");  // Empty frame
            }
        }
        printf("\t\t%s", isPageFound == 0 ? "Page-fault" : "No page-fault");
    }

    // Display the total page fault count
    printf("\nTotal Page Faults: %d\n", pageFaultCount);
}

// LRU Page Replacement Algorithm
void pageReplacementLRU(char referenceString[], int stringLength, int numFrames) {
    int frames[10], lastUsed[10], i, j = 0, k, isPageFound, pageFaultCount = 0;

    // Initialize frames and lastUsed arrays
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\nPAGE\t\tFRAMES\t\tFAULTS");

    // Iterate over the reference string
    for (i = 0; i < stringLength; i++) {
        isPageFound = 0;

        // Check if the page is already in the frames
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == referenceString[i]) {
                isPageFound = 1;
                lastUsed[k] = i;  // Update the last used time
                break;
            }
        }

        // If the page is not found, replace a page using LRU
        if (isPageFound == 0) {
            if (j < numFrames) {
                frames[j] = referenceString[i];  // Insert the new page in the next empty slot
                lastUsed[j] = i;  // Set the last used time to the current index
                j++;
            } else {
                // Find the least recently used page (the one with the smallest last used time)
                int lruIndex = 0;
                for (k = 1; k < numFrames; k++) {
                    if (lastUsed[k] < lastUsed[lruIndex]) {
                        lruIndex = k;
                    }
                }
                frames[lruIndex] = referenceString[i];  // Replace the LRU page
                lastUsed[lruIndex] = i;  // Update the last used time for the replaced page
            }
            pageFaultCount++;
        }

        // Print the current page and frames status
        printf("\n%c\t\t", referenceString[i]);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] != -1) {
                printf("%c ", frames[k]);
            } else {
                printf("- ");  // Empty frame
            }
        }
        printf("\t\t%s", isPageFound == 0 ? "Page-fault" : "No page-fault");
    }

    // Display the total page fault count
    printf("\nTotal Page Faults: %d\n", pageFaultCount);
}

// Optimal Page Replacement Algorithm
void pageReplacementOptimal(char referenceString[], int stringLength, int numFrames) {
    int frames[10], futureUsage[10], i, j = 0, k, isPageFound, pageFaultCount = 0;

    // Initialize frames with -1 (empty)
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    printf("\nPAGE\t\tFRAMES\t\tFAULTS");

    // Iterate over the reference string
    for (i = 0; i < stringLength; i++) {
        isPageFound = 0;

        // Check if the page is already in the frames
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == referenceString[i]) {
                isPageFound = 1;
                break;
            }
        }

        // If the page is not found, replace a page using Optimal strategy
        if (isPageFound == 0) {
            if (j < numFrames) {
                frames[j] = referenceString[i];  // Insert the new page in the next empty slot
                j++;
            } else {
                // Calculate the farthest future use for each page in the frames
                for (k = 0; k < numFrames; k++) {
                    futureUsage[k] = -1;
                    for (int m = i + 1; m < stringLength; m++) {
                        if (frames[k] == referenceString[m]) {
                            futureUsage[k] = m;  // Set the next usage time for the page
                            break;
                        }
                    }
                }

                // Find the page with the farthest future usage
                int maxIndex = 0;
                for (k = 1; k < numFrames; k++) {
                    if (futureUsage[k] == -1 || futureUsage[k] > futureUsage[maxIndex]) {
                        maxIndex = k;  // Find the page with the maximum future usage time
                    }
                }

                frames[maxIndex] = referenceString[i];  // Replace the farthest used page
            }
            pageFaultCount++;
        }

        // Print the current page and frames status
        printf("\n%c\t\t", referenceString[i]);
        for (k = 0; k < numFrames; k++) {
            if (frames[k] != -1) {
                printf("%c ", frames[k]);
            } else {
                printf("- ");  // Empty frame
            }
        }
        printf("\t\t%s", isPageFound == 0 ? "Page-fault" : "No page-fault");
    }

    // Display the total page fault count
    printf("\nTotal Page Faults: %d\n", pageFaultCount);
}


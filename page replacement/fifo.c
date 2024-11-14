#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int frames) {
    int pageFaults = 0;
    int frame[frames]; // array to hold pages in memory frames
    int index = 0; // index to keep track of the oldest page in frames

    // Initialize all frames as empty (-1 indicates an empty frame)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("Page reference string: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\nPage Replacement Process:\n");

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in one of the frames
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1; // page is already in a frame
                break;
            }
        }

        // If page is not found, a page fault occurs
        if (!found) {
            frame[index] = page; // replace the oldest page in FIFO order
            index = (index + 1) % frames; // update index to next oldest page
            pageFaults++; // increment page fault count

            // Print the current state of frames
            printf("Page %d caused a page fault: ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1)
                    printf(" - "); // empty frame
                else
                    printf("%d ", frame[j]);
            }
            printf("\n");
        } else {
            printf("Page %d did not cause a page fault.\n", page);
        }
    }

    printf("\nTotal page faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,1,2,0}; // Page reference string
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3; // Number of frames available

    fifoPageReplacement(pages, n, frames);

    return 0;
}
